#include "stdafx.h"
#include "FileGen.h"

using namespace llvm;

extern LLVMContext llvmContext;
llvm::Function* FileGen::generateCode(llvm::Module* m) {
	 m->getContext();
	Type* type = Type::getVoidTy(llvmContext);

	// ��������ʼ������
	FunctionType* FT = FunctionType::get(type, false);
	auto main_func = Function::Create(FT, Function::ExternalLinkage, "main", m);
	auto alloc = BasicBlock::Create(llvmContext, "main_alloc", main_func);
	auto basicBlock = BasicBlock::Create(llvmContext, "main_basic", main_func);
	auto deallocate = BasicBlock::Create(llvmContext, "dealloc", main_func);

	// д����ģ��
	IRBuilder<> builder(basicBlock);
	Generater generater = { m, main_func,  &builder, deallocate };
	for (auto i : generates) {
		i->generate(generater);
	}
	// д�˳�ģ��
	builder.CreateBr(deallocate);

	builder.SetInsertPoint(alloc);
	builder.CreateBr(basicBlock);
	builder.SetInsertPoint(deallocate);
	builder.CreateRetVoid();

	return main_func;
}