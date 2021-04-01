/*
  ==============================================================================

    FilesPane.cpp
    Created: 29 Mar 2014 8:17:56am
    Author:  goodwin

  ==============================================================================
*/

#include "FilesPane.h"

//==============================================================================
FilesPane::FilesPane()
{
	addAndMakeVisible(filesList);
	TableHeaderComponent *header = new TableHeaderComponent();
	header->addColumn("Name", SamplesModel::name, 150);
	header->addColumn("Sample Rate", SamplesModel::sampleRate, 90);
	header->addColumn("Channels", SamplesModel::channels, 70);
	header->addColumn("Bits", SamplesModel::bits, 70);
	header->addColumn("Size", SamplesModel::size, 90);
    filesList.setHeader(std::unique_ptr<TableHeaderComponent> (std::move(header)));
	filesList.setModel(&model);
	model.addListener(this);
}

FilesPane::~FilesPane()
{
}

void FilesPane::resized()
{
	filesList.setBounds(2, 2, getWidth() - 4, getHeight() - 4);
}

void FilesPane::selectionChanged(const File &file)
{
	model.clear();
	Array<File> files;
	file.findChildFiles(files, File::findFiles, false, "*.wav");
	for (int i = 0; i < files.size(); i++)
	{
		SampleModel *sample = new SampleModel(files[i].getFileNameWithoutExtension(), files[i].getFullPathName());
		model.addSample(sample);
	}
	filesList.updateContent();
	model.startScanning();
}

void FilesPane::updateRow(int row)
{
	filesList.repaintRow(row);
}

void FilesPane::selectedSample(SampleModel *sample)
{
	notifyListeners(sample);
}

void FilesPane::addListener(Listener *listener)
{
	listeners.add(listener);
}

void FilesPane::notifyListeners(SampleModel *sample)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->selectedSample(sample);
	}
}
