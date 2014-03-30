#ifndef _SAMPLESMODEL_H
#define _SAMPLESMODEL_H

#include "SampleModel.h"

class SamplesModel : public TableListBoxModel, public Thread
{
public:
	enum Columns
	{
		name = 1,
		sampleRate,
		channels,
		bits,
		size
	};

	class Listener
	{
	public:
		virtual void updateRow(int row) = 0;
		virtual void selectedSample(SampleModel *sample) = 0;
	};

	SamplesModel();

	int getNumRows() override { return samples.size(); }
	void paintRowBackground(Graphics &g, int row, int width, int height, bool selected) override;
	void paintCell(Graphics &g, int row, int id, int width, int height, bool selected) override;
	void selectedRowsChanged(int row) override;

	void run() override;

	void clear();
	void addSample(SampleModel *sample);
	void startScanning();

	void addListener(Listener *listener);

private:
	OwnedArray<SampleModel> samples;
	Array<Listener *> listeners;

	void notifyListeners(int row);
	void notifyListeners(SampleModel *sample);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplesModel)
};

#endif // _SAMPLESMODEL_H
