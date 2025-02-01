#pragma once

#include <padscore/kpad.h>
#include <padscore/wpad.h>
#include "Input.h"

class KpadInput : public Input
{
    private:
        KPADChan Channel;
        KPADStatus Status;
        KPADError Error;
        int Width;
        int Height;

        uint32_t RemapWiiMote(uint32_t Inputs) {
            uint32_t ConvertedInputs = 0;

            if (Inputs & WPAD_BUTTON_LEFT)
                ConvertedInputs |= Input::BUTTON_LEFT;

            if (Inputs & WPAD_BUTTON_RIGHT)
                ConvertedInputs |= Input::BUTTON_RIGHT;

            if (Inputs & WPAD_BUTTON_DOWN)
                ConvertedInputs |= Input::BUTTON_DOWN;

            if (Inputs & WPAD_BUTTON_UP)
                ConvertedInputs |= Input::BUTTON_UP;

            if (Inputs & WPAD_BUTTON_2)
                ConvertedInputs |= Input::BUTTON_2;

            if (Inputs & WPAD_BUTTON_1)
                ConvertedInputs |= Input::BUTTON_1;

            if (Inputs & WPAD_BUTTON_B)
                ConvertedInputs |= Input::BUTTON_B;

            if (Inputs & WPAD_BUTTON_A)
                ConvertedInputs |= Input::BUTTON_A;

            if (Inputs & WPAD_BUTTON_PLUS)
                ConvertedInputs |= Input::BUTTON_PLUS;

            if (Inputs & WPAD_BUTTON_MINUS)
                ConvertedInputs |= Input::BUTTON_MINUS;

            if (Inputs & WPAD_BUTTON_Z)
                ConvertedInputs |= Input::BUTTON_Z;

            if (Inputs & WPAD_BUTTON_C)
                ConvertedInputs |= Input::BUTTON_C;

            if (Inputs & WPAD_BUTTON_HOME)
                ConvertedInputs |= Input::BUTTON_HOME;

            if (Inputs & WPAD_NUNCHUK_STICK_EMULATION_LEFT)
                ConvertedInputs |= Input::STICK_L_LEFT;

            if (Inputs & WPAD_NUNCHUK_STICK_EMULATION_RIGHT)
                ConvertedInputs |= Input::STICK_L_RIGHT;

            if (Inputs & WPAD_NUNCHUK_STICK_EMULATION_DOWN)
                ConvertedInputs |= Input::STICK_L_DOWN;

            if (Inputs & WPAD_NUNCHUK_STICK_EMULATION_UP)
                ConvertedInputs |= Input::STICK_L_UP;

            return ConvertedInputs;
        }

        uint32_t RemapClassic(uint32_t Inputs) {
            uint32_t ConvertedInputs = 0;

            if (Inputs & WPAD_CLASSIC_BUTTON_LEFT)
                ConvertedInputs |= Input::BUTTON_LEFT;

            if (Inputs & WPAD_CLASSIC_BUTTON_RIGHT)
                ConvertedInputs |= Input::BUTTON_RIGHT;

            if (Inputs & WPAD_CLASSIC_BUTTON_DOWN)
                ConvertedInputs |= Input::BUTTON_DOWN;

            if (Inputs & WPAD_CLASSIC_BUTTON_UP)
                ConvertedInputs |= Input::BUTTON_UP;

            if (Inputs & WPAD_CLASSIC_STICK_L_EMULATION_LEFT)
                ConvertedInputs |= Input::STICK_L_LEFT;

            if (Inputs & WPAD_CLASSIC_STICK_L_EMULATION_RIGHT)
                ConvertedInputs |= Input::STICK_L_RIGHT;

            if (Inputs & WPAD_CLASSIC_STICK_L_EMULATION_DOWN)
                ConvertedInputs |= Input::STICK_L_DOWN;

            if (Inputs & WPAD_CLASSIC_STICK_L_EMULATION_UP)
                ConvertedInputs |= Input::STICK_L_UP;

            if (Inputs & WPAD_CLASSIC_STICK_R_EMULATION_LEFT)
                ConvertedInputs |= Input::STICK_R_LEFT;

            if (Inputs & WPAD_CLASSIC_STICK_R_EMULATION_RIGHT)
                ConvertedInputs |= Input::STICK_R_RIGHT;

            if (Inputs & WPAD_CLASSIC_STICK_R_EMULATION_DOWN)
                ConvertedInputs |= Input::STICK_R_DOWN;

            if (Inputs & WPAD_CLASSIC_STICK_R_EMULATION_UP)
                ConvertedInputs |= Input::STICK_R_UP;

            if (Inputs & WPAD_CLASSIC_BUTTON_Y)
                ConvertedInputs |= Input::BUTTON_Y;

            if (Inputs & WPAD_CLASSIC_BUTTON_X)
                ConvertedInputs |= Input::BUTTON_X;

            if (Inputs & WPAD_CLASSIC_BUTTON_B)
                ConvertedInputs |= Input::BUTTON_B;

            if (Inputs & WPAD_CLASSIC_BUTTON_A)
                ConvertedInputs |= Input::BUTTON_A;

            if (Inputs & WPAD_CLASSIC_BUTTON_PLUS)
                ConvertedInputs |= Input::BUTTON_PLUS;

            if (Inputs & WPAD_CLASSIC_BUTTON_MINUS)
                ConvertedInputs |= Input::BUTTON_MINUS;

            if (Inputs & WPAD_CLASSIC_BUTTON_L)
                ConvertedInputs |= Input::BUTTON_L;
            
            if (Inputs & WPAD_CLASSIC_BUTTON_ZL)
                ConvertedInputs |= Input::BUTTON_ZL;

            if (Inputs & WPAD_CLASSIC_BUTTON_R)
                ConvertedInputs |= Input::BUTTON_R;

            if (Inputs & WPAD_CLASSIC_BUTTON_ZR)
                ConvertedInputs |= Input::BUTTON_ZR;

            if (Inputs & WPAD_CLASSIC_BUTTON_L)
                ConvertedInputs |= Input::BUTTON_HOME;

            return ConvertedInputs;
        }

