///
/// @file    SceneItem.cpp
/// @brief   �A�C�e�����
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "SceneItem.h"


namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    SceneItem::SceneItem(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// ������
    void SceneItem::Init() {
        // �g�p����摜�̃e�[�u��
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"ItemBg",          {"Texture/texture_00006.png",          1, 1, 1920, 1080}},
          /*    {"GameTitleAMG",        {"GameTitle.png",        1, 1, 1553, 224}},
              {"LeftClickToStartAMG", {"LeftClickToStart.png", 1, 1, 1135, 107}},*/
        };
        // �A�Z�b�g�T�[�o�[�̎擾
        auto& as = GetAssetServer();
        // �摜�̓ǂݍ���
        as.LoadTextures(textureToUsed);

        // �摜�̃n���h���擾
        ItemHandle = as.GetTexture("ItemBg");
        /*  _gameTitleHandle = as.GetTexture("GameTitle");
          _leftClickToStart = as.GetTexture("LeftClickToStart");*/

        AppFrame::Asset::AssetServer::SoundMap soundToUsed{
            {"close"  ,{"se/se_close.wav" ,false}}
        };
        GetAssetServer().LoadSounds(soundToUsed);


        // �T�E���h�R���|�[�l���g�̎擾
        auto& sc = GetSoundComponent();
        sc.PlayLoop("bgm1");
        sc.SetVolume("bgm1", 50);
    }
    ///
    /// ����
    /// 
    void SceneItem::Enter() {
        _alpha = 0;
    }
    ///
    /// ����
    ///
    void SceneItem::Input(AppFrame::Input::InputComponent& input) {
        //if (input.GetMouse().LeftClick()) {
        //    // ���N���b�N��InGame�֑J��
        //    GetSceneServer().GoToScene("Team");
        //    _alpha = 255;
        //}

        if (input.GetJoypad().Button_Y()) {

            //*se �A�C�e����ʂ����
            GetSoundComponent().Play("close");

            //GetSceneServer().PopBack();
            //GetSceneServer().PushBack("InGame",1);
            GetSceneServer().GoToScene("InGame", false);
            //GetSceneServer().PopBack();
            _alpha = 255;
        }
    }
    /// �X�V
    void SceneItem::Update() {
        _alpha = (_alpha + 8) % 255;
    }
    ///
    /// �`��
    ///
    void SceneItem::Render() {
        DrawGraph(0, 0, ItemHandle, false);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        // DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // DrawGraph(0, 0, _gameAMGHandle, true);
    }
}
