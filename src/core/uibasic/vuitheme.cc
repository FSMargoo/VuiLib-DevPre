#include "../../../include/core/uibasic/vuitheme.h"

VLIB_BEGIN_NAMESPACE

namespace Core {

VLabelCommomTheme::VLabelCommomTheme(const VLabelCommomTheme& LabelObject) {
	StaticTheme  = LabelObject.StaticTheme;
	OnHoverTheme = LabelObject.OnHoverTheme;
	ActiveTheme  = LabelObject.ActiveTheme;
}
VLabelCommomTheme::VLabelCommomTheme() = default;
VPushButtonTheme::VPushButtonTheme() : VLabelCommomTheme() {
	StaticTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 0);
	StaticTheme.BorderColor = VColor::FromBYTERGBA(53, 53, 53, 255);
	StaticTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 255);
	StaticTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

	OnHoverTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 255);
	OnHoverTheme.BorderColor = VColor::FromBYTERGBA(56, 56, 56, 255);
	OnHoverTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 255);
	OnHoverTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

	OnHoverTheme.BackgroundColor = VColor::FromBYTERGBA(56, 56, 56, 255);
	OnHoverTheme.BorderColor = VColor::FromBYTERGBA(56, 56, 56, 255);
	OnHoverTheme.TextColor = VColor::FromBYTERGBA(126, 126, 126, 255);
	OnHoverTheme.AnimationInterpolatorType = VInterpolatorType::AccelerateInterpolator;

	LocalTheme = StaticTheme;
}

}