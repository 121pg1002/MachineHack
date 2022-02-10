/*****************************************************************//**
 * @file   Actor.h
 * @brief  アクタークラス
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
         * @brief  死亡しているかどうか
         * @return _actorState
         */
        bool IsDead() const { return (_actorState == ActorState::Dead); }

        /**
         * @brief  Activeかどうか
         * @return _actorState
         */
        bool IsActive() const { return (_actorState == ActorState::Active); }

        /**
         * @brief  ハッキングされたかどうか
         * @return _actorState
         */
        bool IsHucked() const { return (_actorState == ActorState::Hucked); }

        /**
         * @brief  ステージかどうか
         * @return TypeId::Stage
         */
        TypeId IsStage() const { return TypeId::Stage; }


        /**
         * @brief   エネミーかどうか
         * @return  TypeId::Enemy
         */
        TypeId IsEnemy() const { return TypeId::Enemy; }

        /**
         * @brief   アイテムかどうか
         * @return  TypeId::Item
         */
        TypeId IsItem() const { return TypeId::Item; }

        /**
         * @brief  ギミックかどうか       
         * @return TypeId::Gimmick
         */
        TypeId IsGimmick() const { return TypeId::Gimmick; }

        /**
         *
         * @brief 死亡状態に変更
         */
        void SetDead() { _actorState = ActorState::Dead; }

        /**
         * @brief ステージフロアとの当たり判定
         * @param oldPos 前フレームの位置
         * @param num    ステージ番号
         * @return 当たっているか当たっていないか
         */
         //bool CollisionFloor(AppFrame::Math::Vector4 oldPos, int num);

        /**
         * @brief  ステージフロアとの当たり判定
         * @return 当たっているか当たっていないか
         */
        bool CollisionFloor();
        /**
         * @brief ステージフロアとの当たり判定と座標を戻すかどうかの判定
         * @param oldPos 前フレームの位置
         * @param r      半径
         * @return 当たっているか当たっていないか
         */
        bool CollisionFloor(AppFrame::Math::Vector4 oldPos, double r);


        /**
         * @brief  ギミックとの当たり判定       
         * @return true  当たっている
         *         false 当たっていない
         */
        bool CollisionGimmick();

        /**
         * @brief  壊せる壁との当たり判定    
         * @param  move   フォワードベクトル
         * @return true   当たっている
         *         false  当たっていない
         */
        bool CollisionWall(Actor& gimmick, Math::Vector4 move);

        /**
         * @brief  ワープ位置との当たり判定
         * @param  num
         * @return 当たっているか当たっていないか
         */
         // bool WarpFloor(int num);

          /**
           * @brief  ワープ位置との当たり判定
           * @return pos ワープ先の座標
           *
           */
        VECTOR WarpFloor(Actor& act);

        /**
         * @brief  ワープ中の当たり判定
         * @return 当たっているか当たっていないか
         */
        bool WarpingFloor();


        /**
         * @brief  ハッキングしたときの敵の移動量を取得
         * @return _huckedMove
         */
        Math::Vector4 GetHuckedMove() { return _huckedMove; }

        /**
         * @brief  ハッキングしたときの敵の移動量を設定
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


        /// ////////////////////追加分 12/01

        Math::Vector4 GetOld() const { return _oldPos; }
        /*
        *@brief     円の半径を取得
        *@return _r 円の半径
        */
        double GetR() const { return _r; }

        /**
         * @brief   ハッキング範囲円の半径を取得
         * @return  _huckR ハッキング範囲円
         */
        double GetHuckR()const { return _huckR; }

        /**
         * @brief  当たり判定用の円の半径を取得       
         * @return _collisionR 当たり判定用の円の半径
         */
        double GetCollisionR() const { return _collisionR; }

        /*
        *@brief                索敵範囲の角度を取得
        *@return _searchRange  索敵範囲の角度
        */
        const double GetSearchRange() const { return _searchRange; }

        /**
         * @brief                ハッキングされる範囲を取得
         * @return _huckingRange ハッキングされる範囲
         */
        const double GetHuckingRange() const { return _huckingRange; }



        /// ////////////////////////////////////////追加分12/02
          /**
           * @brief   AABB用のmin値を取得
           * @return  _minXZ
           */
        Math::Vector2 GetMin()const { return _minXZ; }

        /**
         * @brief  AABB用のmax値を取得
         * @return _maxXZ
         */
        Math::Vector2 GetMax()const { return _maxXZ; }

        ////////////************************////////////

         /**
          * @brief 線分用のmin値を取得
          * @return _lmin
          */
        Math::Vector4 GetLMin() const { return _lmin; }

        /**
         * @brief 線分用のmax値を取得
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
           * @brief シャドウマップへの描画のフラグをセット
           * * @param flg
           */
        void SetShadowMapflg(bool flg) { _shadowmapflg = flg; }

        /**
        * @brief シャドウマップへの描画のフラグを取得
        */
        bool  GetShadowMapflg() { return _shadowmapflg; }




    protected:

        ////*********************************///追加分 12/01
        /*
        *@brief 当たり判定基底クラスの参照
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
        std::unique_ptr<Gauge::GaugeBase> _gaugeBase;              //!< ゲージベースクラスへのユニークポインタ
        std::unique_ptr<Gauge::GaugeEnemy> _gaugeEnemy;
        std::unique_ptr<Gauge::GaugePlayer>_gaugePlayer;
        //std::unique_ptr<Gimmick::GimmickBase>_gimmickBase;

        //std::unique_ptr<CollisionBase> _collision;  //!< 当たり判定基底クラス用のポインタ


        //State _state{State::Active};

        MATRIX _worldTransform{ MGetIdent() };
        Math::Vector4 _position{ 0, 0, 0 };
        Math::Vector4 _rotation{ 0, 0, 0 };
        Math::Vector4 _scale{ 1, 1, 1 };

        Math::Vector4 _move{ 0, 0, 0 };


        double _r{ 0.0 };                            //!< 索敵範囲の円の半径
        double _huckR{ 0.0 };                        //!< ハッキング判定の円の半径
        double _collisionR{ 0.0 };                   //!< 当たり判定用の半径
        Math::Vector4 _oldPos{ 0.0, 0.0, 0.0 };  //!< 前フレームの座標

        Math::Vector2 _minXZ{ 0.0, 0.0 };                 //!< 当たり判定のAABB用の座標
        Math::Vector2 _maxXZ{ 0.0, 0.0 };


        Math::Vector4 _lmin{ 0.0, 0.0, 0.0 };     //!< 当たり判定の線分用の座標
        Math::Vector4 _lmax{ 0.0, 0.0, 0.0 };

        bool _isHit{ false };
        double _searchRange{ 0.0 };
        double _huckingRange{ 0.0 };

        Math::Vector4 _huckedMove{ 0.0, 0.0, 0.0 };

        bool _shadowmapflg;  //シャドウマップへの描画をするかどうかのフラグ

        int _level;   //!< レベル
        int _routine; //!< 思考ルーチン番号
        std::pair<int, int> _floorReserveNum; //!< 一つ目　フロア番号, 2つめ登録番号

#ifdef _DEBUG

        Math::Vector4 _startPos;  //!< 確認用のタックルとギミックとの当たり判定の始めの点
        Math::Vector4 _endPos;    //!< 確認用のタックルとギミックとの当たり判定の最後の点
        bool _judge;              //!< 当たったか当たっていないか
#endif
        
    private:

    };



}



