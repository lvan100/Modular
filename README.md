# Modular

我在实际工作中发现很多类和模块是非常独立和相似的：它们一般都需要有初始化和反初始化的过程。一般做法是在程序初始化的位置对这些类和模块进行集中配置。比如程序中有ModuleA、ModuleE、ModuleF这三个模块，而且这三个模块之间有依赖顺序ModuleE<ModuleF<ModuleA，这时候的初始化过程就是：<br/>
ModuleE.Init();<br/>
ModuleF.Init();<br/>
ModuleA.Init();<br/>
如果模块很多，这种初始化过程就显得非常乏味。那么我们又没有更好的办法解决这个问题呢？这就是该项目给出的答案！

Modular能够自动收集C++项目中那些独立的模块，并提供统一的初始化入口。还是上面的那个问题，如果用Modular来解决你只需要做以下几件事情：

###在模块ModuleE的实现文件中加入当前模块的注册信息：
	#include "SelfModule.h"
	#include "TypeSelect.h"
	#include "Modular.h"
	
	/**
	* 定义当前模块
	*/
	static DefModule _Module("ModuleE"
	#ifdef Mod_Config
		, "ModuleF;"
	#else
		,""
	#endif
		, []$(Initializer)(){
			printf("ModuleE::Initializer()\n");
		}
		, []$(Uninitializer)(){
		printf("ModuleE::Uninitializer()\n");
		});

###在模块ModuleF的实现文件中加入当前模块的注册信息：		
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

###在模块ModuleA的实现文件中加入当前模块的注册信息：		
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
	
###当你对每一个独立的模块进行注册后，就可以在应用初始化的位置使用一句话完成注册过程：

	SelfModuleList::GetInstance()->Inits();

	SelfModuleList::GetInstance()->Uninits();
