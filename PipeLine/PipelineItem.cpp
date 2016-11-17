#include "PipelineItem.h"
#include "stringutils.h"

#include <iostream>
#include <fstream>
PipelineItem::PipelineItem(string n,PipelineFile *p)
{
	name = n; 
	curStage = 1;
	basicInfo = "";
	pipeline = p;
	for (int i = 0; i <pipeline->GetMaxStages(); i++)
		stageNotes.push_back("");//make sure we have a valid vector for later
}
void PipelineItem::AddStageNotes(int index, string note)
{
	stageNotes[index] = note;
}
void PipelineItem::GetCurrentStageInfo()
{
	PipelineNode *curItem = pipeline->GetStageNode(curStage);
	int stage = curItem->GetStage();
	cout << stage << ") " << curItem->GetName() << endl;
	cout << "notes: " << stageNotes[stage-1] <<endl;
}

void PipelineItem::WriteItemToFile(string filePath)
{
	ofstream myfile;
	string filename = filePath;
	
	if (filename.back() != '\\')
		filename.push_back('\\');
	filename.append(name + ".txt");

	myfile.open(filename);
	myfile << "pipelineItem\n";//the header
	myfile << "name:"<<name<<endl;
	myfile << "pipeline:" << pipeline->GetName() << endl;
	myfile << "stage:"<<curStage<<endl;
	myfile << "basic:" << basicInfo << endl;
	myfile << "notes:" << endl;

	for (int i = 0; i < stageNotes.size(); i++)
	{
		myfile << "stage"<<i+1<< ":"<< stageNotes[i]<< endl;
	}
	
	
	myfile.close();
}

void PipelineItem::ReadItemFromFile(string filePath)
{
	ofstream myfile;
	string filename = filePath;

	if (filename.back() != '\\')
		filename.push_back('\\');
	filename.append(name + ".txt");

	myfile.open(filename);
	myfile << "pipelineItem\n";//the header
	myfile << "name:" << name << endl;
	myfile << "pipeline:" << pipeline->GetName() << endl;
	myfile << "stage:" << curStage << endl;
	myfile << "basic:" << basicInfo << endl;
	myfile << "notes:" << endl;

	for (int i = 0; i < stageNotes.size(); i++)
	{
		myfile << "stage" << i + 1 << ":" << stageNotes[i] << endl;
	}


	myfile.close();
}
