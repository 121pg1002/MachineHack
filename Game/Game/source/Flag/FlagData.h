
/*****************************************************************//**
 * @file   FlagData.h
 * @brief  �t���O�f�[�^�Ǘ��N���X
 *
 * @author hikaru Goto
 * @date   January 28 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <vector>
//#include "AppFrame.h"
namespace MachineHuck::Flag {

	class FlagData {

	public:

		/**
		 * @brief  �t�F�[�h�C���t���O���擾     
		 * @return �t�F�[�h�C���̃t���O
		 */
		static bool GetFadeInFlag() { return _fadeInFlag; }

		/**
		 * @brief  �t�F�[�h�A�E�g�t���O���擾     
		 * @return �t�F�[�h�A�E�g�̃t���O
		 */
		static bool GetFadeOutFlag() { return _fadeOutFlag; }

		/**
		 * @brief  �t�F�[�h�C���t���O��ݒ�     
		 * @return �t�F�[�h�C���̃t���O
		 */
		static void SetFadeInFlag(bool flag) { _fadeInFlag = flag; }

		/**
		 * @brief  �t�F�[�h�A�E�g�t���O��ݒ�     
		 * @return �t�F�[�h�A�E�g�̃t���O
		 */
		static void SetFadeOutFlag(bool flag) { _fadeOutFlag = flag; }

		/**
		 *
		 * @brief  �V�[���J�ڂɂ����錻�V�[����Exit�������s��Ȃ����ǂ���
		 * @return _noExitFlag
		 */
		static bool GetNoExitFlag() { return _noExitFlag; }

		/**
		 * @brief  �V�[���J�ڂɂ����錻�V�[����Exit�������s��Ȃ����̐ݒ�
		 * @param  flag
		 */
		static void SetNoExitFlag(bool flag) { _noExitFlag = flag; }

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
		 * @brief  �v���C���[�����S�������t���O���擾
		 * @return _playerDead
		 */
		static bool GetPlayerDead() { return _playerDead; }

		/**
		 * @brief  �v���C���[�����S�����t���O��ݒ�
		 * @param  flag
		 */
		static void SetPlayerDead(bool flag) { _playerDead = flag; }

		/**
		 * @brief  �_�N�g���[�v�̎擾     
		 * @return _ductWarp
		 */
		static bool GetDuctWarp() { return _ductWarp; }

		/**
		 * @brief  �_�N�g���[�v�̐ݒ�    
		 * @param  flag
		 */
		static void SetDuctWarp(bool flag) { _ductWarp = flag; }

		/**
		 * @brief  �X���C�h�C���t���O���擾         
		 * @return _slideInFlag
		 */
		static bool GetSlideIn() { return _slideInFlag; }

		/**
		 * @brief  �X���C�h�A�E�g�t���O���擾       
		 * @return _slideOutFlag
		 */
		static bool GetSlideOut() { return _slideOutFlag; }

		/**
		 * @brief  �X���C�h�C���t���O��ݒ�      
		 * @param  flag
		 */
		static void SetSlideIn(bool flag) { _slideInFlag = flag; }

		/**
		 * @brief  �X���C�h�A�E�g�t���O��ݒ�       
		 * @param  flag
		 */
		static void SetSlideOut(bool flag) { _slideOutFlag = flag; }

		/**
		 * @brief  �X���C�h�C���A�E�g�̃t���O���擾       
		 * @return 
		 */
		static bool GetSlideFlag() { return _slideFlag; }

		/**
		 * @brief  �X���C�h�C���A�E�g�̃t���O��ݒ�      
		 * @param  flag
		 */
		static void SetSlideFlag(bool flag) { _slideFlag = flag; }


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

		/**
		 * @brief  �n�b�L���O���̓G�̓��̈ʒu���擾
		 * @return _headPos
		 */
		static VECTOR GetHeadPos() { return _headPos; }

		/**
		 * @brief  �G�̓��̈ʒu��ݒ�
		 * @param  pos
		 */
		static void SetHeadPos(VECTOR pos) { _headPos = pos; }

		///**
		// * @brief  ���̈ʒu���擾      
		// * @return ���̍��W
		// */
		//static VECTOR GetHolePos() { return _holePos; }

		///**
		// * @brief  �����錊�̈ʒu��ݒ�       
		// * @param  pos
		// */
		//static void SetHolePos(VECTOR pos) { _holePos = pos; }


		/**
		 * @brief  ���[�v��̏����ʒu�̎擾      
		 * @return ���W
		 */
		static VECTOR GetWarpAfterPos() { return _warpAfterPos; }

		/**
		 * @brief  ���[�v��̏����ʒu�̐ݒ�      
		 * @param  pos
		 */
		static void SetWarpAfterPos(VECTOR pos) { _warpAfterPos = pos; }

		/**
		 * @brief  �v���C���[�̂���t���A�ԍ����擾
		 * @return �v���C���[�̂���t���A�ԍ�
		 */
		static int GetPlayerFloorNum() { return _PlayerNowFloorNum; }

		/**
		 * @brief �v���C���[�̂���t���A�ԍ���ݒ�
		 * @param num
		 */
		static void SetPlayerFloorNum(int num) { _PlayerNowFloorNum = num; }

		/**
		 * @brief  �v���C���[�̍s�������Ƃ̂���t���A�ԍ��z���ݒ�         
		 * @return �v���C���[���s�����t���A�ԍ��z��
		 */
		static std::vector<int> GetPlayerFloorVec() { return _playerFloorV; }


		/**
		 * @brief  �v���C���[�̍s�������Ƃ̂���t���A�ԍ��z���ݒ�       
		 * @param  floorV
		 */
		static void SetPlayerFloorVec(std::vector<int> floorV) { _playerFloorV = floorV; }


		/**
		 *.
		 * 
		 * @brief         
		 * @return 
		 */
		static bool GetEpilogueFlag() { return _epilogueFlag;}

		static void SetEpilogueFlag(bool flag) { _epilogueFlag = flag; }


#ifdef _DEBUG
		/**
		 * @brief  �f�o�b�O���[�h�ɂ�����]�ڂ���t���A�ԍ����擾         
		 * @return 
		 */
		static int GetDebugNo() { return _debugNo; }


		/**
		 * @brief  �f�o�b�O���[�h�ɂ�����]�ڂ���t���A�ԍ���ݒ�         
		 * @param  no
		 */
		static void SetDebugNo(int no) { _debugNo = no; }
#endif
		///**
		// * @brief  ������t���O���擾       
		// * @return _fallFlag
		// */
		//static bool GetFallFlag() { return _fallFlag; }

		///**
		// * @brief  ������t���O��ݒ�      
		// * @param  flag
		// */
		//static void SetFallFlag(bool flag) { _fallFlag = flag; }


	private:

		static bool _fadeOutFlag;
		static bool _fadeInFlag;
		static bool _blackOutFlag;
		static VECTOR _cameraPos;
		static bool _noDamageFlag;
		static bool _damageFlag;
		static bool _huckNoDamageFlag;
		static bool _huckDamageFlag;
		static VECTOR _headPos;
		static bool _noExitFlag;
		static bool _playerDead;
		static bool _ductWarp;
		static bool _slideInFlag;
		static bool _slideOutFlag;
		static bool _slideFlag;
	//	static VECTOR _holePos;      //!< �����錊�̈ʒu���W
		static VECTOR _warpAfterPos; //!< ���[�v��̏������W
		static int _PlayerNowFloorNum; //!< �v���C���[�̌��݂���t���A�ԍ���ۑ�
		static std::vector<int> _playerFloorV; //!< �v���C���[�̍s�������Ƃ̂���t���A�ԍ���o�^����
		static bool _epilogueFlag;  //!< �G�s���[�O�̃t���O

#ifdef _DEBUG
		static int _debugNo; //!< �f�o�b�O���[�h���ɓ]�ڂ������ԍ�
#endif
			//	static bool _fallFlag;                        //!< �����邩�ǂ����̃t���O

	};

}


