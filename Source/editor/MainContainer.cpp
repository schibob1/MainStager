//
// Created by Martin Rumori on 10.05.22.
//

#include "MainContainer.h"
#include <ParameterIds.h>

MainContainer::MainContainer (juce::AudioProcessorValueTreeState& apvts)
    : volumeKnobAttachment (apvts, ParameterIds::volume, volumeKnob)
{
    volumeKnob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeKnob.setRange (0.0f, 100.0f);
    volumeKnob.setValue(25.0f);
    volumeKnob.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);

    volumeKnob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    volumeKnob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    addAndMakeVisible (volumeKnob);

    sizeKnob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sizeKnob.setRange (0.0f, 100.0f);
    sizeKnob.setValue(25.0f);
    sizeKnob.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);

    sizeKnob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    sizeKnob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    addAndMakeVisible(sizeKnob);

    sizeLabel.setText("Size", juce::dontSendNotification);
    sizeLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible(sizeLabel);
}

void MainContainer::resized()
{
    volumeKnob.setBoundsRelative (0.06875f, 0.5711f, 0.1975f, 0.3511f);
    sizeKnob.setBoundsRelative(0.28f, 0.5711f, 0.1975f, 0.3511f);
    sizeLabel.setBounds (sizeKnob.getBounds().withY (sizeKnob.getBottom()).withHeight (proportionOfHeight (0.05f)));
}

void MainContainer::paint (juce::Graphics& g)
{

}
