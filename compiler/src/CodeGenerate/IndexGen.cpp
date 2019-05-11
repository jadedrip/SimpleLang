#include "stdafx.h"
#include "IndexGen.h"

llvm::Value* IndexGen::generateCode(const Generater& generater)
{
	auto& builder = generater.builder();

	auto* a = expr->generate(generater);
	auto* b = index->generate(generater);
	auto* p = builder.CreateGEP(a, b);
	if (a->getType()->isStructTy())
		return p;
	return builder.CreateLoad(p);
}
