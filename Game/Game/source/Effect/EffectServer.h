/*****************************************************************//**
 * @file   EffectServer.cpp
 * @brief  �G�t�F�N�g�T�[�o�[
 *
 * @author yamawaki kota
 * @date   December 28 2021
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "appframe.h"
namespace MachineHuck::Effect {
	class EffectServer {
	public:


		EffectServer() {};
		~EffectServer() {};

		//�L�[�ƃt�@�C���l�[���A�G�t�F�N�g�̃T�C�Y���w�肵�ăG�t�F�N�g�̓ǂݍ��݁{_effects�ւ̓o�^
		//�߂�l�@�n���h�� �����@ -1 ���s : ����(������j�C�ӂ̃L�[�̖��O�A�t�@�C���ւ̃p�X���A�G�t�F�N�g�̃T�C�Y�w��
		static int LoadEffect(std::string keyname, std::string filename, float size);

		//�G�t�F�N�g�n���h���̎擾�i�߂�l_�n���h���F ����_Load effect�Ŏw�肵���C�ӂ̃L�[�j
		static int GetEffect(std::string keyname);

		//�G�t�F�N�g�̍Đ��{_playing_effects�ւ̓o�^�@
		//�߂�l  �n���h�� �����@-1 ���s �F �����@LoadEffect()�œǂݍ��񂾃L�[�̖��O
		static int PlayEffect3D(std::string keyname);

		//�G�t�F�N�g�̍Đ��{_playing_effects�ւ̓o�^�@
		//�߂�l  �n���h�� �����@-1 ���s �F �����@LoadEffect()�œǂݍ��񂾃L�[�̖��O
		static int PlayEffect2D(std::string keyname);

		//�Đ����G�t�F�N�g�̃n���h���̎擾
		//�߂�l�@�n���h�� �����@-1 ���s�F���� _playing_effects�ɓo�^����Ă���L�[���iPlay�{����_PlayEffect()�Ŏw�肵���C�ӂ̃L�[���j
		static int GetPlayingEffect(std::string playingkeyname);

		//�G�t�F�N�g�̈ʒu�����肷�� ����(������j�G�t�F�N�g�̈ʒu�A_playing_effects�ɓo�^����Ă���L�[���iPlay�{����_PlayEffect()�Ŏw�肵���C�ӂ̃L�[���j
		static void SetPositionEffect3D(VECTOR _pos, std::string playeffectname);

		//�G�t�F�N�g�̈ʒu�����肷�� ����(������j�G�t�F�N�g�̈ʒu�A_playing_effects�ɓo�^����Ă���L�[���iPlay�{����_PlayEffect()�Ŏw�肵���C�ӂ̃L�[���j
		static void SetPositionEffect2D(std::pair<int, int>_pos2D, std::string playeffectname);

		//�}�b�v�ɓo�^����Ă��邷�ׂĂ̗v�f�̍폜�A�G�t�F�N�g���\�[�X�̉��
		static void Clear();


		//�����o�Ɋ֘A���Ȃ�Effekseer�̊֐�

		//Effekseer�̏�������Effekseer���g�����߂ɕK�v�Ȏ��O����
		static int EffekseerInit();
		// Effekseer�̏I������
		static void EndEffekseer();

		//1�t���[���Ɉ��Ăяo��
		// 3D�֌W
		// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B�i3D���j
		static void SyncCamEffekseer();
		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		static void UpdateEffect3D();
		// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		static void RenderEffect3D();
		//2D�֌W
		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		static void UpdateEffect2D();
		// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		static void RenderEffect2D();


	private:
		//�G�t�F�N�g�̃n���h�����Ǘ�����}�b�v�@�i�L�[�i�C�ӂ̕�����)�F�l (�n���h���ƃt�@�C�����̃y�A�j�j
		static std::unordered_map<std::string, std::pair<int, std::string >> _effects;
		//�Đ����G�t�F�N�g�̃n���h�����Ǘ�����}�b�v�@�i�L�[�i�C�ӂ̕�����)�F�l (�Đ����G�t�F�N�g�̃n���h���j�j
		static std::unordered_map<std::string, int>  _playing_effects;



	};
}