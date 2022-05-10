//
// Created by Martin Rumori on 10.05.22.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class MainContainer : public juce::Component
{
public:
    MainContainer (juce::AudioProcessorValueTreeState& apvts);
    ~MainContainer() override {}

    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::Slider compressorAttackSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment compressorAttackSliderAttachment;

};
