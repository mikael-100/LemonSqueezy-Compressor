#include "MainComponent.h"
#include "KnobLookAndFeel.h" 

//==============================================================================
MainComponent::MainComponent()
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::BG_png, BinaryData::BG_pngSize);
    setSize(615.25, 332);

    juce::Image original = juce::ImageCache::getFromMemory(BinaryData::BL1_png, BinaryData::BL1_pngSize);
    juce::Image scaled = original.rescaled(130, 130); // 👈 Skala PNG:n
    knobLookAndFeel = std::make_unique<KnobLookAndFeel>(scaled);

    slider.setLookAndFeel(knobLookAndFeel.get());
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider.setRotaryParameters(
        juce::MathConstants<float>::pi * -0.0f, // Start = -90 grader (rakt upp)
        juce::MathConstants<float>::pi * 1.0f,  // Slut = +270 grader (ett helt varv)
        true
    );

    addAndMakeVisible(slider);

    
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
}
