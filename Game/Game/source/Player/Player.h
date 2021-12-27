///
/// @file    Player.h
/// @brief   プレイヤー
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "../Actor/Actor.h"
#include "../State/StateComponent.h"
#include <memory>

class CameraComponent;
class ModelAnimeComponent;
namespace Player {
  /// @class   Player
  /// @brief   プレイヤー
  class Player : public Actor {
  public:
    /// コンストラクタ
    /// @param[in] _game ゲームクラスへの参照
    Player(Game& _game);
    /// デストラクタ
    virtual ~Player() override = default;

    /// 入力
    /// @param[in] input インプットコンポーネントへの参照
    virtual void Input(InputComponent& input) override;
    /// 更新
    virtual void Update() override;
    /// 描画
    void Draw() override;
    /// タイプの取得
    /// @return タイプID
    TypeId GetTypeId() const override { return TypeId::Player; };

    /// ワールド行列の計算
    /// モデルのローカルZ座標が逆なのでここで180度回転させる
    void ComputeWorldTransform() override;

  protected:
    //float _angularSpeed{0};      //!< 旋回量
              //!< 主人公の状態のクラス
    enum class STATUS {
      NONE,
      WAIT,
      WALK,
      HUCKING,
      HUCKED,
      _EOT_
    };
    STATUS _status;                  //!< 主人公の状態



    math::Vector4 _backDelta{ 0, 0, 0 };
    /// 移動：向いてる方向に前進
    virtual void Move();
    /// 敵からの攻撃を確認
    void HitCheckFromEnemy();

    /////////////////////////////////////////////↓追加分

    //math::Vector4 _move{0.0, 0.0, 0.0};      //!< 移動量

    //float _moveSpeed_x{ 0 };            //!< x方向の移動量  
    //float _moveSpeed_z{ 0 };            //!< z方向の移動量

    math::Vector4 _dir{ 0.0, 0.0, 1.0 }; //!< 主人公の向き

    double _analogMin{ 0.3 };        //!< アナログスティックの反応しない値
    double lx, ly;                    //!< 左アナログスティックの傾き

    int _huckcount;

    bool _isHit; //!< 扇形の確認(仮)

  public:
    /// @class  StateBase
    /// @brief  プレイヤー状態の基底
    class StateBase : public /*State::*/StateBaseRoot {
    public:
      StateBase(Player& owner) : _owner{ owner } {};
      void Draw() override;
    protected:
      Player& _owner;


    };
    /// @class  StateIdle
    /// @brief  待機
    class StateIdle : public StateBase {
    public:
      StateIdle(Player& owner) : StateBase{ owner } {};
      void Enter() override;
      void Input(InputComponent& input) override;
      void Update() override;

    };
    /// @class  StateRun
    /// @brief  走り
    class StateRun : public StateBase {
    public:
      StateRun(Player& owner) : StateBase{ owner } {};
      void Enter() override;
      void Input(InputComponent& input) override;
      void Update() override;
    };
    /// @class  StateAttack
    /// @brief  攻撃
    class StateAttack : public StateBase {
    public:
      StateAttack(Player& owner) : StateBase{ owner } {};
      void Enter() override;
      //void Input(InputComponent& input) override;
      void Update() override;
      void Draw() override;
    private:
      int _attackcount{ 0 };
    };
    ///// @class  StateKnockBack
    ///// @brief  ノックバック
    //class StateKnockBack : public StateBase {
    //public:
    //    StateKnockBack(Player& owner) : StateBase{ owner } {};
    //    void Enter() override;
    //    void Update() override;
    //private:
    //    int freezeTime{ 0 };
    //};


    /// @class  StateHucking
    /// @brief  ハッキング中
    class StateHucking : public StateBase {
    public:
      StateHucking(Player& owner) : StateBase{ owner } {};
      void Enter() override;
      void Update() override;
    private:
      math::Vector4 _dif{ 0.0, 0.0, 0.0 };
      math::Vector4 _length;
    };

    /// @class  StateHucking
    /// @brief  ハッキング
    class StateHucked : public StateBase {
    public:
      StateHucked(Player& owner) : StateBase{ owner } {};
      void Enter() override;
      void Update() override;
    private:
      //int _freezeTime{ 0 };
    };
  };
}

