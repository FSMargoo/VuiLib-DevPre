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
	VUnknown, VMainWindow, VPushButton, VTextLabel, VImageLabel
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

    VPoint  Radius;

	VInterpolatorType
		AnimationInterpolatorType;

    VLabelStatusTheme() = default;
    VLabelStatusTheme(const VLabelStatusTheme& Theme);
};

struct VLabelCommomTheme : public VBasicUITheme {
 public:
	 VLabelStatusTheme StaticTheme;
	 VLabelStatusTheme OnHoverTheme;
	 VLabelStatusTheme ActiveTheme;
	 VLabelStatusTheme LocalTheme;
     VFont*            LabelFont;

 public:
	 VLabelCommomTheme(const VLabelCommomTheme& LabelObject);
	 VLabelCommomTheme();
};

struct VPushButtonTheme : public VLabelCommomTheme {
 public:
     std::wstring PlaneText;

 public:
	 VPushButtonTheme();
     VPushButtonTheme(const VPushButtonTheme& Theme);

 public:
	 VUIThemeType GetThemeType() override {
		 return VUIThemeType::VPushButton;
	 }
};

struct VTextLabelTheme : public VLabelCommomTheme {
 public:
    std::wstring PlaneText;

 public:
     VTextLabelTheme();
     VTextLabelTheme(const VTextLabelTheme& Theme);

 public:
     VUIThemeType GetThemeType() override {
        return VUIThemeType::VTextLabel;
     }
};

struct VImageLabel : public VBasicUITheme {
    VImage* Image;

    VImageLabel() {

    }

    VUIThemeType GetThemeType() override {
        return VUIThemeType::VImageLabel;
    }
};

}

VLIB_END_NAMESPACE