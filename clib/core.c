﻿#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <assert.h>
#include "core.h"

// core.cpp : 定义 DLL 应用程序的导出函数。
//
const int POINTER_SIZE = sizeof(intptr_t);
const int REF_SIZE = sizeof(uint32_t);

const uint8_t MARK_FLAG_ARRAY = 0x01;	// 是数组
const uint8_t MARK_FLAG_REF = 0x02;	// 引用计数
const uint8_t MARK_FLAG_BASE = 0x80;	// 是否默认类型

inline uint8_t getObjectFlag(uint8_t* object)
{
	intptr_t* ptr = (intptr_t*)(object);
	ptr--;
	return (*ptr & 0xFF);
}

/// 获取引用计数地址
inline uint32_t* referenceCount(uint8_t* object)
{
	// TODO: 大小字节序
	uint8_t flag = getObjectFlag(object);
	// 判断是否有引用计数
	if ((flag & MARK_FLAG_REF) == 0) return NULL;
	object -= (intptr_t)POINTER_SIZE + REF_SIZE;
	return (uint32_t*)object;
}

inline void setReferenceCount(uint8_t* object, uint32_t ref)
{
	uint32_t* p = referenceCount(object);
	*p = ref;
}

inline void setObjectType(uint8_t* object, uint64_t type, uint8_t flag) {
	intptr_t* ptr = (intptr_t*)(object - 8);
	intptr_t d = type << 8 | flag;
	// printf("setObject: %llx", d);
	*ptr = d;
}

inline uint32_t* arraySize(uint8_t* object) 
{
	uint8_t flag = getObjectFlag(object);
	object -= POINTER_SIZE;
	if (flag & MARK_FLAG_REF)
		object -= REF_SIZE;
	if (flag & MARK_FLAG_ARRAY) {
		object -= REF_SIZE;
		return (uint32_t*)object;
	}
	return NULL;
}

/**
	对象( Object ) 存储结构
		4 字节引用计数
		4 字节类型信息引用
		对象数据

	返回时指针指向对象数据，可以直接操作。
*/
void* createObject(uint32_t size, uint64_t typeId) {
	//assert(sizeof(LONG) == 4);
	//return malloc(size);
	uint8_t flag = MARK_FLAG_REF;
	// printf("createObject %ld, %llx\r\n", size, typeId);
	uint8_t* p = (uint8_t*)malloc((size_t)size + POINTER_SIZE + REF_SIZE);
	if (!p) return NULL;
	p = p + POINTER_SIZE + REF_SIZE;
	setObjectType(p, typeId, flag);
	setReferenceCount(p, 1);
	return p;
}

void freeObject(uint8_t* object, destructor func)
{
	assert(sizeof(LONG) == 4);
	if (!object) return;

	uint32_t *ref=referenceCount((uint8_t*)object);
	LONG v = InterlockedDecrement(ref);	// TODO: 跨平台

	// printf("freeObject with: %ld %llx\r\n", v, (uint64_t)func);
	if (v == 0) {
		if(func) (*func)(object);
		// printf("freeObject: desotroy.\r\n");
		uint8_t flag = getObjectFlag(object);

		object -= POINTER_SIZE;
		if (flag & MARK_FLAG_REF)
			object -= REF_SIZE;
		if (flag & MARK_FLAG_ARRAY)
			object -= REF_SIZE;

		free(object);
	}
}

const uint32_t arrayMark = 1 << 31;
void * createArray(uint64_t typeId, uint32_t length) {
	uint8_t flag = MARK_FLAG_REF | MARK_FLAG_ARRAY;
	// printf("createArray %ld, %llx\r\n", length, typeId);
	size_t sz = (size_t)length * sizeof(intptr_t) + POINTER_SIZE + REF_SIZE + REF_SIZE;
	uint8_t* p = (uint8_t*)malloc((size_t)sz);
	if (!p) return NULL;
	memset(p, 0, sz);
	p = p + POINTER_SIZE + REF_SIZE + REF_SIZE;
	setObjectType(p, typeId, flag);
	setReferenceCount(p, 1);
	uint32_t* xsz = arraySize(p);
	*xsz = length;

	return p;
}

void arrayLet(void** arrays, uint64_t index, void* object)
{
	//printf("arrayLet %lld", index);
	referenceIncrease(object); 
	long* sz=arraySize((uint8_t*)arrays);
	if (index >= *sz) {
		assert(0);
	}
	arrays[index] = object;
}

long referenceIncrease(void * object) {
	uint32_t* p = referenceCount(object);
	assert(p);
	return InterlockedIncrement((LONG*)p);	// TODO: 跨平台
}

void* arrayIndex(uint8_t* ptr, uint32_t index)
{
#ifdef _DEBUG
	uint8_t flag=getObjectFlag(ptr);
	assert(flag & MARK_FLAG_ARRAY);
#endif
	uint32_t* sz = arraySize((uint8_t*)ptr);
	if (index >= *sz) {
		assert(0);
	}
	ptr += (intptr_t)index * POINTER_SIZE;
	return ptr;
}

