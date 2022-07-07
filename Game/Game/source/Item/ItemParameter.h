/*****************************************************************//**
* @file   ItemParameter.h
* @brief  アイテムパラメーターを読み込むクラス
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
	 * @class ステージ情報クラス
	 * @brief ステージ情報をjsonから読み込むクラス
	 */
	class ItemParameter {

	public:

		using IMV = std::vector<Parameter::IStageParam>;
		using StageV = std::vector<int>;

		/**
		 * @brief 変数の初期化
		 */
		ItemParameter();

		/**
		 * @brief 変数の解放
		 */
		~ItemParameter();

		/**
		* @brief  ステージの配置情報をjsonから読み込む
		* @param  num ステージ番号
		* @param  filePath ファイルパス
		*/
		void LoadStageItemParam(const int num, const std::string& filePath);

		/**
		 * @brief　ステージのテーブルをjsonから読み込む
		 * @param filePath
		 */
		void LoadStageTable(const std::string& filePath);

		/**
		 * @brief   コンテナを取得する
		 * @return  _stageParamMap
		 */
		 //StageMap GetStageMap() { return _stageParamMap; }

		 /**
		  * @brief   ベクター配列を取得する
		  * @return  _stageParamV
		  */
		IMV GetStageVector() { return _iStageParamV; }

		/**
		 * @brief  フロア番号の情報を取得
		 * @return _stageNumMap
		 */
		std::unordered_map<int, IMV> GetFloorItemMap() { return _iStageNumMap; }



	private:


		IMV _iStageParamV; //!< 1フロアのアイテムの配置情報を格納

		std::unordered_map<int, IMV> _iStageNumMap; //!< フロア番号ごとに格納

		

	};
}
