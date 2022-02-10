/*****************************************************************//**
 * @file   GStageParam.h
 * @brief  ギミックの配置情報クラス
 *
 * @author hikaru Goto
 * @date   December 30 2021
 *********************************************************************/
#include "StageParameterBase.h"

namespace MachineHuck::Parameter {

	class GStageParam : public StageParameterBase {
	
	public:
		GStageParam();

		/**
		 * @brief   登録した番号を取得
		 * @return 
		 */
		int GetNum() { return _num; }

		/**
		 * @brief  登録した番号を設定         
		 * @param  num
		 */
		void SetNum(int num) { _num = num; }

	private:
		int _num{-1};
		/*const GStageParam operator ==(const GStageParam& rhs) const;*/

	};

}

