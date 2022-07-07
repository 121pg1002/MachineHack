/*****************************************************************//**
 * @file   RestrictionGate.h
 * @brief  �����Q�[�g�̃N���X
 *
 * @author kyoga tagawa
 * @date   February 20 2022
 *********************************************************************/
#pragma once
#include <memory>
#include "AppFrame.h"
#include "GimmickBase.h"
#include "../Model/ModelComponent.h"
#include "../State/StateBaseRoot.h"

namespace MachineHuck::Gimmick {

	class RestrictionGate : public GimmickBase {
	public:
		RestrictionGate(AppFrame::Game& game);
		~RestrictionGate() override;

		TypeId GetTypeId() const override { return TypeId::Gimmick; };

		void Update();
		void Draw();

		void SetFlag(bool flag) { _opengate = flag; }

	private:
		std::unique_ptr<Model::ModelComponent> _gate;
        bool _opengate{ false };
		int gatenum{0};
	};


    /// @class  StateBase
       /// @brief  �����Q�[�g�̊��
    class StateBase : public State::StateBaseRoot {
    public:
        StateBase(RestrictionGate& owner) : _owner{ owner } {};
        void Draw() override;
    protected:
        RestrictionGate& _owner;
        static int _noDamageTime;

    };
    /// @class  StateClose
    /// @brief  ����
    class StateClose : public StateBase {
    public:
        StateClose(RestrictionGate& owner) : StateBase{ owner } {};
        void Enter() override;
        void Input(AppFrame::Input::InputComponent& input) override;
        void Update() override;

    };
    /// @class  StateOpen
    /// @brief  �J����
    class StateOpen : public StateBase {
    public:
        StateOpen(RestrictionGate& owner) : StateBase{ owner } {};
        void Enter() override;
        void Input(AppFrame::Input::InputComponent& input) override;
        void Update() override;
    };

}


