#pragma once
#include "appframe.h"
#include <utility>
#include "EffectServer.h"

namespace MachineHuck::Effect {
	class EffectBase {
	public:
		EffectBase(VECTOR p, int t, int x, int y) :pos(p), time(t) { pos2D = std::make_pair(x, y); }
		virtual ~EffectBase() {}
		void virtual Update() {}
		void virtual Render() {}
		void PassingTime(int passtime) { time += passtime; };
		void SetEffect3DPos(VECTOR p) { pos = p; }
		void SetEffect2DPos(int x, int y) { pos2D.first = x, pos2D.second = y; }
		VECTOR GetPosition() { return pos; }
		std::pair<int, int> GetPosition2D() { return pos2D; }
		int GetTime() { return time; }
	protected:
		//3DEffect�̈ʒu
		VECTOR pos;
		//2DEffect�̈ʒu
		std::pair<int, int> pos2D;
		//�A�j���[�V��������p����
		int time;
	};
}