/*****************************************************************//**
 * @file  SpriteServer.h
 * @brief  スプライトサーバー
 *
 * @author yamawaki kota
 * @date   January 18 2022
 *********************************************************************/
#include <vector>
#include <memory>
#include <string>
#include <DxLib.h>
#include "Sprite.h"
#pragma once
namespace AppFrame::Scene {
    class Scene;
}
namespace MachineHuck::UI {

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