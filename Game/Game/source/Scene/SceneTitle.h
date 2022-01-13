///
/// @file    SceneTitle.h
/// @brief   タイトル画面
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"

class InputComponent;
namespace SceneTitle {
  /// @class   SceneTitle
  /// @brief   タイトル画面クラスの宣言
  class SceneTitle : public Scene {
  public:
    /// コンストラクタ
    /// @param[in] game Gameクラスの参照
    SceneTitle(Game& game);
    /// デストラクタ
    ~SceneTitle() = default;
    /// 初期化
    void Init() override;
    /// 入口処理
    virtual void Enter() override;
    /// 入力処理
    void Input(InputComponent& input) override;

    void Update() override;
    /// 描画処理
    void Render() override;
  private:
    int _gameTitleHandle{ -1 };  ///< ゲームタイトル画像
    int _leftClickToStart{ -1 }; ///< Left click to Start画像
    int _titleBgHandle{ -1 };    ///< 背景画像
    int _alpha{ 0 };
  };
}

