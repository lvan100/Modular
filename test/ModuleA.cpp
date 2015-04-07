#include "SelfModule.h"
#include "TypeSelect.h"
#include "Modular.h"

/**
 * 定义当前模块
 */
static DefModule _Module("ModuleA"
	,""
	, []$(Initializer)(){
		printf("ModuleA::Initializer()\n");
	}
	, []$(Uninitializer)(){
		printf("ModuleA::Uninitializer()\n");
	});