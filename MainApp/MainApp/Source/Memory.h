#pragma once
#include <cstdlib>
#include <iostream>
#include "Defines.h"

namespace Framework
{
	namespace Memory
	{
		template<typename T>
		APP_FORCEINLINE T* Allocate(unsigned int size)
		{
			T* allocated = reinterpret_cast<T>(malloc(sizeof(T) * size));
			return allocated;
		};

		template<typename T>
		APP_FORCEINLINE T* Reallocate(T* memChunk, unsigned int newSize)
		{
			T* allocated = reinterpret_cast<T>(relloc(memChunk, newSize));
			return allocated;
		}

		APP_FORCEINLINE void Deallocate(void* memChunk)
		{
			free(memChunk);
		}
	}
}