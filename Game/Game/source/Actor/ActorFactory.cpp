/*****************************************************************//**
 * @file   ActorFactory.cpp
 * @brief  �A�N�^�[�t�@�N�g���[
 *
 * @author yamawaki kota, hikaru Goto
 * @date   December 6 2021
 *********************************************************************/

#include "ActorFactory.h"
#include "ActorServer.h"
#include "../Player/Player.h"
#include "../Enemy/TackleEnemy.h"
#include "../Enemy/CatchEnemy.h"
#include "../Stage/Stage.h"
#include "../Model/ModelAnimComponent.h"
#include "../State/StateComponent.h"
#include "../Camera/CameraComponent.h"
#include "../Gimmick/DamageFloorGimmick.h"
#include "../Gimmick/BrokenWall.h"
#include "../Item/Item.h"
//#include "../Parameter/EStageParam.h"
//#include "../Parameter/IStageParam.h"
#include "../Parameter/GStageParam.h"


namespace Camera = MachineHuck::Camera;

namespace {

    //constexpr int StageAll = 3;        //!< �ǂݍ���stagejson�̐�
    constexpr double Differ = 3000.0; //!< 1�t���A�̃T�C�Y
    constexpr double StartX = -5.0 * Differ;
    constexpr int BoardSize = 10;

    //constexpr double HalfSize = 0.5 * Differ;
    //constexpr int StartZ = -5.0 * Differ;

}

namespace MachineHuck::Actor {
    class CreatorBase;
}

namespace MachineHuck::Actor {
    /// �R���X�g���N�^
    ActorFactory::ActorFactory(AppFrame::Game& game) : _game{ game } {

    }
    /// �N���G�C�^�[�̓o�^
    bool ActorFactory::Register(std::string_view type, std::unique_ptr<CreatorBase> creator) {

        //�L�[�̐���0�łȂ��Ȃ瑶�݂���
        if (_creatorMap.count(type.data()) != 0) {
            return false;
        }
        _creatorMap.emplace(type.data(), std::move(creator));
        return true;
    }

    /// �A�N�^�[�̐���
    std::unique_ptr<Actor> ActorFactory::Create(std::string_view type) {

        //�L�[�̐���1�łȂ��Ȃ瑶�݂��Ȃ�
        if (_creatorMap.count(type.data()) != 1) {
            return nullptr;
        }
        auto&& creator = _creatorMap[type.data()];
        return creator->Create(_game);
    }

    void ActorFactory::Clear() {
        _creatorMap.clear();
    }

    //void ActorFactory::SetSpawnTable(SpawnTable spawnTable) {
    //    _spawnProgress = 0;
    //    _progress = 0;
    //    _spawnTable = spawnTable;
    //}

    void ActorFactory::SetSpawnTable(std::unordered_map<int, ESMV> eStageParamVMap) {
        _spawnProgress = 0;
        _progress = 0;
        _eStageParamVMap = eStageParamVMap;
    }

    void ActorFactory::SetSpawnTable(std::unordered_map<int, ISMV> vIStageParamMap) {
        _spawnProgress = 0;
        _progress = 0;
        _iStageParamVMap = vIStageParamMap;

    }

    void ActorFactory::SetSpawnTable(std::unordered_map<int, GSV> gStageParamVMap) {
        _spawnProgress = 0;
        _progress = 0;
        _gStageParamVMap = gStageParamVMap;
    
    }

    //void ActorFactory::UpdateSpawn() {
    //    while (_spawnTable.size() > _spawnProgress) {
    //        auto& spawnRecord = _spawnTable[_spawnProgress];
    //        if (spawnRecord._progress > _progress) {
    //            break;
    //        }
    //        else {
    //            auto&& actor = Create(spawnRecord._key);
    //            actor->SetPosition(spawnRecord._position);
    //            actor->SetRotation(spawnRecord._rotation);
    //            _game.GetActorServer().Add(std::move(actor));
    //            ++_spawnProgress;
    //        }
    //    }
    //    ++_progress;
    //}

