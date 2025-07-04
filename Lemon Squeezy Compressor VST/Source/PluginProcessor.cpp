/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_dsp/juce_dsp.h>

//==============================================================================
LemonSqueezyCompressorVSTAudioProcessor::LemonSqueezyCompressorVSTAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
    , parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

LemonSqueezyCompressorVSTAudioProcessor::~LemonSqueezyCompressorVSTAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout
LemonSqueezyCompressorVSTAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "threshold", "Threshold", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.05f), 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "attack", "Attack", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.05f), 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "release", "Release", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.05f), 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "outputGain", "Output Gain", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.05f), 0.0f));

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String LemonSqueezyCompressorVSTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LemonSqueezyCompressorVSTAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool LemonSqueezyCompressorVSTAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool LemonSqueezyCompressorVSTAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double LemonSqueezyCompressorVSTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LemonSqueezyCompressorVSTAudioProcessor::getNumPrograms() { return 1; }
int LemonSqueezyCompressorVSTAudioProcessor::getCurrentProgram() { return 0; }
void LemonSqueezyCompressorVSTAudioProcessor::setCurrentProgram(int) {}
const juce::String LemonSqueezyCompressorVSTAudioProcessor::getProgramName(int) { return {}; }
void LemonSqueezyCompressorVSTAudioProcessor::changeProgramName(int, const juce::String&) {}

//==============================================================================
void LemonSqueezyCompressorVSTAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(getTotalNumOutputChannels());

    compressor.prepare(spec);
}

void LemonSqueezyCompressorVSTAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LemonSqueezyCompressorVSTAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void LemonSqueezyCompressorVSTAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // === Parameters from sliders ===
    float inputVal = *parameters.getRawParameterValue("threshold");  // -1.0 to 1.0
    float thresholdDb = juce::jmap(inputVal, -1.0f, 1.0f, 0.0f, -60.0f);
    float ratio = juce::jmap(inputVal, -1.0f, 1.0f, 1.5f, 10.0f);

    float attackVal = *parameters.getRawParameterValue("attack");
    float attackMs = juce::jmap(attackVal, -1.0f, 1.0f, 5.0f, 100.0f);

    float releaseVal = *parameters.getRawParameterValue("release");
    float releaseMs = juce::jmap(releaseVal, -1.0f, 1.0f, 50.0f, 500.0f);

    float outputGainVal = *parameters.getRawParameterValue("outputGain");
    float userGainDb = juce::jmap(outputGainVal, -1.0f, 1.0f, -24.0f, 24.0f);

    // Makeup gain starts from inputVal = -0.5 and grows to +35 dB at inputVal = 1.0
    float makeupGainDb = 0.0f;
    if (inputVal > -0.5f)
    {
        float normInput = juce::jmap(inputVal, -0.5f, 1.0f, 0.0f, 1.0f);
        normInput = juce::jlimit(0.0f, 1.0f, normInput); // clamp between 0–1
        makeupGainDb = normInput * 40.0f; // up to +35 dB
    }

    float totalGainDb = userGainDb + makeupGainDb;
    float gain = juce::Decibels::decibelsToGain(totalGainDb);

    // === Compressor settings ===
    compressor.setThreshold(thresholdDb);
    compressor.setRatio(ratio);
    compressor.setAttack(attackMs);
    compressor.setRelease(releaseMs);

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    compressor.process(context);

    // === Apply post gain ===
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        buffer.applyGain(channel, 0, buffer.getNumSamples(), gain);
}


//==============================================================================
bool LemonSqueezyCompressorVSTAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* LemonSqueezyCompressorVSTAudioProcessor::createEditor()
{
    return new LemonSqueezyCompressorVSTAudioProcessorEditor(*this);
}



//==============================================================================
void LemonSqueezyCompressorVSTAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, true);
    parameters.state.writeToStream(stream);
}

void LemonSqueezyCompressorVSTAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto state = juce::ValueTree::readFromData(data, sizeInBytes);
    if (state.isValid())
        parameters.state = state;
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LemonSqueezyCompressorVSTAudioProcessor();
}
