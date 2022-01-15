///
/// @file    AssetServer.cpp
/// @brief   �A�Z�b�g�T�[�o�[
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AssetServer.h"
#include <DxLib.h>

namespace Asset = AppFrame::Asset;

/// �R���X�g���N�^
Asset::AssetServer::AssetServer(Game& game): _game{game} {
  Init();
}
/// ������
void Asset::AssetServer::Init() {
  Clear();
}
/// �N���A 
void Asset::AssetServer::Clear() {
	ClearTextures();
  ClearModels();
}
/// �摜�̓ǂݍ���
void Asset::AssetServer::LoadTexture(std::string_view key, const Texture& texture) {
  if (_textures.contains(key.data())) {
    // �o�^�ς݂̏ꍇ�͉摜���폜
    auto&& [texture, handles] = _textures[key.data()];  
    for (auto handle : handles) {
      DeleteGraph(handle);
    }
    handles.clear();
    _textures.erase(key.data());
  }
  auto allNum = texture.xNum * texture.yNum;
  std::vector<int> handles(allNum);
  LoadDivGraph(texture.filename.c_str(), allNum,
               texture.xNum, texture.yNum,
               texture.xSize, texture.ySize, handles.data());

  _textures.emplace(key, std::make_pair(texture, handles));
}
/// �摜�̈ꊇ�ǂݍ���
void Asset::AssetServer::LoadTextures(const TextureMap& textureMap) {
    for (auto&& [key, texture] : textureMap) {
        auto tex = texture;
        // _currentPath(�i�[�t�H���_)�{�t�@�C����
        tex.filename = (_currentPath / tex.filename).generic_string();
        LoadTexture(key, tex);
    }
}
void Asset::AssetServer::ChangeCurrentPath(std::string_view path) {
    _currentPath = path;
}

/// �摜�n���h���̎擾
int Asset::AssetServer::GetTexture(std::string_view key, int no) {
  if (!_textures.contains(key.data())) {
    return -1;
  }
  auto&& [divGraph, handles] = _textures[key.data()];
	auto handle = handles.at(no);
	return handle;
}
/// �摜�n���h���̕������̎擾
int Asset::AssetServer::GetTextureCount(std::string_view& key) {
  if (!_textures.contains(key.data())) {
    return -1;
  }
  auto&& [divGraph, handles] = _textures[key.data()];
	int allNnum = static_cast<int>(handles.size());
	return allNnum;
}
/// �摜���̎擾
Asset::Texture Asset::AssetServer::GetTextureInfo(std::string_view& key) {
  if (!_textures.contains(key.data())) {
    return Texture();
  }
  auto&& [divGraph, handles] = _textures[key.data()];
  return divGraph;
}
/// �摜�̍폜
void Asset::AssetServer::ClearTextures() {
  for (auto&& [key, divGraph_handles] : _textures) {
    auto&& [divGraph, handles] = divGraph_handles;
    for (auto&& handle : handles) {
      DeleteGraph(handle);
    }
    handles.clear();
  }
  _textures.clear();
}

/// ���f���̓ǂݍ���
int Asset::AssetServer::LoadModel(std::string_view key, const std::string_view filename) {
	if (_models.contains(key.data())) {
		auto& [filename, handles] = _models[key.data()];
		// �o�^�ς݂̏ꍇ�̓��f�����폜
		for (auto handle : handles) {
			MV1DeleteModel(handle);
		}
		handles.clear();
		_models.erase(key.data());
	}
	auto handle = MV1LoadModel(filename.data());


    ////////////�����Ƀt���A�̖��O����� �����ɃR���W�������b�V�������
    //if (filename == "floor") {
    //    _frameMapCollision = MV1SearchFrame(handle, "collisionname");
    //}



	std::vector<int> handles{handle};
	_models.emplace(key, std::make_pair(filename.data(), handles));
	return handle;
}
/// ���f���̈ꊇ�ǂݍ���
void Asset::AssetServer::LoadModels(const ModelMap& modelMap) {
  for (auto&& [key, filename] : modelMap) {
      // _currentPath(�i�[�t�H���_)�{�t�@�C����
      auto path = (_currentPath / filename).generic_string();
      LoadModel(key, path);
  }
}
/// ���f���̃n���h���̎擾
std::pair<int, int> Asset::AssetServer::GetModel(std::string_view key, int no) {
    if (!_models.contains(key.data())) {
        // �L�[�����o�^
        return std::make_pair(-1, no);
    }
  auto& [filename, handles] = _models[key.data()];
  if (no < handles.size()) {
      return std::make_pair(handles[no], no); // ����no�̏ꍇ
  }
  // �V�Kno�̏ꍇ�͕�������
  auto handle = MV1DuplicateModel(handles[0]);  /// handles[0]���I���W�i��
  handles.push_back(handle);
  return std::make_pair(handle, static_cast<int>(handles.size()) - 1);
}
/// �S�Ẵ��f�����폜���ăN���A����
void Asset::AssetServer::ClearModels() {
	for (auto&& [key, model] : _models) {
    auto&& [filename, handles] = model;
		for (auto handle : handles) {
			MV1DeleteModel(handle);
		}
    handles.clear();
	}
	_models.clear();
}
/// Duplicate�������f�������폜���ăN���A����
void Asset::AssetServer::DeleteDuplicateModels() {
  for (auto&& [key, model] : _models) {
    auto&& [filename, handles] = model;
    auto original = handles[0];
    erase_if(handles, [original](auto handle) {
      if (original != handle) {
        MV1DeleteModel(handle);
        return true;
      }
      return false;
    });
  }
}

/// ���t�@�C���̓ǂݍ���
void Asset::AssetServer::LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad) {
    if (_sounds.contains(key.data())) {
        // �L�[���������o�^�ς�
        return;
    }
    // �L�[����������
    auto&& [filename, isLoad] = filename_isLoad;
    auto handle = -1;
    if (isLoad) {
        handle = LoadSoundMem(filename.c_str());
    }
    // �L�[�ƃf�[�^��map�ɓo�^
    _sounds.emplace(key, std::make_pair(filename, handle));
}
/// ���t�@�C���̈ꊇ�ǂݍ���
void Asset::AssetServer::LoadSounds(const SoundMap& soundMap) {
    for (auto&& [key, filename_isLoad] : soundMap) {
        auto [filename, isLoad] = filename_isLoad;
        // _currentPath(�i�[�t�H���_)�{�t�@�C����
        filename = (_currentPath / filename).generic_string();
        LoadSound(key, { filename, isLoad });
    }
}

/// ���t�@�C�����̎擾
std::pair<std::string, int> Asset::AssetServer::GetSoundInfo(std::string_view key) {
  if (!_sounds.contains(key.data())) {
    // �L�[�����o�^
    return std::make_pair("", -1);
  }
  return _sounds[key.data()];
}

