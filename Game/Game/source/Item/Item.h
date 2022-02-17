/*****************************************************************//**
 * @file   Item.h
 * @brief  アイテムクラス
 *
 * @author kyoga Tagawa
 * @date   2022/02/01
 *********************************************************************/
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
		void	Init();
		virtual	void	Update() override;
		virtual	void	Draw() override;

		//ワールド行列の計算
		//void ComputeWorldTransform() override;

		virtual TypeId GetTypeId()const override { return TypeId::Item; };
	   /**
	    * @brief エネルギーサックの取得フラグをセット(TRUE:取得している、FLASE：取得していない）
	    * @param flg
	    */
		void SetSuckFlg(bool flg) { _suckFig = flg; }

		/**
		* @briefエネルギーサックの取得フラグを取得
		*/
		bool  GetSuckFlg() { return _suckFig; }



	private:
		enum class STATUS
		{
			SUCK,
			TANK,
			KEYITEM,
		};

		

		STATUS _status;
		bool itemflg;
		bool _suckFig;//エネルギーサックを取得したか。

	public:

		STATUS GetStatus() const { return _status; }
		void SetStatus(STATUS status) { _status = status; }

	};
}