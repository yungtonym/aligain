#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class AliLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AliLookAndFeel();
    ~AliLookAndFeel();

    void drawLinearSlider (juce::Graphics&, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          juce::Slider::SliderStyle, juce::Slider&) override;
private:
};

