///
/// @file    SceneFade.h
/// @brief   シーンのフェードクラス
///          画面の最前面にフルスクリーンサイズの画像を重ねてアルファ値によるフェードを行う
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "Scene.h"

  /// @class   SceneFade
  /// @brief   シーンフェードクラスの宣言
  class SceneFade : public Scene {
  public:
    /// コンストラクタ
    /// @param[in] game ゲームクラスの参照
    /// @param[in] state 
    SceneFade(Game& game);
    /// デストラクタ
    virtual ~SceneFade();
    /// 初期化
    virtual void Init() override;
    /// 入口
    virtual void Enter() override;
    /// 更新
    virtual void Update() override;
    /// 描画
    virtual void Render() override;
  protected:
    int _width{ 1920 };
    int _height{ 1080 };
    unsigned int _color{ 0 };
    float _alpha{ 0 };
    float _deltaAlpha{ 0 };
  };

  class SceneFadeIn : public SceneFade {
  public:
    SceneFadeIn(Game& game);
    ~SceneFadeIn();
    void Enter() override;
    void Update() override;
  };

  class SceneFadeOut : public SceneFade {
  public:
    SceneFadeOut(Game& game);
    ~SceneFadeOut();
    void Enter() override;
    void Update() override;
  };
