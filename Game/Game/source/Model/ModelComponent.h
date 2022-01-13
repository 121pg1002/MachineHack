///
/// @file    ModelComponent.h
/// @brief   スタティックモデル用のコンポーネント
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <DxLib.h>
#include <string_view>

class Actor;

///
/// @class   ModelComponent
/// @brief   スタティックモデル用のコンポーネントクラスの宣言
///
class ModelComponent {
public:
  /// コンストラクタ
  /// @param[in] filename モデルのファイル名
  ModelComponent(Actor& owner);
  /// デストラクタ
  virtual ~ModelComponent();

  /// 初期化
	virtual void Init();

  /// 更新
	virtual void Update();

  /// 描画
  virtual void Draw();
  
  /// モデルの設定
  /// @param key AssetServerに登録済みのキー
  /// @return 実際に登録し通し番号
  virtual int SetModel(std::string_view key, int no = 0);

  /// 座標の設定.
  /// @param[in] position 座標x,y,z
  virtual void SetPosition(VECTOR position);

  /// 回転角度の設定.
  /// @param[in] rotation 回転角度x,y,z
  virtual void SetRotation(VECTOR rotation);

  /// 拡大率の設定.
  /// @param[in] scale 拡大率
  virtual void SetScale(VECTOR scale);

  /// ワールド行列の設定
  /// @param world 
  virtual void SetMatrix(MATRIX& world);

  void SetHandle(int handle) { _handle = handle; }
  int GetHandle() { return _handle; }
  void SetColor(int index, float r, float g, float b);

protected:
  Actor& _owner;
  int _handle{-1};
  bool _isLighting{true};
};

