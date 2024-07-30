#pragma once

#include <vpad/input.h>
#include "input.h"

class VpadInput : public Input
{
    private:
        VPADStatus Status;
        VPADReadError Error;
        Vector2D TouchRes;

    public: 

        //Constructor
        VpadInput(int x, int y)
        {
            TouchRes.x = x;
            TouchRes.y = y;
        };

        //Destructor
        ~VpadInput(){};

        //Updates the VPADStatus & more
        void Update()
        {
            VPADRead(VPAD_CHAN_0, &Status, 1, &Error);
            switch (Error) {
                //No errors continue as normal
                case VPAD_READ_SUCCESS: {
                    Connected = true;
                    break;
                }
                //No controller on the channel / lost connection
                case VPAD_READ_INVALID_CONTROLLER: {
                    Connected = false;
                    return;
                }
                default: {
                    return;
                }
            }
        };

        // Public Variables 
        bool Connected;
};