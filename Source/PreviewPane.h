/*
  ==============================================================================

    PreviewPane.h
    Created: 29 Mar 2014 8:18:07am
    Author:  goodwin

  ==============================================================================
*/

#ifndef PREVIEWPANE_H_INCLUDED
#define PREVIEWPANE_H_INCLUDED

#include "ThumbnailComponent.h"

//==============================================================================
/*
*/
class PreviewPane : public Component, public Button::Listener, public Slider::Listener
{
public:
	PreviewPane(TimeSliceThread &theThread, AudioFormatManager &theFormatManager, AudioTransportSource &theTransportSource);
    virtual ~PreviewPane();

    void resized() override;
	void setSampleFile(const File &file);
	void buttonClicked(Button *button) override;
	void sliderValueChanged(Slider* slider) override;

private:
	TimeSliceThread &thread;
	AudioFormatManager &formatManager;
	AudioTransportSource &transportSource;
	ScopedPointer<AudioFormatReaderSource> current;
	ThumbnailComponent preview;
	TextButton playButton;
	TextButton stopButton;
	Slider zoomSlider;

	void playSample();
	void stopSample();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreviewPane)
};


#endif  // PREVIEWPANE_H_INCLUDED
