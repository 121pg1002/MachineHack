/*****************************************************************//**
 * @file   JsonSave.h
 * @brief  json�ɏ����o�����s���N���X
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
		 * @brief �G�l�~�[�p�����[�^�[�̏����o���N���X
		 * @param  ep
		 * @return ����
		 */
		bool SaveParam(const MachineHuck::Parameter::EParam ep);


		//bool SaveParam(SParam sp);
		//bool SaveParam(GParam gp);

		/**
		 * @brief�@�i�s���̏����o���N���X
		 * @param  pp
		 * @return ����
		 */
		bool SaveParam(const ProgressParam pp);

	private:

	};

}


