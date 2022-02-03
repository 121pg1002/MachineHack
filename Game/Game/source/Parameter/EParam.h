
/*****************************************************************//**
 * @file   EParam.h
 * @brief  �G�̃p�����[�^�[���̃N���X
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include <string>
namespace MachineHuck::Parameter{
	class EParam {
	public:

		/**
		 * @brief  �G�̎�ނ�ۑ�
		 * @param  type
		 */
		 /*void SetType(std::string& type) { _type = type; }*/

		 /**
		  * @brief  �G�̃��x����ۑ�
		  * @param  level
		  */
		  /*void SetLevel(int level) { _level = level; }*/

		  /**
		   * @brief  �G�̃G�i�W�[�ʂ�ۑ�
		   * @param  energy
		   */
		void SetEnergy(double energy) { _energy = energy; }

		/**
		 * @brief  ���G�͈͂�ۑ�
		 * @param  searchRange
		 */
		void SetSearchRange(double searchRange) { _searchRange = searchRange; }

		/**
		 * @brief  ���a��ۑ�
		 * @param  r
		 */
		void SetR(double r) { _r = r; }

		/**
		 * @brief  ������ۑ�
		 * @param  speed
		 */
		void SetSpeed(double speed) { _speed = speed; }

	private:

		//std::string _type{ "" };    //!< ���
		//int    _level{0};              //!< ���x��
		double _energy{ 0.0 };      //!< �G�i�W�[��
		double _searchRange{ 0.0 }; //!< ���G�͈͂̊p�x
		double _r{ 0.0 };           //!< ���G���a
		double _speed{ 0.0 };       //!< ����

	};
}

