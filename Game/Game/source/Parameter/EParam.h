
/*****************************************************************//**
 * @file   EParam.h
 * @brief  敵のパラメーター情報のクラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include <string>
namespace MachineHuck::Parameter{
	class EParam {
	public:

		/**
		 * @brief  敵の種類を保存
		 * @param  type
		 */
		 /*void SetType(std::string& type) { _type = type; }*/

		 /**
		  * @brief  敵のレベルを保存
		  * @param  level
		  */
		  /*void SetLevel(int level) { _level = level; }*/

		  /**
		   * @brief  敵のエナジー量を保存
		   * @param  energy
		   */
		void SetEnergy(double energy) { _energy = energy; }

		/**
		 * @brief  索敵範囲を保存
		 * @param  searchRange
		 */
		void SetSearchRange(double searchRange) { _searchRange = searchRange; }

		/**
		 * @brief  半径を保存
		 * @param  r
		 */
		void SetR(double r) { _r = r; }

		/**
		 * @brief  速さを保存
		 * @param  speed
		 */
		void SetSpeed(double speed) { _speed = speed; }

	private:

		//std::string _type{ "" };    //!< 種類
		//int    _level{0};              //!< レベル
		double _energy{ 0.0 };      //!< エナジー量
		double _searchRange{ 0.0 }; //!< 索敵範囲の角度
		double _r{ 0.0 };           //!< 索敵半径
		double _speed{ 0.0 };       //!< 速さ

	};
}

