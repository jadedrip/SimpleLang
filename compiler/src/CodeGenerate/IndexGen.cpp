#include "stdafx.h"
#include "IndexGen.h"

llvm::Value* IndexGen::generateCode(const Generater& generater)
{
	auto& builder = generater.builder();

	auto* a = expr->generate(generater);
	auto* b = index->generate(generater);
	auto* p = builder.CreateGEP(a->getType(), a, b);
	assert(p->getType()->isPointerTy());
	if (type->isStructTy())
		return p;
	return builder.CreateLoad(type, p);
}
