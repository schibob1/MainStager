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
    void configureKnobAndLabel (juce::Slider& knob, juce::Label& label, juce::String labelText);

    juce::Slider dryWetKnob; // bzw. die Funktion, die der Slider hat
    juce::Slider sizeKnob;
    juce::Slider colourKnob;
    juce::Slider widthKnob;
    juce::Slider speedKnob;
    juce::Slider thresholdKnob;

    //label
    juce::Label dryWetLabel;
    juce::Label sizeLabel;
    juce::Label colourLabel;
    juce::Label widthLabel;
    juce::Label speedLabel;
    juce::Label thresholdLabel;

    juce::AudioProcessorValueTreeState::SliderAttachment dryWetKnobAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment sizeKnobAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment widthKnobAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment colourKnobAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment speedKnobAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment thresholdKnobAttachment;
};
