/*****************************************************************//**
 * @file   EffectLaser.h
 * @brief  レーザーエフェクトクラス
 *
 * @author yamawaki kota
 * @date   December 28 2021
 *********************************************************************/
#pragma once
#include "EffectBase.h"
namespace MachineHuck::Effect {
	class EffectLaser : public EffectBase {
	public:
		EffectLaser(VECTOR p, int x, int y, int t) :EffectBase(p, t, x, y) {}
		void LoadEffect(std::string _keyname, std::string _filepass, float expansion);

		void Update() override;
		void Render() override;


	private:
		std::vector<std::string> keyname;
	};
}