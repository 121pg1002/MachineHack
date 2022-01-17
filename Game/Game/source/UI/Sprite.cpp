#include "Sprite.h"
#include <array>
#include "AppFrame.h"

#include <DxLib.h>
namespace MachineHuck::UI {
    Sprite::Sprite(AppFrame::Scene::Scene& owner, int order)
        :_owner{ owner }
        , _order{ order }
    {
    }
    void Sprite::Update(float deltaTime) {
    }
    void Sprite::Draw() {
        auto x = static_cast<int>(_position.x);
        auto y = static_cast<int>(_position.y);
        DrawRotaGraph3(x, y, _width / 2, _height / 2,
            _scale.x, _scale.y, _angle,
            _drawHandle, _transFlag, _turnFlag);
    }
    void Sprite::drawHandle(std::string_view key, int no) {
        // アセットサーバーからハンドルを取得する
        auto asset = _owner.GetGame().GetAssetServer();
        _drawHandle = asset.GetTexture(key, no);
        GetGraphSize(_drawHandle, &_width, &_height);
    }

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
