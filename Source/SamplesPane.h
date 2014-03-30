/*
  ==============================================================================

    SamplesPane.h
    Created: 29 Mar 2014 8:20:15am
    Author:  goodwin

  ==============================================================================
*/

#ifndef SAMPLESPANE_H_INCLUDED
#define SAMPLESPANE_H_INCLUDED

#include "FilesPane.h"
#include "PreviewPane.h"

//==============================================================================
/*
*/
class SamplesPane : public Component
{
public:
	SamplesPane(AudioFormatManager &formatManager, AudioTransportSource &transportSource);
    virtual ~SamplesPane();

    void resized() override;

	void selectionChanged(const File &file);

private:
	StretchableLayoutManager layout;
	FilesPane filesPane;
	StretchableLayoutResizerBar resizer;
	PreviewPane previewPane;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplesPane)
};


#endif  // SAMPLESPANE_H_INCLUDED
