/*****************************************************************//**
 * @file   TackleEnemy.h
 * @brief  タックルする敵
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#pragma once
#include "../State/StateComponent.h"
#include <memory>
#include "EnemyBase.h"

class ModelAnimeComponent;
namespace Math = AppFrame::Math;

namespace MachineHuck::Enemy {
    class TackleEnemy : public EnemyBase {
    public:
        TackleEnemy(AppFrame::Game& game);
        virtual ~TackleEnemy() override = default;
        //void Init() override;
        //virtual void Input(InputComponent& input) override;
        void LoadJson(const std::string& filePath);

        virtual void Update() override;
        void Input(AppFrame::Input::InputComponent& input) override;
        void Draw() override;

#ifdef _DEBUG

        bool DrawTackleLine(bool judge);
#endif

        TypeId GetTypeId() const override { return TypeId::Enemy; };
        Type GetType() const override { return Type::Tackle; };

        /// ワールド行列の計算
        /// モデルのローカルZ座標が逆なのでここで180度回転させる
        void ComputeWorldTransform() override;

      


    protected:
        float _forwardSpeed{ 0 };
        float _angularSpeed{ 0 };

        int _numberTimes{ 0 };
        //int _waitTime{0};
        //std::unique_ptr<ModelAnimeComponent> _model;

        //virtual void Move();

        /**
         * @brief  ハッキングされたときの移動         
         * @param  lx 横方向の傾き
         * @param  ly 縦方向の傾き
         */
        //void HuckedMove(double lx, double ly);

        //virtual void LockOn();
        //void Tackle(Math::Vector4 target);

        //void HitCheckFrom();

    public:
        class StateBase : public State::StateBaseRoot {
        public:
            StateBase(TackleEnemy& owner) : _owner{ owner } {};
            void Draw() override;
        protected:
            TackleEnemy& _owner;
            bool _invincibleTime{ false };
            static int _huckNoDamageTime;
        };

        class StateIdle : public StateBase {
        public:
            StateIdle(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;

        };


        class StateFall : public StateBase {
        public:
            StateFall(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        };
        class StateRun : public StateBase {
        public:
            StateRun(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;

            /**
             * @brief  索敵範囲から外れたかどうか
             * @return 成否
             */
            bool IsLoseSight();

            ///**
            // * @brief  視線の先にプレイヤーがいるかどうか
            // * @return 成否
            // */
            //bool IsViewPlayer();
        private:

            int _loseSightTime{ 60 };
            int _tacklePreTime{ 60 };
            Math::Vector4 _dif;
        };
        class StateDie : public StateBase {
        public:
            StateDie(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        };

        class StateDamage : public StateBase {
        public:
            StateDamage(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        };


        class StateTackle : public StateBase {
        public:
            StateTackle(TackleEnemy& owner);
            void Enter() override;
            void Update() override;
        private:
            //int _tackleTime;
            Math::Vector4 _norm;
            double _speed;
            //Math::Vector4 _startLine; //!< 壊せる壁との判定用の線の始点
            //Math::Vector4 _endLine;   //!< 壊せる壁との判定用の線の終点
        };

        class StateTackleAfter : public StateBase {
        public:
            StateTackleAfter(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        private:

            int _tackleAfterTime;

        };

        class StateHucking : public StateBase
        {
        public:
            StateHucking(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;

        };

        class StateHucked : public StateBase
        {
        public:
            StateHucked(TackleEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;
        private:
            double _lx, _ly;
            bool _warping;
            Math::Vector4 _fadePos;
            int _waitFrame;

        };
    };
}



