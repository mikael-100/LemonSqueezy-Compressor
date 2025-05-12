/*
  ==============================================================================

    MyPluginGuiCode.h
    Created: 12 May 2025 12:41:09pm
    Author:  Mike

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "KnobLookAndFeel.h" 


class MyPluginGuiCode : public juce::Component,
    public juce::Slider::Listener
{

public:
    //==============================================================================
    MyPluginGuiCode();
    ~MyPluginGuiCode() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Slider slider;
    juce::Slider slider2;
    juce::Slider slider3;
    juce::Slider slider4;
    std::unique_ptr<KnobLookAndFeel> knobLarge1;
    std::unique_ptr<KnobLookAndFeel> knobLarge2;
    std::unique_ptr<KnobLookAndFeel> knobSmall1;
    std::unique_ptr<KnobLookAndFeel> knobSmall2;
    juce::Image backgroundImage;

    // Changeing Lemons
    juce::Image imgS, imgM, imgL;
    juce::Image currentImage;

    void sliderValueChanged(juce::Slider* slider) override;




    // Sets start value for DB
    float outputGainDb = 0.0f;

    // Making a instans of juce Compressor Class
    juce::dsp::Compressor<float> compressor;





    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyPluginGuiCode)
};
