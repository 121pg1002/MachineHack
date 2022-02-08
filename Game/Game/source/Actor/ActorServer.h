/*****************************************************************//**
 * @file   ActorServer.h
 * @brief  �A�N�^�[�T�[�o�[
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include "AppFrame.h"
#include "Actor.h"

class Actor;
namespace Input {
	class InputComponent;
}

namespace Math = AppFrame::Math;
using _pos_dir = std::pair<Math::Vector4, Math::Vector4>;


namespace MachineHuck::Actor {
	/// @class ActorServer
/// @brief �A�N�^�[���ꌳ�Ǘ�����
	class ActorServer {
	public:
		/// �A�N�^�[�̒ǉ�
		/// @param actor 
		void Add(std::unique_ptr<Actor> actor);
		/**
		 * @brief �A�N�^�[�̍폜
		 * @param actor
		 */
		void Del(std::unique_ptr<Actor> actor);

		/// 
		/// 		/// ����
		/// @param[in] input �C���v�b�g�R���|�[�l���g
		void Input(AppFrame::Input::InputComponent& input);
		/// �X�V
		void Update();
		/// �`��
		void Render();
		/// �S�A�N�^�[�̍폜
		void Clear();
		/// �A�N�^�[�̓o�^
		/// �o�^����ƃA�N�^�[������𓾂邱�Ƃ��ł���
		/// @param[in] key �C�ӂ̕�����L�[
		/// @param[in] pos �o�^����ʒu
		void Register(std::string_view key, _pos_dir vec);
		/// �A�N�^�[�̈ꗗ�̎擾
		/// @return �A�N�^�[�̈ꗗ�ւ̎Q��
		std::vector<std::unique_ptr<Actor>>& GetActors() { return _actors; };


		/// �o�^�����A�N�^�[�̈ʒu�𓾂�
		/// @param[in] key �o�^�ς݂̃L�[
		/// @return �o�^�����A�N�^�[�̈ʒu
		Math::Vector4 GetPosition(std::string_view key);
		/// �o�^�����A�N�^�[�̑O�i�����𓾂�
		/// @param[in] key �o�^�ς݂̃L�[
		/// @return �o�^�����A�N�^�[�̑O�i�����P�ʃx�N�g��
		//Math::Vector4 GetForward(std::string_view key);

		Math::Vector4 GetDir(std::string_view key);


		int GetGimmickCollision(const int handle)   { return _gimmicksCollision[handle]; }

		void SetGimmickCollision(const std::unordered_map<int, int> gimmicks) { _gimmicksCollision = gimmicks; }
		//Math::Vector4 GetMove(std::string_view key);

	private:
		bool 	_updating{ false };
		std::vector<std::unique_ptr<Actor>> _actors;
		std::vector<std::unique_ptr<Actor>> _pendingActors;
		std::unordered_map<std::string, _pos_dir> _registry;
		std::unordered_map<int, int> _gimmicksCollision;

	};
}

