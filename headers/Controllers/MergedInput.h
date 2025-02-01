#pragma once

#include "Controller.h"
#include <vector>

class MergedInput : public Controller {
    private:
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

    public:
        // TODO -> Make more of the Data from
        // the merged controllers accessible
        std::vector<int> Indexes;
        std::vector<Controller*> MergeSource;

        bool Update() {
            reset();

            for (int i; i < MergeSource.size(); i++) {
                if (MergeSource[i] != nullptr) {
                    MergeSource[i]->Update();
                    combine(*MergeSource[i]);
                }
            }

            process();

            return true;
        };
};