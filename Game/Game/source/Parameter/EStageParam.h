
/*****************************************************************//**
 * @file   EStageParam.h
 * @brief  �X�e�[�W�̓G�̏��N���X
 *
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include "StageParameterBase.h"
#include <string>
namespace MachineHuck::Parameter {

	class EStageParam : public StageParameterBase {
	public:


		/**
		 * @biref ��ނ�ۑ�
		 * @param _type
		 */
		std::string GetType() { return  _type; };



		/**
		 * @brief  ������
		 * @return
		 */
		int GetProgress() { _progress; }

	private:

		int _progress{ 0 }; //!< ������
		std::string _type;
	};
}
