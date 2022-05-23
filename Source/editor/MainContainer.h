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
    juce::Slider sizeKnob;
    juce::Slider dryWetKnob; // bzw. die Funktion, die der Slider hat
    juce::Slider widthKnob;
    juce::Slider colourKnob;

    //label
    juce::Label sizeLabel;
    juce::Label dryWetLabel;
    juce::Label widthLabel;
    juce::Label colourLabel;

    juce::AudioProcessorValueTreeState::SliderAttachment volumeKnobAttachment;
};
