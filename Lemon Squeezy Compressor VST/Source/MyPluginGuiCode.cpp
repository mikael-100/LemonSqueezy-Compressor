#include "MyPluginGuiCode.h"
#include "KnobLookAndFeel.h"
#include <JuceHeader.h>

MyPluginGuiCode::MyPluginGuiCode()
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::BGG_png, BinaryData::BGG_pngSize);
    setSize(615, 332);

    // INPUT (slider1) - ska anva SMALL BS1
    juce::Image bl1 = juce::ImageCache::getFromMemory(BinaryData::BS1_png, BinaryData::BS1_pngSize);
    knobLarge1 = std::make_unique<KnobLookAndFeel>(bl1);
    slider.setLookAndFeel(knobLarge1.get());
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider.setRange(-1.0, 1.0, 0.05);
    slider.setValue(0.0);
    slider.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f,
        true
    );
    slider.addListener(this);
    addAndMakeVisible(slider);

    // OUTPUT (slider2) - ska anvnda SMALL BS2
    juce::Image bl2 = juce::ImageCache::getFromMemory(BinaryData::BS2_png, BinaryData::BS2_pngSize);
    knobLarge2 = std::make_unique<KnobLookAndFeel>(bl2);
    slider2.setLookAndFeel(knobLarge2.get());
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider2.setRange(-1.0, 1.0, 0.05);
    slider2.setValue(0.0);
    slider2.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f,
        true
    );
    addAndMakeVisible(slider2);

    // ATTACK (slider3) - ska anvnda LARGE BL1
    juce::Image smallKnob1 = juce::ImageCache::getFromMemory(BinaryData::BL1_png, BinaryData::BL1_pngSize);
    knobSmall1 = std::make_unique<KnobLookAndFeel>(smallKnob1);
    slider3.setLookAndFeel(knobSmall1.get());
    slider3.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider3.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider3.setRange(-1.0, 1.0, 0.05);
    slider3.setValue(0.0);
    slider3.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f,
        true
    );
    addAndMakeVisible(slider3);

    // RELEASE (slider4) - ska anvnda LARGE BL2
    juce::Image smallKnob2 = juce::ImageCache::getFromMemory(BinaryData::BL2_png, BinaryData::BL2_pngSize);
    knobSmall2 = std::make_unique<KnobLookAndFeel>(smallKnob2);
    slider4.setLookAndFeel(knobSmall2.get());
    slider4.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider4.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider4.setRange(-1.0, 1.0, 0.05);
    slider4.setValue(0.0);
    slider4.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f,
        true
    );
    addAndMakeVisible(slider4);

    // Lemon animation
    imgS = juce::ImageCache::getFromMemory(BinaryData::C1_png, BinaryData::C1_pngSize);
    imgM = juce::ImageCache::getFromMemory(BinaryData::C2_png, BinaryData::C2_pngSize);
    imgL = juce::ImageCache::getFromMemory(BinaryData::C3_png, BinaryData::C3_pngSize);
    currentImage = imgS;
}

MyPluginGuiCode::~MyPluginGuiCode()
{
    slider.removeListener(this);
    slider2.removeListener(this);
    slider3.removeListener(this);
    slider4.removeListener(this);

    slider.setLookAndFeel(nullptr);
    slider2.setLookAndFeel(nullptr);
    slider3.setLookAndFeel(nullptr);
    slider4.setLookAndFeel(nullptr);
}

void MyPluginGuiCode::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);

    if (backgroundImage.isValid())
        g.drawImage(backgroundImage, getLocalBounds().toFloat());

    if (currentImage.isValid())
        g.drawImage(currentImage, 455, 70, 170, 170, 0, 0, currentImage.getWidth(), currentImage.getHeight());
}

void MyPluginGuiCode::resized()
{
    slider.setBounds(80, 95, 130, 130);
    slider2.setBounds(255, 95, 130, 130);
    slider3.setBounds(412, 90, 55, 55);
    slider4.setBounds(412, 180, 55, 55);
}

void MyPluginGuiCode::sliderValueChanged(juce::Slider* s)
{
    if (s == &slider)
    {
        float inputValue = s->getValue();

        if (inputValue < -0.33f)
            currentImage = imgS;
        else if (inputValue < 0.33f)
            currentImage = imgM;
        else
            currentImage = imgL;

        repaint();
    }
}
