#pragma warning(disable : 26495)

#include "../../../include/core/render/vwrite.h"

VLIB_BEGIN_NAMESPACE

namespace Core {
VFont::VFont(const std::wstring& FamilyName, FontWeight TextWidget, FontStyle TextStyle, FontStretch TextStretch,
		float TextSize, const std::wstring& Local) {
	VDirectXWriteFactory.GetInstance()->CreateTextFormat(FamilyName.c_str(), nullptr,
		(DWRITE_FONT_WEIGHT)TextWidget, (DWRITE_FONT_STYLE)TextStyle, (DWRITE_FONT_STRETCH)TextStretch, TextSize, Local.c_str(), &TextFormat);
}
VFont::~VFont() {
	VDXObjectSafeFree(&TextFormat);
}
}

VLIB_END_NAMESPACE