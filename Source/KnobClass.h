//
// Created by PC on 03.05.2022.
//

#ifndef MAINSTAGER_KNOBCLASS_H
#define MAINSTAGER_KNOBCLASS_H

#endif //MAINSTAGER_KNOBCLASS_H

#pragma once

#include "PluginEditor.h"
#include "PluginProcessor.h"


namespace juce
{
    class CustomLNF : public juce::LookAndFeel_V4
    {
    public:
        void drawRotarySlider (Graphics&, int x, int y, int width, int height,
            float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider&);
    };
}



