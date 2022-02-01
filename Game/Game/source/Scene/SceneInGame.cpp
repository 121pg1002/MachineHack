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
#include "../Flag/FlagData.h"

namespace {

    constexpr int StageAll = 1; //!< �ǂݍ���json�̍ő吔

}

namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    SceneInGame::SceneInGame(AppFrame::Game& game)
        :Scene{ game }
    {
        shadowmap = std::make_unique<ShadowMap::Shadowmap>(game);
    }
    /// ������
    void SceneInGame::Init() {
        // �g�p���郂�f��
        AppFrame::Asset::AssetServer::ModelMap usedInGame{
        //{"Player",    "SDChar/SDChar.mv1"},
        {"Player",    "Player/player.mv1"},
        {"SkySphere", "model/skysphere.mv1"},
        {"Ground",    "model/ground.mv1"},
        {"Spider",    "tackle/takcle.mv1"},
        {"pCube",      "model/pCube.mv1"},
        {"floor",     "model/floor.mv1"},
        {"wall",      "model/wall.mv1"},
        {"Dungeon",   "model/Dungeon.mv1"},
        {"breakwall",  "model/breakwall.mv1"},
        {"enemy",      "model/enemy.mv1"},
        {"gate",       "model/gate.mv1"},
        {"normalfloor",  "model/normalfloor.mv1"},
        {"normalwall",  "model/normalwall.mv1"},
        {"secretfloor", "model/secretfloor.mv1"},
        {"secretwall", "model/secretwall.mv1"},
        //  {"damagefloor",  "target.mv1"},
          {"entrypoint", "entrypoint.mv1"},
          {"test", "test.mv1"},
          // {"Dungeon",   "Dungeon.mv1"},
          // {"stage0",    "stage0.mv1"}

        };

        AppFrame::Asset::AssetServer::StageMap stageHandles{
            //{"Dunge0",   "Dungeon.mv1"}
            {"stage0",    "StageFloor/stage0.mv1"},
            {"stage1",    "StageFloor/stage1.mv1"},
            {"Dunge2",   "StageFloor/Dunge2.mv1"}
            //    {"Stage3",    "Stage3.mv1"}
        };


        // ���f���̓ǂݍ���
        GetAssetServer().LoadModels(usedInGame);                                                         //�ǉ�

        //�X�e�[�W�p�̃��f���ǂݍ���
        GetAssetServer().LoadMaps(stageHandles);
        //�ǉ�
        //�V���h�E�}�b�v�̓ǂݍ���
        shadowmap->SetShadowMap();
        // �g�p����e�N�X�`��
        AppFrame::Asset::AssetServer::TextureMap TexUsed{
          {"BarFrame", {"BarFrame.png", 1, 1, 340, 50}},
          {"black", {"BlackColor.png", 1, 1, 1920, 1080}},
          {"Energy0", {"energy/Energy0.png", 1, 1, 85, 85}}
        };
        // �e�N�X�`���̓ǂݍ���
        GetAssetServer().LoadTextures(TexUsed);

        _grHandle = GetAssetServer().GetTexture("black");

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

        //�G�l�~�[�̃X�e�[�W�z�u���ꊇ�œǂݍ���
        for (int i = 0; i < StageAll; i++) {

            //�X�e�[�W�ԍ���string�ɕϊ�
            auto no = std::to_string(i);
            //���̓���N�������json���ǂݍ��߂�
            //auto stageParameter = std::make_unique<StageParameter>();
            GetGame().GetEnemyParameter().LoadStageEnemyParam(i, "resource/json/stageenemy" + no + ".json");
        }


        //�ǂݍ��񂾃G�l�~�[�̃X�e�[�W�z�u���e�[�u���ɓ����
        auto inGame = GetGame().GetEnemyParameter().GetFloorEnemyMap();

        //�G�l�~�[�̃X�|�[���e�[�u���̓ǂݍ���

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
            GetSceneServer().PopBack(true);
            GetSceneServer().PushBack("Map",true);
        }
        if (input.GetJoypad().Button_Y()) {
            // Y�{�^���ŃA�C�e����ʂ�
            GetSceneServer().PopBack(true);
            GetSceneServer().PushBack("Item", true);
        }
        GetActorServer().Input(input);
    }
    /// �X�V
    void SceneInGame::Update() {
        GetActorFactory().UpdateSpawn();
        GetActorServer().Update();
        GetUiComponent().Update();


        if (Flag::FlagData::GetFadeOutFlag()) {
            //GetSceneServer().PopBack(true);
            //GetSceneServer().PushBack("FadeOut");
            GetSceneServer().GoToScene("Loading", "FadeOut", false);

            //Flag::FlagData::SetFadeOutFlag(false);
            //�t�F�[�h�A�E�g�̕���PopBack���Ă��Ȃ��̂��Ǝv��
        }

        if (Flag::FlagData::GetFadeInFlag()) {
            GetSceneServer().GoToScene("Loading", "FadeIn", false);

            Flag::FlagData::SetFadeInFlag(false);
        }

    }

    /// �`��
    void SceneInGame::Render() {


        //�V���h�E�}�b�v�ւ̕`��̃t���O���I���ɂ���
        shadowmap->SetPlayerShadowMapflg(TRUE);
        //�V���h�E�}�b�v�ւ̕`��̏������s��
        ShadowMap_DrawSetup(shadowmap->GetShadowmap());
        //�V���h�E�}�b�v�ɕ`�悵����3D���f���̕`��
        GetActorServer().Render();
        //�V���h�E�}�b�v�ւ̕`����I������
        ShadowMap_DrawEnd();
        //�V���h�E�}�b�v�ւ̕`��̃t���O���I�t�ɂ���B
        shadowmap->SetPlayerShadowMapflg(FALSE);
        //	�`��Ŏg�p����V���h�E�}�b�v��ύX����
        SetUseShadowMap(0, shadowmap->GetShadowmap());
        //3D���f���̕`��
        GetActorServer().Render();
        //�RD���f���̕`��Ŏg�p�����V���h�E�}�b�v�̐ݒ����������
        SetUseShadowMap(0, -1);
        //UI�̕`��
        GetUiComponent().Render();

        if (Flag::FlagData::GetBlackOutFlag()) {
            DrawGraph(0, 0, _grHandle, true);
            //Flag::FlagData::SetBlackOutFlag(false);
        }
    }
    /// �o��
    void SceneInGame::Exit() {
        // �A�N�^�[���폜
        GetActorServer().Clear();
        // �f���v���P�[�g�������f�������폜
        GetAssetServer().DeleteDuplicateModels();

        // �f���v���P�[�g�������f�������폜
        GetAssetServer().DeleteDuplicateMaps();

        // �N���G�C�^�[���폜
        GetActorFactory().Clear();
        //�V���h�E�}�b�v�̍폜
        DeleteShadowMap(shadowmap->GetShadowmap());

    }
}
