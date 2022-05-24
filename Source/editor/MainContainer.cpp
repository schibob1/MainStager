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
    configureKnobAndLabel (dryWetKnob, dryWetLabel, "Dry/Wet");
    addAndMakeVisible (dryWetKnob);
    addAndMakeVisible (dryWetLabel);

    sizeKnob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //sizeKnob.setRange (0.0f, 100.0f);
    //sizeKnob.setValue (25.0f);
    sizeKnob.setTextBoxStyle (juce::Slider::NoTextBox, true, 100, 25);

    sizeKnob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    sizeKnob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    addAndMakeVisible (sizeKnob);

    sizeLabel.setText ("Size", juce::dontSendNotification);
    sizeLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (sizeLabel);

    //colour
    colourKnob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //colourKnob.setRange (0.0f, 100.0f);
    //colourKnob.setValue (25.0f);
    colourKnob.setTextBoxStyle (juce::Slider::NoTextBox, true, 100, 25);

    colourKnob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    colourKnob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    addAndMakeVisible (colourKnob);

    colourLabel.setText ("Colour", juce::dontSendNotification);
    colourLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (colourLabel);

    //width
    widthKnob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //widthKnob.setRange (0.0f, 100.0f);
    //widthKnob.setValue (25.0f);
    widthKnob.setTextBoxStyle (juce::Slider::NoTextBox, true, 100, 25);

    widthKnob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    widthKnob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    addAndMakeVisible (widthKnob);

    widthLabel.setText ("Width", juce::dontSendNotification);
    widthLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (widthLabel);
}

void MainContainer::resized()
{
    //knobs postition
    dryWetKnob.setBoundsRelative (0.06875f, 0.5711f, 0.1975f, 0.3511f);
    sizeKnob.setBoundsRelative (0.28f, 0.5711f, 0.1975f, 0.3511f);
    colourKnob.setBoundsRelative (0.5075f, 0.5711f, 0.1975f, 0.3511f);
    widthKnob.setBoundsRelative (0.735f, 0.5711f, 0.1975f, 0.3511f);

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