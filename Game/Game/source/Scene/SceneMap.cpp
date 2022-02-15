///
/// @file    SceneMap.cpp
/// @brief   �}�b�v���
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "SceneMap.h"
#include <algorithm>
#include "../Flag/FlagData.h"

namespace {
    constexpr double FloorSize = 166.0; //!< 1�t���A�̃T�C�Y
    constexpr double LineSize = 1.0;  //!< �`�悷����̃T�C�Y
    constexpr double BoardSize = 5.0; //!< �s�Ɨ�̃T�C�Y
    constexpr double StartX = 1920/2 - FloorSize * BoardSize/2.0;
    constexpr double StartHeight = 100; //!< ��̊J�n�����󂯂镪
    constexpr double StartY = 150.0;
    constexpr int    GoalNum = 21;

}

namespace MachineHuck::Scene {
    /// �R���X�g���N�^
    SceneMap::SceneMap(AppFrame::Game& game):Scene{ game }{
        _colorFrame = 0;
        _mapHandles.clear();
    }
    /// ������
    void  SceneMap::Init() {
        // �g�p����摜�̃e�[�u��
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"MapBg",    {"Texture/cloth_00146.png",          1, 1, 1920, 1080}},
            {"Map0", {"Texture/SceneMap/map0_small.png", 1, 1, 160, 160}},
            {"Map1", {"Texture/SceneMap/map1_small.png", 1, 1, 160, 160}},
            {"Map2", {"Texture/SceneMap/map2_small.png", 1, 1, 160, 160}},
            {"Map3", {"Texture/SceneMap/map3_small.png", 1, 1, 160, 160}},
            {"Map4", {"Texture/SceneMap/map4_small.png", 1, 1, 160, 160}}
          /*    {"GameTitleAMG",        {"GameTitle.png",        1, 1, 1553, 224}},
              {"LeftClickToStartAMG", {"LeftClickToStart.png", 1, 1, 1135, 107}},*/
        };
        // �A�Z�b�g�T�[�o�[�̎擾
        auto& as = GetAssetServer();
        // �摜�̓ǂݍ���
        as.LoadTextures(textureToUsed);

        // �摜�̃n���h���擾
        MapHandle = as.GetTexture("MapBg");

        for (int i = 0; i < 5; i++) {
        
            auto&& handle = as.GetTexture("Map" + std::to_string(i));
            _mapHandles.push_back(handle);
        }
        /*  _gameTitleHandle = as.GetTexture("GameTitle");
          _leftClickToStart = as.GetTexture("LeftClickToStart");*/

          // �T�E���h�R���|�[�l���g�̎擾
        AppFrame::Asset::AssetServer::SoundMap soundToUsed{
            {"close"  ,{"se/se_close.wav" ,false}}
        };

        GetAssetServer().LoadSounds(soundToUsed);

    }
    ///
    /// ����
    /// 
    void  SceneMap::Enter() {
        _alpha = 0;
        _colorFrame = 0;
    }
    ///
    /// ����
    ///
    void  SceneMap::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // ���N���b�N��InGame�֑J��
            GetSceneServer().GoToScene("Team");
            _alpha = 255;
        }

        if (input.GetJoypad().Button_X()) {
            //*se �}�b�v��ʂ����
            GetSoundComponent().Play("close");

            // GetSceneServer().PopBack();
             //GetSceneServer().PushBack("InGame",1);

            GetSceneServer().GoToScene("InGame", false);
            _alpha = 255;
        }

    }
    /// �X�V
    void  SceneMap::Update() {
        _alpha = (_alpha + 8) % 255;
        _colorFrame++;
        _playerV = Flag::FlagData::GetPlayerFloorVec(); //!< �v���C���[�̍s�����t���A�ԍ��z����擾
    }

    ////�t���A�ԍ���o�^����
    //void SceneMap::RegisterFloor() {
    //
    //    //���ꂾ�ƃ}�b�v��ʂ��J���Ă��Ȃ��Ƃ��ɓo�^����Ȃ�
    //    auto&& playerNum = Flag::FlagData::GetPlayerFloorNum();

    //    //�x�N�^�[�̒�����T��
    //    auto it = std::find(_playerV.begin(), _playerV.end(), playerNum);

    //    //���݂��Ȃ��Ȃ��
    //    if (it == _playerV.end()) {
    //        //�ǉ�
    //        _playerV.push_back(playerNum);
    //    }
    //
    //}

    ///
    /// �`��
    ///
    void  SceneMap::Render() {
       // DrawGraph(0, 0, MapHandle, false);


        
        //int StartY = 100.0;
        int offsetX = StartX;
        int offsetY = StartY;
        int red = 255; int green = 0; int blue = 0;
        //y����
        for (int i = 0; i < BoardSize; i++) {
        
            offsetX = StartX;
            //x����
            for (int j = 0; j < BoardSize; j++) {
            
                //unordered_map�Ńt���A�ԍ���
                //�����̊|���Z���t���A�ԍ��ƈ�v�����ꍇ�ɐF�̏����𕪒f����
                auto value = std::find(_playerV.begin(), _playerV.end(), i * BoardSize + j);

                //��l���̂���ԍ��̃t���A�g��΂ɂ���
                if (Flag::FlagData::GetPlayerFloorNum() == i * BoardSize + j && _colorFrame % 60 < 30) {
                    red = 0; green = 255; blue = 0;
                } //�S�[���̐F��ԐF�ɂ���
                else if (GoalNum == i * BoardSize + j) {
                    red = 255; green = 0; blue = 0;
                }
                //���̔ԍ������������Ƃ�����ꍇ(��)
                else if (value != _playerV.end()) {
                    red = 255; green = 255; blue = 255;
                }  //�O���[�ɂ���
                else {
                    red = 125; green = 125; blue = 125;
                }

                //�g�̕`��
                DrawBox(offsetX, FloorSize * BoardSize - offsetY + FloorSize + StartHeight, offsetX + FloorSize, FloorSize * BoardSize - offsetY + StartHeight, GetColor(red, green, blue), false); //!< �O���[



                //if (i == 0 && j == 0) {

                //    for (auto k : _mapHandles) {

                if (i == 0) {

                    //�}�b�v��ʂ̕\��(��)
                    DrawGraph(offsetX + 3, FloorSize * BoardSize - offsetY + StartHeight + 3, _mapHandles[j], false);
                
                }


                //    }
                //
                //}

                //DrawBox(offsetX, offsetY, offsetX + FloorSize, offsetY + FloorSize, GetColor(red, green, blue), false); //!< ��
                //DrawBox(offsetX, offsetY, offsetX + FloorSize, offsetY + FloorSize, GetColor(red, green, blue), false); //!< ��
                //DrawBox(offsetX, offsetY, offsetX + FloorSize, offsetY + FloorSize, GetColor(red, green, blue), false); //!< ��

                offsetX += FloorSize;
            }

            offsetY += FloorSize;
        }

        
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        // DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // DrawGraph(0, 0, _gameAMGHandle, true);
    }
}
