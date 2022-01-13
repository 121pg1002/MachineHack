
/*****************************************************************//**
 * @file   TackleEnemy.h
 * @brief  ƒ^ƒbƒNƒ‹‚·‚é“G
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#pragma once
#include "../State/StateComponent.h"
#include <memory>
#include "EnemyBase.h"

class ModelAnimeComponent;
namespace Enemy {
  class TackleEnemy : public EnemyBase {
  public:
    TackleEnemy(Game& game);
    virtual ~TackleEnemy() override = default;
    //void Init() override;
    //virtual void Input(InputComponent& input) override;
    //void LoadJson(const std::string& filepath);

    virtual void Update() override;
    void Draw() override;

    TypeId GetTypeId() const override { return TypeId::Enemy; };
    Type GetType() const override { return Type::Tackle; };

    void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }


  protected:
    float _forwardSpeed{ 0 };
    float _angularSpeed{ 0 };

    int _numberTimes{ 0 };
    //int _waitTime{0};
    //std::unique_ptr<ModelAnimeComponent> _model;

    virtual void Move();
    virtual void LockOn();
    void HitCheckFrom();

  public:
    class StateBase : public /*State::*/StateBaseRoot {
    public:
      StateBase(TackleEnemy& owner) : _owner{ owner } {};
      void Draw() override;
    protected:
      TackleEnemy& _owner;
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
      bool IsLoseSight();
    private:

      int _loseSightTime{ 60 };
    };
    class StateDie : public StateBase {
    public:
      StateDie(TackleEnemy& owner) : StateBase{ owner } {};
      void Enter() override;
      void Update() override;
    };


    //class StateAttack : public StateBase {
    //public:
    //    StateAttack(Enemy& owner) : StateBase{ owner } {};
    //    void Enter() override;
    //    void Update() override;
    //    void Draw() override;
    //};

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
      void Update() override;

    };
  };
}

