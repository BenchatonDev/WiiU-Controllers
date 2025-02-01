#pragma once

#include <cstdint>
#include <cstring>

#include <padscore/wpad.h>
#include <padscore/kpad.h>

// Controller types
enum ControllerType {
    TYPE_DRC     = 0,
    TYPE_PRO     = 1,
    TYPE_WII     = 2,
    TYPE_NUNCHUK = 3,
    TYPE_CLASSIC = 4,
    TYPE_MERGED  = 5,
};

// Buttons Values
enum Buttons {
    BUTTON_NONE   = 0x0000,
    VPAD_TOUCH    = 0x80000000,
    BUTTON_Z      = 0x20000,
    BUTTON_C      = 0x10000,
    BUTTON_A      = 0x8000,
    BUTTON_B      = 0x4000,
    BUTTON_X      = 0x2000,
    BUTTON_Y      = 0x1000,
    BUTTON_1      = BUTTON_Y,
    BUTTON_2      = BUTTON_X,
    BUTTON_LEFT   = 0x0800,
    BUTTON_RIGHT  = 0x0400,
    BUTTON_UP     = 0x0200,
    BUTTON_DOWN   = 0x0100,
    BUTTON_ZL     = 0x0080,
    BUTTON_ZR     = 0x0040,
    BUTTON_L      = 0x0020,
    BUTTON_R      = 0x0010,
    BUTTON_PLUS   = 0x0008,
    BUTTON_MINUS  = 0x0004,
    BUTTON_HOME   = 0x0002,
    BUTTON_SYNC   = 0x0001,
    STICK_R_LEFT  = 0x04000000,
    STICK_R_RIGHT = 0x02000000,
    STICK_R_UP    = 0x01000000,
    STICK_R_DOWN  = 0x00800000,
    STICK_R_CLICK = 0x00020000,
    STICK_L_LEFT  = 0x40000000,
    STICK_L_RIGHT = 0x20000000,
    STICK_L_UP    = 0x10000000,
    STICK_L_DOWN  = 0x08000000,
    STICK_L_CLICK = 0x00040000
};

// 2D and 3D Position stuct for i.e touch pos / stick pos / gyro pos
typedef struct ControllerVector2D {
    float x;
    float y;
};

typedef struct ControllerVector3D {
    float x;
    float y;
    float z;
};

// Main Controller class
class Controller
{
    public:
        //Constructor
        Controller() = default;

        //Destructor
        virtual ~Controller() = default;

        KPADChan Channel;

        virtual bool Update();

        // Sruct containing the controller data
        typedef struct ControllerData
        {
            bool Connected;
            int ControllerType;
            bool ValidPointerPos;

            uint32_t BtnHeld;
            uint32_t BtnDown;
            uint32_t BtnReleased;
            
            ControllerVector2D LStickPos;
            ControllerVector2D RStickPos;
            ControllerVector2D PointerPos;

            ControllerVector3D Angle;
            ControllerVector3D Accelerometer;
            float AccMagnitude;
            float AccVariation;

            union
            {
                struct
                {
                    ControllerVector2D StickPos;
                    ControllerVector3D Accelerometer;
    
                    float AccMagnitude;
                    float AccVariation;
                } NUNCHUK;

                struct
                {
                    float AnalogTriggerL;
                    float AnalogTriggerR;
                } CLASSIC;

                struct
                {
                    bool Touched;
                    bool Headphones;

                    ControllerVector2D AccVertical;
                    ControllerVector3D Magnetometer;
                    ControllerVector3D Gyroscope;

                    uint8_t Volume;
                    uint8_t BatteryLvl;
                    uint8_t MicStatus;
                } DRC;
                    
                struct
                {
                    int32_t Charging;
                    int32_t Wired;
                } PRO; 
                #ifdef __has_include("MergedInput.h")
                struct
                {
                    int MergedIndex;
                } MERGED;
                #endif
                    
            };   
        };   

        ControllerData Data{};
        ControllerData PrevData{};
};