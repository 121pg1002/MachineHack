#include "Item.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Actor/ActorServer.h"
#include "../State/StateComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugePlayer.h"


namespace MachineHuck::Item {
	Item::Item(AppFrame::Game& game) : Actor{ game } {

		_r = 1.0;
		_isHit = false;
		_status = STATUS::TANK;
	}


	void Item::Update() {

		_oldPos = _position;


		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
			if ((*i)->GetTypeId() == TypeId::Player) {
				if (_collision->CircleToCircle(*this, **i)) {
					//*se ƒAƒCƒeƒ€“üŽè
					GetGame().GetSoundComponent().Play("getitem");

					if (GetStatus()==STATUS::TANK)
					{
						(*i)->GetGaugePlayer().PlusGauge(1000);
						(*i)->GetGaugeBase().PlusGauge(1000);
						(*i)->GetGaugePlayer().SetGaugeMax((*i)->GetGaugePlayer().GetGaugeMax() + 10);
						(*i)->GetGaugeBase().SetGaugeMax((*i)->GetGaugePlayer().GetGaugeMax() + 10);
						 _actorState= Actor::ActorState::Dead;
						

					  itemflg = true;

					}
					
				}
				else
				{
					itemflg = false;
				}
				break;
			}
		}
		
		
		/*float movex = _oldPos.GetX() + 1.0f;
		AppFrame::Math::Vector4 vec4{ movex,_position.GetY(),_position.GetZ(),_position.GetW() };
		_position.Set(vec4);*/

		ComputeWorldTransform();

		_model->Update();
		
		

	}

	void Item::Draw() {
		_model->Draw();
		//_state->Draw();

		if (itemflg) {
			DrawString(100, 900, "“–‚½‚Á‚½", GetColor(255, 255, 255));
		}
		else {
			DrawString(100, 900, "“–‚½‚Á‚Ä‚È‚¢", GetColor(255, 255, 255));
		}

		
	}

	void Item::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(static_cast<float>(_rotation.GetZ())));
		world = MMult(world, MGetRotX(static_cast<float>(_rotation.GetX())));
		world = MMult(world, MGetRotY(static_cast<float>(_rotation.GetY()) + DX_PI_F));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));

	}
}