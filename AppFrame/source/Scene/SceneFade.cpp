/*****************************************************************//**
 * @file  SceneFade.cpp
 * @brief シーンのフェードクラス 画面の最前面にフルスクリーンサイズの画像を重ねてアルファ値によるフェードを行う
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
              GetSceneServer().PopBack(); // FadeIn自身をポップバック
              GetSceneServer().PopFront(); // FadeInの下をポップバック
              MachineHuck::Flag::FlagData::SetFadeInFlag(false);
            }
            else {
              GetSceneServer().PopBack(); // FadeIn自身をポップバック
            }
            //GetSceneServer().PopBack(); // FadeIn自身をポップバック
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
            GetSceneServer().PopBack(); // FadeOut自身をポップバック

            //ワープ処理用
            if (MachineHuck::Flag::FlagData::GetFadeOutFlag()) {

                //InGameのExitを通らないように
                GetSceneServer().PopBack(false); // FadeOut下のシーンも一緒にポップバック
                MachineHuck::Flag::FlagData::SetFadeOutFlag(false);
                MachineHuck::Flag::FlagData::SetBlackOutFlag(true);
            } //マップ画面やアイテム画面用のフェード処理
            else if (MachineHuck::Flag::FlagData::GetNoExitFlag()) {
                MachineHuck::Flag::FlagData::SetNoExitFlag(false);
                GetSceneServer().PopBack(false);
            }
            else {
                GetSceneServer().PopBack(); // FadeOut下のシーンも一緒にポップバック
            }
        }
    }
}

