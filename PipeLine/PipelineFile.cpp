#include "PipelineFile.h"
#include <fstream>      // std::fstream
#include <iostream>
#include "StringUtils.h"

PipelineFile::PipelineFile()
{
	pipelineName = "";
}
PipelineFile::PipelineFile(string filename)
{
	pipelineName = "";
	ParseFile(filename);
}
bool PipelineFile::ParseFile(string filename)
{

	fstream fs;
	fs.open(filename);
	if (!fs.is_open())
		return false;
	string line;

	PipelineNode *curNode = NULL;
	PipelineNode *prevNode = NULL;

	int stage = 1;
	int lineNum = 0;

	while (getline(fs, line))
	{
		lineNum++;
		if (lineNum == 1)
		{
			if (line != "pipelineFile")
			{
				cout << "pipeline file format error on line "<<lineNum<<endl;
				cout << "the file doesnt have correct header \n";
				return false;
			}
			continue;
		}
		else if (lineNum == 2)
		{
			vector <string> nameTokens = StringUtils::Tokenize(line, "=");
			if (nameTokens.size() != 2)
			{
				cout << "pipeline file format error on line " << lineNum << endl;
				cout << "name of pipeline is not correct! should 'name=<title>'\n";
				return false;
			}

			pipelineName = nameTokens[1];
			continue;
		}
		vector <string> tokens = StringUtils::Tokenize(line, ",");
		curNode = new PipelineNode();
		curNode->SetStage(stage);
		curNode->SetName(tokens[0]);
		curNode->SetDesc(tokens[1]);
		curNode->SetAdvancementQuestion(tokens[2]);
		//how to set next nodes, when they dont exsit yet?
		if (tokens.size() > 3)//we have next nodes that arent in order
		{

		}
		//this should only  be true when we ar on the first node, aka the head of list
		if (prevNode == NULL)
		{
			pipelineHead = curNode;
		}
		else
			prevNode->SetNextNode(curNode);

		prevNode = curNode;
		stage++;
	}
	fs.close();

	if (curNode == NULL || lineNum < 3)
	{
		cout << "pipeline file format error on line " << lineNum << endl;
		cout << "no pipeline stages are defined or defined improperly!";
		return false;
	}
	maxStage = stage;
	
	
	return true;
}


void PipelineFile::DisplayPipeline()
{
	PipelineNode *runner = pipelineHead;
	int stage = 1;
	while (runner != NULL)
	{
		cout <<stage << ") " << runner->GetName() << "-> " << runner->GetDesc() <<endl;
		stage++;
		runner = runner->GetNextNode();
	}
}
	
PipelineNode * PipelineFile::GetStageNode(int stage)
{
	PipelineNode *runner = pipelineHead;
	int cur = 0;
	while (runner != NULL)
	{
		if(cur == stage)
			return runner;
		cur++;
		runner = runner->GetNextNode();
	}
}

