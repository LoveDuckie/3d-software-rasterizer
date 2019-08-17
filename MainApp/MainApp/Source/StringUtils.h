#pragma once
#include "CharTraits.h"

template<class CharType>
struct CharTraits;

template<class UtilsCharType>
class StringUtils : public CharTraits<UtilsCharType>
{
protected:
	static APP_FORCEINLINE const bool Contains(const UtilsCharType* const lhs, const UtilsCharType* const rhs)
	{
		return false;
	}

	static APP_FORCEINLINE const bool EndsWith(const UtilsCharType* const lhs, const UtilsCharType* const rhs)
	{
		return false;
	}

	static APP_FORCEINLINE const bool StartsWith(const UtilsCharType* const lhs, const UtilsCharType* const rhs)
	{
		return memcmp(lhs, rhs) == 0;
	}
};