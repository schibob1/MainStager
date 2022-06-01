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
    //addAndMakeVisible (dryWetLabel);

    //size
    configureKnobAndLabel (sizeKnob, sizeLabel, "Size");
    addAndMakeVisible (sizeKnob);
    //addAndMakeVisible (sizeLabel);

    //colour
    configureKnobAndLabel (colourKnob, colourLabel, "Colour");
    addAndMakeVisible (colourKnob);
    //addAndMakeVisible (colourLabel);

    //width
    configureKnobAndLabel (widthKnob, widthLabel, "Width");
    addAndMakeVisible (widthKnob);
    //addAndMakeVisible (widthLabel);
}

void MainContainer::resized()
{
    //knobs postition
    dryWetKnob.setBoundsRelative (0.046f, 0.043275f, 0.159f, 0.359f);
    sizeKnob.setBoundsRelative (0.1725f, 0.21125f, 0.159f, 0.359f);
    colourKnob.setBoundsRelative (0.04675f, 0.4285f, 0.159f, 0.359f);
    widthKnob.setBoundsRelative (0.1725f, 0.595f, 0.159f, 0.359f);

    //labels
    dryWetLabel.setBounds (dryWetKnob.getBounds().withY (dryWetKnob.getBottom()).withHeight (proportionOfHeight (0.01f)));
    sizeLabel.setBounds (sizeKnob.getBounds().withY (sizeKnob.getBottom()).withHeight (proportionOfHeight (0.02f)));
    colourLabel.setBounds (colourKnob.getBounds().withY (colourKnob.getBottom()).withHeight (proportionOfHeight (0.03f)));
    widthLabel.setBounds (widthKnob.getBounds().withY (widthKnob.getBottom()).withHeight (proportionOfHeight (0.04f)));
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