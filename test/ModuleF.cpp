#include "SelfModule.h"
#include "TypeSelect.h"
#include "Modular.h"

/**
 * 定义当前模块
 */
static DefModule _Module("ModuleF"
#ifdef Mod_Config
	, "ModuleA;"
#else
	,""
#endif
	, []$(Initializer)(){
		printf("ModuleF::Initializer()\n");
	}
	, []$(Uninitializer)(){
		printf("ModuleF::Uninitializer()\n");
	});