        uint32_t RemapPro(uint32_t Inputs) {
            uint32_t ConvertedInputs = 0;

            if (Inputs & WPAD_PRO_BUTTON_LEFT)
                ConvertedInputs |= Input::BUTTON_LEFT;

            if (Inputs & WPAD_PRO_BUTTON_RIGHT)
                ConvertedInputs |= Input::BUTTON_RIGHT;

            if (Inputs & WPAD_PRO_BUTTON_DOWN)
                ConvertedInputs |= Input::BUTTON_DOWN;

            if (Inputs & WPAD_PRO_BUTTON_UP)
                ConvertedInputs |= Input::BUTTON_UP;

            if (Inputs & WPAD_PRO_STICK_L_EMULATION_LEFT)
                ConvertedInputs |= Input::STICK_L_LEFT;

            if (Inputs & WPAD_PRO_STICK_L_EMULATION_RIGHT)
                ConvertedInputs |= Input::STICK_L_RIGHT;

            if (Inputs & WPAD_PRO_STICK_L_EMULATION_DOWN)
                ConvertedInputs |= Input::STICK_L_DOWN;

            if (Inputs & WPAD_PRO_STICK_L_EMULATION_UP)
                ConvertedInputs |= Input::STICK_L_UP;

            if (Inputs & WPAD_PRO_BUTTON_STICK_L)
                ConvertedInputs |= Input::STICK_L_CLICK;

            if (Inputs & WPAD_PRO_STICK_R_EMULATION_LEFT)
                ConvertedInputs |= Input::STICK_R_LEFT;

            if (Inputs & WPAD_PRO_STICK_R_EMULATION_RIGHT)
                ConvertedInputs |= Input::STICK_R_RIGHT;

            if (Inputs & WPAD_PRO_STICK_R_EMULATION_DOWN)
                ConvertedInputs |= Input::STICK_R_DOWN;

            if (Inputs & WPAD_PRO_STICK_R_EMULATION_UP)
                ConvertedInputs |= Input::STICK_R_UP;

            if (Inputs & WPAD_PRO_BUTTON_STICK_R)
                ConvertedInputs |= Input::STICK_R_CLICK;

            if (Inputs & WPAD_PRO_BUTTON_Y)
                ConvertedInputs |= Input::BUTTON_Y;

            if (Inputs & WPAD_PRO_BUTTON_X)
                ConvertedInputs |= Input::BUTTON_X;

            if (Inputs & WPAD_PRO_BUTTON_B)
                ConvertedInputs |= Input::BUTTON_B;

            if (Inputs & WPAD_PRO_BUTTON_A)
                ConvertedInputs |= Input::BUTTON_A;

            if (Inputs & WPAD_PRO_BUTTON_PLUS)
                ConvertedInputs |= Input::BUTTON_PLUS;

            if (Inputs & WPAD_PRO_BUTTON_MINUS)
                ConvertedInputs |= Input::BUTTON_MINUS;

            if (Inputs & WPAD_PRO_TRIGGER_L)
                ConvertedInputs |= Input::BUTTON_L;
            
            if (Inputs & WPAD_PRO_TRIGGER_ZL)
                ConvertedInputs |= Input::BUTTON_ZL;

            if (Inputs & WPAD_PRO_TRIGGER_R)
                ConvertedInputs |= Input::BUTTON_R;

            if (Inputs & WPAD_PRO_TRIGGER_ZR)
                ConvertedInputs |= Input::BUTTON_ZR;

            if (Inputs & WPAD_PRO_BUTTON_HOME)
                ConvertedInputs |= Input::BUTTON_HOME;

            return ConvertedInputs;
        }

