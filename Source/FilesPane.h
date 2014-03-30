/*
  ==============================================================================

    FilesPane.h
    Created: 29 Mar 2014 8:17:56am
    Author:  goodwin

  ==============================================================================
*/

#ifndef FILESPANE_H_INCLUDED
#define FILESPANE_H_INCLUDED

#include "SamplesModel.h"

//==============================================================================
/*
*/
class FilesPane : public Component, public SamplesModel::Listener
{
public:
    FilesPane();
    virtual ~FilesPane();

    void resized() override;
	void selectionChanged(const File &file);
	void updateRow(int row) override;
	void selectedSample(SampleModel *sample) override;

private:
	SamplesModel model;
	TableListBox filesList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilesPane)
};


#endif  // FILESPANE_H_INCLUDED
