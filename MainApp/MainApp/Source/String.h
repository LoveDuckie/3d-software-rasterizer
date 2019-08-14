#pragma once

template<typename CharType>
struct CharTraits;

template<>
struct CharTraits<char>
{

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