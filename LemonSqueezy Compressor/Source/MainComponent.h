#pragma once

#include <JuceHeader.h>
#include "KnobLookAndFeel.h" 

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Slider slider;
    juce::Slider slider2;
    std::unique_ptr<KnobLookAndFeel> knobLarge1;
    std::unique_ptr<KnobLookAndFeel> knobLarge2;
    juce::Image backgroundImage;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
