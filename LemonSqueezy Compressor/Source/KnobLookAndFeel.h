/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 20 Apr 2025 11:32:16pm
    Author:  Mike

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

class KnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel(juce::Image image);

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle,
        juce::Slider& slider) override;

private:
    juce::Image knobImage;
};