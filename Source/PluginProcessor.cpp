/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LiveGUIAudioProcessor::LiveGUIAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

LiveGUIAudioProcessor::~LiveGUIAudioProcessor()
{
}

//==============================================================================
const juce::String LiveGUIAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LiveGUIAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LiveGUIAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LiveGUIAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LiveGUIAudioProcessor::getTailLengthSeconds() const
{
#if JucePlugin_Enable_ARA
    double tail;
    if (getTailLengthSecondsForARA (tail))
        return tail;
#endif

    return 0.0;
}

int LiveGUIAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LiveGUIAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LiveGUIAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LiveGUIAudioProcessor::getProgramName (int index)
{
    return {};
}

void LiveGUIAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LiveGUIAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
#if JucePlugin_Enable_ARA
    if (prepareToPlayForARA (sampleRate, samplesPerBlock, getMainBusNumOutputChannels()))
        return;
#endif

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void LiveGUIAudioProcessor::releaseResources()
{
#if JucePlugin_Enable_ARA
    if (releaseResourcesForARA())
        return;
#endif

    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LiveGUIAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LiveGUIAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

#if JucePlugin_Enable_ARA
    if (processBlockForARA (buffer, isNonRealtime(), getPlayHead()))
        return;
#endif

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool LiveGUIAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LiveGUIAudioProcessor::createEditor()
{
    return new LiveGUIAudioProcessorEditor (*this);
}

//==============================================================================
// SAVE
void LiveGUIAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

    
}

// LOAD
void LiveGUIAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LiveGUIAudioProcessor();
}
