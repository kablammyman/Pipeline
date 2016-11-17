#pragma once
#include <string>
#include <vector>
#include "PipelineNode.h"
#include "PipelineFile.h"
using namespace std;
//each item is something that is going thru the pipeline
//ex tracking the progress of buying a parcel is an item
class PipelineItem
{
	string name; //the name if this item...ex the parcel name, or the employee id 
	string pipelineName;//needed to help couple it to pipeline whenloading from disk
	int curStage;
	//some details that needed to be saved, like sellers name, address, email and phone, as well as special instructions
	string basicInfo;
	vector <string> stageNotes;//the ability to add notes per stage. the stage-1 is the index
	vector <string> stageDueDate;//the ability to add notes per stage. the stage-1 is the index
	PipelineFile *pipeline;
public:
	PipelineItem(string n, PipelineFile *p);//use to create pipeline item
	PipelineItem(string path);//use toread pre existing item
	
	void SetBasicInfo(string info) { basicInfo = info; }
	void SetPipelineStage(int s) {curStage = s;}
	void SetPipeline(PipelineFile *p) { pipeline = p; }
	
	void AddStageNotes(int index, string note);
	void GetCurrentStageInfo();
	bool ReadItemFromFile(string filePath);
	void WriteItemToFile(string filePath);
	string GetPipelineName() { return pipelineName; }
};