
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
		 * @brief  �v���C���[�̖��G�t���O���擾
		 * @return _noDamageTime
		 */
		static bool GetNoDamageFlag() { return _noDamageFlag; }

		/**
		 * @brief �v���C���[�̖��G�t���O��ݒ�
		 * @param time
		 */
		static void SetNoDamageFlag(bool flag) { _noDamageFlag = flag; }

		/**
		 *
		 * @brief  �v���C���[�̃_���[�W�t���O���擾       
		 * @return _damageFlag
		 */
		static int GetDamageFlag() { return _damageFlag; }

		/**
		 * 
		 * @brief  �v���C���[�̃_���[�W�t���O��ݒ�       
		 * @param  flag
		 */
		static void SetDamageFlag(bool flag) { _damageFlag = flag; }


		/**
		 * @brief  �n�b�L���O��Ԃ̖��G�t���O���擾
		 * @return _huckNoDamageTime
		 */
		static bool GetHuckNoDamageFlag() { return _huckNoDamageFlag; }

		/**
		 * @brief �n�b�L���O��Ԃ̖��G�t���O��ݒ�
		 * @param flag
		 */
		static void SetHuckNoDamageFlag(bool flag) { _huckNoDamageFlag = flag; }

		/**
		 *
		 * @brief  �n�b�L���O��Ԃ̃_���[�W�t���O���擾       
		 * @return _huckDamageFlag
		 */
		static int GetHuckDamageFlag() { return _huckDamageFlag; }

		/**
		 * 
		 * @brief  �n�b�L���O��Ԃ̃_���[�W�t���O��ݒ�       
		 * @param  flag
		 */
		static void SetHuckDamageFlag(bool flag) { _huckDamageFlag = flag; }





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
		static bool _noDamageFlag;
		static bool _damageFlag;
		static bool _huckNoDamageFlag;
		static bool _huckDamageFlag;


	};

}


