#include "PluginEditor.h"
#include <processor/PluginProcessor.h>

#include <BinaryData.h>

//==============================================================================
MainStagerAudioProcessorEditor::MainStagerAudioProcessorEditor (MainStagerAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processorRef (p),
      mainContainer (p.getApvts()),
      backgroundImage (juce::Drawable::createFromImageData (BinaryData::background_jpg, BinaryData::background_jpgSize))
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 450);

    juce::LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
    volumeSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setRange (0.0f, 100.0f);
    volumeSlider.setValue(25.0f);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);

    volumeSlider.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    volumeSlider.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    addAndMakeVisible (volumeSlider);

    addAndMakeVisible (mainContainer);
}

MainStagerAudioProcessorEditor::~MainStagerAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel (nullptr);
}

//==============================================================================
void MainStagerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // draw background image
    backgroundImage->drawWithin (g, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, 0.5f);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MainStagerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //mySlider.setBounds (getWidth()/ 2-100, getHeight() / 2 -100, 200, 200);
    volumeSlider.setBoundsRelative (0.06875f, 0.5711f, 0.1975f, 0.3511f);
}
