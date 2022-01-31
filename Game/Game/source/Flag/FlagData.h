
/*****************************************************************//**
 * @file   FlagData.h
 * @brief  �t���O�f�[�^�Ǘ��N���X
 *  
 * @author hikaru Goto
 * @date   January 28 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
namespace MachineHuck::Flag {

	class FlagData {

	public:


		static bool GetFadeInFlag() { return _fadeInFlag; }

		static bool GetFadeOutFlag() { return _fadeOutFlag; }

		static void SetFadeInFlag(bool flag) { _fadeInFlag = flag; }

		static void SetFadeOutFlag(bool flag) { _fadeOutFlag = flag; }

		/**
		 * @brief  �u���b�N�A�E�g�̃t���O���擾
		 * @return _blackOutFlag
		 */
		static bool GetBlackOutFlag() { return _blackOutFlag; }

		/**
		 * @brief �u���b�N�A�E�g�̃t���O��ݒ�
		 * @param flag
		 */
		static void SetBlackOutFlag(bool flag) { _blackOutFlag = flag; }

		/**
		 * @brief  �v���C���[�̖��G���Ԃ��擾
		 * @return _noDamageTime
		 */
		static bool GetNoDamageTime() { return _noDamageTime; }

		/**
		 * @brief �v���C���[�̖��G���Ԃ�ݒ�
		 * @param time
		 */
		static void SetNoDamageTime(bool time) { _noDamageTime = time; }

		/**
		 * @brief  �J�����ʒu���擾
		 * @return _cameraPos
		 */
		static VECTOR GetCameraPos() { return _cameraPos; }

		/**
		 * @brief �J�����ʒu��ݒ�
		 * @param pos�@�J�����ʒu
		 */
		static void SetCameraPos(VECTOR pos) { _cameraPos = pos; }

	private:

		static bool _fadeOutFlag;
		static bool _fadeInFlag;
		static bool _blackOutFlag;
		static VECTOR _cameraPos;
		static int _noDamageTime;
	};

}


