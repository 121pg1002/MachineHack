/*****************************************************************//**
 * @file   GStageParam.h
 * @brief  �M�~�b�N�̔z�u���N���X
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
		 * @brief   �o�^�����ԍ����擾
		 * @return 
		 */
		int GetNum() { return _num; }

		/**
		 * @brief  �o�^�����ԍ���ݒ�         
		 * @param  num
		 */
		void SetNum(int num) { _num = num; }

	private:
		int _num{-1};
		/*const GStageParam operator ==(const GStageParam& rhs) const;*/

	};

}

