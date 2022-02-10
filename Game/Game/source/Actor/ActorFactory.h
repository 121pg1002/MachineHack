/*****************************************************************//**
 * @file   ActorFactory.h
 * @brief  �A�N�^�[�t�@�N�g���[
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

        /**
         * @brief  �M�~�b�N�}�b�v���̓���̗v�f���폜      
         */
        //void ClearValueGimmick(StageV old);

        /**
         * @breif �o�^�����C���X�^���X���폜
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
          * @brief  �X�|�[���e�[�u���̒��g�𐶐�
          * @param  vEStageParamMap
          */
        void SetSpawnTable(std::unordered_map<int, ESMV> vEStageParamMap);
        void SetSpawnTable(std::unordered_map<int, ISMV> vIStageParamMap);
        void SetSpawnTable(std::unordered_map<int, GSV> gStageParamVMap);
        /**
         *
         * @brief ���t���[�������̊m�F
         */
        void UpdateSpawn();

        /**
         * .
         */
        std::unordered_map<int, ESMV> GetSpawn() { return _eStageParamVMap; }

        /**
         * @brief  �X�|�[���e�[�u����ݒ�
         * @param  eStageParamV
         */
        void SetSpawn(const std::unordered_map<int, ESMV> eStageParamVMap) { _eStageParamVMap = eStageParamVMap; }


        /**
         * @brief  �v���C���[�̂��錻�݂̃X�e�[�W�ԍ����擾
         * @return _currentStageNo
         */
        StageV GetStageNo() { return _currentStageNo; }

        /**
         * @brief  ���̃X�e�[�W�ԍ���ݒ�
         * @param  currentStageNo
         */
        void SetStageNo(const StageV currentStageNo) { _currentStageNo = currentStageNo; }


        /**
         *
         * @brief  �X�e�[�W�e�[�u�����擾
         * @return _stageTableV
         */
        std::vector<StageV> GetStagetable() { return _stageTableV; }

        /**
         *
         * @brief  �X�e�[�W�e�[�u����ۑ�
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

        ISMV _iClearV; //!< �폜�A�C�e���̕ۑ�
        GSV _gClearV;  //!< �폜�M�~�b�N�̕ۑ�

        int _progress{ 0 };
        int _spawnProgress{ 0 };
        StageV _oldStageNo{ -1 };
        StageV _currentStageNo{ 0 };
        std::vector<StageV> _stageTableV;
        //std::vector<Actor> _brokenWallClear;
        static std::unordered_map<int, std::vector<int>> _floorBrokenWall; //!< �t���A�ԍ��ŉ󂹂�ǂ̃x�N�^�[���L�^
        //std::unordered_map<int, int> _frameGimmicks; //!< �n���h�����ŃR���W������ۑ�
        //std::unordered_map<>

    };

    /// @class CreatorBase
    /// @brief ActorFactory�ɓo�^����N���G�C�^�[�̊��N���X
    class CreatorBase {
    public:
        virtual ~CreatorBase() = default;
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game) = 0;
    };
    /// @class PlayerCreator
    /// @brief �v���C���[�p�̃N���G�C�^�[
    class PlayerCreator : public CreatorBase {
        /// �v���C���[�̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
        /// @return �v���C���[�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };
    /// @class TackleEnemyCreator
    /// @brief �^�b�N���G�l�~�[�p�̃N���G�C�^�[
    class TackleEnemyCreator : public CreatorBase {
        // �^������
   //     std::random_device _seed;
    //    std::mt19937 _engine{ _seed() };
    //    std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// �G�l�~�[�̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
        /// @return �G�l�~�[�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);

    };

    /// @class CatchEnemyCreator
    /// @brief �L���b�`�G�l�~�[�p�̃N���G�C�^�[
    class CatchEnemyCreator : public CreatorBase {
        // �^������
        //std::random_device _seed;
        //std::mt19937 _engine{ _seed() };
        //std::uniform_real_distribution<float> _forwardSpeed{ 3, 9 };
        int _count{ 0 };
        /// �G�l�~�[�̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
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

    /**
     * @class StageCreator
     * @brief �X�e�[�W�p�̃N���G�C�^�[
     */
    class StageCreator : public CreatorBase {
        /// �X�e�[�W�̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
        /// @return �X�e�[�W�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);
    };

    /**
     * @class DamageFloorGimmickCreator
     * @brief �_���[�W���M�~�b�N�p�̃N���G�C�^�[
     */
    class DamageFloorGimmickCreator : public CreatorBase {
        /// �_���[�W���M�~�b�N�̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
        /// @return �_���[�W���M�~�b�N�̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);

    };

    class BrokenWallCreator : public CreatorBase {
        /// �󂹂�ǂ̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
        /// @return �󂹂�ǂ̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);


    };

    class ItemCreator : public CreatorBase {
        /// �A�C�e���̐���
        /// @param  game �Q�[���N���X�ւ̎Q��
        /// @return �A�C�e���̃C���X�^���X
        virtual std::unique_ptr<Actor> Create(AppFrame::Game& game);

    };

}

