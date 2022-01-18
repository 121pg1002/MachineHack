/*****************************************************************//**
 * @file  SpriteServer.cpp
 * @brief  スプライトサーバー
 *
 * @author yamawaki kota
 * @date   January 18 2022
 *********************************************************************/
#include "Sprite.h"
#include "AnimeSprite.h"
#include <array>
#include "AppFrame.h"
#include <DxLib.h>
namespace MachineHuck::UI {
    AnimeSprite::AnimeSprite(AppFrame::Scene::Scene& owner, int order)
        :Sprite{ owner, order }
        , _animeNo{ 0 }
        , _animeMax{ 0 }
        , _animeFPS{ 60 }
    {
    }
    void AnimeSprite::allHandles(std::string_view key) {
        // アセットサーバーからハンドルを取得する
        auto asset = _owner.GetGame().GetAssetServer();
        asset.GetTextures(key, _allHandles);
        _animeMax = static_cast<int>(_allHandles.size());
        _drawHandle = _allHandles[0];
        GetGraphSize(_drawHandle, &_width, &_height);
    }
    void AnimeSprite::Update(float deltaTime) {

        _animeNo += _animeFPS * deltaTime;

        while (_animeNo >= _animeMax) {
            _animeNo -= _animeMax;
        }
        _drawHandle = _allHandles[static_cast<int>(_animeNo)];
    }
}