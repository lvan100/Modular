#include "StdAfx.h"
#include "SelfModule.h"

/**
 * 定义当前模块
 */
static DefModule _Module(_T("SelfModuleList")
	, _T("")
	, [](){
	}
	, [](){
	}
	, [](){
	}
	, [](){
		SelfModuleList::DelInstance();
	});

/**
 * DefModule
 */
DefModule::DefModule(StdString id
	, StdString depends
	, SelfFunction preinit
	, SelfFunction init
	, SelfFunction uninit
	, SelfFunction destructor)
	: _destructor(destructor)
{
	SelfModuleList* list = SelfModuleList::GetInstance();

	size_t offset = 0;
	size_t lastOffset = offset;
	while ((offset = depends.find(';', lastOffset)) != -1)
	{
		StdString dep = depends.substr(lastOffset, offset - lastOffset);
		
		SelfModule& mod = list->FindModule(dep);
		if (&mod == &SelfModuleList::_NullModule)
		{
			SelfModule module;
			module._id = dep;
			list->AddModule(module);
		}

		lastOffset = offset + 1;
	}

	SelfModule& mod = list->FindModule(id);
	if (&mod != &SelfModuleList::_NullModule)
	{
		mod._init = init;
		mod._uninit = uninit;
		mod._preinit = preinit;
		mod._depends = depends;
	}
	else
	{
		SelfModule module;
		module._id = id;
		module._init = init;
		module._uninit = uninit;
		module._preinit = preinit;
		module._depends = depends;
		list->AddModule(module);		
	}
}

DefModule::~DefModule()
{
	_destructor();
}

/**
 * 模块的空引用
 */
SelfModule SelfModuleList::_NullModule;

/**
 * 全局唯一的实例
 */
SelfModuleList* SelfModuleList::_instance = NULL;

SelfModule& SelfModuleList::FindModule(StdString id)
{
	for (auto iter = _list.begin(); iter != _list.end(); iter++)
	{
		if ((*iter)._id.compare(id) == 0)
		{
			return (*iter);
		}
	}
	return _NullModule;
}