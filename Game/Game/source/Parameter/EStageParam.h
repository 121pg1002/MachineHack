
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
		//int GetLevel() { return _level; }

		/**
		 * @brief  �G�̃��x����ۑ�
		 * @param  level
		 */
		//void SetLevel(int level) { _level = level; }

		/**
		 * @brief  �ړ����[�`���ԍ����擾
		 * @return _routine
		 */
		int GetRoutine() { return _routine; }

		/**
		 * @brief �ړ����[�`���ԍ���ݒ�
		 * @param num
		 */
		void SetRoutine(int num) { _routine = num; }

		/** 
		 * @brief  �ړ��ʂ��擾
		 * @return �ړ���
		 */
		int GetNumRange() { return _numRange; }

		/** 
		 * @brief  �ړ��ʂ�ݒ�       
		 * @param  numRange
		 */
		void SetNumRange(int numRange) { _numRange = numRange; }

		/**
		 * @brief  ������
		 * @return
		 */
		int GetProgress() { _progress; }

	private:

		int _level; //!< �G�̃��x��
		int _routine; //!< �ړ����[�`��
		int _numRange; //!< �ړ���
		int _progress{ 0 }; //!< ������
		std::string _type;
	};
}
