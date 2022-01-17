#pragma once
#include "EffectBase.h"

namespace MachineHuck::Effect {
	class EffectWind : public EffectBase {
	public:
		//�����i������j3D���̍��W�A2D���̍��W�A�A�j���[�V��������p����
		EffectWind(VECTOR p, int x, int y, int t) :EffectBase(p, t, x, y) {

		}

		//�����i������j�C�ӂ̃L�[�̖��O�A���[�h����.efkefc�g���q�t�@�C���ւ̃p�X�A�g�嗦
		void LoadEffect(std::string _keyname, std::string _filepass, float expansion);

		void Update() override;
		void Render() override;



	private:
		std::vector<std::string> keyname;
	};
}