
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
		 * @brief  �G�̃��x�����擾����
		 * @return _level
		 */
		int GetLevel() { return _level; }

		/**
		 * @brief  �G�̃��x����ۑ�
		 * @param  level
		 */
		void SetLevel(int level) { _level = level; }

	private:

		int _level; //!< �G�̃��x��
		std::string _type;
	};
}
