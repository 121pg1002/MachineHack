
/*****************************************************************//**
 * @file   CatchEnemy.h
 * @brief  �L���b�`����G�̃N���X
 * 
 * @author hikaru Goto
 * @date   February 1 2022
 *********************************************************************/

#pragma once
#include "../State/StateComponent.h"
#include "EnemyBase.h"


namespace MachineHuck::Enemy {

	class CatchEnemy : public EnemyBase {
	public:
		CatchEnemy(AppFrame::Game& game);
		virtual ~CatchEnemy() = default;

		void LoadJson(const std::string& filePath);

		TypeId GetTypeId() const override { return TypeId::Enemy; }
        Type GetType() const override { return Type::Catch; };

        virtual void Update() override;
        void Input(AppFrame::Input::InputComponent& input) override;
        void Draw() override;

        /**
         * 
         * @brief  �n�b�L���O���̌������w��         
         * @param  lx
         * @param  ly
         */
        void HuckedRotation(double lx, double ly);

    private:
        double _catchR;      //!< �L���b�`�p�̔��a
        double _catchRange;  //!< �L���b�`�p�͈̔͊p�x

    public:
        class StateBase : public State::StateBaseRoot {
        public:
            StateBase(CatchEnemy& owner) : _owner{ owner } {};
            void Draw() override;
        protected:
            CatchEnemy& _owner;
            bool _invincibleTime{ false };
            static int _huckNoDamageTime;
        };

        class StateIdle : public StateBase {
        public:
            StateIdle(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;

        };


        class StateFall : public StateBase {
        public:
            StateFall(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        };

        //�U���O�v���C���[����������
        class StateCatchPre : public StateBase {
        public:
            StateCatchPre(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
           // void Input(AppFrame::Input::InputComponent& input) override;
            void Update() override;
            bool IsLoseSight();
        private:
            int _catchPreTime{20}; //!< �U���܂ł̗P�\

        };

        //�U����
        class StateCatch : public StateBase {
        public:
            StateCatch(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        private:
            int _catchTime{60}; //!< �L���b�`���쎞��
        };

        //�U����
        class StateCatchAfter : public StateBase {
        public:
            StateCatchAfter(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        private:

            int _catchAfterTime;

        };

        //�U����
        //class StateAttack : public StateBase {
        //public:
        //    StateAttack(CatchEnemy& owner) : StateBase{ owner } {};
        //    void Enter() override;
        //    void Update() override;
        //    /**
        //     * @brief  ���G�͈͂���O�ꂽ���ǂ���
        //     * @return ����
        //     */
        //    bool IsLoseSight();
        //};

        //class StateRun : public StateBase {
        //public:
        //    StateRun(CatchEnemy& owner) : StateBase{ owner } {};
        //    void Enter() override;
        //    void Update() override;

        //    /**
        //     * @brief  ���G�͈͂���O�ꂽ���ǂ���
        //     * @return ����
        //     */
        //    bool IsLoseSight();

        //    ///**
        //    // * @brief  �����̐�Ƀv���C���[�����邩�ǂ���
        //    // * @return ����
        //    // */
        //    //bool IsViewPlayer();
        //private:

        //    int _loseSightTime{ 60 };
        //    int _tacklePreTime{ 60 };
        //    Math::Vector4 _dif;
        //};
        class StateDie : public StateBase {
        public:
            StateDie(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        };

        class StateDamage : public StateBase {
        public:
            StateDamage(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;
        };



        class StateHucking : public StateBase
        {
        public:
            StateHucking(CatchEnemy& owner) : StateBase{ owner } {};
            void Enter() override;
            void Update() override;

        };

        class StateHucked : public StateBase
        {
        public:
            StateHucked(CatchEnemy& owner) : StateBase{ owner } {};
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

