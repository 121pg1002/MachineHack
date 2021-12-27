/**
 * @file    EnemyParameter.h
 * @brief  �p�����[�^�[��json����ǂݍ���
 *
 *
 * @author Hikaru Goto
 * @date   2021/11/27
 */

#pragma once
#include<unordered_map>
#include<string>
#include<DxLib.h>
#include "AppFrame.h"

using EStageParam = std::unordered_map < std::string, math::Vector4>;
using EParam      = std::unordered_map < std::string, double>;

namespace Enemy {
	class EnemyParameter
	{
	public:

		/*
		* @brief �R���X�g���N�^
		*/
		EnemyParameter();

		/*
		* @brief �f�X�g���N�^
		*/
		~EnemyParameter();

		/**
		 * @brief  �G�l�~�[�̃X�e�[�W�z�u�p�����[�^�[��json����ǂݍ���
		 * @param  filePath
		 */
		void LoadStageEnemyParam(const std::string& filePath);

		/*
		* @brief  json����G�̃p�����[�^�[��ǂݍ���
		* @param  filePath
		*/
		void LoadEnemyParam(const std::string& filePath);

		/*
		* @brief �ǂݍ��񂾃p�����[�^�[���擾
		* @param  filePath
		* @return �p�����[�^�[
		*/
		double GetEnemyParam(const std::string& paramName);

	private:
		std::unordered_map<std::string, EStageParam>     _enemyStageMap; //!< �G�̃X�e�[�W�z�u��ۑ�
	 // std::unordered_map<std::string, double> _enemyParamMap; //!< �G�̃p�����[�^�[��ۑ�
		//std::unordered_map<std::string, EnemyParameter> _enemyParamMap;
		std::unordered_map<std::string, EParam> _enemyParamMap;
		std::string _filename;
		std::string _handlename;
		math::Vector4 _position;
		math::Vector4 _rotation;
		math::Vector4 _scale;


		double _type{ 0.0 };  //!< ���
		double _energy{ 0.0 }; //!< �G�i�W�[��
		double _searchRange{ 0.0 }; //!< ���G�͈͂̊p�x
		double _r{ 0.0 }; //!< ���G���a
		double _speed{ 0.0 }; //!< ����

	};
}