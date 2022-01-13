
/*****************************************************************//**
 * @file   StageParameterBase.h
 * @brief  json����ǂݍ��ރp�����[�^�[�̊��N���X
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace Math = AppFrame::Math;

namespace MachineHuck::Parameter {
	class StageParameterBase {
	public:

		/**
		 * @brief �ϐ��̏�����
		 */
		StageParameterBase();

		/**
		 * @brief �ϐ��̉��
		 */
		~StageParameterBase() = default;


		/**
		 * @brief  �t�@�C�������擾����
		 * @return _fileName
		 */
		std::string GetName() { return _fileName; }

		/**
		 * @biref �ʒu����ۑ�
		 * @param pos �ʒu
		 */
		Math::Vector4 GetPosition() { return _pos; };

		/**
		 * @biref ��]����ۑ�
		 * @param rot ��]
		 */
		Math::Vector4 GetRotation() { return _rot; };

		/**
		 * @biref �X�P�[������ۑ�
		 * @param scale �X�P�[��
		 */
		Math::Vector4 GetScale() { return  _scale; };






		/**
		* @brief  �t�@�C������ۑ�
		* @param  fileName
		*/
		void SetName(std::string fileName) { _fileName = fileName; }


		/**
		 * @biref �ʒu����ۑ�
		 * @param pos �ʒu
		 */
		void SetPos(Math::Vector4 pos) { _pos = pos; };

		/**
		 * @biref ��]����ۑ�
		 * @param rot ��]
		 */
		void SetRot(Math::Vector4 rot) { _rot = rot; };

		/**
		 * @biref �X�P�[������ۑ�
		 * @param scale �X�P�[��
		 */
		void SetScale(Math::Vector4 scale) { _scale = scale; };

	protected:

		std::string _fileName{ "" };      //!< �n���h����
		Math::Vector4 _pos{ 0.0, 0.0, 0.0 };           //!< ���s�ړ� 
		Math::Vector4 _rot{ 0.0, 0.0, 0.0 };           //!< ��]
		Math::Vector4 _scale{ 0.0, 0.0, 0.0 };         //!< �X�P�[��
		std::string _type{ "" };            //!< ���

	};
}


