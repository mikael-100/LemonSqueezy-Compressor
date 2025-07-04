#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyPluginGuiCode.h"

//==============================================================================
class LemonSqueezyCompressorVSTAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    LemonSqueezyCompressorVSTAudioProcessorEditor(LemonSqueezyCompressorVSTAudioProcessor&);
    ~LemonSqueezyCompressorVSTAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    LemonSqueezyCompressorVSTAudioProcessor& audioProcessor;

    MyPluginGuiCode myGui;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LemonSqueezyCompressorVSTAudioProcessorEditor)
};
