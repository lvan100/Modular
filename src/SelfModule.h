#ifndef Self_Module_H
#define Self_Module_H

#include <vector>
#include <string>
#include <functional>
using namespace std;

#ifndef _UNICODE
typedef std::string StdString;
#else
typedef std::wstring StdString;
#endif

/**
 * 定义初始化及反初始化函数类型
 */
typedef function<void()> SelfFunction;

/**
 * 定义模块类型
 */
struct SelfModule
{
	/**
	 * 模块的ID
	 */
	StdString _id;

	/**
	 * 模块的依赖，不同的依赖项之间用';'分割
	 */
	StdString _depends;

	/**
	 * 初始化之前的操作
	 */
	SelfFunction _preinit;

	/**
	 * 初始化函数
	 */
	SelfFunction _init;

	/**
	 * 反初始化函数
	 */
	SelfFunction _uninit;
};

/**
 * 声明模块的定义
 */
class DefModule
{
public:
	/*
	 * 构造函数
	 * 
	 * @Param id
	 *        模块的ID
	 * @Param depends
	 *        模块的依赖
	 * @Param preinit
	 *        初始化之前的操作
	 * @Param init
	 *        模块的初始化函数
	 * @Param uninit
	 *        模块的反初始化函数
	 * @Param destructor
	 *        模块的析构函数
	 */
	DefModule(StdString id
		, StdString depends
		, SelfFunction preinit
		, SelfFunction init
		, SelfFunction uninit
		, SelfFunction destructor);

	/**
	 * 析构函数
	 */
	~DefModule();

protected:
	/**
	 * 析构函数
	 */
	SelfFunction _destructor;
};

/**
 * 模块列表
 */
class SelfModuleList
{
public:
	/**
	 * 获取唯一实例
	 * 
	 * @Return 返回全局唯一的实例
	 */
	static SelfModuleList* GetInstance()
	{
		if (_instance != NULL)
		{
			return _instance;
		}

		if (_instance == NULL)
		{
			_instance = new SelfModuleList();
		}

		return _instance;
	}

	/**
	 * 删除唯一实例
	 */
	static void DelInstance()
	{
		if (_instance != NULL)
		{
			delete _instance;
			_instance = NULL;
		}
	}

public:
	/**
	 * 初始化之前的操作
	 */
	void PreInits()
	{
		for (auto iter = _list.begin(); iter != _list.end(); iter++)
		{
			(*iter)._preinit();
		}
	}

	/**
	 * 初始化函数
	 */
	void Inits()
	{
		for (auto iter = _list.begin(); iter != _list.end(); iter++)
		{
			(*iter)._init();
		}
	}

	/**
	 * 反初始化函数
	 */
	void Uninits()
	{
		for (auto iter = _list.rbegin(); iter != _list.rend(); iter++)
		{
			(*iter)._uninit();
		}
	}

	/**
	 * 增加模块
	 * 
	 * @Param mod
	 *        模块
	 */
	void AddModule(SelfModule mod)
	{
		_list.push_back(mod);
	}

	/**
	 * 查找模块
	 * 
	 * @Param id
	 *        待查找的模块的ID
	 * @Return 返回查找到的模块
	 */
	SelfModule& FindModule(StdString id);

	/**
	 * 模块的空引用
	 */
	static SelfModule _NullModule;

protected:
	/**
	 * 模块列表
	 */
	vector<SelfModule> _list;

protected:
	SelfModuleList(void) {}
	~SelfModuleList(void) {}

private:
	/**
	 * 全局唯一的实例
	 */
	static SelfModuleList* _instance;
};

#endif /* Self_Module_H */