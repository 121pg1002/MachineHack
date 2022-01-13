///
/// @file    Scene.h
/// @brief   シーンの基底クラス
///          各シーンはこのクラスを継承する
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>

namespace MachineHuck::Actor {
	class ActorServer;
	class ActorFactory;
}

namespace AppFrame {
	class Game;
	namespace Input {
		class InputComponent;
	}

	namespace Asset{
		class AssetServer;
	}

	namespace Scene {
		class SceneServer;
	}
	namespace Sound {
		class SoundComponent;
	}
}

namespace AppFrame::Scene {
	/// @class   Scene
	/// @brief   シーンのフレームワーク
	class Scene {
	public:
		/// コンストラクタ
		/// @param[in] game ゲームクラスの参照
		Scene(Game& game);
		/// デストラクタ
		virtual ~Scene();
		/// 初期化
		/// SceneServer::Register登録時に実行する
		virtual void Init() = 0;
		/// 入口処理
		/// SceneServer::PushBack時に実行する
		virtual void Enter() {};
		/// 入力処理
		/// SceneServer::Inputから実行する
		virtual void Input(Input::InputComponent& input) {};
		/// 更新処理
		/// SceneServer::Updateから実行する
		virtual void Update() {};
		/// 描画処理
		/// SceneServer::Renderから実行する
		virtual void Render() {};
		/// 出口処理
		/// SceneServer::PopBackから実行する
		virtual void Exit() {};
		/// ゲームの取得
		/// @return ゲームクラスの参照
		Game& GetGame() const { return _game; };
		/// アクターサーバーの取得
		/// @return アクターサーバーの参照
		MachineHuck::Actor::ActorServer& GetActorServer();
		/// アクターファクトリーの取得
		/// @return アクターファクトリーの参照
		MachineHuck::Actor::ActorFactory& GetActorFactory();
		/// アセットサーバーの取得
		/// @return アセットサーバーの参照
		Asset::AssetServer& GetAssetServer();
		/// シーンサーバーの取得
		/// @return シーンサーバーの参照
		SceneServer& GetSceneServer();
		/// サウンドコンポーネントの取得
		/// @return サウンドコンポーネントの参照
		Sound::SoundComponent& GetSoundComponent();
	private:
		/// ゲームクラスの参照
		Game& _game;
	};
}


