/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "DirectoryPane.h"
#include "SamplesPane.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component, public DirectoryPane::Listener
{
public:
    //==============================================================================
    MainComponent();
    virtual ~MainComponent();

    void resized() override;
	void selectionChanged(const File &file) override;

private:
	LookAndFeel_V3 lookAndFeel;

	AudioFormatManager formatManager;
	AudioTransportSource transportSource;

	StretchableLayoutManager layout;
	DirectoryPane directoryPane;
	StretchableLayoutResizerBar resizer;
	SamplesPane samplesPane;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
