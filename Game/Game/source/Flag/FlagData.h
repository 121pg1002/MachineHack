
/*****************************************************************//**
 * @file   FlagData.h
 * @brief  フラグデータ管理クラス
 *  
 * @author hikaru Goto
 * @date   January 28 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
namespace MachineHuck::Flag {

	class FlagData {

	public:


		static bool GetFadeInFlag() { return _fadeInFlag; }

		static bool GetFadeOutFlag() { return _fadeOutFlag; }

		static void SetFadeInFlag(bool flag) { _fadeInFlag = flag; }

		static void SetFadeOutFlag(bool flag) { _fadeOutFlag = flag; }

		/**
		 * @brief  ブラックアウトのフラグを取得
		 * @return _blackOutFlag
		 */
		static bool GetBlackOutFlag() { return _blackOutFlag; }

		/**
		 * @brief ブラックアウトのフラグを設定
		 * @param flag
		 */
		static void SetBlackOutFlag(bool flag) { _blackOutFlag = flag; }

		/**
		 * @brief  プレイヤーの無敵フラグを取得
		 * @return _noDamageTime
		 */
		static bool GetNoDamageFlag() { return _noDamageFlag; }

		/**
		 * @brief プレイヤーの無敵フラグを設定
		 * @param time
		 */
		static void SetNoDamageFlag(bool flag) { _noDamageFlag = flag; }

		/**
		 *
		 * @brief  プレイヤーのダメージフラグを取得       
		 * @return _damageFlag
		 */
		static int GetDamageFlag() { return _damageFlag; }

		/**
		 * 
		 * @brief  プレイヤーのダメージフラグを設定       
		 * @param  flag
		 */
		static void SetDamageFlag(bool flag) { _damageFlag = flag; }


		/**
		 * @brief  ハッキング状態の無敵フラグを取得
		 * @return _huckNoDamageTime
		 */
		static bool GetHuckNoDamageFlag() { return _huckNoDamageFlag; }

		/**
		 * @brief ハッキング状態の無敵フラグを設定
		 * @param flag
		 */
		static void SetHuckNoDamageFlag(bool flag) { _huckNoDamageFlag = flag; }

		/**
		 *
		 * @brief  ハッキング状態のダメージフラグを取得       
		 * @return _huckDamageFlag
		 */
		static int GetHuckDamageFlag() { return _huckDamageFlag; }

		/**
		 * 
		 * @brief  ハッキング状態のダメージフラグを設定       
		 * @param  flag
		 */
		static void SetHuckDamageFlag(bool flag) { _huckDamageFlag = flag; }





		/**
		 * @brief  カメラ位置を取得
		 * @return _cameraPos
		 */
		static VECTOR GetCameraPos() { return _cameraPos; }

		/**
		 * @brief カメラ位置を設定
		 * @param pos　カメラ位置
		 */
		static void SetCameraPos(VECTOR pos) { _cameraPos = pos; }

	private:

		static bool _fadeOutFlag;
		static bool _fadeInFlag;
		static bool _blackOutFlag;
		static VECTOR _cameraPos;
		static bool _noDamageFlag;
		static bool _damageFlag;
		static bool _huckNoDamageFlag;
		static bool _huckDamageFlag;


	};

}


