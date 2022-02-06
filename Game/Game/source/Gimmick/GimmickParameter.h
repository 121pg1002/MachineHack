
/*****************************************************************//**
 * @file   GimmickParameter.h
 * @brief  �M�~�b�N��json���Ǘ��N���X
 * 
 * @author hikaru Goto
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <string>
#include "../Parameter/GStageParam.h"

namespace MachineHuck::Gimmick {

	class GimmickParameter {
	public:

        using GSV = std::vector<Parameter::GStageParam>;
        //using StageV = std::vector<int>;

        /**
         * @brief �ϐ��̏�����        
         */
        GimmickParameter();

        /**
         * @brief �ϐ��̉��         
         */
        ~GimmickParameter();

		/**
        * @brief  json����M�~�b�N�̃X�e�[�W�z�u��ǂݍ���
        * @param  stageNo      �X�e�[�W�ԍ�
        * @param  filePath �t�@�C���p�X
        * @return true  �ǂݍ��ݐ���
        *         false �ǂݍ��ݎ��s
        */
		bool LoadGimmickStageParameter(const int stageNo, const std::string& filePath);

        /**
        * @brief   �x�N�^�[�z����擾����
        * @return  _gimickStageParamV
        */
        GSV GetStageVector() { return _gimmickStageParamV; }

        /**
         * @brief  �t���A�ԍ��̏����擾
         * @return _gimmickStageNumMap
         */
        std::unordered_map<int, GSV> GetFloorGimmickMap() { return _gimmickStageNumMap; }


    private:

        GSV _gimmickStageParamV; //!< 1�t���A�����i�[

        std::unordered_map<int, GSV> _gimmickStageNumMap; //!< �t���A�ԍ����ƂɊi�[

	};
}

