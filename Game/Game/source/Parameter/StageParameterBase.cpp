
/*****************************************************************//**
 * @file   StageParameterBase.cpp
 * @brief  json����ǂݍ��ރp�����[�^�[�̊��N���X
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


