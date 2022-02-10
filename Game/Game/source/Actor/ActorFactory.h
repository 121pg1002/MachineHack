/*****************************************************************//**
 * @file   ActorFactory.h
 * @brief  アクターファクトリー
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/


#pragma once
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <DxLib.h>
#include "AppFrame.h"
#include "../Parameter/EStageParam.h"
#include "../Parameter/IStageParam.h"
//#include "../Parameter/GStageParam.h"



namespace MachineHuck::Actor {
    class Actor;
    class CreatorBase;
}

namespace AppFrame {
    class Game;
}

namespace MachineHuck::Parameter {
    //class EStageParam;
    //class IStageParam;
    class GStageParam;
}



namespace Math = AppFrame::Math;

namespace MachineHuck::Actor {

    using ESMV = std::vector<Parameter::EStageParam>;
    using StageV = std::vector<int>;
    using ISMV = std::vector<Parameter::IStageParam>;
    using GSV = std::vector<Parameter::GStageParam>;

    /// @class ActorFactory
    /// @brief アクターの生成を一元管理する
    ///        生成したいアクター用のクリエイターを登録して使用する
    class ActorFactory {
    public:
        /// コンストラクタ
        /// @param[in] game ゲームクラスへの参照 
        ActorFactory(AppFrame::Game& game);
        /// クリエイターの登録
        /// @param[in] type 任意の文字列キー
        /// @param[in] creator 登録するクリエイターのインスタンス
        /// @return 登録の成否
        bool Register(std::string_view type, std::unique_ptr<CreatorBase> creator);
        /// アクターの生成
        /// @param[in] type 登録済みの任意の文字列キー
        /// @return 生成したインスタンスのポインタ
        std::unique_ptr<Actor> Create(std::string_view type);

        void Clear();

        /**
         * @brief  ギミックマップ内の特定の要素を削除      
         */
        //void ClearValueGimmick(StageV old);

        /**
         * @breif 登録したインスタンスを削除
         */
         //void Delete();

         //struct SpawnRecord {
         //    int _progress{ 0 };
         //    std::string _key;
         //    Math::Vector4 _position{ 0, 0, 0 };
         //    Math::Vector4 _rotation{ 0, 0, 0 };
         //};

      //   using SpawnTable = std::vector<SpawnRecord>;



        // void SetSpawnTable(SpawnTable spawnTable);

         /**
          * @brief  スポーンテーブルの中身を生成
          * @param  vEStageParamMap
          */
        void SetSpawnTable(std::unordered_map<int, ESMV> vEStageParamMap);
        void SetSpawnTable(std::unordered_map<int, ISMV> vIStageParamMap);
        void SetSpawnTable(std::unordered_map<int, GSV> gStageParamVMap);
        /**
         *
         * @brief 毎フレーム生成の確認
         */
        void UpdateSpawn();

        /**
         * .
         */
        std::unordered_map<int, ESMV> GetSpawn() { return _eStageParamVMap; }

        /**
         * @brief  スポーンテーブルを設定
         * @param  eStageParamV
         */
        void SetSpawn(const std::unordered_map<int, ESMV> eStageParamVMap) { _eStageParamVMap = eStageParamVMap; }


        /**
         * @brief  プレイヤーのいる現在のステージ番号を取得
         * @return _currentStageNo
         */
        StageV GetStageNo() { return _currentStageNo; }

        /**
         * @brief  今のステージ番号を設定
         * @param  currentStageNo
         */
        void SetStageNo(const StageV currentStageNo) { _currentStageNo = currentStageNo; }


        /**
         *
         * @brief  ステージテーブルを取得
         * @return _stageTableV
         */
        std::vector<StageV> GetStagetable() { return _stageTableV; }

        /**
         *
         * @brief  ステージテーブルを保存
         * @param  stageTable
         */
        void SetStageTable(const std::vector<StageV> stageTable) { _stageTableV = stageTable; }
 
        void SetOldStageNo() { _oldStageNo.clear(); _oldStageNo.emplace_back(-1); }

        //void SetBrokenWall(const Actor& act) { _brokenWallClear.push_back(act); }

        //int GetGimmickCollision(const int handle)  { return _frameGimmicks[handle]; }

       // void SetClearGimmick(Parameter::GStageParam gimmick);
        void SetBrokenWall(int num, int brokenWallNum); 

    private:
        AppFrame::Game& _game;
        std::unordered_map<std::string, std::unique_ptr<CreatorBase>> _creatorMap;
        // std::vector<SpawnRecord> _spawnTable;

        std::unordered_map<int, ESMV> _eStageParamVMap;
        std::unordered_map<int, ISMV> _iStageParamVMap;
        std::unordered_map<int, GSV> _gStageParamVMap;

        ISMV _iClearV; //!< 削除アイテムの保存
        GSV _gClearV;  //!< 削除ギミックの保存

        int _progress{ 0 };
        int _spawnProgress{ 0 };
        StageV _oldStageNo{ -1 };
        StageV _currentStageNo{ 0 };
        std::vector<StageV> _stageTableV;
        //std::vector<Actor> _brokenWallClear;
        static std::unordered_map<int, std::vector<int>> _floorBrokenWall; //!< フロア番号で壊せる壁のベクターを記録
        //std::unordered_map<int, int> _frameGimmicks; //!< ハンドル名でコリジョンを保存
        //std::unordered_map<>

    };

    /// @class CreatorBase
    /// @brief ActorFactoryに登録するクリエイターの基底クラス
    class CreatorBase {
    public:
        virtual ~CreatorBase() = default;
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game) = 0;
    };
    /// @class PlayerCreator
    /// @brief プレイヤー用のクリエイター
    class PlayerCreator : public CreatorBase {
        /// プレイヤーの生成
        /// @param  game ゲームクラスへの参照
        /// @return プレイヤーのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };
    /// @class TackleEnemyCreator
    /// @brief タックルエネミー用のクリエイター
    class TackleEnemyCreator : public CreatorBase {
        // 疑似乱数
   //     std::random_device _seed;
    //    std::mt19937 _engine{ _seed() };
    //    std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// エネミーの生成
        /// @param  game ゲームクラスへの参照
        /// @return エネミーのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);

    };

    /// @class CatchEnemyCreator
    /// @brief キャッチエネミー用のクリエイター
    class CatchEnemyCreator : public CreatorBase {
        // 疑似乱数
        //std::random_device _seed;
        //std::mt19937 _engine{ _seed() };
        //std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// エネミーの生成
        /// @param  game ゲームクラスへの参照
        /// @return エネミーのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };

    //class AlartEnemyCreator : public CreatorBase {
    //    // 疑似乱数
    //    std::random_device _seed;
    //    std::mt19937 _engine{ _seed() };
    //    std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
    //    int _count{ 0 };
    //    /// エネミーの生成
    //    /// @param[in] game ゲームクラスへの参照
    //    /// @return エネミーのインスタンス
    //    virtual std::unique_ptr<Actor> Create(Game& game);
    //};

    /**
     * @class StageCreator
     * @brief ステージ用のクリエイター
     */
    class StageCreator : public CreatorBase {
        /// ステージの生成
        /// @param  game ゲームクラスへの参照
        /// @return ステージのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };

    /**
     * @class DamageFloorGimmickCreator
     * @brief ダメージ床ギミック用のクリエイター
     */
    class DamageFloorGimmickCreator : public CreatorBase {
        /// ダメージ床ギミックの生成
        /// @param  game ゲームクラスへの参照
        /// @return ダメージ床ギミックのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);

    };

    class BrokenWallCreator : public CreatorBase {
        /// 壊せる壁の生成
        /// @param  game ゲームクラスへの参照
        /// @return 壊せる壁のインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);


    };

    class ItemCreator : public CreatorBase {
        /// アイテムの生成
        /// @param  game ゲームクラスへの参照
        /// @return アイテムのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);

    };

}

