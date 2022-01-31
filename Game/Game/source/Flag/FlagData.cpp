
/*****************************************************************//**
 * @file   FlagData.cpp
 * @brief  フラグデータ管理クラス
 *
 * @author hikaru Goto
 * @date   January 28 2022
 *********************************************************************/
#include "FlagData.h"

namespace MachineHuck::Flag {

 bool FlagData::_fadeInFlag = false;
 bool FlagData::_fadeOutFlag = false;
 bool FlagData::_blackOutFlag = false;
 VECTOR FlagData::_cameraPos = VGet(0.f, 0.f, 0.f);
 int FlagData::_noDamageTime = -1;

}

