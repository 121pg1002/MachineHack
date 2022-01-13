///
/// @file    AssetServer.h
///   アセットサーバー
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <filesystem>
#include <unordered_map>
#include <string>
#include <memory>

namespace AppFrame {
	class Game;
}

namespace AppFrame {

	namespace Asset {
		// 画像ファイル用
		struct Texture {
			std::string filename;
			int xNum;
			int yNum;
			int xSize;
			int ySize;
		};

		// リソース管理サーバ
		class AssetServer {
		public:
			/// 任意の文字列をキーとしてDivGraphを管理
			using TextureMap = std::unordered_map<std::string, Texture>;

			/// 任意の文字列をキーにして音ファイル名と事前読み込みの有無を管理
			using SoundMap = std::unordered_map<std::string, std::pair<std::string, bool>>;

			/// 任意の文字列をキーにしてモデルファイル名を管理
			using ModelMap = std::unordered_map<std::string, std::string>;

			/// コンストラクタ
			/// @param game Gameクラスへの参照
			AssetServer(Game& game);
			/// デストラクタ 
			virtual ~AssetServer() = default;

			/// 初期化
			virtual void	Init();

			/// クリア
			/// 画像、モデル、音の全てをクリアする
			virtual void	Clear();

			/// 画像の読み込み
			/// @param key キーとなる任意の文字列
			/// @param divGraph 
			virtual void LoadTexture(std::string_view key, const Texture& texture);

			/// 画像の一括読み込み
			/// @param[in] textureMap 画像のテーブル
			virtual void LoadTextures(const TextureMap& textureMap);

			/// 読み込み時のカレントフォルダの変更
		  /// カレントフォルダ直下のファイルを読み込む
		  /// @param[in] path カレントフォルダ
			virtual void ChangeCurrentPath(std::string_view path);


			/// 画像ハンドルの取得
			/// @param[in] key 登録済みのキー
			/// @param[in] no  分割時の番号
			/// @return 画像のハンドル
			virtual int GetTexture(std::string_view key, int no = 0);

			/// 画像ハンドルの分割数の取得
			/// @param[in] key 登録済みのキー
			/// @return 分割総数
			virtual int GetTextureCount(std::string_view& key);

			/// 画像情報の取得
			/// @param[in] key 登録済みのキー
			/// @return	Texture 画像情報
			virtual Texture GetTextureInfo(std::string_view& key);

			/// 画像の削除
			/// @param[in] key 登録済みのキー
			virtual void	ClearTextures();

			/// モデルの読み込み
			/// @param key キーとなる任意の文字列
			/// @param[in] filename mv1ファイル名
			/// @return モデルのハンドル
			virtual int LoadModel(std::string_view key, const std::string_view filename);

			/// モデルの一括読み込み
			/// @param modelMap モデルのテーブル
			virtual void LoadModels(const ModelMap& modelMap);

			/// モデルのハンドルの取得
			/// 既読の場合は複製する
			/// @param key 登録済みのキー
			/// @param no 同一モデルの通し番号
			/// @return モデルのハンドルと実施の登録番号
			virtual std::pair<int, int> GetModel(std::string_view key, int no = 0);

			/// 全てのモデルを削除してクリアする
			virtual void ClearModels();
			/// Duplicateしたモデルだけ削除してクリアする
			virtual void DeleteDuplicateModels();

			/// 音ファイルの読み込み
		  /// @param[in] key キーとなる任意の文字列
		  /// @param[in] filename_isLoad ファイル名と事前読み込み有無のペア 
			virtual void LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad);


			/// 音ファイルの一括読み込み
			/// @param[in] soundMap 音ファイルのテーブル
			virtual void LoadSounds(const SoundMap& soundMap);

			/// 音ファイル情報の取得
			/// @param[in] key 登録済みのキー
			/// @return 音ファイル名, ハンドル
			virtual std::pair<std::string, int> GetSoundInfo(std::string_view key);

		private:
			Game& _game;

			/// 格納フォルダへの相対パス
			std::filesystem::path _currentPath;

			/// 任意の文字列をキーにしてDivGraphと画像ハンドルのペアを管理
			std::unordered_map<std::string, std::pair<Texture, std::vector<int>>> _textures;
			/// 任意の文字列をキーにして音ファイル名とハンドルのペアを管理
			std::unordered_map<std::string, std::pair<std::string, int>> _sounds;
			/// 任意の文字列をキーにしてモデルファイル名とハンドルのペアを管理
			std::unordered_map<std::string, std::pair<std::string, std::vector<int>>> _models;
		};
	}

}






