///
/// @file    SceneEpilogue.cpp
/// @brief   �^�C�g�����
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "SceneEpilogue.h"
#include <DxLib.h>

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
    /// ��������
    /// 
    void SceneEpilogue::Enter() {
        _alpha = 0;
    }
    ///
    /// ���͏���.
    ///
    void SceneEpilogue::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // ���N���b�N��InGame�֑J��
            GetSceneServer().GoToScene("Title");
            _alpha = 255;
        }
    }
    void SceneEpilogue::Update() {
        _alpha = (_alpha + 8) % 255;
        if (_alpha > 200) {
            // Team�֑J��
            GetSceneServer().GoToScene("Title");
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