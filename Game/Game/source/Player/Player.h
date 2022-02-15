/*****************************************************************//**
 * @file   Player.h
 * @brief  プレイヤークラス
 *
 * @author hikaru Goto
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Actor/Actor.h"
#include "../State/StateComponent.h"
#include "../ShadowMap/Shadowmap.h"
#include <memory>

//namespace MachineHuck::Camera {
//    class CameraComponent;
//}
//namespace MachineHuck::Model {
//    class ModelAnimeComponent;
//}

namespace MachineHuck::Player {
    /// @class   Player
    /// @brief   プレイヤー
    class Player : public Actor::Actor {
    public:
        /// コンストラクタ
        /// @param[in] _game ゲームクラスへの参照
        Player(AppFrame::Game& _game);
        /// デストラクタ
        virtual ~Player() override = default;

        /// 入力
        /// @param[in] input インプットコンポーネントへの参照
        virtual void Input(AppFrame::Input::InputComponent& input) override;
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

        /**
         * @brief  ハックカウントを取得
         * @return _huckCount
         */
        int GetHuckCount() { return _huckCount; }

        /**
         * @brief ハックカウンタを設定
         * @param count
         */
        void SetHuckCount(int count) { _huckCount = count; }
        
        /**
         * @brief  ハック失敗フラグを取得
         * @return _huckFailureFlag 0 が失敗 
         *                          1 が成功 
         *                          2が判定中
         */
        int GetHuckFailureFlag() { return _huckFailureFlag; }

        /**
         * @brief ハック成功失敗フラグを設定
         * @param flag 0が失敗
         *             1が成功 
         *             2が判定中
         */
        void SetHuckFailureFlag(int flag) { _huckFailureFlag = flag; }

        /**
         * 
         * @brief  無敵かどうか       
         * @return _invincible
         */
        //bool GetInvincible() { return _invincible; }

        ///**
        // * 
        // * @brief  無敵を設定       
        // * @param  invincible
        // */
        //void SetInvincible(bool invincible) { _invincible = invincible; }


      
    protected:
        //float _angularSpeed{0};      //!< 旋回量
                  //!< 主人公の状態のクラス
        //enum class STATUS {
        //    NONE,
        //    WAIT,
        //    WALK,
        //    HUCKING,
        //    HUCKED,
        //    _EOT_
        //};
        //STATUS _status{ STATUS::WAIT };                  //!< 主人公の状態



        Math::Vector4 _backDelta{ 0, 0, 0 };
        /// 移動：向いてる方向に前進
        virtual void Move();
        /// 敵からの攻撃を確認
        //void HitCheckFromEnemy();

        /////////////////////////////////////////////↓追加分

        //Math::Vector4 _move{0.0, 0.0, 0.0};      //!< 移動量

        //float _moveSpeed_x{ 0 };            //!< x方向の移動量  
        //float _moveSpeed_z{ 0 };            //!< z方向の移動量

        Math::Vector4 _dir{ 0.0, 0.0, 1.0 }; //!< 主人公の向き

        double _analogMin{ 0.3 };        //!< アナログスティックの反応しない値
        double lx{ 0.0 }, ly{ 0.0 };                    //!< 左アナログスティックの傾き

        int _huckCount{ 0 };
        int _huckFailureFlag{2};        //!< ハッキングに失敗したかどうか 失敗 0 成功 1　判定中 2

        bool _isHit; //!< 扇形の確認(仮)
        Math::Vector4 _fadePos; //!< ワープ中の座標保存用



      
    private:
        float _hp{ 100 };//プレイヤーのエネルギー残量
        int _noDamageTime{0};
        bool _warping{ false };
        int _waitframe{ 0 };
        int _gaugehp{ 0 };//HP

#ifdef _DEBUG

        bool _debugMode; //!< デバッグモードフラグ
        double _no;
#endif 
      //  bool _invincible{ false }; //!< 無敵フラグ
       
    public:
        /// @class  StateBase
        /// @brief  プレイヤー状態の基底
        class StateBase : public State::StateBaseRoot {
        public:
            StateBase(Player& owner) : _owner{ owner } {};
            void Draw() override;
        protected:
            Player& _owner;
            static int _noDamageTime;

        };
        /// @class  StateIdle
        /// @brief  待機
        class StateIdle : public StateBase {
        public:
            StateIdle(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;

        };
        /// @class  StateRun
        /// @brief  走り
        class StateRun : public StateBase {
        public:
            StateRun(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;
        };

        /// @class  StateDamage
        /// @brief  ダメージ
        class StateDamage : public StateBase {
        public:
            StateDamage(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        private:
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

        // @class StateFallPre
        // @brief 落ちる準備
        class StateFallPre : public StateBase {
        public:
            StateFallPre(Player& owner) : StateBase{ owner } {};
            void Enter() override;

            void Update() override;
        private:
            Math::Vector4 _norm;


        };

        //落ちる
        class StateFall : public StateBase {
        public:
            StateFall(Player& owner) : StateBase{ owner } {};
            void Enter() override;

            void Update() override;
        private:
            //int _fallCount{ 0 }; //!< 落ちるカウント


        };

        //class StateFallAfter : public StateBase {
        //public:
        //    StateFallAfter(Player& owner) :StateBase{ owner } {};
        //    void Enter() override;
        //    void Update() override;


        //};

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
            Math::Vector4 _dif{ 0.0, 0.0, 0.0 };
            Math::Vector4 _length;
            int _huckingTime{0};
            bool _huckFlag{false};
        };

        /// @class  StateHucking
        /// @brief  ハッキング
        class StateHucked : public StateBase {
        public:
            StateHucked(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;
        private:
            //int _freezeTime{ 0 };
        };



        /**
         * @class  StateDie
         * @brief  死亡
         */
        class StateDie : public StateBase {
        public:
            StateDie(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        private:
        };




    };
}


