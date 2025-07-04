#include "KnobLookAndFeel.h"

KnobLookAndFeel::KnobLookAndFeel(juce::Image image)
    : knobImage(image)
{
}

void KnobLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional,
    float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    auto centerX = x + width * 0.5f;
    auto centerY = y + height * 0.5f;

    if (knobImage.isValid())
    {
        g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);

        float imgWidth = (float)knobImage.getWidth();
        float imgHeight = (float)knobImage.getHeight();

        juce::AffineTransform t =
            juce::AffineTransform::rotation(angle, imgWidth * 0.5f, imgHeight * 0.5f)
            .translated(centerX - imgWidth * 0.5f, centerY - imgHeight * 0.5f);

        g.drawImageTransformed(knobImage, t);
    }
}
