/*****************************************************************//**
 * @file  SpriteServer.cpp
 * @brief  スプライトサーバー
 *
 * @author yamawaki kota
 * @date   January 18 2022
 *********************************************************************/
#include "SpriteServer.h"
#include "Sprite.h"
#include "AnimeSprite.h"
#include <array>
#include "AppFrame.h"
#include <DxLib.h>
namespace MachineHuck::UI {
    void SpriteServer::Add(std::unique_ptr<Sprite> sprite) {
        if (_updating) {
            return;
        }
        auto order = sprite->order();
        auto ret = std::find_if(_sprites.begin(), _sprites.end(),
            [order](auto&& spt) { return spt->order() > order; });

        if (ret == _sprites.end()) {
            _sprites.emplace_back(std::move(sprite));
        }
        else {
            _sprites.insert(ret, std::move(sprite));
        }
    }

    void SpriteServer::Update(float deltaTime) {
        _updating = true;
        for (auto&& sprite : _sprites) {
            sprite->Update(deltaTime);
        }
        _updating = false;
        // 死んだスプライトを削除する
        _sprites.erase(
            std::remove_if(_sprites.begin(), _sprites.end(),
                [](auto&& spr) {return spr->isDead(); }),
            _sprites.end());
    }

    void SpriteServer::Render() {
        for (auto&& sprite : _sprites) {
            sprite->Draw();
        }
    }
    void SpriteServer::Remove(Sprite& sprite) {
        sprite.Die();
        // 死んだスプライトを削除する
        _sprites.erase(
            std::remove_if(_sprites.begin(), _sprites.end(),
                [](auto&& spt) {return spt->isDead(); }),
            _sprites.end());
    }

    void SpriteServer::Clear() {
        _sprites.clear();
    }
}