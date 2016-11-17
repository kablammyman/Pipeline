#pragma once

#include <string>
#include <vector>

#include "PipelineNode.h"

using namespace std;


//the files that will define the pipeline
class PipelineFile
{
	int maxStage;
	string pipelineName;
	PipelineNode * pipelineHead;
public:
	PipelineFile();
	bool ParseFile(string filename);
	void DisplayPipeline();
	PipelineNode * GetStageNode(int stage);
	int GetMaxStages() { return maxStage; }
	string GetName() { return pipelineName; }
};

