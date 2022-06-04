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
    sizeLabel.toBehind (&sizeKnob);
    colourLabel.toBehind (&colourKnob);
    widthLabel.toBehind (&widthKnob);
}

void MainContainer::resized()
{
    auto knobSize = proportionOfWidth (0.159f);

    //knobs postition
    dryWetKnob.setBounds (proportionOfWidth (0.046f), proportionOfHeight ( 0.0825f /* 0.043275f 0.09f 0.08f*/), knobSize, knobSize);
    sizeKnob.setBounds (proportionOfWidth (0.1725f), proportionOfHeight (0.25f /*0.21125f 0.26f 0.2511f*/), knobSize, knobSize);
    colourKnob.setBounds (proportionOfWidth (0.04675f), proportionOfHeight (0.4678f /*0.4285f 0.46f 0.4676f*/), knobSize, knobSize);
    widthKnob.setBounds (proportionOfWidth (0.1725f), proportionOfHeight (0.635f /*0.595f 0.64f 0.63f */), knobSize, knobSize);

    //labels
    auto labelOffset = -proportionOfHeight (0.01f);
    auto labelHeight = proportionOfHeight (0.03f);

    dryWetLabel.setBounds (dryWetKnob.getBounds().withY (dryWetKnob.getBottom() + labelOffset).withHeight (labelHeight));
    sizeLabel.setBounds (sizeKnob.getBounds().withY (sizeKnob.getBottom() + labelOffset).withHeight (labelHeight));
    colourLabel.setBounds (colourKnob.getBounds().withY (colourKnob.getBottom() + labelOffset).withHeight (labelHeight));
    widthLabel.setBounds (widthKnob.getBounds().withY (widthKnob.getBottom() + labelOffset).withHeight (labelHeight));
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