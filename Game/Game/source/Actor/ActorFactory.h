///
/// @file    ActorFactory.h
/// @brief   アクターファクトリー
/// @date    2021/12/6
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#pragma once
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <DxLib.h>
#include "AppFrame.h"
#include "../Parameter/EStageParam.h"

namespace MachineHuck::Actor {
    class Actor;
    class CreatorBase;
}
class Game;




namespace Math = AppFrame::Math;

namespace MachineHuck::Actor {
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

        struct SpawnRecord {
            int _progress{ 0 };
            std::string _key;
            Math::Vector4 _position{ 0, 0, 0 };
            Math::Vector4 _rotation{ 0, 0, 0 };
        };

        using SpawnTable = std::vector<SpawnRecord>;

        void SetSpawnTable(SpawnTable spawnTable);


        void SetSpawnTable(std::vector<Parameter::EStageParam> vEStageParam);

        void UpdateSpawn();

    private:
        AppFrame::Game& _game;
        std::unordered_map<std::string, std::unique_ptr<CreatorBase>> _creatorMap;
        std::vector<SpawnRecord> _spawnTable;

        std::vector<Parameter::EStageParam> _eStageParamV;

        int _progress{ 0 };
        int _spawnProgress{ 0 };
    };

    /// @class CreatorBase
    /// @brief ActorFactoryに登録するクリエイターの基底クラス
    ///        このクラスを継承してクリエイターを定義する
    class CreatorBase {
    public:
        virtual ~CreatorBase() = default;
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game) = 0;
    };
    /// @class PlayerCreator
    /// @brief プレイヤー用のクリエイター
    class PlayerCreator : public CreatorBase {
        /// プレイヤーの生成
        /// @param[i] game ゲームクラスへの参照
        /// @return プレイヤーのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };
    /// @class TackleEnemyCreator
    /// @brief タックルエネミー用のクリエイター
    class TackleEnemyCreator : public CreatorBase {
        // 疑似乱数
        std::random_device _seed;
        std::mt19937 _engine{ _seed() };
        std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// エネミーの生成
        /// @param[in] game ゲームクラスへの参照
        /// @return エネミーのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };

    /// @class GrabEnemyCreator
    /// @brief グラブエネミー用のクリエイター
    class GrabEnemyCreator : public CreatorBase {
        // 疑似乱数
        std::random_device _seed;
        std::mt19937 _engine{ _seed() };
        std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// エネミーの生成
        /// @param[in] game ゲームクラスへの参照
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

    /// @class StageCreator
    /// @brief ステージ用のクリエイター
    class StageCreator : public CreatorBase {
        /// ステージの生成
        /// @param[in] game ゲームクラスへの参照
        /// @return ステージのインスタンス
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };
}

