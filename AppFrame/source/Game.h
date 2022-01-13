///
/// @file    Game.h
/// @brief   ゲームクラスの宣言
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>
class ActorFactory;
class ActorServer;
class AssetServer;
class SceneServer;
class InputComponent;
class SoundComponent;

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
	virtual void Input();
  /// 更新
  /// メインループ内で実行する
	virtual void Update();
  /// 描画
  /// メインループ内で実行する
  virtual void Render();
  /// アセットサーバーの取得
  /// @return アセットサーバーの参照
  /*Asset::*/AssetServer& GetAssetServer() const { return *_assetServer; }
  /// シーンサーバーの取得
  /// @return シーンサーバーの参照
  SceneServer& GetSceneServer() const { return *_sceneServer; }
  /// アクターサーバーの取得
  /// @return アクターサーバーの参照
  ActorServer& GetActorServer() const { return *_actorServer; };
  /// アクターサーバーの取得
  /// @return アクターサーバーの参照
  ActorFactory& GetActorFactory() const { return *_actorFactory; };
  /// サウンドコンポーネントの取得
  /// @return サウンドコンポーネントの参照
  SoundComponent& GetSoundComponent() const { return *_sound; };


private:
  /// 状態
	State _state{State::Play};

  std::unique_ptr<ActorServer> _actorServer;

  /// アクターファクトリのユニークポインタ
  std::unique_ptr<ActorFactory> _actorFactory;

  /// アセットサーバーのユニークポインタ
  std::unique_ptr</*Asset::*/AssetServer> _assetServer;
  /// シーンサーバーのユニークポインタ
  std::unique_ptr<SceneServer> _sceneServer;
  /// インプットコンポーネントのユニークポインタ
  std::unique_ptr<InputComponent> _input;
  /// サウンドコンポーネントのユニークポインタ
  std::unique_ptr<SoundComponent> _sound;
};
