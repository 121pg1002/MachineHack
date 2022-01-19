/*****************************************************************//**
 * @file   Player.h
 * @brief  �v���C���[�N���X
 *
 * @author hikaru Goto
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Actor/Actor.h"
#include "../State/StateComponent.h"
#include <memory>

//namespace MachineHuck::Camera {
//    class CameraComponent;
//}
//namespace MachineHuck::Model {
//    class ModelAnimeComponent;
//}

namespace MachineHuck::Player {
    /// @class   Player
/// @brief   �v���C���[
    class Player : public Actor::Actor {
    public:
        /// �R���X�g���N�^
        /// @param[in] _game �Q�[���N���X�ւ̎Q��
        Player(AppFrame::Game& _game);
        /// �f�X�g���N�^
        virtual ~Player() override = default;

        /// ����
        /// @param[in] input �C���v�b�g�R���|�[�l���g�ւ̎Q��
        virtual void Input(AppFrame::Input::InputComponent& input) override;
        /// �X�V
        virtual void Update() override;
        /// �`��
        void Draw() override;
        /// �^�C�v�̎擾
        /// @return �^�C�vID
        TypeId GetTypeId() const override { return TypeId::Player; };

        /// ���[���h�s��̌v�Z
        /// ���f���̃��[�J��Z���W���t�Ȃ̂ł�����180�x��]������
        void ComputeWorldTransform() override;

    protected:
        //float _angularSpeed{0};      //!< �����
                  //!< ��l���̏�Ԃ̃N���X
        //enum class STATUS {
        //    NONE,
        //    WAIT,
        //    WALK,
        //    HUCKING,
        //    HUCKED,
        //    _EOT_
        //};
        //STATUS _status{ STATUS::WAIT };                  //!< ��l���̏��



        Math::Vector4 _backDelta{ 0, 0, 0 };
        /// �ړ��F�����Ă�����ɑO�i
        virtual void Move();
        /// �G����̍U�����m�F
        //void HitCheckFromEnemy();

        /////////////////////////////////////////////���ǉ���

        //Math::Vector4 _move{0.0, 0.0, 0.0};      //!< �ړ���

        //float _moveSpeed_x{ 0 };            //!< x�����̈ړ���  
        //float _moveSpeed_z{ 0 };            //!< z�����̈ړ���

        Math::Vector4 _dir{ 0.0, 0.0, 1.0 }; //!< ��l���̌���

        double _analogMin{ 0.3 };        //!< �A�i���O�X�e�B�b�N�̔������Ȃ��l
        double lx{ 0.0 }, ly{ 0.0 };                    //!< ���A�i���O�X�e�B�b�N�̌X��

        int _huckCount{ 0 };

        bool _isHit; //!< ��`�̊m�F(��)
    private:
        float _hp{ 100 };//�v���C���[�̃G�l���M�[�c��
        int _noDamageTime{0};

    public:
        /// @class  StateBase
        /// @brief  �v���C���[��Ԃ̊��
        class StateBase : public State::StateBaseRoot {
        public:
            StateBase(Player& owner) : _owner{ owner } {};
            void Draw() override;
        protected:
            Player& _owner;


        };
        /// @class  StateIdle
        /// @brief  �ҋ@
        class StateIdle : public StateBase {
        public:
            StateIdle(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;

        };
        /// @class  StateRun
        /// @brief  ����
        class StateRun : public StateBase {
        public:
            StateRun(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;
        };
        /// @class  StateAttack
        /// @brief  �U��
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
        ///// @brief  �m�b�N�o�b�N
        //class StateKnockBack : public StateBase {
        //public:
        //    StateKnockBack(Player& owner) : StateBase{ owner } {};
        //    void Enter() override;
        //    void Update() override;
        //private:
        //    int freezeTime{ 0 };
        //};


        /// @class  StateHucking
        /// @brief  �n�b�L���O��
        class StateHucking : public StateBase {
        public:
            StateHucking(Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        private:
            Math::Vector4 _dif{ 0.0, 0.0, 0.0 };
            Math::Vector4 _length;
        };

        /// @class  StateHucking
        /// @brief  �n�b�L���O
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
         * @brief  ���S
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


