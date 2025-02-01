#pragma once

// Standard Include
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <vector>

// Wut / Pads Include
#include <vpad/input.h>
#include <padscore/kpad.h>
#include <padscore/wpad.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>

// Controller Headers Include
#include "Controllers/Controller.h"
#include "Controllers/KpadInput.h"
#include "Controllers/VpadInput.h"
#include "Controllers/MergedInput.h"

// Main Controller / Input Source List
std::vector<Controller*> Controllers;

// List of Merged Inputs, The purpose
// of this list is to store all the merged
// input source and allow them to be destroyed
std::vector<MergedInput*> MergedInputs;

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

    // I don't know how the Balance board handles things so it's disabled by default
    WPADEnableWBC(false);

    // Disable specified controller types
    if ( !EnabledContollerTypes[0] ) { MoveToUnused(0); }   //Disables DRC
    if ( !EnabledContollerTypes[1] ) { EnablePRO(false); }  //Disables PRO
    else                             { EnablePRO(true); }   //Enables  PRO (not on by default ?)
    if ( !EnabledContollerTypes[2] ) { EnableWII(false); }  //Disables WII (and it's extensions ?)
};

/**
 * Quits the WiiU's controller libs
 * and clears input source lists
*/
void ControllersQuit() {
    KPADShutdown();
    Controllers.~vector();
    MergedInputs.~vector();
    UnusedControllers.~vector();
};

/**
 * Creates a new input that will occupy the place of the
 * Input with the index closest to 0 in the list of indexes
 * to be used merged into that new input source
 * \param Indexes Vector containing the indexes of the
 * controllers to be merged
*/
bool CreateMergedInput(const std::vector<int>& Indexes) {
    if (Indexes.empty()) { return false; };

    MergedInput* NewMerged;
    NewMerged->Data.ControllerType = TYPE_MERGED;

    for (int i : Indexes) {
        if (Controllers[i] == nullptr || 
            NewMerged->Data.ControllerType == TYPE_MERGED)
            { continue; }
        
        MoveToUnused(i);
        NewMerged->Indexes.push_back(i);
        NewMerged->MergeSource.push_back(UnusedControllers[i]);
    }

    if (NewMerged->MergeSource.empty()) { return false; };
    if (NewMerged->MergeSource.size() == 1) { MoveToUsed(NewMerged->Indexes[0]); return false; };

    int ControllerIndex = *std::min_element(NewMerged->Indexes.begin(), NewMerged->Indexes.end());

    Controllers[ControllerIndex] = NewMerged;
    NewMerged->Data.MERGED.MergedIndex = MergedInputs.size() + 1;
    MergedInputs.push_back(NewMerged);

    return true;
}

/**
 * Function to destroy a merged input source and places
 * it's merging sources back in the Controllers vector
 * \param Index The Index of the merged input source to Destroy
*/
bool DestroyMergedInput(int Index) {
    if (MergedInputs[Index] == nullptr) { return false; };

    for (int i : MergedInputs[Index]->Indexes) {
        MoveToUsed(i);
    }

    MergedInputs[Index]->Indexes.~vector();
    MergedInputs[Index]->MergeSource.~vector();
    MergedInputs[Index]->~MergedInput();
    MergedInputs[Index] = nullptr;

    return true;
}

/**
 * Simple Macro that destroys all the merged input sources
*/
#define DestroyAllMergedInputs() \
{ for (int i = 0; i < MergedInputs.size(); i++) { DestroyMergedInput(i); }; }

/**
 * Grabs the latest input data from all the controllers
*/
void ControllersUpdate() {
    for (int i = 0; i < 7; i++) {
        if (Controllers[i] == nullptr) { continue; };
        Controllers[i]->Update();
    }
};

/**
 * Macro to rumble the DRC, it allows for finer control compared
 * to the universal function but is DRC only, doesn't rumble if the
 * DRC is diabled or merged with another controller / input source
 * \param Patern An array of uint8_t ranging from 0x00 to 0xFF
*/
#define RumbleDRC(Patern) \
{ if (Controllers[0] != nullptr && Controllers[0]->Data.ControllerType == TYPE_DRC) \
{ VPADControlMotor(VPAD_CHAN_0, Patern, sizeof(Patern)); }; }

/**
 * Universal Rumble Function, Note that it can only use on or
 * off states, this is to be compatible with all controller types
 * the DRC allows for finer controls so for that use the
 * ``RumbleDRC(Patern)`` macro
 * \param Controller The Index of the controller to rumble
 * \param Patern An array of on and off states to play as a rumble
*/
void RumbleController(int Controller, bool *Patern) {
    // If the controller is not enabled why bother ?
    if (Controllers[Controller] == nullptr) { return; }

    // Bool Patern to simple DRC patern macro
    #define PATERN_TO_DRC_PATERN(SrcPatern, DestPatern) \
    { for (size_t i = 0; i < sizeof(SrcPatern) / sizeof(SrcPatern[0]); ++i) { \
        if (SrcPatern[i] == 0) { DestPatern[i] = 0x00; } \
        else { DestPatern[i] = 0xFF; } \
    } }

    // If the controller is the DRC
    if (Controllers[Controller]->Data.ControllerType == TYPE_DRC) {
        uint8_t VpadPatern[sizeof(Patern)];
        PATERN_TO_DRC_PATERN(Patern, VpadPatern);
        RumbleDRC(VpadPatern);
        return;
    }

    if (Controllers[Controller]->Data.ControllerType == TYPE_MERGED) {
        #define INPUTS MergedInputs[Controllers[Controller]->Data.MERGED.MergedIndex]
        for (int i : INPUTS->Indexes) {
            if (UnusedControllers[i]->Data.ControllerType == TYPE_DRC) {
                uint8_t VpadPatern[sizeof(Patern)];
                PATERN_TO_DRC_PATERN(Patern, VpadPatern);
                RumbleDRC(VpadPatern);
            } else { continue; };
            // Same as bellow I don't know how to implement if for
            // all controller types so It's blank for now 
            return;
        };

        #undef INPUTS
        return;
    }

    #undef PATERN_TO_DRC_PATERN
    // In any other case I don't yet know how to implement
    // that correctly, so I'll just leave it as is for now
};