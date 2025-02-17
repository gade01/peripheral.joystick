/*
 *  Copyright (C) 2005-2021 Team Kodi (https://kodi.tv)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include <memory>

#include "CharsetConverter.h"

#include <windows.h>

namespace KODI
{
namespace PLATFORM
{
namespace WINDOWS
{
std::string FromW(const wchar_t* str, size_t length)
{
  int result = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str, static_cast<int>(length), nullptr, 0, nullptr, nullptr);
  if (result == 0)
    return std::string();

  auto newStr = std::make_unique<char[]>(result);
  result = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str, static_cast<int>(length), newStr.get(), result, nullptr, nullptr);
  if (result == 0)
    return std::string();

  return std::string(newStr.get(), result);
}

std::string FromW(const std::wstring& str)
{
  return FromW(str.c_str(), str.length());
}

std::wstring ToW(const char* str, size_t length)
{
  int result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, static_cast<int>(length), nullptr, 0);
  if (result == 0)
    return std::wstring();

  auto newStr = std::make_unique<wchar_t[]>(result);
  result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, static_cast<int>(length), newStr.get(), result);

  if (result == 0)
    return std::wstring();

  return std::wstring(newStr.get(), result);
}

std::wstring ToW(const std::string& str)
{
  return ToW(str.c_str(), str.length());
}

}
}
}
