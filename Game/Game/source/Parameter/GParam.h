/*****************************************************************//**
 * @file   GParam.h
 * @brief  �M�~�b�N�̏��N���X
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include <string>
namespace MachineHuck::Parameter {
	class GParam {
	public:

		/**
		 * @brief  �M�~�b�N�̎�ނ�ۑ�
		 * @param  type
		 */
		void SetType(std::string type) { _type = type; }

		/**
		 * @brief  �n���h������ۑ�
		 * @param  handleName
		 */
		void SetHandleName(std::string handleName) { _handleName = handleName; }

		/**
		 * @brief  ���b�V���̏���ۑ�
		 */
		void SetCollisionFrame(int handle);

	private:

		std::string _type;
		std::string _handleName;
		int _collisionFrame;

	};
}

