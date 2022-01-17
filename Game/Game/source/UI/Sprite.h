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
namespace AppFrame::Scene {
    class Scene;
}
namespace MachineHuck::UI {

    class Sprite {
    public:
        Sprite(AppFrame::Scene::Scene& owner, int order = 0);
        virtual void Update(float deltaTime);
        virtual void Draw();
        void drawHandle(std::string_view key, int no = 0);
        int drawHandle() { return _drawHandle; }
        int width() { return _width; }
        int height() { return _height; }
        int order() { return _order; }
        bool isDead() { return !_active; };
        void Die() { _active = false; }
        //protected:
        AppFrame::Scene::Scene& _owner;
        bool _active{ true };
        int _drawHandle{ -1 };
        VECTOR _position{ 0,0,0 };
        VECTOR _scale{ 1.f,1.f,1.f };
        float _angle{ 0 };
        int _width{ 0 }, _height{ 0 };
        bool _transFlag{ true }, _turnFlag{ false };
        int _order;
    };

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


    class SpriteServer
    {
    public:
        void Add(std::unique_ptr<Sprite> sprite);
        void Update(float deltaTime);
        void Render();
        void Remove(Sprite& sprite);
        void Clear();
    private:
        bool _updating{ false };
        std::vector<std::unique_ptr<Sprite>> _sprites;
    };

}