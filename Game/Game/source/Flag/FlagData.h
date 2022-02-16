
/*****************************************************************//**
 * @file   FlagData.h
 * @brief  フラグデータ管理クラス
 *
 * @author hikaru Goto
 * @date   January 28 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <vector>
//#include "AppFrame.h"
namespace MachineHuck::Flag {

	class FlagData {

	public:

		/**
		 * @brief  フェードインフラグを取得     
		 * @return フェードインのフラグ
		 */
		static bool GetFadeInFlag() { return _fadeInFlag; }

		/**
		 * @brief  フェードアウトフラグを取得     
		 * @return フェードアウトのフラグ
		 */
		static bool GetFadeOutFlag() { return _fadeOutFlag; }

		/**
		 * @brief  フェードインフラグを設定     
		 * @return フェードインのフラグ
		 */
		static void SetFadeInFlag(bool flag) { _fadeInFlag = flag; }

		/**
		 * @brief  フェードアウトフラグを設定     
		 * @return フェードアウトのフラグ
		 */
		static void SetFadeOutFlag(bool flag) { _fadeOutFlag = flag; }

		/**
		 *
		 * @brief  シーン遷移における現シーンのExit処理を行わないかどうか
		 * @return _noExitFlag
		 */
		static bool GetNoExitFlag() { return _noExitFlag; }

		/**
		 * @brief  シーン遷移における現シーンのExit処理を行わないかの設定
		 * @param  flag
		 */
		static void SetNoExitFlag(bool flag) { _noExitFlag = flag; }

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
		 * @brief  プレイヤーが死亡したかフラグを取得
		 * @return _playerDead
		 */
		static bool GetPlayerDead() { return _playerDead; }

		/**
		 * @brief  プレイヤーが死亡したフラグを設定
		 * @param  flag
		 */
		static void SetPlayerDead(bool flag) { _playerDead = flag; }

		/**
		 * @brief  ダクトワープの取得     
		 * @return _ductWarp
		 */
		static bool GetDuctWarp() { return _ductWarp; }

		/**
		 * @brief  ダクトワープの設定    
		 * @param  flag
		 */
		static void SetDuctWarp(bool flag) { _ductWarp = flag; }

		/**
		 * @brief  スライドインフラグを取得         
		 * @return _slideInFlag
		 */
		static bool GetSlideIn() { return _slideInFlag; }

		/**
		 * @brief  スライドアウトフラグを取得       
		 * @return _slideOutFlag
		 */
		static bool GetSlideOut() { return _slideOutFlag; }

		/**
		 * @brief  スライドインフラグを設定      
		 * @param  flag
		 */
		static void SetSlideIn(bool flag) { _slideInFlag = flag; }

		/**
		 * @brief  スライドアウトフラグを設定       
		 * @param  flag
		 */
		static void SetSlideOut(bool flag) { _slideOutFlag = flag; }

		/**
		 * @brief  スライドインアウトのフラグを取得       
		 * @return 
		 */
		static bool GetSlideFlag() { return _slideFlag; }

		/**
		 * @brief  スライドインアウトのフラグを設定      
		 * @param  flag
		 */
		static void SetSlideFlag(bool flag) { _slideFlag = flag; }


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

		/**
		 * @brief  ハッキング中の敵の頭の位置を取得
		 * @return _headPos
		 */
		static VECTOR GetHeadPos() { return _headPos; }

		/**
		 * @brief  敵の頭の位置を設定
		 * @param  pos
		 */
		static void SetHeadPos(VECTOR pos) { _headPos = pos; }

		///**
		// * @brief  穴の位置を取得      
		// * @return 穴の座標
		// */
		//static VECTOR GetHolePos() { return _holePos; }

		///**
		// * @brief  落ちる穴の位置を設定       
		// * @param  pos
		// */
		//static void SetHolePos(VECTOR pos) { _holePos = pos; }


		/**
		 * @brief  ワープ後の初期位置の取得      
		 * @return 座標
		 */
		static VECTOR GetWarpAfterPos() { return _warpAfterPos; }

		/**
		 * @brief  ワープ後の初期位置の設定      
		 * @param  pos
		 */
		static void SetWarpAfterPos(VECTOR pos) { _warpAfterPos = pos; }

		/**
		 * @brief  プレイヤーのいるフロア番号を取得
		 * @return プレイヤーのいるフロア番号
		 */
		static int GetPlayerFloorNum() { return _PlayerNowFloorNum; }

		/**
		 * @brief プレイヤーのいるフロア番号を設定
		 * @param num
		 */
		static void SetPlayerFloorNum(int num) { _PlayerNowFloorNum = num; }

		/**
		 * @brief  プレイヤーの行ったことのあるフロア番号配列を設定         
		 * @return プレイヤーが行ったフロア番号配列
		 */
		static std::vector<int> GetPlayerFloorVec() { return _playerFloorV; }


		/**
		 * @brief  プレイヤーの行ったことのあるフロア番号配列を設定       
		 * @param  floorV
		 */
		static void SetPlayerFloorVec(std::vector<int> floorV) { _playerFloorV = floorV; }


		/**
		 *.
		 * 
		 * @brief         
		 * @return 
		 */
		static bool GetEpilogueFlag() { return _epilogueFlag;}

		static void SetEpilogueFlag(bool flag) { _epilogueFlag = flag; }


#ifdef _DEBUG
		/**
		 * @brief  デバッグモードにおける転移するフロア番号を取得         
		 * @return 
		 */
		static int GetDebugNo() { return _debugNo; }


		/**
		 * @brief  デバッグモードにおける転移するフロア番号を設定         
		 * @param  no
		 */
		static void SetDebugNo(int no) { _debugNo = no; }
#endif
		///**
		// * @brief  落ちるフラグを取得       
		// * @return _fallFlag
		// */
		//static bool GetFallFlag() { return _fallFlag; }

		///**
		// * @brief  落ちるフラグを設定      
		// * @param  flag
		// */
		//static void SetFallFlag(bool flag) { _fallFlag = flag; }


	private:

		static bool _fadeOutFlag;
		static bool _fadeInFlag;
		static bool _blackOutFlag;
		static VECTOR _cameraPos;
		static bool _noDamageFlag;
		static bool _damageFlag;
		static bool _huckNoDamageFlag;
		static bool _huckDamageFlag;
		static VECTOR _headPos;
		static bool _noExitFlag;
		static bool _playerDead;
		static bool _ductWarp;
		static bool _slideInFlag;
		static bool _slideOutFlag;
		static bool _slideFlag;
	//	static VECTOR _holePos;      //!< 落ちる穴の位置座標
		static VECTOR _warpAfterPos; //!< ワープ後の初期座標
		static int _PlayerNowFloorNum; //!< プレイヤーの現在いるフロア番号を保存
		static std::vector<int> _playerFloorV; //!< プレイヤーの行ったことのあるフロア番号を登録する
		static bool _epilogueFlag;  //!< エピローグのフラグ

#ifdef _DEBUG
		static int _debugNo; //!< デバッグモード中に転移したい番号
#endif
			//	static bool _fallFlag;                        //!< 落ちるかどうかのフラグ

	};

}