    void ActorFactory::UpdateSpawn() {

        std::vector<int> num;


        //���݂���ԍ��z��ƑO�̃X�e�[�W�ԍ��z�񂪈قȂ�ꍇ
        if (_oldStageNo != _currentStageNo) {


            //�Â��z��̒��̐V�����ԍ������o��
            for (auto old : _oldStageNo) {

                for (auto newNum : _currentStageNo) {

                    //�Â��ԍ��z��ɐV�����ԍ������������ꍇ
                    if (old != newNum) {

                        //�Â��ԍ��z��ɂ��邩
                        auto result = std::find(_oldStageNo.begin(), _oldStageNo.end(), newNum);

                        //���������ꍇ
                        if (result == _oldStageNo.end()) {

                            //�V�����G�l�~�[�𐶂ݏo���ԍ�
                            num.push_back(newNum);
                        }
                    }
                    //else {
                    //    continue;
                    //}

                }

            }

            //�O�̃t���A�̃G�l�~�[���폜����
            for (auto i = _game.GetActorServer().GetActors().begin(); i < _game.GetActorServer().GetActors().end(); i++) {

                //�G�l�~�[���ǂ���//�����A�C�e�����M�~�b�N��������
                if ((*i)->GetTypeId() == (*i)->IsEnemy() || (*i)->GetTypeId() == (*i)->IsItem()) {

                    //�n�b�L���O�����ǂ���
                    if ((*i)->IsHucked()) {

                        continue;
                    }

                    (*i)->SetDead();

                }


            }

            ////�O�̃X�e�[�W�ԍ����X�V
            _oldStageNo = _currentStageNo;



            ////�`�悷��t���A�̃X�e�[�W�ԍ��ŉ�
            //for (auto&& num : _currentStageNo) {

            //�󂩂ǂ����m�F
            if (!num.empty()) {

                //�V�����ԍ��ŉ�
                for (auto no : num) {

                    auto& spawnFloor = _eStageParamVMap[no];

                    //�V�����`��t���A�̃G�l�~�[�����X�|�[��������
                    for (auto&& floorEnemy : spawnFloor) {

                        auto&& actor = Create(floorEnemy.GetName());

                        //auto pos = floor.GetPosition();
                        //Math::Vector4 dif = {};

                        actor->SetPosition(floorEnemy.GetPosition());
                        actor->SetRotation(floorEnemy.GetRotation());
                        actor->SetScale(floorEnemy.GetScale());

                        //actor->SetLevel(floorEnemy.GetLevel());
                        actor->SetRoutine(floorEnemy.GetRoutine());

                        _game.GetActorServer().Add(std::move(actor));

                    }

                    auto& spawnFloori = _iStageParamVMap[no];
                    //�V�����`��t���A�̃A�C�e�������X�|�[��������
                    for (auto&& floorItem : spawnFloori) {

                        auto&& actor = Create("Item");

                        actor->SetPosition(floorItem.GetPosition());
                        actor->SetRotation(floorItem.GetRotation());
                        actor->SetScale(floorItem.GetScale());

                        _game.GetActorServer().Add(std::move(actor));

                    }



                    //auto& spawnFloorGimmick = _gStageParamVMap[no];
                    //////�V�����`��t���A�̃M�~�b�N�����X�|�[��������
                    //for (auto&& floorGimmick : spawnFloorGimmick) {

                    //    auto&& actor = Create(floorGimmick.GetName());

                    //    actor->SetPosition(floorGimmick.GetPosition());
                    //    actor->SetRotation(floorGimmick.GetRotation());
                    //    actor->SetScale(floorGimmick.GetScale());

                    //    _game.GetActorServer().Add(std::move(actor));

                    //}




                }


            }



        }

    }

    //void ActorFactory::Delete() {



    //}

    /// �v���C���[�̐���
    std::unique_ptr<Actor> PlayerCreator::Create(AppFrame::Game& game) {
        // �J�����̐���
        auto camera = std::make_shared<Camera::CameraComponent>();
        camera->Init();
        camera->SetPosition({ 0, 1000, -500 });
        camera->SetTarget({ 0, 100, 0 });

        // �v���C���[�̐���
        auto player = std::make_unique<Player::Player>(game);
        player->SetCameraComponent(camera);
        player->SetPosition({ -Differ * 5.0 + Differ * 0.5, 0, Differ * 0.5 });
        player->SetRotation({ 0.5, 0.0, 0.0 });

        // ���f���̓ǂݍ��݂Ɛ���
        auto model = std::make_unique<Model::ModelAnimeComponent>(*player);
        model->SetModel("Player");
        model->Register("Attack", 0);
        model->Register("Run", 1);
        model->Register("Idle", 2);
        model->Register("Die", 3);
        //model->Register("JumpStart", 3);
        //model->Register("JumpLoop", 4);
        //model->Register("JumpEnd", 5);
        player->SetModelAnimeComponent(std::move(model));

        auto state = std::make_unique<State::StateComponent>("Idle", std::make_shared <Player::Player::StateIdle>(*player));
        state->Register("Run", std::make_shared<Player::Player::StateRun>(*player));
        state->Register("Attack", std::make_shared<Player::Player::StateAttack>(*player));
        //state->Register("KnockBack", std::make_shared<Player::StateKnockBack>(*player));
        state->Register("Hucking", std::make_shared<Player::Player::StateHucking>(*player));
        state->Register("Hucked", std::make_shared<Player::Player::StateHucked>(*player));
        state->Register("Die", std::make_shared<Player::Player::StateDie>(*player));
        state->Register("Damage", std::make_unique<Player::Player::StateDamage>(*player));
        player->SetStateComponent(std::move(state));

        return player;
    }

