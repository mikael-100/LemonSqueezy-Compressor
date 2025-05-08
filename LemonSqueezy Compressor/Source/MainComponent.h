#pragma once

#include <JuceHeader.h>
#include "KnobLookAndFeel.h" 




//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
/*
class MainComponent  : public juce::AudioAppComponent, 
                       public juce::Slider::Listener
{
*/

class MainComponent : public juce::Component,
    public juce::Slider::Listener
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

    /*
    // Audio playback
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::FileChooser> fileChooser;



    juce::TextButton loadButton { "Load Audio" };
    juce::TextButton playButton { "Play" };
    juce::TextButton stopButton { "Stop" }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    */


    // Sets start value for DB
    float outputGainDb = 0.0f;

    // Making a instans of juce Compressor Class
    juce::dsp::Compressor<float> compressor;




    



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
