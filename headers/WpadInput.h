#pragma once

#include <padscore/kpad.h>
#include <padscore/wpad.h>
#include "input.h"

class WpadInput : public Input
{
    private:
        KPADChan Channel;
        KPADStatus Status;
        KPADError Error;
        Vector2D TouchRes;

    public: 

        //Constructor
        WpadInput(int x, int y, KPADChan Channel)
        {
            this->Channel = Channel;
            TouchRes.x = x; TouchRes.y = y;
        };

        //Destructor
        ~WpadInput() override {};

        //Updates the VPADStatus & more
        bool Update()
        {
            KPADReadEx(Channel, &Status, 1, &Error);
            switch (Error) {
                //No errors continue as normal
                case KPAD_ERROR_OK: {
                    Data.Connected = true;
                    break;
                }
                //No controller on the channel / lost connection
                case KPAD_ERROR_INVALID_CONTROLLER: {
                    Data.Connected = false;
                    return false;
                }
                default: {
                    return false;
                }
            }

            return true;
        };
};