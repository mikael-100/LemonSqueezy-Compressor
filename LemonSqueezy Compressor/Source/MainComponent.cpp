#include "MainComponent.h"
#include "KnobLookAndFeel.h" 

//==============================================================================
MainComponent::MainComponent()
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::BG_png, BinaryData::BG_pngSize);
    setSize(615.25, 332);

    // Large Knob 1
    juce::Image largeKnob1 = juce::ImageCache::getFromMemory(BinaryData::BL1_png, BinaryData::BL1_pngSize);
    juce::Image bl1 = largeKnob1.rescaled(130, 130); // 👈 Skala PNG:n


    knobLarge1 = std::make_unique<KnobLookAndFeel>(bl1);
    slider.setLookAndFeel(knobLarge1.get());
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider.setRotaryParameters(
        juce::MathConstants<float>::pi * -0.0f, // Start = -90 grader (rakt upp)
        juce::MathConstants<float>::pi * 1.0f,  // Slut = +270 grader (ett helt varv)
        true
    );

    addAndMakeVisible(slider);

    // Large Knob 2

    juce::Image largeKnob2 = juce::ImageCache::getFromMemory(BinaryData::BL2_png, BinaryData::BL2_pngSize);
    juce::Image bl2 = largeKnob2.rescaled(130, 130);

    knobLarge2 = std::make_unique<KnobLookAndFeel>(bl2);
    slider2.setLookAndFeel(knobLarge2.get());
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider2.setRotaryParameters(
        juce::MathConstants<float>::pi * -0.0f,
        juce::MathConstants<float>::pi * -1.0f,
        true
    );
    addAndMakeVisible(slider2);
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black); // Valfri bakgrundsfärg om bilden inte laddas

    if (backgroundImage.isValid())
    {
        // Rita bilden så att den fyller hela komponenten
        g.drawImage(backgroundImage,
            getLocalBounds().toFloat()); // Skalar automatiskt bilden till att fylla fönstret
    }
}


void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    slider.setBounds(80, 95, 130, 130); // Anpassa efter ditt GUI
    slider2.setBounds(255, 95, 130, 130);

}
