///
/// @file    AssetServer.cpp
/// @brief   アセットサーバー
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AssetServer.h"
#include <DxLib.h>

namespace Asset = AppFrame::Asset;

/// コンストラクタ
Asset::AssetServer::AssetServer(Game& game): _game{game} {
  Init();
}
/// 初期化
void Asset::AssetServer::Init() {
  Clear();
}
/// クリア 
void Asset::AssetServer::Clear() {
	ClearTextures();
  ClearModels();
}
/// 画像の読み込み
void Asset::AssetServer::LoadTexture(std::string_view key, const Texture& texture) {
  if (_textures.contains(key.data())) {
    // 登録済みの場合は画像を削除
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
/// 画像の一括読み込み
void Asset::AssetServer::LoadTextures(const TextureMap& textureMap) {
    for (auto&& [key, texture] : textureMap) {
        auto tex = texture;
        // _currentPath(格納フォルダ)＋ファイル名
        tex.filename = (_currentPath / tex.filename).generic_string();
        LoadTexture(key, tex);
    }
}
void Asset::AssetServer::ChangeCurrentPath(std::string_view path) {
    _currentPath = path;
}

/// 画像ハンドルの取得
int Asset::AssetServer::GetTexture(std::string_view key, int no) {
  if (!_textures.contains(key.data())) {
    return -1;
  }
  auto&& [divGraph, handles] = _textures[key.data()];
	auto handle = handles.at(no);
	return handle;
}
/// 画像ハンドルの分割数の取得
int Asset::AssetServer::GetTextureCount(std::string_view& key) {
  if (!_textures.contains(key.data())) {
    return -1;
  }
  auto&& [divGraph, handles] = _textures[key.data()];
	int allNnum = static_cast<int>(handles.size());
	return allNnum;
}
/// 画像情報の取得
Asset::Texture Asset::AssetServer::GetTextureInfo(std::string_view& key) {
  if (!_textures.contains(key.data())) {
    return Texture();
  }
  auto&& [divGraph, handles] = _textures[key.data()];
  return divGraph;
}
/// 画像の削除
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

/// モデルの読み込み
int Asset::AssetServer::LoadModel(std::string_view key, const std::string_view filename) {
	if (_models.contains(key.data())) {
		auto& [filename, handles] = _models[key.data()];
		// 登録済みの場合はモデルを削除
		for (auto handle : handles) {
			MV1DeleteModel(handle);
		}
		handles.clear();
		_models.erase(key.data());
	}
	auto handle = MV1LoadModel(filename.data());


    ////////////ここにフロアの名前を入力 ↓↓にコリジョンメッシュを入力
    //if (filename == "floor") {
    //    _frameMapCollision = MV1SearchFrame(handle, "collisionname");
    //}



	std::vector<int> handles{handle};
	_models.emplace(key, std::make_pair(filename.data(), handles));
	return handle;
}
/// モデルの一括読み込み
void Asset::AssetServer::LoadModels(const ModelMap& modelMap) {
  for (auto&& [key, filename] : modelMap) {
      // _currentPath(格納フォルダ)＋ファイル名
      auto path = (_currentPath / filename).generic_string();
      LoadModel(key, path);
  }
}
/// モデルのハンドルの取得
std::pair<int, int> Asset::AssetServer::GetModel(std::string_view key, int no) {
    if (!_models.contains(key.data())) {
        // キーが未登録
        return std::make_pair(-1, no);
    }
  auto& [filename, handles] = _models[key.data()];
  if (no < handles.size()) {
      return std::make_pair(handles[no], no); // 既存noの場合
  }
  // 新規noの場合は複製する
  auto handle = MV1DuplicateModel(handles[0]);  /// handles[0]がオリジナル
  handles.push_back(handle);
  return std::make_pair(handle, static_cast<int>(handles.size()) - 1);
}
/// 全てのモデルを削除してクリアする
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
/// Duplicateしたモデルだけ削除してクリアする
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

/// 音ファイルの読み込み
void Asset::AssetServer::LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad) {
    if (_sounds.contains(key.data())) {
        // キーがあった登録済み
        return;
    }
    // キーが無かった
    auto&& [filename, isLoad] = filename_isLoad;
    auto handle = -1;
    if (isLoad) {
        handle = LoadSoundMem(filename.c_str());
    }
    // キーとデータをmapに登録
    _sounds.emplace(key, std::make_pair(filename, handle));
}
/// 音ファイルの一括読み込み
void Asset::AssetServer::LoadSounds(const SoundMap& soundMap) {
    for (auto&& [key, filename_isLoad] : soundMap) {
        auto [filename, isLoad] = filename_isLoad;
        // _currentPath(格納フォルダ)＋ファイル名
        filename = (_currentPath / filename).generic_string();
        LoadSound(key, { filename, isLoad });
    }
}

/// 音ファイル情報の取得
std::pair<std::string, int> Asset::AssetServer::GetSoundInfo(std::string_view key) {
  if (!_sounds.contains(key.data())) {
    // キーが未登録
    return std::make_pair("", -1);
  }
  return _sounds[key.data()];
}

