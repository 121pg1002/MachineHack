/*****************************************************************//**
 * @file   SceneEpilogue.cpp
 * @brief  �G�s���[�O���
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "SceneEpilogue.h"
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include "../ShadowMap/Shadowmap.h"
#include "../Flag/FlagData.h"

namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    SceneEpilogue::SceneEpilogue(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// ������
    void SceneEpilogue::Init() {
        // �g�p����摜�̃e�[�u��
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"EpilogueBg",          {"title/team.png",          1, 1, 1920, 1080}},
          //{"GameTitleTeam",        {"GameTitle.png",        1, 1, 1553, 224}},
          //{"LeftClickToStartTeam", {"LeftClickToStart.png", 1, 1, 1135, 107}},
        };
        // �A�Z�b�g�T�[�o�[�̎擾
        auto& as = GetAssetServer();
        // �摜�̓ǂݍ���
        as.LoadTextures(textureToUsed);


        // �摜�̃n���h���擾
        _epilogueBgHandle = as.GetTexture("EpilogueBg");
        //_gameTitleHandle = as.GetTexture("GameTitleTeam");
        //_leftClickToStart = as.GetTexture("LeftClickToStartTeam");

        // �T�E���h�R���|�[�l���g�̎擾
        auto& sc = GetSoundComponent();
        sc.PlayLoop("bgm1");
        sc.SetVolume("bgm1", 50);
    }
    ///
    /// �o������
    /// 
    void SceneEpilogue::Exit() {
        // �A�N�^�[���폜
        GetActorServer().Clear();
        // �f���v���P�[�g�������f�������폜
        GetAssetServer().DeleteDuplicateModels();
        // �f���v���P�[�g�������f�������폜
        GetAssetServer().DeleteDuplicateMaps();

        // �N���G�C�^�[���폜
        GetActorFactory().Clear();
        //�V���h�E�}�b�v�̍폜
       // DeleteShadowMap(shadowmap.GetShadowmap());
    }
    ///
    /// ��������
    /// 
    void SceneEpilogue::Enter() {
        _alpha = 0;
    }
    ///
    /// ���͏���.
    ///
    void SceneEpilogue::Input(AppFrame::Input::InputComponent& input) {
        //if (input.GetMouse().LeftClick()) {
        //    // ���N���b�N��InGame�֑J��
        //    GetSceneServer().GoToScene("Title");
        //    _alpha = 255;
        //}
    }
    void SceneEpilogue::Update() {
        _alpha = (_alpha + 8) % 255;
        if (_alpha > 200) {
            // Team�֑J��
            GetSceneServer().GoToScene("Title");
           // Flag::FlagData::SetBlackOutFlag(true);
            _alpha = 255;
        }
    }
    ///
    /// �`��
    ///
    void SceneEpilogue::Render() {
        DrawGraph(0, 0, _epilogueBgHandle, FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        //  DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        //  DrawGraph(0, 0, _gameTeamHandle, TRUE);
    }
}