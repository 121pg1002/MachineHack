/*****************************************************************//**
 * @file   GStageParam.h
 * @brief  ƒMƒ~ƒbƒN‚Ì”z’uî•ñƒNƒ‰ƒX
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
		 * @brief   “o˜^‚µ‚½”Ô†‚ğæ“¾
		 * @return 
		 */
		int GetNum() { return _num; }

		/**
		 * @brief  “o˜^‚µ‚½”Ô†‚ğİ’è         
		 * @param  num
		 */
		void SetNum(int num) { _num = num; }

	private:
		int _num{-1};
		/*const GStageParam operator ==(const GStageParam& rhs) const;*/

	};

}

