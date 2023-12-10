#pragma once
#include "FloatPointerGen.h"
#include "IntegerGen.h"

inline double getDouble(CodeGen* gen) {
	auto p = dynamic_cast<FloatPointerGen*>(gen);
	if (p) return p->getDouble();
	auto q = dynamic_cast<IntegerGen*>(gen);
	if (q) return q->value;
		
	throw std::runtime_error("Not float pointer type.");
}

inline int64_t getInteger(CodeGen* gen) {
	auto p = dynamic_cast<IntegerGen*>(gen);
	if (p) return p->value;
	auto q = dynamic_cast<FloatPointerGen*>(gen);
	if (q) return (int64_t)q->getDouble();

	throw std::runtime_error("Not integer pointer type.");
}

/**
* �ж� llvm �����Ƿ��Ӧ String ����
*/
bool isString(llvm::Type* type);
