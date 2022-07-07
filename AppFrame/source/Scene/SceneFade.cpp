/*****************************************************************//**
 * @file  SceneFade.cpp
 * @brief �V�[���̃t�F�[�h�N���X ��ʂ̍őO�ʂɃt���X�N���[���T�C�Y�̉摜���d�˂ăA���t�@�l�ɂ��t�F�[�h���s��
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/

#include "SceneFade.h"
#include <DxLib.h>
#include "SceneServer.h"
#include "../../../Game/Game/source/Flag/FlagData.h"

namespace AppFrame::Scene {
    namespace {
        constexpr float ALPHA_MIN = 0.f;
        constexpr float ALPHA_MAX = 255.f;
        constexpr float FADE_TIME = 60.f;
        constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME);
    }
    ///
    SceneFade::SceneFade(Game& game)
        :Scene{ game }
        , _color{ GetColor(0, 0, 0) }
    {
    }

    SceneFade::~SceneFade() {
    }

    void SceneFade::Init() {
        _color = GetColor(0, 0, 0);
    }

    void SceneFade::Enter() {
    }

    void SceneFade::Update() {
    }

    void SceneFade::Render() {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
        DrawBox(0, 0, _width, _height, _color, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }


    SceneFadeIn::SceneFadeIn(Game& game) : SceneFade{ game } {
    }
    SceneFadeIn::~SceneFadeIn() {
    }

    void SceneFadeIn::Enter() {
        _alpha = ALPHA_MAX;
        _deltaAlpha = -ALPHA_DELTA;
    }
    void SceneFadeIn::Update() {

      //if (!MachineHuck::Flag::FlagData::GetInGameExitFlag()) {
        MachineHuck::Flag::FlagData::SetBlackOutFlag(false);
      //}
        

        _alpha += _deltaAlpha;
        if (_alpha <= ALPHA_MIN) {
            _alpha = ALPHA_MIN;   


            if (MachineHuck::Flag::FlagData::GetFadeInFlag()) {
              GetSceneServer().PopBack(); // FadeIn���g���|�b�v�o�b�N
              GetSceneServer().PopFront(); // FadeIn�̉����|�b�v�o�b�N
              MachineHuck::Flag::FlagData::SetFadeInFlag(false);
            }
            else {
              GetSceneServer().PopBack(); // FadeIn���g���|�b�v�o�b�N
            }
            //GetSceneServer().PopBack(); // FadeIn���g���|�b�v�o�b�N
        }

    }

    SceneFadeOut::SceneFadeOut(Game& game) : SceneFade{ game } {
    }

    SceneFadeOut::~SceneFadeOut() {
    }

    void SceneFadeOut::Enter() {
        _alpha = ALPHA_MIN;
        _deltaAlpha = ALPHA_DELTA;
    }
    void SceneFadeOut::Update() {

        
        _alpha += _deltaAlpha;
        if (_alpha >= ALPHA_MAX) {
            _alpha = ALPHA_MAX;
            GetSceneServer().PopBack(); // FadeOut���g���|�b�v�o�b�N

            //���[�v�����p
            if (MachineHuck::Flag::FlagData::GetFadeOutFlag()) {

                //InGame��Exit��ʂ�Ȃ��悤��
                GetSceneServer().PopBack(false); // FadeOut���̃V�[�����ꏏ�Ƀ|�b�v�o�b�N
                MachineHuck::Flag::FlagData::SetFadeOutFlag(false);
                MachineHuck::Flag::FlagData::SetBlackOutFlag(true);
            } //�}�b�v��ʂ�A�C�e����ʗp�̃t�F�[�h����
            else if (MachineHuck::Flag::FlagData::GetNoExitFlag()) {
                MachineHuck::Flag::FlagData::SetNoExitFlag(false);
                GetSceneServer().PopBack(false);
            }
            else {
                GetSceneServer().PopBack(); // FadeOut���̃V�[�����ꏏ�Ƀ|�b�v�o�b�N
            }
        }
    }
}

