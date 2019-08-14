#pragma once

template<typename CharType>
struct CharTraits;

template<>
struct CharTraits<char>
{
private:
	CharTraits() = default;
	~CharTraits() = default;

public:
	typedef char CharType;
	static const char Space = ' ';
	static const char Tab = '\t';
	static const char NewLine = '\n';
	static const char Return = '\r';
	static const char Backslash = '\\';
	static const char Forwardslash = '/';
};

template<>
struct CharTraits<wchar_t>
{

};

template<typename CharType>
class StringUtils
{

};

template<typename CharType>
class String : public StringUtils<typename CharTraits<CharType>>
{

};
