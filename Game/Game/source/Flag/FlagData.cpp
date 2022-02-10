
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
	bool FlagData::_noDamageFlag = false;
	bool FlagData::_damageFlag = false;
	bool FlagData::_huckNoDamageFlag = false;
	bool FlagData::_huckDamageFlag = false;
	VECTOR FlagData::_headPos = VGet(0.f, 0.f, 0.f);
	bool FlagData::_noExitFlag = false;
	bool FlagData::_playerDead = false;
	bool FlagData::_ductWarp = false;
	bool FlagData::_slideInFlag = false;
	bool FlagData::_slideOutFlag = false;
	bool FlagData::_slideFlag = false;



}

