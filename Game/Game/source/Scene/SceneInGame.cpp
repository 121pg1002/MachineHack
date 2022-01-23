/*****************************************************************//**
 * @file   SceneInGame.cpp
 * @brief  �C���Q�[�����
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/


#include "SceneInGame.h"
//#include <numbers>
#include "AppFrame.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include "../Enemy/EnemyParameter.h"
#include "../UI/UIComponent.h"

namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    SceneInGame::SceneInGame(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// ������
    void SceneInGame::Init() {
        // �g�p���郂�f��
        AppFrame::Asset::AssetServer::ModelMap usedInGame{
        //{"Player",    "SDChar/SDChar.mv1"},
        {"Player",    "Player/player.mv1"},
        {"SkySphere", "skysphere.mv1"},
        {"Ground",    "ground.mv1"},
        //{"Spider",    "Spider_3.mv1"},
        {"Spider",    "tackle/takcle.mv1"},
        {"pCube",      "pCube.mv1"},
        {"floor",     "floor.mv1"},
        {"wall",      "wall.mv1"},
        {"Dungeon",   "Dungeon.mv1"},
        {"breakwall",  "breakwall.mv1"},
        {"enemy",      "enemy.mv1"},
        {"gate",       "gate.mv1"},
        {"normalfloor",  "normalfloor.mv1"},
        {"normalwall",  "normalwall.mv1"},
        {"secretfloor", "secretfloor.mv1"},
        {"secretwall", "secretwall.mv1"},
        {"damagefloor",  "target.mv1"}
        };
        // ���f���̓ǂݍ���
        GetAssetServer().LoadModels(usedInGame);                                                         //�ǉ�
        //�V���h�E�}�b�v�̓ǂݍ���
        shadowmap.SetShadowMap();
        // �g�p����e�N�X�`��
        AppFrame::Asset::AssetServer::TextureMap TexUsed{
          {"BarFrame", {"BarFrame.png", 1, 1, 340, 50}}
        };
        // �e�N�X�`���̓ǂݍ���
        GetAssetServer().LoadTextures(TexUsed);

    }
    /// ����
    void SceneInGame::Enter() {
        // �t�@�N�g���̐����ƃN���G�C�^�[�̓o�^
        auto& af = GetActorFactory();
        af.Register("Player", std::make_unique<Actor::PlayerCreator>());
        af.Register("TackleEnemy", std::make_unique<Actor::TackleEnemyCreator>());
        // af.Register("GrabEnemy", std::make_unique<GrabEnemyCreator>());
       //  af.Register("AlartEnemy", std::make_unique<AlartEnemyCreator>());
        af.Register("Stage", std::make_unique<Actor::StageCreator>());
        af.Register("DamageFloor", std::make_unique<Actor::DamageFloorGimmickCreator>());
        af.Register("BrokenWall", std::make_unique<Actor::BrokenWallCreator>());


        //for (int i = 0; i < StageAll; i++) {



        
        //    //�X�e�[�W�ԍ���string�ɕϊ�
        //    auto no = std::to_string(i);
        //    //���̓���N�������json���ǂݍ��߂�
        //    //auto stageParameter = std::make_unique<StageParameter>();
        //    game.GetStageParameter().LoadStageParameter("resource/json/sample" + no + ".json");

        //}


        //auto EParam = std::make_unique<EnemyParameter>();

        //for (int i = 0; i < 10; i++) {

        //    //�X�e�[�W�ԍ���string�ɕϊ�
        //    auto no = std::to_string(i);
        //    //���̓���N�������json���ǂݍ��߂�
        //    EParam->LoadStageEnemyParam("resource/json/stageenemy" + no + ".json");

        //}

        MachineHuck::Actor::ActorFactory::SpawnTable inGame{
          {0     , "TackleEnemy", { 300.f, 200.f, 300.0f}},
          {0     , "TackleEnemy", {   0.f, 220.f, 500.0f}},
          {0     , "TackleEnemy", {-300.f, 210.f, 400.0f}},

          //{0     , "DamageFloor", { 500.f, 200.f, 0.0f}},
          //{0     , "DamageFloor", {  0.f,  200.f, 100.0f}},
          //{0     , "DamageFloor", {-500.f, 200.f, 200.0f}},

          //{60 * 10,"Enemy", { 1000.f, 2000.f, -4500}},
          //{0     , "Enemy", {    0.f, 2200.f, -4500}},
          //{0     , "Enemy", {-1000.f, 2100.f, -4500}},

          //{60 * 15,"Enemy", { 1500.f, 2000.f, -4500}},
          //{0     , "Enemy", {    0.f, 2200.f, -4500}},
          //{0     , "Enemy", {-1500.f, 2100.f, -4500}},
        };


        af.SetSpawnTable(inGame);

        //af.SetSpawnTable(EParam->GetStageEnemyParameter());

        //// �A�N�^�[�T�[�o�[�ɓo�^���ʃA�N�Z�X�p
        auto& as = GetActorServer();

        // �X�e�[�W�̐����ƒǉ�
        auto stage = af.Create("Stage");
        as.Add(std::move(stage));

        ////�_���[�W���M�~�b�N�̐����ƒǉ�
        //auto damageFloorGimmick = af.Create("DamageFloor");
        //as.Add(std::move(damageFloorGimmick));


        //for (int i = 0; i < 3; i++) 
        //{
        //    auto spawnTable = inGame[i];
        //    std::string u = static_cast<std::string>(i);
        //    auto enemy = af.Create(spawnTable._key);
        //    std::pair<Math::Vector4, Math::Vector4> pos_dir = { spawnTable._position, spawnTable._rotation };
        //    as.Register("Enemy" + u, pos_dir);
        //    as.Add(std::move(enemy));
        //}

        // �v���C���[�̐����ƒǉ�
        auto player = af.Create("Player");
        std::pair<Math::Vector4, Math::Vector4> pos_dir = { player->GetPosition(), player->GetRotation() };
        as.Register("Player", pos_dir);
        as.Add(std::move(player));

        GetUiComponent().Enter();

        // �^������
        //std::random_device seed;
        //std::mt19937 engine{seed()};
        //std::uniform_real_distribution<float> zPosition{1000, 2500};
        //std::uniform_real_distribution<float> forwardSpeed{3, 9};
        Update();
    }
    /// ���͏���
    void SceneInGame::Input(AppFrame::Input::InputComponent& input) {

        if (input.GetMouse().RightClick()) {
            // �E�N���b�N�Ń^�C�g���֑J��
            //GetSceneServer().GoToScene("Title");
            GetSceneServer().GoToScene("Epilogue");
        }
        if (input.GetJoypad().Button_X()) {
            // X�{�^���Ń}�b�v��ʂ�
            GetSceneServer().PopBack(1);
            GetSceneServer().PushBack("Map",1);
        }
        if (input.GetJoypad().Button_Y()) {
            // Y�{�^���ŃA�C�e����ʂ�
            GetSceneServer().PopBack(1);
            GetSceneServer().PushBack("Item", 1);
        }
        GetActorServer().Input(input);
    }
    /// �X�V
    void SceneInGame::Update() {
        GetActorFactory().UpdateSpawn();
        GetActorServer().Update();
        GetUiComponent().Update();
    }

    /// �`��
    void SceneInGame::Render() {
        //�V���h�E�}�b�v�ւ̕`��̏������s��
        ShadowMap_DrawSetup(shadowmap.GetShadowmap());
        //�V���h�E�}�b�v�ɕ`�悵����3D���f���̕`��
        GetActorServer().Render();
        //�V���h�E�}�b�v�ւ̕`����I������
        ShadowMap_DrawEnd();
        //	�`��Ŏg�p����V���h�E�}�b�v��ύX����
        SetUseShadowMap(0, shadowmap.GetShadowmap());
        //3D���f���̕`��
        GetActorServer().Render();
        //�RD���f���̕`��Ŏg�p�����V���h�E�}�b�v�̐ݒ����������
        SetUseShadowMap(0, -1);
        //UI�̕`��
        GetUiComponent().Render();
    }
    /// �o��
    void SceneInGame::Exit() {
        // �A�N�^�[���폜
        GetActorServer().Clear();
        // �f���v���P�[�g�������f�������폜
        GetAssetServer().DeleteDuplicateModels();
        // �N���G�C�^�[���폜
        GetActorFactory().Clear();
        //�V���h�E�}�b�v�̍폜
        DeleteShadowMap(shadowmap.GetShadowmap());

    }
}
