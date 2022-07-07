/*****************************************************************//**
* @file   ItemParameter.h
* @brief  �A�C�e���p�����[�^�[��ǂݍ��ރN���X
*
* @author kyoga Tagawa
* @date  2022/02/01
* ********************************************************************/


#include <string>
#include <unordered_map>
#include "../Parameter/IStageParam.h"


//using Level = std::unordered_map<std::string, StageParam>;
namespace MachineHuck::Item {
	/**
	 * @class �X�e�[�W���N���X
	 * @brief �X�e�[�W����json����ǂݍ��ރN���X
	 */
	class ItemParameter {

	public:

		using IMV = std::vector<Parameter::IStageParam>;
		using StageV = std::vector<int>;

		/**
		 * @brief �ϐ��̏�����
		 */
		ItemParameter();

		/**
		 * @brief �ϐ��̉��
		 */
		~ItemParameter();

		/**
		* @brief  �X�e�[�W�̔z�u����json����ǂݍ���
		* @param  num �X�e�[�W�ԍ�
		* @param  filePath �t�@�C���p�X
		*/
		void LoadStageItemParam(const int num, const std::string& filePath);

		/**
		 * @brief�@�X�e�[�W�̃e�[�u����json����ǂݍ���
		 * @param filePath
		 */
		void LoadStageTable(const std::string& filePath);

		/**
		 * @brief   �R���e�i���擾����
		 * @return  _stageParamMap
		 */
		 //StageMap GetStageMap() { return _stageParamMap; }

		 /**
		  * @brief   �x�N�^�[�z����擾����
		  * @return  _stageParamV
		  */
		IMV GetStageVector() { return _iStageParamV; }

		/**
		 * @brief  �t���A�ԍ��̏����擾
		 * @return _stageNumMap
		 */
		std::unordered_map<int, IMV> GetFloorItemMap() { return _iStageNumMap; }



	private:


		IMV _iStageParamV; //!< 1�t���A�̃A�C�e���̔z�u�����i�[

		std::unordered_map<int, IMV> _iStageNumMap; //!< �t���A�ԍ����ƂɊi�[

		

	};
}
