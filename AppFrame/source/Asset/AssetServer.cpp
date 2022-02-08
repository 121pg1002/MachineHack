/*****************************************************************//**
 * @file   AssetServer.cpp
 * @brief  �A�Z�b�g�T�[�o�[
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
 *********************************************************************/

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
  ClearMaps();
}
/// �摜�̓ǂݍ���
void Asset::AssetServer::LoadTexture(std::string_view key, const Texture& texture) {
  if (_textures.count(key.data()) != 0) {
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
  if (_textures.count(key.data()) != 1) {
    return -1;
  }
  auto&& [divGraph, handles] = _textures[key.data()];
	auto handle = handles.at(no);
	return handle;
}

bool Asset::AssetServer::GetTextures(std::string_view key, std::vector<int>& outHandles) {
    if (_textures.count(key.data()) != 1) {
        return false;
    }
    auto&& [divGraph, handles] = _textures[key.data()];
    outHandles.resize(handles.size());
    outHandles = handles;
    return true;
}
/// �摜�n���h���̕������̎擾
int Asset::AssetServer::GetTextureCount(std::string_view& key) {
  if (_textures.count(key.data()) != 1) {
    return -1;
  }
  auto&& [divGraph, handles] = _textures[key.data()];
	int allNnum = static_cast<int>(handles.size());
	return allNnum;
}
/// �摜���̎擾
Asset::Texture Asset::AssetServer::GetTextureInfo(std::string_view& key) {
  if (_textures.count(key.data()) != 1) {
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
	if (_models.count(key.data()) != 0) {
		auto& [filename, handles] = _models[key.data()];
		// �o�^�ς݂̏ꍇ�̓��f�����폜
		for (auto handle : handles) {
			MV1DeleteModel(handle);
		}
		handles.clear();
		_models.erase(key.data());
	}
	auto handle = MV1LoadModel(filename.data());

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

//�X�e�[�W�p�̃��f���ǂݍ���
int Asset::AssetServer::LoadMap(std::string key, const std::string_view filename) {
    
    //������2���̏ꍇ����ōl����
    auto keyNum = key.substr(5, 1);
    int num = std::stoi(keyNum);
    //auto keyNum = key.substr(4, 2);

    
    if (_maps.count(num) != 0) {
        auto&& [filename, handles] = _maps[num];
        // �o�^�ς݂̏ꍇ�̓��f�����폜
        for (auto handle : handles) {
            MV1DeleteModel(handle);
        }
        handles.clear();
        _maps.erase(num);
    }

    auto handle = MV1LoadModel(filename.data());

    ////////////�����Ƀt���A�̖��O����� �����ɃR���W�������b�V�������
    //if (filename == "floor") {
    //    _frameMapCollision = MV1SearchFrame(handle, "collisionname");
    //}
    
    //������2���̏ꍇ����ōl���遪��������
    //key�́AStage + number�Ő����������o��

    std::vector<int> handles{ handle };
    _maps.emplace(num, std::make_pair(filename.data(), handles));
    return handle;
}

//�X�e�[�W�p�̃��f���ꊇ�ǂݍ���
void Asset::AssetServer::LoadMaps(const StageMap& stageMap) {

    for (auto&& [key, fileName] : stageMap) {
    
        auto path = (_currentPath / fileName).generic_string();
        LoadMap(key, path);
    
    }
}


/// ���f���̃n���h���̎擾
std::pair<int, int> Asset::AssetServer::GetModel(std::string_view key, int no) {
    if (_models.count(key.data()) != 1) {
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


/// �X�e�[�W���f���̃n���h���̎擾
std::pair<int, int> Asset::AssetServer::GetMap(int keyNum, int no) {
    if (_maps.count(keyNum) != 1) {
        // �L�[�����o�^
        return std::make_pair(-1, no);
    }
    auto& [filename, handles] = _maps[keyNum];

    if (no < handles.size()) {
        return std::make_pair(handles[no], no); // ����no�̏ꍇ
    }

    // �V�Kno�̏ꍇ�͕�������
    auto&& handle = MV1DuplicateModel(handles[0]);  /// handles[0]���I���W�i��
    handles.push_back(handle);
    return std::make_pair(handle, static_cast<int>(handles.size()) - 1);
       // return handle; 
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

///Duplicate���f���̂ݍ폜���ăN���A����
/// //���
void Asset::AssetServer::ClearDuplicateModels() {

    for (auto&& [key, model] : _models) {
        auto&& [filename, handles] = model;

        for (auto handle : handles) {

            //if()


            MV1DeleteModel(handle);
        }
        handles.clear();
    }

}

/// �S�ẴX�e�[�W���f�����폜���ăN���A����
void Asset::AssetServer::ClearMaps() {
    for (auto&& [key, model] : _maps) {
        auto&& [filename, handles] = model;
        for (auto handle : handles) {
            MV1DeleteModel(handle);
        }
        handles.clear();
    }
    _maps.clear();
}



/// Duplicate�������f�������폜���ăN���A����
void Asset::AssetServer::DeleteDuplicateModels() {
  for (auto&& [key, model] : _models) {
    auto&& [filename, handles] = model;

    auto original = handles[0];
    auto isDead = [original](auto handle) {
        if (original != handle) {
            MV1DeleteModel(handle);
            return true;
        } 
        return false; };
    auto it = std::remove_if(handles.begin(), handles.end(), isDead);
    handles.erase(it, handles.end());
    
  }
}

/// Duplicate�������f�������폜���ăN���A����
void Asset::AssetServer::DeleteDuplicateMaps() {
    for (auto&& [key, model] : _maps) {
        auto&& [filename, handles] = model;

        auto original = handles[0];
        auto isDead = [original](auto handle) {
            if (original != handle) {
                MV1DeleteModel(handle);
                return true;
            }
            return false; };
        auto it = std::remove_if(handles.begin(), handles.end(), isDead);
        handles.erase(it, handles.end());

    }
}


/// ���t�@�C���̓ǂݍ���
void Asset::AssetServer::LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad) {
    if (_sounds.count(key.data()) != 0) {
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
  if (_sounds.count(key.data()) != 1) {
    // �L�[�����o�^
    return std::make_pair("", -1);
  }
  return _sounds[key.data()];
}

