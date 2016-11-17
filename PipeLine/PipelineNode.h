#pragma once

#include <string>

using namespace std;

//each node is a stage in the pipeline
class PipelineNode
{
	string name;
	int stage;//is this needed?
	string desc;
	string advancementQuestion; //ask this question to see if we should goto next node

	PipelineNode *left;
	PipelineNode *right;
public:
	PipelineNode()
	{
		name = "";
		stage = 0;
		desc = "";
		advancementQuestion = "";

		left = NULL;
		right = NULL;
	}
	void SetStage(int s) { stage = s; }
	void SetName(string n) { name = n; }
	void SetDesc(string d) { desc = d; }
	void SetAdvancementQuestion(string q) {
		advancementQuestion = q;
	}
	int GetStage() { return stage; }
	string GetName() { return name; }
	string GetDesc() { return desc; }
	string GetAdvancementQuestion() {
		return advancementQuestion;
	}

	void SetLeftNode(PipelineNode *l) { left = l; }
	void SetRightNode(PipelineNode *r) { right = r; }
	void SetNextNode(PipelineNode *n) { right = n; }
	
	PipelineNode * GetLeftNode() { return left; }
	PipelineNode * GetRightNode() { return right; }
	PipelineNode * GetNextNode() { return right; }
};