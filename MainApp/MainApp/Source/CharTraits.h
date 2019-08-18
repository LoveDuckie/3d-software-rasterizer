#pragma once
#include "StringRef.h"
#include "StringUtils.h"

template<class CharType>
struct CharTraits;

template<>
struct CharTraits<char>
{
private:
	CharTraits() = default;
	~CharTraits() = default;

public:
	typedef char CharType;
	typedef wchar_t OtherCharType;
	typedef StringRefBase<StringUtils<char>> StringRef;
	static const char Space = ' ';
	static const char Tab = '\t';
	static const char NewLine = '\n';
	static const char Return = '\r';
	static const char Backslash = '\\';
	static const char Forwardslash = '/';
	static const char NullTerminator = '\0';

	static APP_FORCEINLINE const int32 GetLength(const CharType* rhs)
	{
		return -1;
	}

	static APP_FORCEINLINE const int32 StrCmp(const CharType* lhs, const CharType* rhs)
	{
		return -1;
	}

	static APP_FORCEINLINE const float32 ToFloat32(const StringRef& rhs)
	{
		return 0.f;
	}
};

template<>
struct CharTraits<wchar_t>
{
private:
	CharTraits() = default;
	~CharTraits() = default;

public:
	typedef wchar_t CharType;
	typedef char OtherCharType;
	typedef StringRefBase<StringUtils<wchar_t>> StringRef;
	static const wchar_t Space = L' ';
	static const wchar_t Tab = L'\t';
	static const wchar_t NewLine = L'\n';
	static const wchar_t Return = L'\r';
	static const wchar_t Backslash = L'\\';
	static const wchar_t Forwardslash = L'/';
	static const wchar_t NullTerminator = L'\0';

	static APP_FORCEINLINE const int32 GetLength(const CharType* rhs)
	{
		return -1;
	}

	static APP_FORCEINLINE const int32 StrCmp(const CharType* lhs, const CharType* rhs)
	{
		return -1;
	}

	static APP_FORCEINLINE const float32 ToFloat32(const StringRef& rhs)
	{
		return 0.f;
	}
};