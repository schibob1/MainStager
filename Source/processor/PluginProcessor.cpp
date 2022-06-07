
#include "PluginProcessor.h"
#include <ParameterIds.h>
#include <editor/PluginEditor.h>

//==============================================================================
MainStagerAudioProcessor::MainStagerAudioProcessor()
    : AudioProcessor (BusesProperties()
#if !JucePlugin_IsMidiEffect
    #if !JucePlugin_IsSynth
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
    #endif
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
            ),
      apvts (*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

MainStagerAudioProcessor::~MainStagerAudioProcessor()
{
}

//==============================================================================
const juce::String MainStagerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MainStagerAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool MainStagerAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool MainStagerAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double MainStagerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MainStagerAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
}

int MainStagerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MainStagerAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String MainStagerAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void MainStagerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void MainStagerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);

    //juce::dsp::ProcessSpec object to hold the information necessary to initialize the Reverb object you have created
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = juce::uint32 (samplesPerBlock);
    spec.numChannels = juce::uint32 (getMainBusNumInputChannels());
    compressorBuffer.setSize (getMainBusNumInputChannels() * 2, samplesPerBlock); //worst case: wenn buffer groesser wird -> neue Werte aktualisieren
    reverb.prepare (spec);
    compressor.prepare (spec);
}

void MainStagerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool MainStagerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
    #if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    #endif

    return true;
#endif
}

void MainStagerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, //Ref. auf Audiobuffer
    juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // params.wetLevel = apvts.getParameter (ParameterIds::dryWet)->getValue(); //normalisierter Wert --> am Ende oder ganz weg
    params.wetLevel = 1.0f;
    params.roomSize = apvts.getParameter (ParameterIds::size)->getValue(); //normalisierter Wert
    params.damping = apvts.getParameter (ParameterIds::colour)->getValue();
    params.width = apvts.getParameter (ParameterIds::width)->getValue();

    reverb.setParameters (params);

    compressor.setAttack (1.0f); //fixieren
    compressor.setRelease (*apvts.getRawParameterValue (ParameterIds::speed)); //flexibel
    compressor.setThreshold (*apvts.getRawParameterValue (ParameterIds::threshold)); // nicht-normalisierter Wert
    compressor.setRatio (10.0f); //fixiert

    auto wetLevel = apvts.getParameter (ParameterIds::dryWet)->getValue();

    juce::dsp::AudioBlock<float> block (buffer); //Ref. auf Buffer, wrappt bel. Arten v. Speicher
    auto numChannels = size_t (buffer.getNumChannels());
    auto compressorBlock = juce::dsp::AudioBlock<float> (compressorBuffer).getSubBlock (0, size_t (buffer.getNumSamples())); //auto = dass es keine Dopplung gibt
    auto mainBlock = compressorBlock.getSubsetChannelBlock (0, numChannels);
    auto sideBlock = compressorBlock.getSubsetChannelBlock (numChannels, numChannels);
    sideBlock.copyFrom (block); //copies block

    juce::dsp::ProcessContextNonReplacing<float> reverbContext (block, mainBlock);
    juce::dsp::ProcessContextReplacing<float> compressorContext (compressorBlock); //mainInputBlock aka Channel 0+1 wird ueberschrieben, compressorInputBlock aka 2+3 v. compressorInputBlock bleibt erhalten, da SC

    reverb.process (reverbContext);
    compressor.process (compressorContext);
    block.addProductOf (mainBlock, wetLevel);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused (channelData);
        // ..do something to the data...
    }
}

//==============================================================================
bool MainStagerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MainStagerAudioProcessor::createEditor()
{
    return new MainStagerAudioProcessorEditor (*this);
}

//==============================================================================
void MainStagerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void MainStagerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MainStagerAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout MainStagerAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    //dry/wet
    layout.add (std::make_unique<juce::AudioParameterFloat> (ParameterIds::dryWet,
        "Dry/Wet",
        juce::NormalisableRange<float> (0.0f, 100.0f, 1.0f, 1.0f),
        100.0f,
        "%",
        juce::AudioProcessorParameter::genericParameter,
        nullptr,
        nullptr));

    //size
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        ParameterIds::size,
        "Size",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f, 1.0f),
        0.8f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [] (float value, int) {
            if (value * 100.0f < 10.0f)
                return juce::String (value * 100.0f, 2);
            else if (value * 100.0f < 100.0f)
                return juce::String (value * 100.0f, 1);
            else
                return juce::String (value * 100.0f, 0); },
        nullptr));
    //colour
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        ParameterIds::colour,
        "Colour",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f, 1.0f),
        0.5f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [] (float value, int) {
            if (value * 100.0f < 10.0f)
                return juce::String (value * 100.0f, 2);
            else if (value * 100.0f < 100.0f)
                return juce::String (value * 100.0f, 1);
            else
                return juce::String (value * 100.0f, 0); },
        nullptr));

    //width
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        ParameterIds::width,
        "Width",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f, 1.0f),
        0.75f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [] (float value, int) {
            if (value * 100.0f < 10.0f)
                return juce::String (value * 100.0f, 2);
            else if (value * 100.0f < 100.0f)
                return juce::String (value * 100.0f, 1);
            else
                return juce::String (value * 100.0f, 0); },
        nullptr));

    //speed aka release
    layout.add (std::make_unique<juce::AudioParameterFloat> (ParameterIds::speed,
        "Speed",
        juce::NormalisableRange<float> (0.0f, 1000.0f, 1.0f, 1.0f),
        100.0f,
        "ms",
        juce::AudioProcessorParameter::genericParameter,
        nullptr,
        nullptr));

    //threshold
    layout.add (std::make_unique<juce::AudioParameterFloat> (ParameterIds::threshold,
        "Ducking/Intensity",
        juce::NormalisableRange<float> (-100.0f, 0.0f, 1.0f, 0.25f),
        -24.0f,
        "dB",
        juce::AudioProcessorParameter::genericParameter,
        nullptr,
        nullptr));

    return layout;
}
