#include "stdafx.h"
#include "LambdaGen.h"

using namespace std;
using namespace llvm;
LambdaGen::LambdaGen(AstFunction* func, FunctionInstance * instance) 
	: _func(func), _instance(instance)
{
	if(_instance->func)
		type = _instance->func->getType();
}

// ������������Ϊ��ֵʱ�ᱻ���ã����غ���ָ��
llvm::Value * LambdaGen::generateCode(const Generater& generater)
{
	auto* m = generater.module;
	auto& builder = generater.builder();

	llvm::Value* fun = _instance->generateCode(m, builder.getContext());
	// _instance->generateBody(m, builder.getContext());
	return fun;
}