    /// �^�b�N���G�l�~�[�̐���
    std::unique_ptr<Actor> TackleEnemyCreator::Create(AppFrame::Game& game) {
        // �^�b�N���G�l�~�[�̐���
        auto enemy = std::make_unique<Enemy::TackleEnemy>(game);

        //std::vector<std::string> type = { "Tackle", "Grab", "Alart" };

        // �G�l�~�[��json����p�����[�^�[��ǂݍ���

        //auto i = game.GetStageParameter().GetStageMap().find();
        //for(int i =0; i < )

        enemy->LoadJson("resource/json/tackle.json");

        //���������������������������������������������́A���̐�������Ƃ��ɓ����G�̎�ނ̂��̂�����
        //enemy->LoadJson("resource/json/Grab.json");
        //enemy->LoadJson("resource/json/Alart.json");

        // ���x��3�`9�Ń����_��
        enemy->SetForwardSpeed(1.0f);

        // ���f���̓ǂݍ��݂Ɛ���
        auto model = std::make_unique<Model::ModelAnimeComponent>(*enemy);
        model->SetModel("Spider", 1000);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        //model->Register("Fall", 3);
        //model->Register("Attack", 4);
        /*No.0 idle
            No.1 walk
            No, 2 attack
            No.3 tackle
            */
        model->Register("Hucking", 3);
        model->Register("Die", 0);
        model->Register("Idle", 0);
        model->Register("Walk", 1);
        model->Register("Attack", 2);
        model->Register("Tackle", 3);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        ////model->Register("Die2", 2);
        //model->Register("Fall", 3);
        //model->Register("Attack", 4);
        //model->Register("Normal", 5);
        //model->Register("RunAniBack", 6);
        model->Register("RunAniVor", 7);
        //model->Register("RunLeft", 8);
        //model->Register("RunRight", 9);
        //model->Register("WalkAniBack", 10);
        //model->Register("WalkAniBor", 11);
        //model->Register("WalkLeft", 12);
        //model->Register("WalkRight", 13);
        //model->Register("WartePose", 14);
        enemy->SetModelAnimeComponent(std::move(model));

        auto state = std::make_unique<State::StateComponent>("Fall", std::make_shared <Enemy::TackleEnemy::StateFall>(*enemy));
        state->Register("Idle", std::make_shared<Enemy::TackleEnemy::StateIdle>(*enemy));
        state->Register("Run", std::make_shared<Enemy::TackleEnemy::StateRun>(*enemy));
        state->Register("Die", std::make_shared<Enemy::TackleEnemy::StateDie>(*enemy));
        state->Register("Tackle", std::make_shared<Enemy::TackleEnemy::StateTackle>(*enemy));
        state->Register("TackleAfter", std::make_shared<Enemy::TackleEnemy::StateTackleAfter>(*enemy));
        //state->Register("Attack", std::make_shared<Enemy::StateAttack>(*enemy));
        state->Register("IsHucking", std::make_shared<Enemy::TackleEnemy::StateHucking>(*enemy));
        state->Register("IsHucked", std::make_shared<Enemy::TackleEnemy::StateHucked>(*enemy));
        enemy->SetStateComponent(std::move(state));


        // ���̐����ׂ̈ɃJ�E���g�A�b�v
        ++_count;
        return enemy;
    }

