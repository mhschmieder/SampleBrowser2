#include "SamplesModel.h"

SamplesModel::SamplesModel() : Thread("sample file reader")
{

}

void SamplesModel::paintRowBackground(Graphics &g, int row, int width, int height, bool selected)
{
	if (selected)
	{
		g.setColour(Colours::lightblue);
		g.fillRect(0, 0, width, height);
	}
	else
	{
		if (row % 2 == 1)
		{
			g.setColour(Colours::aliceblue);
			g.fillRect(0, 0, width, height);
		}
	}
}

void SamplesModel::paintCell(Graphics &g, int row, int id, int width, int height, bool)
{
	String text;
	SampleModel *sample = samples[row];
	if (sample)
	{
		switch (id)
		{
		case name:
			text = sample->getName();
			break;

		case sampleRate:
			text = String(sample->getSampleRate());
			break;

		case channels:
			text = String(sample->getChannels());
			break;

		case bits:
			text = String(sample->getBits());
			break;

		case size:
			text = String(sample->getSize());
			break;
		}
		g.setColour(Colours::black);
		g.drawText(text, 2, 2, width - 4, height - 4, Justification::left, true);
	}
}

void SamplesModel::run()
{
	for (int i = 0; i < samples.size(); i++)
	{
		if (!isThreadRunning())
			return;

		SampleModel *sample = samples[i];
		File file(sample->getFilename());
		FileInputStream *stream = new FileInputStream(file);
		WavAudioFormat format;
		ScopedPointer<AudioFormatReader> reader = format.createReaderFor(stream, false);
		if (reader)
		{
			sample->setSampleRate((int)reader->sampleRate);
			sample->setChannels(reader->numChannels);
			sample->setBits(reader->bitsPerSample);
			sample->setSize((int)reader->lengthInSamples);

			notifyListeners(i);
		}
	}
}

void SamplesModel::clear()
{
	stopThread(300);
	samples.clear();
}

void SamplesModel::addSample(SampleModel *sample)
{
	samples.add(sample);
}

void SamplesModel::startScanning()
{
	startThread();
}

void SamplesModel::addListener(Listener *listener)
{
	listeners.add(listener);
}

void SamplesModel::notifyListeners(int row)
{
	const MessageManagerLock lock;

	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->updateRow(row);
	}
}

void SamplesModel::notifyListeners(SampleModel *sample)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->selectedSample(sample);
	}
}

void SamplesModel::selectedRowsChanged(int row)
{
	if (row != -1)
	{
		SampleModel *sample = samples[row];
		notifyListeners(sample);
	}
}