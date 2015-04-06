#include "SelfModule.h"
#include "TypeSelect.h"

/**
 * 定义当前模块
 */
static DefModule _Module("SelfModuleList"
	, ""
	, []$(Constructor)(){
	}
	, []$(Initializer)(){
	}
	, []$(Uninitializer)(){
	}
	, []$(Destructor)(){
		SelfModuleList::DelInstance();
	});

/**
 * DefModule
 */
DefModule::DefModule(StdString id
	, StdString depends
	, SelfFunction constructor
	, SelfFunction initializer
	, SelfFunction uninitializer
	, SelfFunction destructor)
	: _destructor(destructor)
{
	SelfModuleList* list = SelfModuleList::GetInstance();

	if(id.compare("SelfModuleList") == 0){
		return;
	}

	ModuleWhere insPos = list->Begin();

	size_t offset = 0;
	size_t lastset = offset;
	while ((offset = depends.find(';', lastset)) != -1)
	{
		auto dep = depends.substr(lastset, offset - lastset);

		auto where = list->Find(dep);
		if (insPos - where <= 0) {

			if (!list->End(where)) {
				insPos = where + 1;
			} else {
				insPos = where;
			}
		}

		lastset = offset + 1;
	}

	SelfModule module(id);
	module._dep = depends;
	module._init = initializer;
	module._uninit = uninitializer;
	list->Insert(insPos, module);

	constructor();
}

DefModule::DefModule(StdString id
	, StdString depends
	, SelfFunction initializer
	, SelfFunction uninitializer)
{
	DefModule(id, depends, [](){}, initializer, uninitializer, [](){});
}

DefModule::~DefModule()
{
	_destructor._Empty() ? int(5) : _destructor();
}

/**
 * 全局唯一的实例
 */
SelfModuleList* SelfModuleList::_instance = NULL;