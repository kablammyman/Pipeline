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

PipelineItem::PipelineItem(string path)
{
	ReadItemFromFile(path);
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
	myfile << "basic:" << "\""<<basicInfo<<"\"" << endl;
	for (int i = 0; i < stageNotes.size(); i++)
	{
		myfile << "stage"<<i+1<< " notes:\""<< stageNotes[i]<<"\""<< endl;
	}
	
	
	myfile.close();
}

bool PipelineItem::ReadItemFromFile(string filename)
{
	fstream fs;
	fs.open(filename);

	if (!fs.is_open())
		return false;
	
	string line;
	pipelineName = "";
	string curData = "";
	
	int lineNum = 0;

	bool error = false;
	bool quoteOn = false;

	while (getline(fs, line))
	{
		lineNum++;
		if (lineNum == 1)
		{
			if (line != "pipelineItem")
			{
				cout << "pipeline item file format error on line " << lineNum << endl;
				cout << "the file doesnt have correct header \n";
				return false;
			}
			continue;
		}
		if (lineNum > 1 && lineNum < 6)
		{
			vector <string> tokens = StringUtils::Tokenize(line, ":");
			if (tokens.size() != 2)
			{
				cout << "pipeline item file format error on line " << lineNum << endl;
				error = true;
			}
			switch (lineNum)
			{
			case 2:
				if (error)
					cout << "pipeline item name is not correct! should 'name:<title>'\n";
				else
					name = tokens[1];
				break;
			case 3:
				if (error)
					cout << "name of pipeline is not correct! should 'pipeline:<item name>'\n";
				else
					pipelineName = tokens[1];
				break;
			case 4:
				if (error)
					cout << "pipeline stage is not correct! should 'pipeline:<int>'\n";
				else
					curStage = stoi(tokens[1]);
				break;
			case 5:
				if (error)
					cout << "basic info is not correct! should 'pipeline:<int>'\n";
				else
					basicInfo = tokens[1];
				break;
			}
			if (error)
				return false;
			continue;
		}

		else
		{
			//are we in the middle of grabbing data for some stage note?
			if (quoteOn)
			{
				size_t found = line.find_first_of("\"");
				//still grabbing data, no end on this line
				if (found == string::npos)
					curData += line;
				//end of note, get the data until ending quote
				else
				{
					curData += line.substr(0, found);
					quoteOn = false;
					stageNotes.push_back(curData);
					curData.clear();
				}
			}
			
			else //look for next stage note
			{
				//crude way to verify format is correct
				size_t found = line.find("stage");
				if (found != string::npos)
				{
					if (found == 0 && isdigit(line[5]))//this is prob stageXYZ
					{
						found = line.find_first_of("\"");
						//we actually have data
						if (found != string::npos)
						{
							found++;
							size_t end = line.find_first_of("\"",found);
							//this is a multi line piece of data
							if (end == string::npos)
							{
								quoteOn = true;
								curData = line.substr(found);
								curData += "\n";
							}
							else
							{
								string temp = line.substr(found, (end-found));
								stageNotes.push_back(temp);
							}
						}
						else //theres no notes for this stage
						{
							stageNotes.push_back("");
						}
					}
				}
			}
		}
	}

	fs.close();
}
