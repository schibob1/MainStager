//
// Created by PC on 03.05.2022.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class MainstagerLNF : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider (juce::Graphics&, int x, int y, int width, int height,
            float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&) override;
};
