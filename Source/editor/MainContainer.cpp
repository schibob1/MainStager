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

    dryWetLabel.toBehind (&dryWetKnob);
}

void MainContainer::resized()
{
    auto knobSize = proportionOfWidth (0.159f);

    //knobs postition
    dryWetKnob.setBounds (proportionOfWidth (0.046f), proportionOfHeight ( 0.092222f /* 0.043275f */), knobSize, knobSize);
    sizeKnob.setBounds (proportionOfWidth (0.1725f), proportionOfHeight (0.21125f), knobSize, knobSize);
    colourKnob.setBounds (proportionOfWidth (0.04675f), proportionOfHeight (0.4285f), knobSize, knobSize);
    widthKnob.setBounds (proportionOfWidth (0.1725f), proportionOfHeight (0.595f), knobSize, knobSize);

    //labels
    auto labelOffset = -proportionOfHeight (0.01f);

    dryWetLabel.setBounds (dryWetKnob.getBounds().withY (dryWetKnob.getBottom() + labelOffset).withHeight (proportionOfHeight (0.03f)));
    sizeLabel.setBounds (sizeKnob.getBounds().withY (sizeKnob.getBottom() + labelOffset).withHeight (proportionOfHeight (0.03f)));
    colourLabel.setBounds (colourKnob.getBounds().withY (colourKnob.getBottom() + labelOffset).withHeight (proportionOfHeight (0.03f)));
    widthLabel.setBounds (widthKnob.getBounds().withY (widthKnob.getBottom() + labelOffset).withHeight (proportionOfHeight (0.03f)));
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