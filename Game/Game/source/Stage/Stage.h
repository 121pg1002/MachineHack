///
/// @file    Stage.h
/// @brief   ステージ
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "../Actor/Actor.h"
#include <memory>

class ModelComponent;
namespace Stage {
  class Stage : public Actor {
  public:
    Stage(Game& game);
    virtual void Update() override;
    void Draw() override;
    TypeId GetTypeId() const override { return TypeId::Stage; };
  private:
    std::unique_ptr<ModelComponent> _skySphere;
    std::unique_ptr<ModelComponent> _ground;
  };
}
