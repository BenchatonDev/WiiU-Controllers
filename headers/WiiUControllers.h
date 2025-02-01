#pragma once

// Standard Include
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>

// Wut Pads Include
#include <vpad/input.h>
#include <padscore/kpad.h>
#include <padscore/wpad.h>

// Controller Headers Include
#include "Controllers/Controller.h"
#include "Controllers/KpadInput.h"
#include "Controllers/VpadInput.h"

// Main Controller / Input Source List
std::vector<Controller*> Controllers;

// Unused Controller / Input Source List for i.e
// Controllers that can't be used in the current config
// (controllers beyond 4 if maxControllers is false at init)
// or controllers that are merged into a single input source
std::vector<Controller*> UnusedControllers;

// Macros
#define EnableWII(enable) \
{ WPADEnableWiiRemote(enable); }

#define EnablePRO(enable) \
{ WPADEnableURCC(enable); }

#define MoveToUnused(index) \
{ UnusedControllers[index] = Controllers[index]; Controllers[index] = nullptr; }

#define MoveToUsed(index) \
{ Controllers[index] = UnusedControllers[index]; UnusedControllers[index] = nullptr; }

// Not usefull but might makes more sense than
// contoller numbering starting from 0 for some
#define CONTROLLER_1 = 0
#define CONTROLLER_2 = 1
#define CONTROLLER_3 = 2
#define CONTROLLER_4 = 3
#define CONTROLLER_5 = 4
#define CONTROLLER_6 = 5
#define CONTROLLER_7 = 6
#define CONTROLLER_8 = 7

// Init Function
/**
 * Inits the WiiU's contoller libs, and creates input soures
 * for all the specified controller types and number (4 or 8).
 * \param EnabledContollerTypes Array of bools for the controller
 * types to enable (0 = DRC, 1 = Pro, 2 = Wii), can always be
 * enabled later on with EnableControllerType()
 * \param Width The horizontal resolution for touch / Wii IR
 * pointer input
 * \param Height The vertical resolution for touch / Wii IR
 * pointer input
 * \param maxControllers If true, it will create the maximum of 8
 * input sources, else it will create the default of 4
*/
void ControllersInit(bool EnabledContollerTypes[3], int Width, int Height, bool maxControllers) {
    KPADInit();
    VPADInit();

    VpadInput VpadInputs = {Width, Height};

    KpadInput KpadInputs[7] = {
            {Width, Height, WPAD_CHAN_0},
            {Width, Height, WPAD_CHAN_1},
            {Width, Height, WPAD_CHAN_2},
            {Width, Height, WPAD_CHAN_3},
            {Width, Height, WPAD_CHAN_4},
            {Width, Height, WPAD_CHAN_5},
            {Width, Height, WPAD_CHAN_6}};
    

    Controllers.reserve(8);
    UnusedControllers.reserve(8);

    if (maxControllers) {
        for (int i = 0; i < 7; i++) {
            if (i == 0) { Controllers[i] = &VpadInputs; continue; };
            Controllers[i] = &KpadInputs[i - 1];
        }
    } else {
        for (int i = 0; i < 7; i++) {
            if (i == 0) { Controllers[i] = &VpadInputs; continue; };
            if (i >  4) { UnusedControllers[i] = &KpadInputs[i - 1]; continue; };
            Controllers[i] = &KpadInputs[i - 1];
            UnusedControllers[i] = nullptr;
        }
    }


    // Disable specified controller types
    if ( !EnabledContollerTypes[0] ) { MoveToUnused(0); }   //Disables DRC
    if ( !EnabledContollerTypes[1] ) { EnablePRO(false); }  //Disables PRO
    else                             { EnablePRO(true); }   //Enables  PRO (not on by default ?)
    if ( !EnabledContollerTypes[2] ) { EnableWII(false); }  //Disables WII (and it's extensions ?)
};