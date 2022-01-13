/*****************************************************************//**
 * @file   GParam.h
 * @brief  ギミックの情報クラス
 * 
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#pragma once
#include <string>
namespace MachineHuck::Parameter {
	class GParam {
	public:

		/**
		 * @brief  ギミックの種類を保存
		 * @param  type
		 */
		void SetType(std::string type) { _type = type; }

		/**
		 * @brief  ハンドル名を保存
		 * @param  handleName
		 */
		void SetHandleName(std::string handleName) { _handleName = handleName; }

		/**
		 * @brief  メッシュの情報を保存
		 */
		void SetCollisionFrame(int handle);

	private:

		std::string _type;
		std::string _handleName;
		int _collisionFrame;

	};
}

