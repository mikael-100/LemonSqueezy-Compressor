#pragma once

#include <JuceHeader.h>

class KnobLookAndFeel;

class MyPluginGuiCode : public juce::Component,
    public juce::Slider::Listener
{
public:
    MyPluginGuiCode();
    ~MyPluginGuiCode() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

    juce::Slider slider;   // input
    juce::Slider slider2;  // output
    juce::Slider slider3;  // attack
    juce::Slider slider4;  // release


private:
                 
 

    juce::Image backgroundImage;
    juce::Image imgS, imgM, imgL, currentImage;

    std::unique_ptr<KnobLookAndFeel> knobLarge1;
    std::unique_ptr<KnobLookAndFeel> knobLarge2;
    std::unique_ptr<KnobLookAndFeel> knobSmall1;
    std::unique_ptr<KnobLookAndFeel> knobSmall2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyPluginGuiCode)
};
