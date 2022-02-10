/*****************************************************************//**
 * @file   Actor.h
 * @brief  �A�N�^�[�N���X
 *
 * @author yamawaki kota
 * @date   December 19 2021
 *********************************************************************/

#pragma once
#include <memory>
#include <DxLib.h>
#include "AppFrame.h"
//#include "../Gimmick/GimmickBase.h"
 //#include "../Collision/CollisionBase.h"


class Game;
class ActorServer;
namespace Input {
    class InputComponent;
}

namespace MachineHuck::State {
    class StateComponent;
}

namespace MachineHuck::Model {
    class ModelAnimeComponent;
    class ModelComponent;
}

namespace MachineHuck::Camera {
    class CameraComponent;
}

namespace MachineHuck::Collision {
    class CollisionComponent;
}

namespace MachineHuck::Gauge {
    class GaugeBase;
    class GaugeEnemy;
    class GaugePlayer;
}

//namespace MachineHuck::Gimmick {
//
//    class GimmickBase;
//}
//class CollisionBase;

//namespace Camera = MachineHuck::Camera;
//namespace Collision = MachineHuck::Collision;
namespace Math = AppFrame::Math;

namespace MachineHuck::Actor {


    class Actor {
    public:
        enum class TypeId {
            Actor = 0,
            Player,
            Enemy,
            Stage,
            Gimmick,
            ShadowMap,
            Item
        };

        enum class TypeGimmick {
            BrokenWall,
            Hole,
            DamageFloor
        };

        enum class ActorState {
            Active,
            Paused,
            Dead,
            Hucking,
            Hucked
        };

        Actor(AppFrame::Game& game);
        virtual ~Actor();
        virtual	void	Init() {};
        virtual	void	Input(AppFrame::Input::InputComponent& input) {};
        virtual	void	Update() {};
        virtual	void	Draw();

        virtual TypeId GetTypeId() const = 0;

        TypeGimmick GetTypeGimmick() const { return _typeGimmick; }

        /**
         * @brief  ���S���Ă��邩�ǂ���
         * @return _actorState
         */
        bool IsDead() const { return (_actorState == ActorState::Dead); }

        /**
         * @brief  Active���ǂ���
         * @return _actorState
         */
        bool IsActive() const { return (_actorState == ActorState::Active); }

        /**
         * @brief  �n�b�L���O���ꂽ���ǂ���
         * @return _actorState
         */
        bool IsHucked() const { return (_actorState == ActorState::Hucked); }

        /**
         * @brief  �X�e�[�W���ǂ���
         * @return TypeId::Stage
         */
        TypeId IsStage() const { return TypeId::Stage; }


        /**
         * @brief   �G�l�~�[���ǂ���
         * @return  TypeId::Enemy
         */
        TypeId IsEnemy() const { return TypeId::Enemy; }

        /**
         * @brief   �A�C�e�����ǂ���
         * @return  TypeId::Item
         */
        TypeId IsItem() const { return TypeId::Item; }

        /**
         * @brief  �M�~�b�N���ǂ���       
         * @return TypeId::Gimmick
         */
        TypeId IsGimmick() const { return TypeId::Gimmick; }

        /**
         *
         * @brief ���S��ԂɕύX
         */
        void SetDead() { _actorState = ActorState::Dead; }

        /**
         * @brief �X�e�[�W�t���A�Ƃ̓����蔻��
         * @param oldPos �O�t���[���̈ʒu
         * @param num    �X�e�[�W�ԍ�
         * @return �������Ă��邩�������Ă��Ȃ���
         */
         //bool CollisionFloor(AppFrame::Math::Vector4 oldPos, int num);

        /**
         * @brief  �X�e�[�W�t���A�Ƃ̓����蔻��
         * @return �������Ă��邩�������Ă��Ȃ���
         */
        bool CollisionFloor();
        /**
         * @brief �X�e�[�W�t���A�Ƃ̓����蔻��ƍ��W��߂����ǂ����̔���
         * @param oldPos �O�t���[���̈ʒu
         * @param r      ���a
         * @return �������Ă��邩�������Ă��Ȃ���
         */
        bool CollisionFloor(AppFrame::Math::Vector4 oldPos, double r);


        /**
         * @brief  �M�~�b�N�Ƃ̓����蔻��       
         * @return true  �������Ă���
         *         false �������Ă��Ȃ�
         */
        bool CollisionGimmick();

        /**
         * @brief  �󂹂�ǂƂ̓����蔻��    
         * @param  move   �t�H���[�h�x�N�g��
         * @return true   �������Ă���
         *         false  �������Ă��Ȃ�
         */
        bool CollisionWall(Actor& gimmick, Math::Vector4 move);

