
/*****************************************************************//**
 * @file   StageParameter.h
 * @brief  �X�e�[�W�̏���json����ǂݍ��ރN���X
 * 
 * @author hikaru Goto
 * @date   December 28 2021
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include "../Parameter/StageParam.h"

//using Level = std::unordered_map<std::string, StageParam>;
namespace MachineHuck::Stage {
	/**
	 * @class �X�e�[�W���N���X
	 * @brief �X�e�[�W����json����ǂݍ��ރN���X
	 */
	class StageParameter {

	public:

		using SMV = std::vector<Parameter::StageParam>;
		using StageV = std::vector<int>;

		/**
		 * @brief �ϐ��̏�����
		 */
		StageParameter();

		/**
		 * @brief �ϐ��̉��
		 */
		~StageParameter();

		/**
		* @brief  �X�e�[�W�̔z�u����json����ǂݍ���
		* @param  num �X�e�[�W�ԍ�
		* @param  filePath
		*/
		void LoadStageParameter(const int num, const std::string& filePath);

        /**
         * @brief�@�X�e�[�W�̃e�[�u����json����ǂݍ���
         * @param filePath
         */
		void LoadStageTable(const std::string& filePath);

		/**
		 * @brief   �R���e�i���擾����
		 * @return  _stageParamMap
		 */
		 //StageMap GetStageMap() { return _stageParamMap; }

		 /**
		  * @brief   �x�N�^�[�z����擾����
		  * @return  _stageParamV
		  */
		std::vector<Parameter::StageParam> GetStageVector() { return _stageParamV; }

		/**
		 * @brief  �t���A�ԍ��̏����擾
		 * @return _stageNumMap
		 */
		std::unordered_map<int, SMV> GetFloorMap() { return _stageNumMap; }

		/**
		  * @brief   �X�e�[�W�e�[�u���z����擾����
		  * @return  _stageTableV
		  */
		std::vector<StageV> GetStageTableVector() { return _stageTableV; }


	private:


		SMV _stageParamV; //!< 1�t���A�����i�[

		std::unordered_map<int, SMV> _stageNumMap; //!< �t���A�ԍ����ƂɊi�[

		std::vector<StageV> _stageTableV; //!< �X�e�[�W�e�[�u�����i�[����z��



	};
}
