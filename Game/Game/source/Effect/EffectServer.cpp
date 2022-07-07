/*****************************************************************//**
 * @file   EffectServer.cpp
 * @brief  �G�t�F�N�g�T�[�o�[
 *
 * @author yamawaki kota
 * @date   December 28 2021
 *********************************************************************/

#include "EffectServer.h"
namespace MachineHuck::Effect {
	std::unordered_map<std::string, std::pair<int, std::string >> EffectServer::_effects;
	std::unordered_map<std::string, int>  EffectServer::_playing_effects;
	int  EffectServer::LoadEffect(std::string keyname, std::string filename, float size) {
		auto ite = _effects.find(keyname);
		if (ite != _effects.end()) {
			return -1;  //���ɃL�[���������玸�s
		}
		int handle = LoadEffekseerEffect(filename.data(), size);
		std::pair<int, std::string > a(handle, filename);
		_effects.emplace(keyname, a);
		return _effects[keyname].first;
	}
	int EffectServer::GetEffect(std::string keyname) {
		auto ite = _effects.find(keyname);
		if (ite == _effects.end()) {
			return -1;  //�L�[���Ȃ������玸�s
		}
		else
		{
			return _effects[keyname].first;
		}
	}
	int EffectServer::PlayEffect3D(std::string keyname) {
		auto ite = _effects.find(keyname);
		if (ite == _effects.end()) {
			return -1;   //�L�[���Ȃ������玸�s
		}
		int playhandle = PlayEffekseer3DEffect(_effects[keyname].first);
		auto ite2 = _playing_effects.find(keyname);
		if (ite2 == _playing_effects.end()) {
			_playing_effects.emplace(keyname, playhandle);//�L�[���Ȃ����� �V���ɓo�^
		}
		if (ite2 != _playing_effects.end())
		{
			_playing_effects[keyname] = playhandle; //�L�[���������@�n���h���̍X�V
		}
		return playhandle;
	}
	int EffectServer::PlayEffect2D(std::string keyname) {
		auto ite = _effects.find(keyname);
		if (ite == _effects.end()) {
			return -1;   //�L�[���Ȃ������玸�s
		}
		int playhandle = PlayEffekseer2DEffect(_effects[keyname].first);
		auto ite2 = _playing_effects.find(keyname);
		if (ite2 == _playing_effects.end()) {
			_playing_effects.emplace(keyname, playhandle);//�L�[���Ȃ����� �V���ɓo�^
		}
		if (ite2 != _playing_effects.end())
		{
			_playing_effects[keyname] = playhandle; //�L�[���������@�n���h���̍X�V
		}


		return playhandle;
	}
	int EffectServer::GetPlayingEffect(std::string keyname) {
		auto ite = _playing_effects.find(keyname);
		if (ite == _playing_effects.end()) {
			return -1;   //�L�[���Ȃ������玸�s
		}
		else
		{
			return _playing_effects[keyname];
		}
	}
	void EffectServer::SetPositionEffect3D(VECTOR _pos, std::string playeffectname) {
		// �Đ����̃G�t�F�N�g���ړ�����B
		SetPosPlayingEffekseer3DEffect(GetPlayingEffect(playeffectname), _pos.x, _pos.y, _pos.z);
	}
	void EffectServer::SetPositionEffect2D(std::pair<int, int> _pos2D, std::string playeffectname) {
		SetPosPlayingEffekseer2DEffect(GetPlayingEffect(playeffectname), _pos2D.first, _pos2D.second, 0);
	}
	void EffectServer::Clear() {
		for (auto&& key : _effects) {
			DeleteEffekseerEffect(key.second.first); // �G�t�F�N�g���\�[�X���폜����B
		}
		_effects.clear();
		_playing_effects.clear();
	}
	int  EffectServer::EffekseerInit() {  //Effekseer�̏������ƁAEffekseer���g�����߂ɕK�v�Ȏ��O����
		SetUseDirect3DVersion(DX_DIRECT3D_11);
		if (Effekseer_Init(8000) == -1) {
			DxLib_End();
			return -1;
		}
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
		Effekseer_SetGraphicsDeviceLostCallbackFunctions();
		Effekseer_Set2DSetting(1920, 1080);
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		return 0;
	}
	void   EffectServer::SyncCamEffekseer() {
		Effekseer_Sync3DSetting(); // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	}

	void EffectServer::UpdateEffect3D() {
		UpdateEffekseer3D(); // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	}

	void EffectServer::RenderEffect3D() {
		DrawEffekseer3D(); // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B

	}

	void EffectServer::UpdateEffect2D() {
		UpdateEffekseer2D(); // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	}


	void EffectServer::RenderEffect2D() {
		DrawEffekseer2D(); // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	}


	void EffectServer::EndEffekseer() {
		EffectServer::Clear();
		Effkseer_End(); // Effekseer���I������B
	}
}