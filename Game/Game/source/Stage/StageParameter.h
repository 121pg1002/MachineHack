
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

		using StageMap = std::unordered_map<std::string, Parameter::StageParam>;

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
		* @param  filePath
		*/
		void LoadStageParameter(const std::string& filePath);

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


	private:
		//std::vector<StageP>  _stageParamV; //!<�X�e�[�W�����i�[����vector
		StageMap _stageParamMap;//!<�X�e�[�W�����i�[����map
		std::vector<Parameter::StageParam> _stageParamV;

	};
}
