//
// Created by timemachine on 18-6-26.
//

#include "SlicerCore.h"
#include "configManager.h"
#include "FilterRender.h"

#include <sys/stat.h>
#include <unistd.h>

#include <set>



void SlicerCore::initFolder()
{
	//clear last time
	//rmdir();
	//mkdir
	//std::cerr << "init: mkdir" << std::endl;
	//mkdir("~/.slicer",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	//ConfigManager::idSet = std::set<int64_t>();
}

void* SlicerCore::update(uint64_t id, void *data, uint width, uint height)
{
	Config config;

	config = ConfigManager::loadConfig(id);
	return FilterRender::render(data, width, height, &config);
	//filterIt(data, width, height, config);
}

bool SlicerCore::test()
{
	ConfigManager::test();

}


