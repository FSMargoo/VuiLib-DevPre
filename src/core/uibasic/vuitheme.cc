#include "../../../include/core/uibasic/vuitheme.h"

VLIB_BEGIN_NAMESPACE

namespace Core {

VLabelStatusTheme::VLabelStatusTheme(const VLabelStatusTheme& Theme) {
    BackgroundColor = Theme.BackgroundColor;
    BorderColor = Theme.BorderColor;
    TextColor = Theme.TextColor;
    BorderThickness = Theme.BorderThickness;
    Radius = Theme.Radius;
    AnimationInterpolatorType = Theme.AnimationInterpolatorType;
}
VLabelCommomTheme::VLabelCommomTheme(const VLabelCommomTheme& LabelObject) {
	StaticTheme  = LabelObject.StaticTheme;
	OnHoverTheme = LabelObject.OnHoverTheme;
	ActiveTheme  = LabelObject.ActiveTheme;
}
VLabelCommomTheme::VLabelCommomTheme() {
    LCID    LocaleID = GetThreadLocale();
    wchar_t LocaleName[LOCALE_NAME_MAX_LENGTH];
    if(!LCIDToLocaleName(LocaleID, LocaleName, LOCALE_NAME_MAX_LENGTH, 0)){
        VLIB_REPORT_ERROR(L"Failed to get the system locale");
    }

    LabelFont = new VFont(L"Microsoft YaHei UI", VFont::WEIGHT_NORMAL, VFont::STYLE_NORMAL, VFont::STRETCH_NORMAL, 12.f, LocaleName);
}
VPushButtonTheme::VPushButtonTheme(const VPushButtonTheme& Theme) {
    StaticTheme  = Theme.StaticTheme;
    OnHoverTheme = Theme.OnHoverTheme;
    ActiveTheme  = Theme.ActiveTheme;
    LabelFont    = new VFont(*Theme.LabelFont);
    PlaneText    = Theme.PlaneText;
    LocalTheme   = Theme.StaticTheme;
}
VPushButtonTheme::VPushButtonTheme() : VLabelCommomTheme() {
	StaticTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 0);
	StaticTheme.BorderColor = VColor::FromBYTERGBA(53, 53, 53, 255);
    StaticTheme.BorderThickness = 1.3f;
    StaticTheme.Radius = { 5, 5 };
	StaticTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 255);
	StaticTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

	OnHoverTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 255);
	OnHoverTheme.BorderColor = VColor::FromBYTERGBA(56, 56, 56, 255);
	OnHoverTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 255);
    OnHoverTheme.Radius = { 5, 5 };
    OnHoverTheme.BorderThickness = 1.3f;
	OnHoverTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

    ActiveTheme.BackgroundColor = VColor::FromBYTERGBA(98, 100, 167, 255);
    ActiveTheme.BorderColor = VColor::FromBYTERGBA(98, 100, 167, 255);
    ActiveTheme.TextColor = VColor::FromBYTERGBA(255, 255, 255, 255);
    ActiveTheme.Radius = { 5, 5 };
    ActiveTheme.BorderThickness = 1.3f;
    ActiveTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

	LocalTheme = StaticTheme;

    LabelFont->SetParagraphAlignment(VFontParagraphAlilgnment::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    LabelFont->SetLineAlignment(VFontAlignment::DWRITE_TEXT_ALIGNMENT_CENTER);
}

VTextLabelTheme::VTextLabelTheme() : VLabelCommomTheme() {
    StaticTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 0);
    StaticTheme.BorderColor = VColor::FromBYTERGBA(53, 53, 53, 0);
    StaticTheme.BorderThickness = 1.3f;
    StaticTheme.Radius = { 5, 5 };
    StaticTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 119);
    StaticTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

    OnHoverTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 0);
    OnHoverTheme.BorderColor = VColor::FromBYTERGBA(56, 56, 56, 0);
    OnHoverTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 119);
    OnHoverTheme.Radius = { 5, 5 };
    OnHoverTheme.BorderThickness = 1.3f;
    OnHoverTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

    ActiveTheme.BackgroundColor = VColor::FromBYTERGBA(98, 100, 167, 0);
    ActiveTheme.BorderColor = VColor::FromBYTERGBA(98, 100, 167, 0);
    ActiveTheme.TextColor = VColor::FromBYTERGBA(255, 255, 255, 119);
    ActiveTheme.Radius = { 5, 5 };
    ActiveTheme.BorderThickness = 1.3f;
    ActiveTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

    LocalTheme = StaticTheme;
}
VTextLabelTheme::VTextLabelTheme(const VTextLabelTheme& Theme) {
    StaticTheme  = Theme.StaticTheme;
    OnHoverTheme = Theme.OnHoverTheme;
    ActiveTheme  = Theme.ActiveTheme;
    LabelFont    = new VFont(*Theme.LabelFont);
    PlaneText    = Theme.PlaneText;
    LocalTheme   = Theme.StaticTheme;
}

}