/*****************************************************************//**
 * @file   JsonSave.h
 * @brief  jsonに書き出しを行うクラス
 * 
 * @author hikaru Goto
 * @date   December 26 2021
 *********************************************************************/
#pragma once
#include "../Enemy/EnemyParameter.h"
//#include "../Stage/Stage.h"
#include <unordered_map>
#include <string>


namespace JsonSave {
	using ProgressParam = std::unordered_map<std::string, int>;


	class JsonSave {

	public:

		JsonSave(ProgressParam pp);
		~JsonSave() = default;
		/**
		 * @brief エネミーパラメーターの書き出しクラス
		 * @param  ep
		 * @return 合否
		 */
		bool SaveParam(const MachineHuck::Parameter::EParam ep);


		//bool SaveParam(SParam sp);
		//bool SaveParam(GParam gp);

		/**
		 * @brief　進行情報の書き出しクラス
		 * @param  pp
		 * @return 合否
		 */
		bool SaveParam(const ProgressParam pp);

	private:

	};

}


