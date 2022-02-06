/*****************************************************************//**
 * @file  SoundComponent.cpp
 * @brief �����̓R���|�[�l���g
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/
#include "../Asset/AssetServer.h"
#include "SoundComponent.h"
#include "../Game.h"
#include <DxLib.h>

namespace AppFrame::Sound {

    SoundComponent::~SoundComponent() {
    }

    void SoundComponent::Play(std::string_view key) {
        Play(key, DX_PLAYTYPE_BACK);
    }
    void SoundComponent::PlayLoop(std::string_view key) {
        Play(key, DX_PLAYTYPE_LOOP);
    }

    void SoundComponent::SetVolume(std::string_view key, int volume) {
        //auto asset = _game.GetAssetServer();
        auto&& [filename, handle] = _game.GetAssetServer().GetSoundInfo(key);

        if (handle != -1) {
            // �ǂݍ��ݗL��
            ChangeVolumeSoundMem(volume, handle);
        }
        else {
            // �ǂݍ��ݖ���
            SetVolumeMusic(volume);
        }
    }

    void SoundComponent::Play(std::string_view key, int playType) {
        if (_isMute) {
            return;
        }


       // auto asset = _game.GetAssetServer();
        auto&& [filename, handle] = _game.GetAssetServer().GetSoundInfo(key);

        if (handle != -1) {
            // �ǂݍ��ݗL��
            PlaySoundMem(handle, playType, TRUE);
        }
        else {
            // �ǂݍ��ݖ���
            PlayMusic(filename.c_str(), playType);
        }

    }

    int SoundComponent::CheckSoundPlaying() { return CheckSoundFile(); }
}

