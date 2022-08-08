// License(MIT)
// Athuor: Margoo
// The widget (VMainWindow)
#pragma once

#include "../object/vuiobject.h"

VLIB_BEGIN_NAMESPACE

namespace Core {
class VPushButton : public VUIObject {
 private:
     VPushButtonTheme* Theme{};
 private:
     VRect GetRegion() override {
         VRect Rect = VUIObject::GetRegion();

         Rect.Extended(Theme->LocalTheme.BorderThickness, Theme->LocalTheme.BorderThickness,
                       Theme->LocalTheme.BorderThickness, Theme->LocalTheme.BorderThickness);
         return Rect;
     }

 public:
     explicit VPushButton(VUIObject* Parent) : VUIObject(Parent) {

     }
};
}


VLIB_END_NAMESPACE