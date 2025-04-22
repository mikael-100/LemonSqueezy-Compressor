#include "MainComponent.h"
#include "KnobLookAndFeel.h" 

//==============================================================================
MainComponent::MainComponent()
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::BG_png, BinaryData::BG_pngSize);
    setSize(615.25, 332);

    // Large Knob 1 (INPUT)
    juce::Image largeKnob1 = juce::ImageCache::getFromMemory(BinaryData::BL1_png, BinaryData::BL1_pngSize);
    juce::Image bl1 = largeKnob1.rescaled(130, 130); // 👈 Skala PNG:n


    knobLarge1 = std::make_unique<KnobLookAndFeel>(bl1);
    slider.setLookAndFeel(knobLarge1.get());
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider.setRange(-1.0, 1.0, 0.05); // eller -100 till 100, beroende på vad du styr
    slider.setValue(0.0); // mitten
  


    slider.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f, // ≈ 225° → Start längst ner till vänster
        juce::MathConstants<float>::pi * 2.75f, // ≈ 495° → Slut längst ner till höger
        true
    );

    addAndMakeVisible(slider);

    // Large Knob 2 (OUTPUT)

    juce::Image largeKnob2 = juce::ImageCache::getFromMemory(BinaryData::BL2_png, BinaryData::BL2_pngSize);
    juce::Image bl2 = largeKnob2.rescaled(130, 130);

    knobLarge2 = std::make_unique<KnobLookAndFeel>(bl2);
    slider2.setLookAndFeel(knobLarge2.get());
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider2.setRange(-1.0, 1.0, 0.05); // eller -100 till 100, beroende på vad du styr
    slider2.setValue(0.0); // mitten
    slider2.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f, // ≈ 225° → Start längst ner till vänster
        juce::MathConstants<float>::pi * 2.75f, // ≈ 495° → Slut längst ner till höger
        true
    );
    addAndMakeVisible(slider2);

    // Small Knob 1 (ATTACK)

    juce::Image smallKnob1 = juce::ImageCache::getFromMemory(BinaryData::BS1_png, BinaryData::BS1_pngSize);
    juce::Image bs1 = smallKnob1.rescaled(55, 55);

    knobSmall1 = std::make_unique<KnobLookAndFeel>(bs1);
    slider3.setLookAndFeel(knobSmall1.get());
    slider3.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider3.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider3.setRange(-1.0, 1.0, 0.05); // eller -100 till 100, beroende på vad du styr
    slider3.setValue(0.0); // mitten
    slider3.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f, // ≈ 225° → Start längst ner till vänster
        juce::MathConstants<float>::pi * 2.75f, // ≈ 495° → Slut längst ner till höger
        true
    );
    addAndMakeVisible(slider3);

    // Small Knob 2 (RELEASE)

    juce::Image smallKnob2 = juce::ImageCache::getFromMemory(BinaryData::BS2_png, BinaryData::BS2_pngSize);
    juce::Image bs2 = smallKnob2.rescaled(55, 55);

    knobSmall2 = std::make_unique<KnobLookAndFeel>(bs2);
    slider4.setLookAndFeel(knobSmall2.get());
    slider4.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider4.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
    slider4.setRange(-1.0, 1.0, 0.05); // eller -100 till 100, beroende på vad du styr
    slider4.setValue(0.0); // mitten
    slider4.setRotaryParameters(
        juce::MathConstants<float>::pi * 1.25f, // ≈ 225° → Start längst ner till vänster
        juce::MathConstants<float>::pi * 2.75f, // ≈ 495° → Slut längst ner till höger
        true
    );
    addAndMakeVisible(slider4);

    // Lemon Switch

    imgS = juce::ImageCache::getFromMemory(BinaryData::C1_png, BinaryData::C1_pngSize);
    imgM = juce::ImageCache::getFromMemory(BinaryData::C2_png, BinaryData::C2_pngSize);
    imgL = juce::ImageCache::getFromMemory(BinaryData::C3_png, BinaryData::C3_pngSize);

    currentImage = imgS;

    slider.addListener(this);

    
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

    // Paint Lemon depending on Slider Rita
    if (currentImage.isValid())
    {
        g.drawImage(currentImage,
            455, 70, 170, 170,  // Anpassa position/storlek som du vill
            0, 0, currentImage.getWidth(), currentImage.getHeight());
    }
}


void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    slider.setBounds(80, 95, 130, 130); // Anpassa efter ditt GUI
    slider2.setBounds(255, 95, 130, 130);
    slider3.setBounds(412, 90, 55, 55);
    slider4.setBounds(412, 180, 55, 55);

}

void MainComponent::sliderValueChanged(juce::Slider* s)
{
    if (s == &slider) 
    {
        float val = slider.getValue();

        if (val < -0.33f)
            currentImage = imgS;
        else if (val < 0.33f)
            currentImage = imgM;
        else
            currentImage = imgL;

        repaint();
    }
}
