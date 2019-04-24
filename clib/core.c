﻿#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <assert.h>
#include "core.h"

// core.cpp : 定义 DLL 应用程序的导出函数。
//
const int OBJECT_HEAD_SIZE = 12;
const int ARRAY_HEAD_SIZE = 16;
typedef unsigned char byte;

#define MARK_FLAG_ARRAY 0x01
#define MARK_FLAG_REF	0x02

inline byte getObjectFlag(byte* object)
{
	uint64_t* ptr = (uint64_t*)(object - 8);
	return (*ptr & 0xFF);
}

/// 获取引用计数地址
inline uint32_t* referenceCount(byte* object)
{
	// TODO: 大小字节序
	byte flag = getObjectFlag(object);
	// 判断是否有引用计数
	if ((flag & MARK_FLAG_REF) == 0) return NULL;
	if ((flag & MARK_FLAG_ARRAY) == MARK_FLAG_ARRAY) // 有数组长度
		object -= 4;
	object -= 12;
	return (uint32_t*)object;
}

inline void setReferenceCount(byte* object, uint32_t ref)
{
	uint32_t* p = referenceCount(object);
	*p = ref;
}

inline void setObjectType(byte* object, uint64_t type, byte flag) {
	assert(sizeof(uint64_t) == 8);
	uint64_t* ptr = (uint64_t*)(object - 8);
	uint64_t d = type << 8 | flag;
	printf("setObject: %llx", d);
	*ptr = d;
}

/**
	对象( Object ) 存储结构
		4 字节引用计数
		4 字节类型信息引用
		对象数据

	返回时指针指向对象数据，可以直接操作。
*/
void* createObject(uint64_t size, uint64_t typeId) {
	//assert(sizeof(LONG) == 4);
	//return malloc(size);
	byte flag = MARK_FLAG_REF;
	printf("createObject %lld, %llx\r\n", size, typeId);
	byte* p = (byte*)malloc(size + OBJECT_HEAD_SIZE);
	if (!p) return NULL;
	p = p + OBJECT_HEAD_SIZE;
	setObjectType(p, typeId, flag);
	setReferenceCount(p, 1);
	return p;
}

void freeObject(void* object, destructor func)
{
	assert(sizeof(LONG) == 4);

	uint32_t *ref=referenceCount((byte*)object);
	LONG v = InterlockedDecrement(ref);	// TODO: 跨平台

	printf("freeObject with: %ld %llx\r\n", v, (uint64_t)func);
	if (v == 0) {
		if(func) (*func)(object);
		printf("freeObject: desotroy.\r\n");
		byte* x = (byte*)object;
		x -= OBJECT_HEAD_SIZE;
		free(x);
	}
}

const uint32_t arrayMark = 1 << 31;
void * createArray(uint32_t objectSize, uint32_t typeId, uint32_t length) {
	return createObject((objectSize + OBJECT_HEAD_SIZE) * length, arrayMark | typeId);
}

long referenceIncrease(void * object) {
	assert(sizeof(LONG) == 4);
	uint32_t* p = referenceCount(object);
	return InterlockedIncrement((LONG*)p);	// TODO: 跨平台
}

