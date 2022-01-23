
/*****************************************************************//**
 * @file   SpawnTable.h
 * @brief  スポーンテーブルクラス
 * 
 * @author hikaru Goto
 * @date   January 23 2022
 *********************************************************************/
#pragma once
#include <string>
#include "AppFrame.h" 

namespace Math = AppFrame::Math;

class SpawnTable {
public:

private:
    int _progress{ 0 };
    std::string _key;
    Math::Vector4 _position{ 0, 0, 0 };
    Math::Vector4 _rotation{ 0, 0, 0 };

};
