#pragma once

#include <vpad/input.h>
#include "Controller.h"

class VpadInput : public Controller
{
    private:
        VPADStatus Status;
        VPADReadError Error;
        VPADTouchData Touch;
        int Width;
        int Height;

    public: 

        //Constructor
        VpadInput(int Width, int Height)
        {
            memset(&Status, 0, sizeof(Status));
            this->Width = Width; this->Height = Height;
        };

        //Destructor
        ~VpadInput() override = default;

        

        //Updates the VPADStatus & more
        bool Update()
        {
            PrevData = Data;
            VPADRead(VPAD_CHAN_0, &Status, 1, &Error);
            switch (Error) {
                //No errors continue as normal
                case VPAD_READ_SUCCESS: {
                    Data.Connected = true;
                    break;
                }
                //No controller on the channel / lost connection
                case VPAD_READ_INVALID_CONTROLLER: {
                    Data.BtnHeld = 0;
                    Data.Connected = false;
                    return false;
                }
                default: {
                    Data.BtnHeld = 0;
                    return false;
                }
            }
            
            Data.BtnReleased     = Status.release;
            Data.BtnHeld         = Status.hold;
            Data.BtnDown         = Status.trigger;
            Data.ValidPointerPos = !Status.tpNormal.validity;
            Data.DRC.Touched     = Status.tpNormal.touched;
            Data.DRC.BatteryLvl  = Status.battery;
            Data.DRC.Headphones  = Status.usingHeadphones;
            Data.DRC.Volume      = Status.slideVolume;
            Data.DRC.MicStatus   = Status.micStatus;

            Data.Accelerometer.x = Status.accelorometer.acc.x;
            Data.Accelerometer.y = Status.accelorometer.acc.y;
            Data.Accelerometer.z = Status.accelorometer.acc.z;

            Data.AccMagnitude    = Status.accelorometer.magnitude;
            Data.AccVariation    = Status.accelorometer.variation;

            Data.DRC.AccVertical.x = Status.accelorometer.vertical.x;
            Data.DRC.AccVertical.y = Status.accelorometer.vertical.y;

            Data.Angle.x         = Status.angle.x;
            Data.Angle.y         = Status.angle.y;
            Data.Angle.z         = Status.angle.z;

            Data.DRC.Gyroscope.x = Status.gyro.x;
            Data.DRC.Gyroscope.y = Status.gyro.y;
            Data.DRC.Gyroscope.z = Status.gyro.z;

            Data.DRC.Magnetometer.x = Status.mag.x;
            Data.DRC.Magnetometer.y = Status.mag.y;
            Data.DRC.Magnetometer.z = Status.mag.z;

            VPADGetTPCalibratedPoint(VPAD_CHAN_0, &Touch, &Status.tpFiltered1);

            //! calculate the screen offsets
            Data.PointerPos.x = -(Width >> 1) + (int32_t) (((float) Touch.x / 1280.0f) * (float) Width);
            Data.PointerPos.y = -(Height >> 1) + (int32_t) (float) Height - (((float) Touch.y / 720.0f) * (float) Height);

            return true;
        };
};