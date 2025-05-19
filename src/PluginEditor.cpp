#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    juce::File fontFile ("/home/aleksei-klopot/Fonts/MiriamLibre-VariableFont_wght.ttf");

    setSize (300, 600);
    if (fontFile.existsAsFile())
    {
        juce::MemoryBlock fontData;
        fontFile.loadFileAsData(fontData);
        auto typeface = juce::Typeface::createSystemTypefaceFor(fontData.getData(), fontData.getSize());
        juce::Font customFont(juce::FontOptions()
                                  .withTypeface(typeface)
                                  .withHeight(60.0f));

        titleLabel.setText("Aligain", juce::dontSendNotification);
        titleLabel.setFont(customFont);
        titleLabel.setJustificationType(juce::Justification::centred);
        titleLabel.setLookAndFeel(&defaultLookAndFeel);
        addAndMakeVisible(titleLabel);
    }



    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    // gainSlider.setRange(-48, 15);
    // gainSlider.setValue(0.0);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    // gainSlider.addListener(this);
    gainSlider.setLookAndFeel(&defaultLookAndFeel);
    // gainSlider.setNumDecimalPlacesToDisplay(2); //???
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider);
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.parameters, "gain", gainSlider);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    gainSlider.setLookAndFeel(nullptr);
}

//==============================================================================

void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient gradient(
        juce::Colour::fromRGB(252, 252, 252),
        getWidth() / 2.0f, 0.0f,
        juce::Colour::fromRGB(159, 160, 162),
        getWidth() / 2.0f, getHeight(),
        false
        );
    g.setGradientFill(gradient);
    g.fillAll();

}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto labelArea = area.removeFromTop(area.getHeight() / 5);
    titleLabel.setBounds(labelArea);
    gainSlider.setBounds(area.reduced(60));
}

// void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
// {
//     if (slider == &gainSlider)
//     {
//         processorRef.rawVolume = pow(10, gainSlider.getValue() / 20);
//     }
// }
