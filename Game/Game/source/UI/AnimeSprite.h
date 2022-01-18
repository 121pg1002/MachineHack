/*****************************************************************//**
 * @file  AnimeSprite.h
 * @brief  �A�j���X�v���C�g�N���X
 *
 * @author yamawaki kota
 * @date   January 18 2022
 *********************************************************************/
#pragma once
//!
//! @file Sprite.cpp
//!
//! @brief �X�v���C�g�N���X
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
        float _animeNo;   // �A�j���ԍ�
        int _animeMax;    // �A�j���ő吔
        float _animeFPS;  // �A�j����FPS
    };
}