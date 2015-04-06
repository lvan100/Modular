#ifndef Type_Select_H
#define Type_Select_H

/**
 * 定义匿名函数的名称
 */
#define $(NAME)

/**
 * $，定义类型选择器
 */
template<class _T> struct $ {

	/**
	 * 基本类型
	 */
	typedef _T Type;

	/**
	 * 指针类型
	 */
	typedef _T *Ptr;

	/**
	 * 引用类型
	 */
	typedef _T &Ref;
};

/**
 * 定义Lambda函数类型
 */
#define Lambda auto&

#endif /* Type_Select_H */