/*****************************************************************//**
 * @file   SceneAMG.cpp
 * @brief  AMG���S���
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "AppFrame.h"
#include "SceneAMG.h"
#include <DxLib.h>

namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    SceneAMG::SceneAMG(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// ������
    void SceneAMG::Init() {
        // �g�p����摜�̃e�[�u��
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"AMGBg",          {"title/AMG.png",          1, 1, 1920, 1080}},
          /*    {"GameTitleAMG",        {"GameTitle.png",        1, 1, 1553, 224}},
              {"LeftClickToStartAMG", {"LeftClickToStart.png", 1, 1, 1135, 107}},*/
        };
        // �A�Z�b�g�T�[�o�[�̎擾
        auto& as = GetAssetServer();
        // �摜�̓ǂݍ���
        as.LoadTextures(textureToUsed);

        // �摜�̃n���h���擾
        _amgBgHandle = as.GetTexture("AMGBg");
        /*  _gameTitleHandle = as.GetTexture("GameTitle");
          _leftClickToStart = as.GetTexture("LeftClickToStart");*/

          // �T�E���h�R���|�[�l���g�̎擾
        auto& sc = GetSoundComponent();
        sc.PlayLoop("bgm1");
        sc.SetVolume("bgm1", 100);
    }
    ///
    /// ����
    /// 
    void SceneAMG::Enter() {
        _alpha = 0;
    }
    ///
    /// ����
    ///
    void SceneAMG::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // ���N���b�N��InGame�֑J��
            GetSceneServer().GoToScene("Team");
            _alpha = 255;
        }
    }
    /// �X�V
    void SceneAMG::Update() {
        _alpha = (_alpha + 8) % 255;
        if (_alpha > 200) {
            // Team�֑J��
            GetSceneServer().GoToScene("Team");
            _alpha = 255;
            StopMusic();
        }
    }
    ///
    /// �`��
    ///
    void SceneAMG::Render() {
        DrawGraph(0, 0, _amgBgHandle, false);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        // DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // DrawGraph(0, 0, _gameAMGHandle, true);
    }
}
