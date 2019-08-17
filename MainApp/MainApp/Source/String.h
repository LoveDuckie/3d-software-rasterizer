#pragma once

#include "Memory.h"
#include "Defines.h"
#include "CharTraits.h"
#include "StringRef.h"
#include "StringUtils.h"
#include <assert.h>

using namespace Framework;




template<typename Traits>
class StringBase : Traits
{

public:
	typedef typename Traits::CharType CharType;

	StringBase() : _buffer(0), _length(0)
	{

	}
	StringBase(const CharType* const Rhs)
	{

	}
	StringBase(const StringBase& Rhs)
	{

	}
	StringBase& operator=(const StringBase& rhs)
	{
		return *this;
	}
	CharType& operator[](const unsigned int index)
	{
		return const_cast<CharType&>(static_cast<const StringBase>(*this)[index]);
	}
	const CharType& operator[](const unsigned int index) const
	{
		return this->_buffer[index];
	}
	~StringBase()
	{
		Free();
	}
	const unsigned int GetLength() const
	{
		// include the null terminator
		return this->_length + 1;
	}
	StringBase operator+(const StringBase& rhs) const
	{
		return StringBase();
	}
	StringBase& operator+=(const StringBase& rhs)
	{
		return *this;
	}
private:
	void Allocate(unsigned int size) 
	{
		assert(size != 0);
	}
	void Initialize(const CharType* const rhs)
	{
		assert(rhs == nullptr);
		_length = 0;
	}
	
	void Initialize()
	{
		_buffer = Memory::Allocate<typename CharType>(1);

	}
	
	void Free() 
	{

	}

	CharType* _buffer;
	unsigned int _length;
};

typedef StringBase<StringUtils<char>> StringA;
typedef StringBase<StringUtils<wchar_t>> StringW;
typedef StringBase<StringUtils<tchar>> String;