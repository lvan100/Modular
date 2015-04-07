#ifndef Self_Module_H
#define Self_Module_H

#include <vector>
#include <string>
#include <functional>
using namespace std;

/**
 * 定义标准字符串类
 */
#ifndef STD_STRING_TYPE
#define STD_STRING_TYPE
typedef std::string StdString;
#endif

/**
 * 定义初始化及反初始化函数类型
 */
#ifndef SELF_FUCTION_TYPE
#define SELF_FUCTION_TYPE
typedef function<void()> SelfFunction;
#endif

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
	StdString _dep;

	/**
	 * 初始化函数
	 */
	SelfFunction _init;

	/**
	 * 反初始化函数
	 */
	SelfFunction _uninit;

	/**
	 * 构造函数
	 */
	SelfModule(StdString id)
		: _id(id)
	{}
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
	 * @Param constructor
	 *        模块的构造函数
	 * @Param initializer
	 *        模块的初始化函数
	 * @Param uninitializer
	 *        模块的反初始化函数
	 * @Param destructor
	 *        模块的析构函数
	 */
	DefModule(StdString id
		, StdString depends
		, SelfFunction constructor
		, SelfFunction initializer
		, SelfFunction uninitializer
		, SelfFunction destructor);

	/*
	 * 构造函数
	 * 
	 * @Param id
	 *        模块的ID
	 * @Param depends
	 *        模块的依赖
	 * @Param initializer
	 *        模块的初始化函数
	 * @Param uninitializer
	 *        模块的反初始化函数
	 */
	DefModule(StdString id
		, StdString depends
		, SelfFunction initializer
		, SelfFunction uninitializer);

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
 * 列表索引类型
 */
typedef vector<SelfModule>::iterator ModuleWhere;

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
	 * 查找模块
	 * 
	 * @Param id
	 *        待查找的模块的ID
	 * @Return 返回查找到的模块位置
	 */
	ModuleWhere Find(StdString id)
	{
		ModuleWhere iter = _list.begin();

		for (; iter != _list.end(); iter++)
		{
			if ((*iter)._id.compare(id) == 0)
			{
				break;
			}
		}

		return iter;
	}

	/**
	 * 插入模块到指定位置
	 * 
	 * @Param where
	 *        插入位置
	 * @Param module
	 *        模块对象
	 * @return 返回插入位置
	 */
	ModuleWhere Insert(ModuleWhere where, SelfModule module)
	{
		return _list.insert(where, module);
	}

	/*
	 * 获取模块列表开始位置
	 * 
	 * @return 返回列表开始位置
	 */
	ModuleWhere Begin()
	{
		return _list.begin();
	}

	/**
	 * 模块位置是否为列表尾端
	 * 
	 * @Param where
	 *        查找位置
	 * @return 如果是列表尾端返回true，否则返回false。
	 */
	bool End(ModuleWhere where)
	{
		return where == _list.end();
	}

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