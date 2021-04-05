#include "stdafx.h"
#include <Windows.h>
#include <llvm/IR/Constants.h>

#include "StringLiteGen.h"
#include "ValueGen.h"
#include "CallGen.h"
#include "NewGen.h"
#include "../modules.h"
#include "AstContext.h"
#include "CodeGenerate/IntegerGen.h"
#include <vcruntime.h>
using namespace std;
using namespace llvm;
extern bool utf8File;
StringLiteGen::StringLiteGen(AstContext* c, const std::string & s) : _str(s)
{
	// ������
	UINT code = utf8File ? CP_UTF8 : CP_ACP;
	int  len = (int)_str.length();
	int  unicodeLen = ::MultiByteToWideChar(code,
											0,
											_str.c_str(),
											-1,
											NULL,
											0);
	wchar_t *  pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(code,
						  0,
						  _str.c_str(),
						  -1,
						  (LPWSTR)pUnicode,
						  unicodeLen);
	int ulen = unicodeLen * sizeof(wchar_t);

	_data.assign(pUnicode, unicodeLen-1);
	delete[]  pUnicode;

	//auto charset = c->findClass("Charset");
	//vector<pair<string, CodeGen*>> vec = { pair(string(), new IntegerGen(c->context(), 65001)) };
	//auto charsetObj = charset->makeNew(c, vec); // utf8

	//auto* str = c->findClass("String");
	//str->makeNew(c, s.c_str(), )
	
	type = c->findStruct("struct.String__sl");
	assert(type);
	_init= c->getFunction("Init__String__sl");
	assert(_init);
	_finalize = c->getFunction("Finalize__String__sl");
	assert(_finalize);
}

void StringLiteGen::append(StringLiteGen * g)
{
	_str += g->_str;
}

llvm::Value * StringLiteGen::generateCode(const Generater& generater)
{
	auto& builder = generater.builder();
	auto &c = generater.context();

	if (hope == IntegerType::getInt8PtrTy(c)) {
		auto* v = builder.CreateGlobalStringPtr(_str);
		type = v->getType();
		return v;
	}

	int ulen = (int)_data.size() * sizeof(wchar_t);
	auto *v=builder.CreateGlobalStringPtr(StringRef(
		(const char*)_data.c_str(), ulen
	));

	NewGen n(type);
	n.escape = escape;
	n.finalize = new ValueGen(_finalize);
	auto* obj = n.generate(generater);
	auto *call=CallGen::call(builder, _init,
		obj,
		v,
		_data.size(),
		1200);
	return obj;
}
