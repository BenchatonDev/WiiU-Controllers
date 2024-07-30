#pragma once

#include <cstdint>
#include <cstring>

class Input
{
    public:

        //Constructor
        Input(){};

        //Destructor
        ~Input(){};

        // Setting up structs for sticks / gyro / pointing device data
        struct Vector2D
        {
            float x, y;
        };

        struct Vector3D
        {
            float x, y, z;
        };

        // Sruct containing the controller data
        typedef struct Data
        {
            uint32_t BtnHeld;
            uint32_t BtnDown;
            uint32_t BtnReleased;
            
            Vector2D LStickPos;
            Vector2D RStickPos;
            Vector2D PointerPos;

            Vector3D GyroVector;

            bool Touched;
        };   
};
