//
// Created by Martin Rumori on 10.05.22.
//

#include "MainContainer.h"
#include <ParameterIds.h>

MainContainer::MainContainer (juce::AudioProcessorValueTreeState& apvts) //constructor
    : dryWetKnobAttachment (apvts, ParameterIds::dryWet, dryWetKnob),
      sizeKnobAttachment (apvts, ParameterIds::size, sizeKnob),
      widthKnobAttachment (apvts, ParameterIds::width, widthKnob),
      colourKnobAttachment (apvts, ParameterIds::colour, colourKnob)
{
    //dryWet
    configureKnobAndLabel (dryWetKnob, dryWetLabel, "Dry/Wet");
    addAndMakeVisible (dryWetKnob);
    addAndMakeVisible (dryWetLabel);

    //size
    configureKnobAndLabel (sizeKnob, sizeLabel, "Size");
    addAndMakeVisible (sizeKnob);
    addAndMakeVisible (sizeLabel);

    //colour
    configureKnobAndLabel (colourKnob, colourLabel, "Colour");
    addAndMakeVisible (colourKnob);
    addAndMakeVisible (colourLabel);

    //width
    configureKnobAndLabel (widthKnob, widthLabel, "Width");
    addAndMakeVisible (widthKnob);
    addAndMakeVisible (widthLabel);
}

void MainContainer::resized()
{
    //knobs postition
    dryWetKnob.setBoundsRelative (0.0425f, 0.045f, 0.1625f, 0.3625f);
    sizeKnob.setBoundsRelative (0.17f, 0.22f, 0.16f, 0.36f);
    colourKnob.setBoundsRelative (0.045f, 0.42f, 0.16f, 0.36f);
    widthKnob.setBoundsRelative (0.16f, 0.625f, 0.16f, 0.36f);

    //labels
    dryWetLabel.setBounds (dryWetKnob.getBounds().withY (dryWetKnob.getBottom()).withHeight (proportionOfHeight (0.05f)));
    sizeLabel.setBounds (sizeKnob.getBounds().withY (sizeKnob.getBottom()).withHeight (proportionOfHeight (0.05f)));
    colourLabel.setBounds (colourKnob.getBounds().withY (colourKnob.getBottom()).withHeight (proportionOfHeight (0.05f)));
    widthLabel.setBounds (widthKnob.getBounds().withY (widthKnob.getBottom()).withHeight (proportionOfHeight (0.05f)));
}

void MainContainer::paint (juce::Graphics& g)
{
}

void MainContainer::configureKnobAndLabel (juce::Slider& knob, juce::Label& label, juce::String labelText)
{
    knob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle (juce::Slider::NoTextBox, true, 100, 25);
    knob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    knob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
}