/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyPluginGuiCode.h"

//==============================================================================
LemonSqueezyCompressorVSTAudioProcessorEditor::LemonSqueezyCompressorVSTAudioProcessorEditor(LemonSqueezyCompressorVSTAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    addAndMakeVisible(myGui);
    setSize(615, 332);

    // slider = threshold (used for both threshold and ratio in processor logic)
    thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "threshold", myGui.slider);

    // slider2 = outputGain
    outputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "outputGain", myGui.slider2);

    // slider3 = attack
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "attack", myGui.slider3);

    // slider4 = release
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "release", myGui.slider4);
}

LemonSqueezyCompressorVSTAudioProcessorEditor::~LemonSqueezyCompressorVSTAudioProcessorEditor()
{
}

//==============================================================================
void LemonSqueezyCompressorVSTAudioProcessorEditor::paint(juce::Graphics& g)
{
    // All visual painting handled in MyPluginGuiCode
}

void LemonSqueezyCompressorVSTAudioProcessorEditor::resized()
{
    myGui.setBounds(getLocalBounds());
}
