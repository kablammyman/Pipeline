#pragma once

#include <vector>
#include <string>

#include "PipelineFile.h"
#include "PipelineItem.h"

using namespace std;

class PipelineManager
{
	vector<PipelineFile *> pipelines;
	vector<PipelineItem *> pipelinesItems;
	bool LinkItemToPipeline(PipelineItem *item);
public:
	PipelineManager(string cfgPath="");
	
	PipelineFile * LoadPipeline(string filepath);//loads a pipeline from disk
	PipelineItem * LoadPipelineItem(string filepath);

	
	void CreatePipeline(string name);//creates a new pipeline
	void CreatePipelineItem(string name);

	void DeletePipeline(string name);
	void RemovePipelineStage(string name, int stage);//remove  steps
	void EditPipelineStage(string name, int stage);// edit steps
	int CountStagesDueToday();//goes thoe each pipeline item, and see whats due today
};