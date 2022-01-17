///
/// @file    ActorFactory.h
/// @brief   �A�N�^�[�t�@�N�g���[
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
    /// @brief �A�N�^�[�̐������ꌳ�Ǘ�����
    ///        �����������A�N�^�[�p�̃N���G�C�^�[��o�^���Ďg�p����
    class ActorFactory {
    public:
        /// �R���X�g���N�^
        /// @param[in] game �Q�[���N���X�ւ̎Q�� 
        ActorFactory(AppFrame::Game& game);
        /// �N���G�C�^�[�̓o�^
        /// @param[in] type �C�ӂ̕�����L�[
        /// @param[in] creator �o�^����N���G�C�^�[�̃C���X�^���X
        /// @return �o�^�̐���
        bool Register(std::string_view type, std::unique_ptr<CreatorBase> creator);
        /// �A�N�^�[�̐���
        /// @param[in] type �o�^�ς݂̔C�ӂ̕�����L�[
        /// @return ���������C���X�^���X�̃|�C���^
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
    /// @brief ActorFactory�ɓo�^����N���G�C�^�[�̊��N���X
    ///        ���̃N���X���p�����ăN���G�C�^�[���`����
    class CreatorBase {
    public:
        virtual ~CreatorBase() = default;
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game) = 0;
    };
    /// @class PlayerCreator
    /// @brief �v���C���[�p�̃N���G�C�^�[
    class PlayerCreator : public CreatorBase {
        /// �v���C���[�̐���
        /// @param[i] game �Q�[���N���X�ւ̎Q��
        /// @return �v���C���[�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };
    /// @class TackleEnemyCreator
    /// @brief �^�b�N���G�l�~�[�p�̃N���G�C�^�[
    class TackleEnemyCreator : public CreatorBase {
        // �^������
        std::random_device _seed;
        std::mt19937 _engine{ _seed() };
        std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// �G�l�~�[�̐���
        /// @param[in] game �Q�[���N���X�ւ̎Q��
        /// @return �G�l�~�[�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };

    /// @class GrabEnemyCreator
    /// @brief �O���u�G�l�~�[�p�̃N���G�C�^�[
    class GrabEnemyCreator : public CreatorBase {
        // �^������
        std::random_device _seed;
        std::mt19937 _engine{ _seed() };
        std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// �G�l�~�[�̐���
        /// @param[in] game �Q�[���N���X�ւ̎Q��
        /// @return �G�l�~�[�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };

    //class AlartEnemyCreator : public CreatorBase {
    //    // �^������
    //    std::random_device _seed;
    //    std::mt19937 _engine{ _seed() };
    //    std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
    //    int _count{ 0 };
    //    /// �G�l�~�[�̐���
    //    /// @param[in] game �Q�[���N���X�ւ̎Q��
    //    /// @return �G�l�~�[�̃C���X�^���X
    //    virtual std::unique_ptr<Actor> Create(Game& game);
    //};

    /// @class StageCreator
    /// @brief �X�e�[�W�p�̃N���G�C�^�[
    class StageCreator : public CreatorBase {
        /// �X�e�[�W�̐���
        /// @param[in] game �Q�[���N���X�ւ̎Q��
        /// @return �X�e�[�W�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };
}

