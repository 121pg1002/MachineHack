/*****************************************************************//**
 * @file  AnimeSprite.h
 * @brief  アニメスプライトクラス
 *
 * @author yamawaki kota
 * @date   January 18 2022
 *********************************************************************/
#pragma once
//!
//! @file Sprite.cpp
//!
//! @brief スプライトクラス
//!
#include <vector>
#include <memory>
#include <string>
#include <DxLib.h>
#include "Sprite.h"
namespace AppFrame::Scene {
    class Scene;
}
namespace MachineHuck::UI {
    class AnimeSprite : public Sprite {
    public:
        AnimeSprite(AppFrame::Scene::Scene& owner, int order);
        void allHandles(std::string_view key);
        void Update(float deltaTime) override;
        void animeFPS(float animeFPS) { _animeFPS = animeFPS; }
        std::vector<int>& allHandles() { return _allHandles; }
    protected:
        std::vector<int> _allHandles;
        float _animeNo;   // アニメ番号
        int _animeMax;    // アニメ最大数
        float _animeFPS;  // アニメのFPS
    };
}