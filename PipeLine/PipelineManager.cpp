#include "PipelineManager.h"
#include "CFGUtils.h"

PipelineManager::PipelineManager(string cfgPath)
{
	if (cfgPath.empty())
		cfgPath = "pipelinecfg.txt";
	
	if (!CFGUtils::ReadCfgFile(cfgPath, '|'))
	{
		string errorMsg = "Error opening :";
		errorMsg += cfgPath;
		//cout << errorMsg << "\nno cfg text file" << endl;
		return;
	}


	vector<string> pipelineNames = CFGUtils::GetCfgListValue("pipelines");
	
	for (int i = 0; i < pipelineNames.size(); i++)
	{
		LoadPipeline(pipelineNames[i]);
	}


	vector<string> pipelineItems= CFGUtils::GetCfgListValue("pipelineItems");

	for (int i = 0; i < pipelineItems.size(); i++)
	{
		PipelineItem *item = LoadPipelineItem(pipelineItems[i]);
		if (LinkItemToPipeline(item) == false)
		{
			//error!
			exit(0);
		}
		item->GetCurrentStageInfo();
	}

}

PipelineFile * PipelineManager::LoadPipeline(string filepath)
{
	PipelineFile *file = new PipelineFile(filepath); //"D:\\source\\test.txt"
	pipelines.push_back(file);
	return file;
}

PipelineItem * PipelineManager::LoadPipelineItem(string filepath)
{
	PipelineItem *item = new PipelineItem(filepath); //D:\\source\\some owner.txt
	pipelinesItems.push_back(item);
	return item;
	//item->GetCurrentStageInfo();
}

bool PipelineManager::LinkItemToPipeline(PipelineItem *item)
{
	string name = item->GetPipelineName();
	for (int i = 0; i < pipelines.size(); i++)
	{
		if (pipelines[i]->GetName() == name)
		{
			item->SetPipeline(pipelines[i]);
			return true;
		}
	}
	return false;
}


void PipelineManager::CreatePipeline(string name)
{
}

void PipelineManager::CreatePipelineItem(string name)
{
	/*PipelineItem item("some owner",&file);
	item.SetPipelineStage(1);
	item.AddStageNotes(2, "he wants to sell");
	item.AddStageNotes(1,"what will this do?\n");
	item.WriteItemToFile("D:\\source\\");
	*/
}


void PipelineManager::DeletePipeline(string name)
{
}
void PipelineManager::RemovePipelineStage(string name, int stage)
{
}
void PipelineManager::EditPipelineStage(string name, int stage)
{
}
int PipelineManager::CountStagesDueToday()
{
	return 0;
}