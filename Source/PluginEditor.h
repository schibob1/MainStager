#pragma once

#include "PluginProcessor.h"
#include "KnobClass.h"

//==============================================================================
class MainStagerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit MainStagerAudioProcessorEditor (MainStagerAudioProcessor&);
    ~MainStagerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MainStagerAudioProcessor& processorRef;

    // background image
    std::unique_ptr<juce::Drawable> backgroundImage;

    //knobs
    juce::CustomLNF lookAndFeel;
    juce::Slider volumeSlider; // bzw. die Funktion, die der Slider hat

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainStagerAudioProcessorEditor)
};