    public: 

        //Constructor
        KpadInput(int Width, int Height, KPADChan Channel)
        {
            this->Channel = Channel;
            this->Width = Width; this->Height = Height;
        };

        //Destructor
        ~KpadInput() override {};


        //Updates the VPADStatus & more
        bool Update()
        {
            PrevData = Data;
            KPADReadEx(Channel, &Status, 1, &Error);
            switch (Error) {
                //No errors continue as normal
                case KPAD_ERROR_OK: {
                    Data.Connected = true;
                    break;
                }
                //No controller on the channel / lost connection
                case KPAD_ERROR_INVALID_CONTROLLER: {
                    Data.BtnHeld = 0;
                    Data.Connected = false;
                    return false;
                }
                default: {
                    Data.BtnHeld = 0;
                    return false;
                }
            }

            Data.Angle.x = Status.angle.x;
            Data.Angle.y = Status.angle.y;

            Data.Accelerometer.x = Status.acc.x;
            Data.Accelerometer.y = Status.acc.y;
            Data.Accelerometer.z = Status.acc.z;

            Data.AccMagnitude = Status.accMagnitude;
            Data.AccVariation = Status.accVariation;

            if (Status.extensionType == WPAD_EXT_CORE || Status.extensionType == WPAD_EXT_NUNCHUK) {
                Data.ControllerType = WII;

                Data.BtnReleased = RemapWiiMote(Status.release);
                Data.BtnHeld     = RemapWiiMote(Status.hold);
                Data.BtnDown     = RemapWiiMote(Status.trigger);
                
                if (Status.extensionType == WPAD_EXT_NUNCHUK) {
                    Data.ControllerType = WII_NUNCHUK;

                    Data.Nunchuk.Accelerometer.x = Status.nunchuk.acc.x;
                    Data.Nunchuk.Accelerometer.y = Status.nunchuk.acc.y;
                    Data.Nunchuk.Accelerometer.z = Status.nunchuk.acc.z;

                    Data.Nunchuk.AccMagnitude = Status.nunchuk.accMagnitude;
                    Data.Nunchuk.AccVariation = Status.nunchuk.accVariation;
                }

            } else if (Status.extensionType == WPAD_EXT_CLASSIC) {
                Data.ControllerType = WII_CLASSIC;

                Data.BtnReleased = RemapClassic(Status.classic.release);
                Data.BtnHeld     = RemapClassic(Status.classic.hold);
                Data.BtnDown     = RemapClassic(Status.classic.trigger);

                Data.LStickPos.x = Status.classic.leftStick.x;
                Data.LStickPos.y = Status.classic.leftStick.y;

                Data.RStickPos.x = Status.classic.rightStick.x;
                Data.RStickPos.y = Status.classic.rightStick.y;

                Data.Classic.AnalogTriggerL = Status.classic.leftTrigger;
                Data.Classic.AnalogTriggerR = Status.classic.rightTrigger;
                
            } else {
                Data.ControllerType = PRO;

                Data.BtnReleased = RemapPro(Status.pro.release);
                Data.BtnHeld     = RemapPro(Status.pro.hold);
                Data.BtnDown     = RemapPro(Status.pro.trigger);

                Data.LStickPos.x = Status.pro.leftStick.x;
                Data.LStickPos.y = Status.pro.leftStick.y;

                Data.RStickPos.x = Status.pro.rightStick.x;
                Data.RStickPos.y = Status.pro.rightStick.y;

                Data.Pro.Charging = Status.pro.charging;
                Data.Pro.Wired = Status.pro.wired;
            }

            Data.ValidPointerPos = (Status.posValid == 1 || Status.posValid == 2) &&
                                   (Status.pos.x >= -1.0f && Status.pos.x <= 1.0f) &&
                                   (Status.pos.y >= -1.0f && Status.pos.y <= 1.0f);

            //! calculate the screen offsets if pointer is valid else leave old value
            if (Data.ValidPointerPos) {
                Data.PointerPos.x = (Width >> 1) * Status.pos.x;
                Data.PointerPos.y = (Height >> 1) * (-Status.pos.y);
            }
            
            return true;
        };
};