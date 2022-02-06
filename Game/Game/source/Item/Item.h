#pragma once
#include "../Actor/Actor.h"

namespace MachineHuck::Item {

	class Item :public Actor::Actor {
	public:
		/// コンストラクタ
	   /// @param[in] _game ゲームクラスへの参照
		Item(AppFrame::Game& game);
		/// デストラクタ
		virtual ~Item() override = default;

		virtual	void	Init() override;
		virtual	void	Input(AppFrame::Input::InputComponent& input) override;
		virtual	void	Update() override;
		virtual	void	Draw() override;

		/// ワールド行列の計算
	   /// モデルのローカルZ座標が逆なのでここで180度回転させる
		void ComputeWorldTransform() override;

		virtual TypeId GetTypeId()const override { return TypeId::Item; };

	private:
		enum class STATUS
		{
			SUCK,
			TANK,
			KEYITEM,
		};

		

		STATUS _status;
		bool itemflg;

	public:

		STATUS GetStatus() const { return _status; }
		void SetStatus(STATUS status) { _status = status; }

	};
}