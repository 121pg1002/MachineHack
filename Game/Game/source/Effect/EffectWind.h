#pragma once
#include "EffectBase.h"

namespace MachineHuck::Effect {
	class EffectWind : public EffectBase {
	public:
		//引数（左から）3D時の座標、2D時の座標、アニメーション制御用時間
		EffectWind(VECTOR p, int x, int y, int t) :EffectBase(p, t, x, y) {

		}

		//引数（左から）任意のキーの名前、ロードする.efkefc拡張子ファイルへのパス、拡大率
		void LoadEffect(std::string _keyname, std::string _filepass, float expansion);

		void Update() override;
		void Render() override;



	private:
		std::vector<std::string> keyname;
	};
}