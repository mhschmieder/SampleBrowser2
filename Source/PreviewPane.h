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
class PreviewPane    : public Component
{
public:
    PreviewPane(AudioFormatManager &formatManager, AudioTransportSource &transportSource);
    virtual ~PreviewPane();

    void resized() override;

private:
	ThumbnailComponent preview;
	TextButton playButton;
	TextButton stopButton;
	Slider zoomSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreviewPane)
};


#endif  // PREVIEWPANE_H_INCLUDED
