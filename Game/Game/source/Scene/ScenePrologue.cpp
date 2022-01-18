/*****************************************************************//**
 * @file   ScenePrologue.cpp
 * @brief  �v�����[�O���
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "AppFrame.h"
#include "ScenePrologue.h"
#include <DxLib.h>

namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    ScenePrologue::ScenePrologue(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// ������
    void ScenePrologue::Init() {
        // �g�p����摜�̃e�[�u��
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"PrologueBg",          {"title/team.png",          1, 1, 1920, 1080}},
          //{"GameTitleTeam",        {"GameTitle.png",        1, 1, 1553, 224}},
          //{"LeftClickToStartTeam", {"LeftClickToStart.png", 1, 1, 1135, 107}},
        };
        // �A�Z�b�g�T�[�o�[�̎擾
        auto& as = GetAssetServer();
        // �摜�̓ǂݍ���
        as.LoadTextures(textureToUsed);


        // �摜�̃n���h���擾
        _epilogueBgHandle = as.GetTexture("PrologueBg");
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
    void ScenePrologue::Enter() {
        _alpha = 0;
    }
    ///
    /// ���͏���.
    ///
    void ScenePrologue::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // ���N���b�N��InGame�֑J��
            GetSceneServer().GoToScene("InGame");
            _alpha = 255;
        }
    }
    void ScenePrologue::Update() {
        _alpha = (_alpha + 8) % 255;
        if (_alpha > 200) {
            // Team�֑J��
            GetSceneServer().GoToScene("InGame");
            _alpha = 255;
        }
    }
    ///
    /// �`��
    ///
    void ScenePrologue::Render() {
        DrawGraph(0, 0, _epilogueBgHandle, FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        //  DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        //  DrawGraph(0, 0, _gameTeamHandle, TRUE);
    }
}