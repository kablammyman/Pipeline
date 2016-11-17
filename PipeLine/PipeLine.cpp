// DataBaseBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <windows.h>
#include <stdio.h>

#include <vector>


#include "CommandLineUtils.h"
#include "CFGUtils.h"

#include "LogMessage.h"
#include "ConsoleOutput.h"
#include "LogfileOutput.h"

#include "PipelineFile.h"
#include "PipelineItem.h"


int main(int argc, char *argv[])
{
	//vector<PipelineNode *> pipelines;
	PipelineFile file;
	file.ParseFile("D:\\source\\test.txt");
	file.DisplayPipeline();

	PipelineItem item("some owner",&file);
	item.SetPipelineStage(1);
	item.AddStageNotes(2, "he wants to sell");
	item.AddStageNotes(1,"what will this do?\n");
	item.GetCurrentStageInfo();
	item.WriteItemToFile("D:\\source\\");

	return 0;
}

