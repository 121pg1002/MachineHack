
/*****************************************************************//**
 * @file   StageParameterBase.cpp
 * @brief  jsonから読み込むパラメーターの基底クラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#include "StageParameterBase.h"

namespace MachineHuck::Parameter {
	StageParameterBase::StageParameterBase() {

		_fileName = "";
		_pos = { 0.0, 0.0, 0.0 };
		_rot = { 0.0, 0.0, 0.0 };
		_scale = { 0.0, 0.0, 0.0 };

	}
}


