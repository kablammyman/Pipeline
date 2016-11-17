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


#include "PipelineManager.h"

int main(int argc, char *argv[])
{
	PipelineManager manager("D:\\source\\pipelinecfg.txt");


	return 0;
}

