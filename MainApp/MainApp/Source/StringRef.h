#pragma once
#include "CharTraits.h"

template<typename Traits>
class StringRefBase : Traits
{
	typedef typename Traits::CharType CharType;

public:
	StringRefBase(CharType* const rhs) : _buffer(rhs), StringRefBase()
	{

	}

	StringRefBase& operator=(const StringRefBase& rhs)
	{
		if (&rhs == this)
		{
			return *this;
		}

		this->_buffer = rhs._buffer;
		this->_length = rhs._length;

		return *this;
	}
	APP_FORCEINLINE const bool operator==(const StringRefBase& rhs)
	{
		return false;
	}
	~StringRefBase()
	{

	}
private:
	StringRefBase() : _buffer(0), _length(0)
	{

	}

	CharType* _buffer;
	int32 _length;
};
