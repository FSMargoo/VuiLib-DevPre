#include "../../../include/core/widget/vwidget.h"

VLIB_BEGIN_NAMESPACE

namespace Core {

void VMainWindow::Win32ThreadResized(int Width, int Height) {
     Win32Cache.UserSetGeomtery = true;
     Win32Cache.UserSetWidth    = Width;
     Win32Cache.UserSetHeight   = Height;
}
void VMainWindow::Win32LoseFocus() {
    CallWidgetUnlockFocusID();

    VKillFocusMessage* KillFocusMessage = new VKillFocusMessage;
    SendMessageToChild(KillFocusMessage, false);

    delete KillFocusMessage;
}

void VMainWindow::InitKernel() {
    FpsTimer.Start(16);
    _VMainConfigs.insert(std::make_pair<HWND, VMainWindowConfig*>(GetHWnd(), &WindowConfig));
}
void VMainWindow::InitWindow() {
    initgraph(GetWidth(), GetHeight());

    if (Theme->WindowSizble) {
        SetWindowLong(GetHWnd(), GWL_STYLE, GetWindowLong(GetHWnd(), GWL_STYLE) | (WS_MAXIMIZEBOX));
        SetWindowLong(GetHWnd(), GWL_STYLE, (GetWindowLong(GetHWnd(), GWL_STYLE) | WS_THICKFRAME));
    }

    _VExWindowProcess = reinterpret_cast<WNDPROC>(GetWindowLongPtr(GetHWnd(), GWLP_WNDPROC));
    SetWindowLongPtr(GetHWnd(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(_VWidgetWNDPROC));

    BeginBatchDraw();

    Direct2DRender = new VDCRender(VDirectXD2DFactory.GetInstance(), GetImageHDC(),
                                   { 0, 0, GetWidth(), GetHeight() }, true);
    BufferPainter  = new VPainter(Direct2DRender->GetDirectXRenderTarget());

    WindowConfig.WindowOnSize = [this](auto PH1, auto PH2)
            { Win32ThreadResized(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); };
    WindowConfig.LosedUserFocus = [this]() -> void
            { Win32LoseFocus(); };
}
void VMainWindow::InitIME() {
    WindowConfig.IMEX = -1;
    WindowConfig.IMEY = -1;
}

VMainWindow::VMainWindow(const int& Width, const int& Height, VApplication* Parent, const bool& Sizble)
        : VUIObject(Parent) {
    Resize(Width, Height);

    Theme = static_cast<VMainWindowTheme*>(GetTargetTheme(VUIThemeType::VMainWindow));
    VLIB_CHECK_REPORT(Theme == nullptr, L"Object [VMainWindow] losed!");

    Theme->WindowSizble = Sizble;

    if (Parent == nullptr) {
        VLIB_REPORT_ERROR(L"VMainWindow should be init after VApplication!");

        exit(-1);
    }

    InitWindow();
    InitKernel();
    InitIME();

    Update( { 0, 0, GetWidth(), GetHeight() } );
}

void VMainWindow::CallWidgetSetIME(const int& X, const int& Y) {
    WindowConfig.IMEX = X;
    WindowConfig.IMEY = Y;
}
void VMainWindow::CallWidgetSetFocusID(const std::wstring& ObjectID) {
    WindowConfig.GlobalFocusID = ObjectID;
}
std::wstring VMainWindow::CallWidgetGetFocusID() {
    return WindowConfig.GlobalFocusID;
}
void VMainWindow::CallWidgetLockFocusID() {
    WindowConfig.LockFocus = true;
}
void VMainWindow::CallWidgetUnlockFocusID() {
    WindowConfig.LockFocus = false;
}
bool VMainWindow::CallWidgetGetLockingStatus() {
    return WindowConfig.LockFocus;
}
void VMainWindow::CallWidgetSendMessage(VMessage *Message) {
    SendMessageToChild(Message);
}
Core::VDCRender* VMainWindow::CallWidgetGetDCRenderTarget() {
    return Direct2DRender;
}

void VMainWindow::OnPaint(VCanvasPainter* Canvas, const VRect& Rect) {
    VSolidBrush BackgroundColor(CallWidgetGetDCRenderTarget()->GetDirectXRenderTarget(), Theme->BackgroundColor);

    Canvas->SolidRectangle(Rect, &BackgroundColor);
}

void VMainWindow::Update(VRect UpdateRect) {
    VGetRepaintAeraMessage RepaintMessage(UpdateRect);

    std::map<int, int>     AlreadySendedObject;

    int                    ObjectCount = 0;

    for (auto ChildObject = ObjectKernel.ChildObjectContainer.begin();
         ChildObject != ObjectKernel.ChildObjectContainer.end(); ++ObjectCount) {
        if (AlreadySendedObject.find(ObjectCount) == AlreadySendedObject.end()) {
            if (ChildObject.operator*()->SysProcessMessage(&RepaintMessage)) {
                AlreadySendedObject.insert(std::pair<int, bool>(ObjectCount, 1));

                ChildObject = ObjectKernel.ChildObjectContainer.begin();

                ObjectCount = -1;

                continue;
            }
        }

        ++ChildObject;
    }

    for (auto& AlreadyExsitsMessage : RepaintMessages) {
        if (AlreadyExsitsMessage->DirtyRectangle == *(RepaintMessage.RepaintAera)) {
            return;
        }

        if (AlreadyExsitsMessage->DirtyRectangle.Overlap(*(RepaintMessage.RepaintAera))) {
            AlreadyExsitsMessage->DirtyRectangle.FusionRect(*(RepaintMessage.RepaintAera));
            return;
        }
    }

    VRect RepaintRect = *(RepaintMessage.RepaintAera);

    RepaintMessages.push_back(new VRepaintMessage(RepaintRect));
}

void VMainWindow::CheckFrame() {
    if (FpsTimer.End()) {
        FpsTimer.Start(14);

        if (Win32Cache.UserSetGeomtery) {
            Win32Cache.UserSetGeomtery = false;

            VUIObject::Resize(Win32Cache.UserSetWidth, Win32Cache.UserSetHeight);
            ExResize(Win32Cache.UserSetWidth, Win32Cache.UserSetHeight);

            Resized.Emit(Win32Cache.UserSetWidth, Win32Cache.UserSetHeight);

            delete Direct2DRender;
            delete BufferPainter;

            Direct2DRender = new VDCRender(VDirectXD2DFactory.GetInstance(), GetImageHDC(),
                                           { 0, 0, GetWidth(), GetHeight() }, true);
            BufferPainter  = new VPainter(Direct2DRender->GetDirectXRenderTarget());

            Update( { 0, 0, GetWidth(), GetHeight() } );
        }

        if (!RepaintMessages.empty()) {
            Canvas = new VCanvasPainter(GetWidth(), GetHeight(),
                                                               CallWidgetGetDCRenderTarget()->GetDirectXRenderTarget());

            Canvas->BeginDraw();
            for (auto& Message : RepaintMessages) {
                OnPaint(Canvas, Message->DirtyRectangle);
                SendMessageToChild(Message, false);

                delete Message;
            }
            Canvas->EndDraw();

            RepaintMessages.clear();

            BufferPainter->BeginDraw();
            BufferPainter->DrawCanvas(GetRegion(), Canvas, GetRegion(), 1.f);
            BufferPainter->EndDraw();

            delete Canvas;
        }

        FlushBatchDraw();
    }
}

void VMainWindow::SetTitle(const std::wstring& WindowText) {
    Theme->WindowPlaneText = WindowText;
    SetWindowTextW(GetHWnd(), Theme->WindowPlaneText.c_str());
}
void VMainWindow::SetBackgroundColor(const VColor& Color) {
    Theme->BackgroundColor = Color;

    Update( { 0, 0, GetWidth(), GetHeight() } );
}
void VMainWindow::SetMaxSize(const VGeomtery& MaxSize) {
    WindowConfig.UseMaxMinSize = true;
    WindowConfig.WindowMaxSize = MaxSize;
}
void VMainWindow::SetMiniSize(const VGeomtery& MiniSize) {
    WindowConfig.UseMaxMinSize = true;
    WindowConfig.WindowMiniSize = MiniSize;
}

}

VLIB_END_NAMESPACE