#pragma once

#include "Controller.h"

class CombinedInput : public Controller {
    public:
        void combine(const Controller &b) {
            Data.BtnHeld |= b.Data.BtnHeld;
        }

        void process() {
            Data.BtnDown |= (Data.BtnHeld & (~PrevData.BtnHeld));
            Data.BtnReleased |= (PrevData.BtnHeld & (~Data.BtnHeld));
            PrevData.BtnHeld = Data.BtnHeld;
        }

        void reset() {
            Data.BtnHeld = 0;
            Data.BtnDown = 0;
            Data.BtnReleased = 0;
        }
};