    /// �L���b�`�G�l�~�[�̐���
    std::unique_ptr<Actor> CatchEnemyCreator::Create(AppFrame::Game& game) {
        // �^�b�N���G�l�~�[�̐���
        auto enemy = std::make_unique<Enemy::CatchEnemy>(game);

        //std::vector<std::string> type = { "Tackle", "Grab", "Alart" };

        // �G�l�~�[��json����p�����[�^�[��ǂݍ���

        //auto i = game.GetStageParameter().GetStageMap().find();
        //for(int i =0; i < )

        enemy->LoadJson("resource/json/catch.json");

        enemy->SetForwardSpeed(1.0f);

        // ���f���̓ǂݍ��݂Ɛ���
        auto model = std::make_unique<Model::ModelAnimeComponent>(*enemy);
        model->SetModel("Spider", 1000);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        //model->Register("Fall", 3);
        //model->Register("Catch", 4);
        //model->Register("RunAniVor", 7);

        model->Register("Hucking", 3);
        model->Register("Die", 0);
        model->Register("Idle", 0);
        model->Register("Walk", 1);
        model->Register("Attack", 2);
        model->Register("Tackle", 3);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        ////model->Register("Die2", 2);
        //model->Register("Fall", 3);
        //model->Register("Attack", 4);
        //model->Register("Normal", 5);
        //model->Register("RunAniBack", 6);
        model->Register("RunAniVor", 7);
        //model->Register("RunLeft", 8);
        //model->Register("RunRight", 9);
        //model->Register("WalkAniBack", 10);
        //model->Register("WalkAniBor", 11);
        //model->Register("WalkLeft", 12);
        //model->Register("WalkRight", 13);
        //model->Register("WartePose", 14);
        enemy->SetModelAnimeComponent(std::move(model));

        auto state = std::make_unique<State::StateComponent>("Fall", std::make_shared <Enemy::CatchEnemy::StateFall>(*enemy));
        state->Register("Idle", std::make_shared<Enemy::CatchEnemy::StateIdle>(*enemy));
        //state->Register("Run", std::make_shared<Enemy::CatchEnemy::StateRun>(*enemy));
        state->Register("Die", std::make_shared<Enemy::CatchEnemy::StateDie>(*enemy));
        state->Register("Catch", std::make_shared<Enemy::CatchEnemy::StateCatch>(*enemy));
        state->Register("CatchAfter", std::make_shared<Enemy::CatchEnemy::StateCatchAfter>(*enemy));
        state->Register("CatchPre", std::make_shared<Enemy::CatchEnemy::StateCatchPre>(*enemy));
        // state->Register("Attack", std::make_shared<Enemy::CatchEnemy::StateAttack>(*enemy));
        state->Register("IsHucking", std::make_shared<Enemy::CatchEnemy::StateHucking>(*enemy));
        state->Register("IsHucked", std::make_shared<Enemy::CatchEnemy::StateHucked>(*enemy));
        enemy->SetStateComponent(std::move(state));


        // ���̐����ׂ̈ɃJ�E���g�A�b�v
        ++_count;
        return enemy;
    }



    /// �X�e�[�W�̐���
    std::unique_ptr<Actor> StageCreator::Create(AppFrame::Game& game) {
        /// �X�e�[�W�̐���
        auto stage = std::make_unique<Stage::Stage>(game);
        return stage;
    }

    //�_���[�W���M�~�b�N�̐���
    std::unique_ptr<Actor> DamageFloorGimmickCreator::Create(AppFrame::Game& game) {

        /// �_���[�W���M�~�b�N�̐���
        auto damageFloorGimmick = std::make_unique<Gimmick::DamageFloorGimmick>(game);

        // ���f���̓ǂݍ��݂Ɛ���
        //auto model = std::make_unique<Model::ModelComponent>(*damageFloorGimmick);
        //model->SetModel("damagefloor", 1000);
        //damageFloorGimmick->SetModelComponent(std::move(model));
        return damageFloorGimmick;
    }

    //�󂹂�ǂ��쐬
    std::unique_ptr<Actor> BrokenWallCreator::Create(AppFrame::Game& game) {
        /// �󂹂�ǂ̐���
        auto brokenWall = std::make_unique<Gimmick::BrokenWall>(game);
        //// ���f���̓ǂݍ��݂Ɛ���
        auto model = std::make_unique<Model::ModelComponent>(*brokenWall);
        model->SetModel("BrokenWall", 1000);
        brokenWall->SetModelComponent(std::move(model));
        return brokenWall;
    }


    //�G�l���M�[�A�C�e���̍쐬
    std::unique_ptr<Actor> ItemCreator::Create(AppFrame::Game& game) {
        auto item = std::make_unique<Item::Item>(game);
        auto model = std::make_unique<Model::ModelComponent>(*item);
        model->SetModel("Item", 1000);
        item->SetModelComponent(std::move(model));

        return item;
    }
}