        /**
         * @brief  ���[�v�ʒu�Ƃ̓����蔻��
         * @param  num
         * @return �������Ă��邩�������Ă��Ȃ���
         */
         // bool WarpFloor(int num);

          /**
           * @brief  ���[�v�ʒu�Ƃ̓����蔻��
           * @return pos ���[�v��̍��W
           *
           */
        VECTOR WarpFloor(Actor& act);

        /**
         * @brief  ���[�v���̓����蔻��
         * @return �������Ă��邩�������Ă��Ȃ���
         */
        bool WarpingFloor();


        /**
         * @brief  �n�b�L���O�����Ƃ��̓G�̈ړ��ʂ��擾
         * @return _huckedMove
         */
        Math::Vector4 GetHuckedMove() { return _huckedMove; }

        /**
         * @brief  �n�b�L���O�����Ƃ��̓G�̈ړ��ʂ�ݒ�
         * @param  huckedMove
         */
        void SetHuckedMove(Math::Vector4 huckedMove) { _huckedMove = huckedMove; }

        AppFrame::Game& GetGame() { return _game; }
        virtual void ComputeWorldTransform();
        const MATRIX& GetWorldTransform() const { return _worldTransform; }
        //VECTOR GetForward() const { return VTransform({0, 0, 1}, MGetRotY(_rotation.GetY())); }

        void SetPosition(const Math::Vector4& position) { _position = position; }
        Math::Vector4 GetPosition() const { return _position; }
        void SetRotation(const Math::Vector4& rotation) { _rotation = rotation; }
        Math::Vector4 GetRotation() const { return _rotation; }
        void SetScale(const Math::Vector4& scale) { _scale = scale; }
        Math::Vector4 GetScale() const { return _scale; }

        void SetLevel(const int& level) { _level = level; }
        int GetLevel() const { return _level; }
        void SetRoutine(const int& routine) { _routine = routine; }
        int GetRoutine() const { return _routine; }


        std::pair<int, int> GetFloorNumReserveNum() { return _floorReserveNum; }
        void SetFloorNumReserveNum(std::pair<int, int> floorReserveNum) { _floorReserveNum = floorReserveNum; }


        void SetMove(const Math::Vector4& move) { _move = move; }
        Math::Vector4 GetMove() const { return _move; }

        void SetStateComponent(std::unique_ptr<State::StateComponent> state);
        void SetModelAnimeComponent(std::unique_ptr<Model::ModelAnimeComponent> model);
        void SetModelComponent(std::unique_ptr<Model::ModelComponent> model);
        void SetCameraComponent(std::shared_ptr<Camera::CameraComponent> camera);


        /// ////////////////////�ǉ��� 12/01

        Math::Vector4 GetOld() const { return _oldPos; }
        /*
        *@brief     �~�̔��a���擾
        *@return _r �~�̔��a
        */
        double GetR() const { return _r; }

        /**
         * @brief   �n�b�L���O�͈͉~�̔��a���擾
         * @return  _huckR �n�b�L���O�͈͉~
         */
        double GetHuckR()const { return _huckR; }

        /**
         * @brief  �����蔻��p�̉~�̔��a���擾       
         * @return _collisionR �����蔻��p�̉~�̔��a
         */
        double GetCollisionR() const { return _collisionR; }

        /*
        *@brief                ���G�͈͂̊p�x���擾
        *@return _searchRange  ���G�͈͂̊p�x
        */
        const double GetSearchRange() const { return _searchRange; }

        /**
         * @brief                �n�b�L���O�����͈͂��擾
         * @return _huckingRange �n�b�L���O�����͈�
         */
        const double GetHuckingRange() const { return _huckingRange; }



        /// ////////////////////////////////////////�ǉ���12/02
          /**
           * @brief   AABB�p��min�l���擾
           * @return  _minXZ
           */
        Math::Vector2 GetMin()const { return _minXZ; }

        /**
         * @brief  AABB�p��max�l���擾
         * @return _maxXZ
         */
        Math::Vector2 GetMax()const { return _maxXZ; }

        ////////////************************////////////

         /**
          * @brief �����p��min�l���擾
          * @return _lmin
          */
        Math::Vector4 GetLMin() const { return _lmin; }

        /**
         * @brief �����p��max�l���擾
         * @return _lmax
         */
        Math::Vector4 GetLMax() const { return _lmax; }

        //void SetState(State state) { _state = state; }
        //State GetState() const { return _state; }

        State::StateComponent& GetState() { return *_state; }
        Model::ModelAnimeComponent& GetModelAnime() const { return *_modelAnime; }
        const Model::ModelComponent& GetModel() const { return *_model; }
        Camera::CameraComponent& GetCamera() { return *_camera; }

