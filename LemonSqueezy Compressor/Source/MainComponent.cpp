#include <JuceHeader.h>
#include "MainComponent.h"
#include "KnobLookAndFeel.h"

//==============================================================================

MainComponent::MainComponent()
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::BG_png, BinaryData::BG_pngSize);
    setSize(615, 332); 

    // Large Knob 1 (INPUT)
    juce::Image bl1 = juce::ImageCache::getFromMemory(BinaryData::BL1_png, BinaryData::BL1_pngSize)
        .rescaled(130, 130);

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
    addAndMakeVisible(slider);

    // Large Knob 2 (OUTPUT)
    juce::Image bl2 = juce::ImageCache::getFromMemory(BinaryData::BL2_png, BinaryData::BL2_pngSize)
        .rescaled(130, 130);

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

    // Small Knob 1 (ATTACK)
    juce::Image smallKnob1 = juce::ImageCache::getFromMemory(BinaryData::BS1_png, BinaryData::BS1_pngSize)
        .rescaled(55, 55);

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

    // Small Knob 2 (RELEASE)
    juce::Image smallKnob2 = juce::ImageCache::getFromMemory(BinaryData::BS2_png, BinaryData::BS2_pngSize)
        .rescaled(55, 55);

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

   
    slider3.addListener(this);
    slider4.addListener(this);


    // Lemon Switch
    imgS = juce::ImageCache::getFromMemory(BinaryData::C1_png, BinaryData::C1_pngSize);
    imgM = juce::ImageCache::getFromMemory(BinaryData::C2_png, BinaryData::C2_pngSize);
    imgL = juce::ImageCache::getFromMemory(BinaryData::C3_png, BinaryData::C3_pngSize);

    currentImage = imgS;

    slider.addListener(this);
    slider2.addListener(this);

    /*
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);

    formatManager.registerBasicFormats();

    loadButton.onClick = [this]()
    {
        if (fileChooser == nullptr)
        {
            fileChooser = std::make_unique<juce::FileChooser>(
                "Valj en ljudfil...",
                juce::File{},
                formatManager.getWildcardForAllFormats()
            );
        }

        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (!file.existsAsFile())
                {
                    DBG("No file choosen!");
                    return;
                }

                if (auto* reader = formatManager.createReaderFor(file))
                {
                    transportSource.stop();
                    transportSource.setSource(nullptr);

                    auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
                    transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
                    readerSource = std::move(newSource);

                    DBG("Loaded: " + file.getFileName());
                }
                else
                {
                    DBG("Coulden create reder for file: " + file.getFullPathName());
                }
            });
    };

    setAudioChannels(0, 2);

    playButton.onClick = [this]()
    {
        if (readerSource.get() != nullptr)
        {
            if (transportSource.getCurrentPosition() >= transportSource.getLengthInSeconds())
            {
                transportSource.setPosition(0.0);
            }
            transportSource.start();
            DBG("Start Playing");
        }
        else
        {
            DBG("No audio uploaded");
        }
    };

    stopButton.onClick = [this]()
    {
        transportSource.stop();
        DBG("Stop playing");
    };
    */
}

MainComponent::~MainComponent()
{
    slider.setLookAndFeel(nullptr);
    slider2.setLookAndFeel(nullptr);
    slider3.setLookAndFeel(nullptr);
    slider4.setLookAndFeel(nullptr);

    /*
    shutdownAudio();
    */
}

/*
// Preparing the compressor with the sample rate and how big chunks it will contain 
// plus the default treshold and ratio settings
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlockExpected);
    spec.numChannels = 2; 

    compressor.prepare(spec);

    // Default settings on Treshold & Ratio
    compressor.setThreshold(-30.0f);  
    compressor.setRatio(6.0f);       
}

// Sending the audio file to the compressor in realtime
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() != nullptr)
    {
        //Sending the audio in sample box
        transportSource.getNextAudioBlock(bufferToFill);

        juce::dsp::AudioBlock<float> block(*bufferToFill.buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);

        compressor.process(context);

        float gainLinear = juce::Decibels::decibelsToGain(outputGainDb);
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            bufferToFill.buffer->applyGain(channel, bufferToFill.startSample, bufferToFill.numSamples, gainLinear);
        }
    }
    else
    {
        bufferToFill.clearActiveBufferRegion();
    }
}


void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}
*/

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    if (backgroundImage.isValid())
    {
        g.drawImage(backgroundImage, getLocalBounds().toFloat());
    }

    if (currentImage.isValid())
    {
        g.drawImage(currentImage,
            455, 70, 170, 170,
            0, 0, currentImage.getWidth(), currentImage.getHeight());
    }
}

void MainComponent::resized()
{
    slider.setBounds(80, 95, 130, 130);
    slider2.setBounds(255, 95, 130, 130);
    slider3.setBounds(412, 90, 55, 55); 
    slider4.setBounds(412, 180, 55, 55);

    /*
    loadButton.setBounds(10, 10, 100, 30);
    playButton.setBounds(120, 10, 100, 30);
    stopButton.setBounds(230, 10, 100, 30);
    */
}

void MainComponent::sliderValueChanged(juce::Slider* s)
{
    // Input s becomes slider (INPUT)
    if (s == &slider) 
    {
        float thresholdDb = juce::jmap<float>(s->getValue(), -1.0f, 1.0f, 0.0f, -60.0f);
        compressor.setThreshold(thresholdDb);

        float ratio = juce::jmap<float>(s->getValue(), -1.0f, 1.0f, 1.5f, 10.0f);
        compressor.setRatio(ratio);

        DBG("Treshold change to: " << thresholdDb << " dB");
        DBG("Ratio change to: " << ratio << ":1");

        // Changeing Lemon Images
        float inputValue = s->getValue();
        if (inputValue < -0.33f)
            currentImage = imgS;
        else if (inputValue < 0.33f)
            currentImage = imgM;
        else
            currentImage = imgL;

        repaint();
    }
    // Output Knob
    else if (s == &slider2)
    {
        outputGainDb = juce::jmap<float>(slider2.getValue(), -1.0f, 1.0f, -24.0f, 24.0f);
    }
    //Attack Knob
    else if (s == &slider3) 
    {
        float attackMs = juce::jmap<float>(slider3.getValue(), -1.0f, 1.0f, 5.0f, 100.0f);
        compressor.setAttack(attackMs);
        DBG("Attack ändrad till: " << attackMs << " ms");
    }
    // Release knob
    else if (s == &slider4)
    {
        float releaseMs = juce::jmap<float>(slider4.getValue(), -1.0f, 1.0f, 50.0f, 500.0f);
        compressor.setRelease(releaseMs);
        DBG("Release ändrad till: " << releaseMs << " ms");
    }

}
