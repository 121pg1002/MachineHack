///
/// @file    Actor.h
/// @brief   �A�N�^�[
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <DxLib.h>
#include "AppFrame.h"
//#include "../Collision/CollisionBase.h"
#include <memory>

class Game;
class ActorServer;
class InputComponent;
class StateComponent;
class ModelAnimeComponent;
class CameraComponent;
class CollisionComponent;
//class CollisionBase;
//namespace Actor {
  class Actor {
  public:
    enum class TypeId {
      Actor = 0,
      Player,
      Enemy,
      Stage,
      Gimmick
    };



    enum class ActorState {
      Active,
      Paused,
      Dead,
      Hucking,
      Hucked
    };

    Actor(Game& game);
    virtual ~Actor();
    virtual	void	Init() {};
    virtual	void	Input(InputComponent& input) {};
    virtual	void	Update() {};
    virtual	void	Draw() {};

    virtual TypeId GetTypeId() const = 0;

    bool isDead() const { return (_actorState == ActorState::Dead); }
    bool isActive() const { return (_actorState == ActorState::Active); }

    Game& GetGame() { return _game; }
    virtual void ComputeWorldTransform();
    const MATRIX& GetWorldTransform() const { return _worldTransform; }
    //VECTOR GetForward() const { return VTransform({0, 0, 1}, MGetRotY(_rotation.GetY())); }

    void SetPosition(const math::Vector4& position) { _position = position; }
    math::Vector4 GetPosition() const { return _position; }
    void SetRotation(const math::Vector4& rotation) { _rotation = rotation; }
    math::Vector4 GetRotation() const { return _rotation; }
    void SetScale(const math::Vector4& scale) { _scale = scale; }
    math::Vector4 GetScale() const { return _scale; }

    void SetMove(const math::Vector4& move) { _move = move; }
    math::Vector4 GetMove() const { return _move; }

    void SetStateComponent(std::unique_ptr<StateComponent> state);
    void SetModelComponent(std::unique_ptr</*Model::*/ModelAnimeComponent> model);
    void SetCameraComponent(std::shared_ptr<CameraComponent> camera);


    /// ////////////////////�ǉ��� 12/01

    math::Vector4 GetOld() const { return _oldPos; }
    /*
    *@brief     �~�̔��a���擾
    *@return _r �~�̔��a
    */
    double Get_r() const { return _r; }

    /*
    *@brief                ���G�͈͂̊p�x���擾
    *@return _searchRange  ���G�͈͂̊p�x
    */
    double GetSearchRange() const { return _searchRange; }

    /// ////////////////////////////////////////�ǉ���12/02

    math::Vector2 GetMin()const { return _minXZ; }
    math::Vector2 GetMax()const { return _maxXZ; }

    ////////////************************////////////

    math::Vector4 GetLMin() const { return _lmin; }
    math::Vector4 GetLMax() const { return _lmax; }

    //void SetState(State state) { _state = state; }
    //State GetState() const { return _state; }

    /*  State::*/StateComponent& GetState() { return *_state; }
    /*Model::*/ModelAnimeComponent& GetModel() { return *_model; }
    CameraComponent& GetCamera() { return *_camera; }

    ActorServer& GetActorServer();

    ActorState GetActorState() const { return _actorState; }
    void SetActorState(ActorState state) { _actorState = state; }

    CollisionComponent& GetCollision() { return *_collision; }

    void SetIsHit(bool isHit) { _isHit = isHit; };

  protected:

    ////*********************************///�ǉ��� 12/01
    /*
    *@brief �����蔻����N���X�̎Q��
    */
    //CollisionComponent& GetCollision();
  ////////////***********************///


    Game& _game;
    ActorState _actorState{ ActorState::Active };
    std::unique_ptr</*State::*/StateComponent> _state;
    std::unique_ptr</*Model::*/ModelAnimeComponent> _model;
    std::shared_ptr<CameraComponent> _camera;
    //CameraComponent* _camera;
    std::unique_ptr<CollisionComponent> _collision;


    //std::unique_ptr<CollisionBase> _collision;  //!< �����蔻����N���X�p�̃|�C���^


    //State _state{State::Active};

    MATRIX _worldTransform{ MGetIdent() };
    math::Vector4 _position{ 0, 0, 0 };
    math::Vector4 _rotation{ 0, 0, 0 };
    math::Vector4 _scale{ 1, 1, 1 };

    math::Vector4 _move{ 0, 0, 0 };

    ////*********************************///�ǉ��� 12/01
    double _r{ 0 };                            //!< �����蔻��̉~�̔��a
    math::Vector4 _oldPos{ 0.0, 0.0, 0.0 };  //!< �O�t���[���̍��W
    ///////******************************///////�ǉ��� 12/02
    math::Vector2 _minXZ{ 0.0, 0.0 };                 //!< �����蔻���AABB�p�̍��W
    math::Vector2 _maxXZ{ 0.0, 0.0 };
    //***********************************//////

    math::Vector4 _lmin{ 0.0, 0.0, 0.0 };     //!< �����蔻��̐����p�̍��W
    math::Vector4 _lmax{ 0.0, 0.0, 0.0 };

    bool _isHit{ false };
    double _searchRange{ 0.0 };
  private:

  };
//}