        ActorServer& GetActorServer();

        ActorState GetActorState() const { return _actorState; }
        void SetActorState(ActorState state) { _actorState = state; }

        Collision::CollisionComponent& GetCollision() const { return *_collision; }

        Gauge::GaugeBase& GetGaugeBase() const  { return *_gaugeBase; }
        Gauge::GaugeEnemy& GetGaugeEnemy() const { return *_gaugeEnemy; }
        Gauge::GaugePlayer& GetGaugePlayer() const { return *_gaugePlayer; }

        //Gimmick::GimmickBase& GetGimmickBase() const { return *_gimmickBase; }

        void SetIsHit(bool isHit) { _isHit = isHit; };

        /**
           * @brief �V���h�E�}�b�v�ւ̕`��̃t���O���Z�b�g
           * * @param flg
           */
        void SetShadowMapflg(bool flg) { _shadowmapflg = flg; }

        /**
        * @brief �V���h�E�}�b�v�ւ̕`��̃t���O���擾
        */
        bool  GetShadowMapflg() { return _shadowmapflg; }




    protected:

        ////*********************************///�ǉ��� 12/01
        /*
        *@brief �����蔻����N���X�̎Q��
        */
        //CollisionComponent& GetCollision();
      ////////////***********************///


        AppFrame::Game& _game;
        ActorState _actorState{ ActorState::Active };
        TypeId _typeId{ TypeId::Actor };
        TypeGimmick _typeGimmick{ TypeGimmick::BrokenWall };

        std::unique_ptr<State::StateComponent> _state;
        std::unique_ptr<Model::ModelAnimeComponent> _modelAnime;
        std::unique_ptr<Model::ModelComponent> _model;
        std::shared_ptr<Camera::CameraComponent> _camera;
        std::unique_ptr<Collision::CollisionComponent> _collision;
        std::unique_ptr<Gauge::GaugeBase> _gaugeBase;              //!< �Q�[�W�x�[�X�N���X�ւ̃��j�[�N�|�C���^
        std::unique_ptr<Gauge::GaugeEnemy> _gaugeEnemy;
        std::unique_ptr<Gauge::GaugePlayer>_gaugePlayer;
        //std::unique_ptr<Gimmick::GimmickBase>_gimmickBase;

        //std::unique_ptr<CollisionBase> _collision;  //!< �����蔻����N���X�p�̃|�C���^


        //State _state{State::Active};

        MATRIX _worldTransform{ MGetIdent() };
        Math::Vector4 _position{ 0, 0, 0 };
        Math::Vector4 _rotation{ 0, 0, 0 };
        Math::Vector4 _scale{ 1, 1, 1 };

        Math::Vector4 _move{ 0, 0, 0 };


        double _r{ 0.0 };                            //!< ���G�͈͂̉~�̔��a
        double _huckR{ 0.0 };                        //!< �n�b�L���O����̉~�̔��a
        double _collisionR{ 0.0 };                   //!< �����蔻��p�̔��a
        Math::Vector4 _oldPos{ 0.0, 0.0, 0.0 };  //!< �O�t���[���̍��W

        Math::Vector2 _minXZ{ 0.0, 0.0 };                 //!< �����蔻���AABB�p�̍��W
        Math::Vector2 _maxXZ{ 0.0, 0.0 };


        Math::Vector4 _lmin{ 0.0, 0.0, 0.0 };     //!< �����蔻��̐����p�̍��W
        Math::Vector4 _lmax{ 0.0, 0.0, 0.0 };

        bool _isHit{ false };
        double _searchRange{ 0.0 };
        double _huckingRange{ 0.0 };

        Math::Vector4 _huckedMove{ 0.0, 0.0, 0.0 };

        bool _shadowmapflg;  //�V���h�E�}�b�v�ւ̕`������邩�ǂ����̃t���O

        int _level;   //!< ���x��
        int _routine; //!< �v�l���[�`���ԍ�
        std::pair<int, int> _floorReserveNum; //!< ��ځ@�t���A�ԍ�, 2�ߓo�^�ԍ�

#ifdef _DEBUG

        Math::Vector4 _startPos;  //!< �m�F�p�̃^�b�N���ƃM�~�b�N�Ƃ̓����蔻��̎n�߂̓_
        Math::Vector4 _endPos;    //!< �m�F�p�̃^�b�N���ƃM�~�b�N�Ƃ̓����蔻��̍Ō�̓_
        bool _judge;              //!< �����������������Ă��Ȃ���
#endif
        
    private:

    };



}



