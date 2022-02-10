/*****************************************************************//**
 * @file   TackleEnemy.h
 * @brief  �^�b�N������G
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

        /// ���[���h�s��̌v�Z
        /// ���f���̃��[�J��Z���W���t�Ȃ̂ł�����180�x��]������
        void ComputeWorldTransform() override;

      


    protected:
        float _forwardSpeed{ 0 };
        float _angularSpeed{ 0 };

        int _numberTimes{ 0 };
        //int _waitTime{0};
        //std::unique_ptr<ModelAnimeComponent> _model;

        //virtual void Move();

        /**
         * @brief  �n�b�L���O���ꂽ�Ƃ��̈ړ�         
         * @param  lx �������̌X��
         * @param  ly �c�����̌X��
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
             * @brief  ���G�͈͂���O�ꂽ���ǂ���
             * @return ����
             */
            bool IsLoseSight();

            ///**
            // * @brief  �����̐�Ƀv���C���[�����邩�ǂ���
            // * @return ����
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
            //Math::Vector4 _startLine; //!< �󂹂�ǂƂ̔���p�̐��̎n�_
            //Math::Vector4 _endLine;   //!< �󂹂�ǂƂ̔���p�̐��̏I�_
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



