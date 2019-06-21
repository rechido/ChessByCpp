#pragma once

#include <iostream>
#include <windows.h>   // WinApi header
#include <memory>
#include <cassert>
#include "eObjectType.h"
#include "eModeType.h"

// 앞=바탕색, 뒤=글자색
constexpr auto BLACK_GREEN = 10;
constexpr auto BLACK_SKYBLUE = 11;
constexpr auto BLACK_PINK = 12;
constexpr auto BLACK_PURPLE = 13;
constexpr auto BLACK_YELLOW = 14;
constexpr auto BLACK_WHITE = 15; // 길
constexpr auto BLUE_WHITE = 159;
constexpr auto PURPLE_WHITE = 223;
constexpr auto GREEN_WHITE = 175; // 사람
constexpr auto RED_WHITE = 207; // 박스
constexpr auto YELLOW_WHITE = 239; // 골
constexpr auto WHITE_BLACK = 240; // 벽