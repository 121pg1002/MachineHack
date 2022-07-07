/*****************************************************************//**
 * @file   EnemyParameter.h
 * @brief  �G�l�~�[�p�����[�^�[��ǂݍ��ރN���X
 *
 * @author hikaru Goto
 * @date   December 26 2021
 *********************************************************************/
#pragma once
#include<unordered_map>
#include<string>
#include<DxLib.h>
#include "../Parameter/EStageParam.h"
#include "../Parameter/EParam.h"




namespace MachineHuck::Enemy {

	using ESMV = std::vector<Parameter::EStageParam>;
	//using StageV = std::vector<int>;

	//using Type = std::unordered_map<std::string, Parameter::EStageParam>;
	//using StageMap = std::unordered_map<std::string, Type>;
	using DoubleMap = std::unordered_map<std::string, double>;
	using LevelRoutine = std::vector<std::pair<int, int>>; //!< ���x���Ǝv�l���[�`���ԍ���ۑ�


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
		 * @brief  �G�l�~�[�̃X�e�[�W�z�u����json����ǂݍ���
		 * @param  stageNo  �X�e�[�W�ԍ�
		 * @param  filePath
		 */
		void LoadStageEnemyParam(const int stageNo, const std::string& filePath);

		/*
		* @brief  json����G�̏���ǂݍ���
		* @param  filePath
		*/
		void LoadEnemyParam(const std::string& filePath);

		/*
		* @brief �ǂݍ��񂾃p�����[�^�[���擾
		* @param  filePath
		* @return �p�����[�^�[
		*/
		double GetEnemyParam(const std::string& paramName, int no);

		/**
		* @brief   �x�N�^�[�z����擾����
		* @return  _eStageParamV
		*/
		ESMV GetStageVector() { return _eStageParamV; }

		/**
		 * @brief  �X�e�[�W�̓G�z�u�}�b�v���擾
		 * @return _enemyStageParamMap
		 */
		 //std::unordered_map<std::string, Parameter::EStageParam>GetStageEnemyParameter() { return _enemyStageParamMap; }
		std::unordered_map<int, ESMV> GetFloorEnemyMap() { return _eStageNumMap; }

		/**
		 * @brief  �t���A�ԍ����L�[�Ƃ������x���Ǝv�l���[�`���ԍ��̃R���e�i���擾
		 * @return _vLevelRoutineMap
		 */
		//std::unordered_map<int, LevelRoutine> GetLevelRoutineMap() { return _vLevelRoutineMap; }


	private:
		//std::unordered_map<std::string, Parameter::EStageParam>     _enemyStageParamMap; //!< �G�̃X�e�[�W�z�u��ۑ�
		//std::unordered_map<std::string, Type>            _eType;              //!< �G�̎�ނ��L�[�Ƃ����v�f��ۑ�
		//std::unordered_map<std::string, StageMap>        _eSMap;              //!< �X�e�[�W�ԍ����L�[�Ƃ��ėv�f��ۑ�

		ESMV _eStageParamV; //!< 1�t���A�̓G�z�u�����i�[

		std::unordered_map<int, ESMV> _eStageNumMap; //!< �t���A�ԍ����ƂɊi�[
		std::vector<DoubleMap> _vDoubleMap; //!< double�^���i�[����R���e�i
		//LevelRoutine _vLevelRoutine; //!< ���x���Ǝv�l���[�`���ԍ���ۑ�
		//std::unordered_map<int, LevelRoutine> _vLevelRoutineMap; //!< �t���A�ԍ����Ƃɕۑ�

	};
}

