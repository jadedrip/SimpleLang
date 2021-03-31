﻿#include "stdafx.h"
#include "modules.h"
#include "Ast/AstModule.h"
#include "Ast/AstPackage.h"

#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

#include <CompilerOptions.h>

using namespace std;
using namespace llvm;
namespace stdfs = filesystem;

map<string, string> funcs;	// 被使用的函数
map<string, StructType* > _structs;
map<string, Function*> _functions;
map<string, AstPackage*> _packages;

Module* _clib;

extern unique_ptr<Module> module;
extern llvm::LLVMContext llvmContext;

llvm::Function* CLangModule::getFunction(const string& name) {
	auto *p=module->getFunction(name);
	if (p) return p;

	for (auto i : _packages) {
		auto f=i.second->getFunction(name);
		if (f) {
			auto x = llvm::Function::Create(f->getFunctionType(), llvm::Function::ExternalLinkage, name, module.get());
			return x;
		}
	}
	return nullptr;
}

llvm::Function* CLangModule::getFunction(const string& package, const string& name) {
	auto iter = _packages.find(package);
	if (iter != _packages.end()) {
		auto func = iter->second->getFunction(name);
		return Function::Create(func->getFunctionType(), Function::ExternalLinkage, name, module.get());
	}
	return nullptr;
}

void CLangModule::moveAll(llvm::ExecutionEngine* engine) {
	//for (auto& i : _packages) {
	//	auto& v = i.second;   
	//	std::unique_ptr<llvm::Module> p(v->llvmModule());
	//	engine->addModule(std::move(p));
	//}
}

string getPackageName(const string& filename) {
	string n = filename.substr(4);// 去除 "lib/"
	replace(n.begin(), n.end(), '/', '.');
	replace(n.begin(), n.end(), '\\', '.');
	// 去除文件名
	size_t i = n.find_last_of('.');
	return n.substr(0, i);
}

// 在 packages.cpp 中实现
void addModule(const string& InputFile, Module* Mod);
extern unique_ptr<Module> module;
//Module* CLangModule::loadLLFile(const string& filename) {
//	auto i = _modules.find(filename);
//	if (i != _modules.end())
//		return i->second.get();
//
//	cout << "Try to load:" << filename << endl;
//	llvm::SMDiagnostic error;
//
//	auto m = parseIRFile(filename, error, llvmContext);
//	if (!m) {
//		clog << "Can't load file: " << filename << endl;
//		return nullptr;
//	}
//
//	for (auto& i : m->getIdentifiedStructTypes()) {
//		_structs[i->getStructName()] = i;
//	}
//
//	auto* p = m.get();
//	_modules.insert(make_pair(filename, move(m)));
//	return p;
//}

extern int yyparse(void);
extern FILE* yyin;
extern AstModule* currentPackage;
extern int yylineno;
AstModule* CLangModule::loadSiFile(const stdfs::path& file, const string& packageName) {
	string fname = file.string();
	auto* old = currentPackage;

	currentPackage = new AstModule();
	currentPackage->name = packageName;
	int ono = yylineno;
	yylineno = 0;
	yyin = fopen(fname.c_str(), "r"); /* 首先打开要被处理的文件（参数1）yyin是lex默认的文件输入指针，设置了则不处理控制台输入 */
	if (!yyin) {
		throw runtime_error("无法打开文件：" + fname);
	}
	if (0 != yyparse()) {
		throw new runtime_error("解析" + fname + "异常");
	}
	yylineno = ono;
	fclose(yyin);

	auto* importedPackage = currentPackage;
	currentPackage = old;

	return importedPackage;
}

void CLangModule::shutdown() {
	// _modules.clear();
}

using namespace std::filesystem;

AstPackage* CLangModule::loadPackage(const string& packageName)
{
	auto iter=_packages.find(packageName);
	if (iter!=_packages.end())
		return iter->second;

	auto package = new AstPackage(packageName);
	_packages[packageName] = package;
	return package;
}



