// License(MIT)
// Athuor: Margoo
// This is the native theme in vuilib
#pragma once

#include "../vbasiccore.h"
#include "vuiinterpolator.h"
#include "../render/vpainter.h"

VLIB_BEGIN_NAMESPACE

namespace Core {

enum class VUIThemeType {
	VUnknown, VMainWindow, VPushButton
};

struct VBasicUITheme {
 public:
	 VBasicUITheme() = default;

 public:
	 virtual VUIThemeType GetThemeType() {
		 return VUIThemeType::VUnknown;
	 }
};

class VMainWindowTheme : public VBasicUITheme {
 public:
     VColor       BackgroundColor;
     bool         WindowSizble;
     std::wstring WindowPlaneText;

     VMainWindowTheme() {
         BackgroundColor = VColor::FromBYTERGBA(41, 42, 43);
         WindowSizble    = true;
     }

     VUIThemeType GetThemeType() override {
         return VUIThemeType::VMainWindow;
     }
};

struct VLabelStatusTheme {
	VColor  BackgroundColor;
	VColor  BorderColor;
	VColor  TextColor;

	float   BorderThickness;

	VInterpolatorType
		AnimationInterpolatorType;
};

struct VLabelCommomTheme : public VBasicUITheme {
 public:
	 VLabelStatusTheme StaticTheme;
	 VLabelStatusTheme OnHoverTheme;
	 VLabelStatusTheme ActiveTheme;
	 VLabelStatusTheme LocalTheme;

 public:
	 VLabelCommomTheme(const VLabelCommomTheme& LabelObject);
	 VLabelCommomTheme();
};

struct VPushButtonTheme : public VLabelCommomTheme {
 public:
	 VPushButtonTheme();

 public:
	 VUIThemeType GetThemeType() override {
		 return VUIThemeType::VPushButton;
	 }
};

}

VLIB_END_NAMESPACE