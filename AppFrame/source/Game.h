///
/// @file    Game.h
/// @brief   ゲームクラスの宣言
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>

namespace AppFrame {

	namespace Asset {
		class AssetServer;
	}

	namespace Scene {
		class SceneServer;
	}

	namespace Input {
		class InputComponent;
	}

	namespace Sound {
		class SoundComponent;
	}

}

namespace MachineHuck::Actor {
	class ActorFactory;
	class ActorServer;
}

namespace MachineHuck::UI {
	class UIComponent;
	class SpriteServer;
}

namespace MachineHuck::Stage {
	class StageParameter;
}

namespace AppFrame {
	/// @class   Game
/// @brief   ゲーム全体のフレームワーク
	class Game {
	public:
		///ゲームの状態
		enum class State {
			Play,    ///< 実行中
			Paused,  ///< 一時停止
			Quit     ///< 終了
		};
		Game();
		virtual ~Game();
		/// 初期化
		/// DxLibの初期化を行う
		/// @return 初期化(true:成功, false:失敗).
		virtual bool Initialize();
		/// 実行
		/// メインループを実行する
		virtual void Run();
		/// 停止
		/// DxLibを終了する
		virtual void Shutdown();
		/// 入力
		/// メインループ内で実行する
		virtual void Input(Input::InputComponent& input);
		/// 更新
		/// メインループ内で実行する
		virtual void Update();
		/// 描画
		/// メインループ内で実行する
		virtual void Render();
		/// アセットサーバーの取得
		/// @return アセットサーバーの参照
		Asset::AssetServer& GetAssetServer() const { return *_assetServer; }
		/// シーンサーバーの取得
		/// @return シーンサーバーの参照
		Scene::SceneServer& GetSceneServer() const { return *_sceneServer; }
		/// アクターサーバーの取得
		/// @return アクターサーバーの参照
		MachineHuck::Actor::ActorServer& GetActorServer() const { return *_actorServer; };
		/// アクターサーバーの取得
		/// @return アクターサーバーの参照
		MachineHuck::Actor::ActorFactory& GetActorFactory() const { return *_actorFactory; };
		/// サウンドコンポーネントの取得
		/// @return サウンドコンポーネントの参照
		Sound::SoundComponent& GetSoundComponent() const { return *_sound; };
		/// スプライトサーバーの取得
        /// @return スプライトサーバーの参照
		MachineHuck::UI::SpriteServer& spriteServer() const { return *_spriteServer; }
		/// UIコンポーネントの取得
        /// @return UIコンポーネントの参照
		MachineHuck::UI::UIComponent& GetUiComponent() const { return *_ui; }

		/**
		 * @brief ステージパラメーターの取得
		 * @return ステージパラメーターの参照
		 */
		MachineHuck::Stage::StageParameter& GetStageParameter() const { return *_stageParam; };


	private:
		/// 状態
		State _state{ State::Play };

		std::unique_ptr<MachineHuck::Actor::ActorServer> _actorServer;

		/// アクターファクトリのユニークポインタ
		std::unique_ptr<MachineHuck::Actor::ActorFactory> _actorFactory;

		/// アセットサーバーのユニークポインタ
		std::unique_ptr<Asset::AssetServer> _assetServer;
		/// シーンサーバーのユニークポインタ
		std::unique_ptr<Scene::SceneServer> _sceneServer;
		/// インプットコンポーネントのユニークポインタ
		std::unique_ptr<Input::InputComponent> _input;
		/// サウンドコンポーネントのユニークポインタ
		std::unique_ptr<Sound::SoundComponent> _sound;
		/// スプライトサーバーの取得
		/// スプライトサーバーのユニークポインタ
		std::unique_ptr<MachineHuck::UI::SpriteServer> _spriteServer;
		/// UIコンポーネントのユニークポインタ
		std::unique_ptr<MachineHuck::UI::UIComponent> _ui;
		std::unique_ptr<MachineHuck::Stage::StageParameter> _stageParam;//!< 

	};
}


