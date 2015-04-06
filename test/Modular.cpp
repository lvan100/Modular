#include "SelfModule.h"

int main(int argc, char* argv[])
{
	printf("\n");

	SelfModuleList::GetInstance()->Inits();

	printf("\n");

	// 如果我们不指定模块间的依赖顺序，那么
	// 初始化顺序也许是CDAEFB，也许是其他；

	// 如果限制一些初始化顺序如E<F<A=B<D<C，
	// 那么请检查输出结果吧!（Mod_Config）

	SelfModuleList::GetInstance()->Uninits();

	printf("\n");

	return 0;
}

