/*****************************************************************//**
 * @file  SceneServer.h
 * @brief �V�[���T�[�o�[
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/

#pragma once
#include <memory>
#include <unordered_map>
#include <string_view>

//class Scene;
namespace AppFrame {

	namespace Input {
		class InputComponent;
	}
	namespace Scene {
		class Scene;
	}
}

namespace AppFrame::Scene {

	/// @class   SceneServer
/// @brief   �V�[���T�[�o�[�N���X�̐錾
///          �V�[���N���X���Ǘ�����
	class SceneServer {
	public:
		SceneServer(std::string_view key, std::shared_ptr<Scene> scene);
		///
		/// �V�[���̓o�^
		/// @param[in] key    Scene�̃C���X�^���X�Ɋ֘A�t����C�ӂ̕�����
		/// @param[in] scene  Scene�̃C���X�^���X
		///
		void Register(std::string_view key, std::shared_ptr<Scene> scene);
		///
		/// �V�[���̃v�b�V���o�b�N
		/// ���X�g�̈�Ԍ��(�őO��)�ɃV�[�����v�b�V���ǉ�����
		/// Scene�̓�������Enter�����s����
		/// @param[in] key  Scene�̃C���X�^���X�Ɋ֘A�t���邽�C�ӂ̕�����
		///
		void PushBack(std::string_view key);
		void PushBack(std::string_view key, bool menuflg);
		///
		/// 
		/// �V�[���̃|�b�v�o�b�N
		/// ���X�g�̈�Ԍ��(���O��)�̃V�[�����|�b�v���O����
		/// Scene�̏o������Exit�����s����
		///
		void PopBack();
		void PopBack(bool menuflg);
		///
		/// �V�[���̑J��
		/// PopBack����PushBack����
		/// @param[in] key  Scene�̃C���X�^���X�Ɋ֘A�t���邽�C�ӂ̕�����
		///
		void GoToScene(std::string_view key);

		void GoToScene(std::string_view key, bool flag);


		/// �V�[���̑J��
		/// PopBack����PushBack����
		/// @param[in] key  Scene�̃C���X�^���X�Ɋ֘A�t���邽�C�ӂ̕�����
		/// @param  sceneNext ���̃V�[��
		/// @param  flag Enter���s�����ǂ���
		///
		void GoToScene(std::string_view key, std::string_view sceneNext, bool flag);
		 
		/**
		 * @brief ���X�g�̈�Ԏ�O�̃V�[�����폜����
		 */
		void PopFront();

		/// ���X�g�̈�Ԍ��(���O��)�̃V�[���̐^���ɑ}������
		/// @param[in] key  Scene�̃C���X�^���X�Ɋ֘A�t���邽�C�ӂ̕�����
		/// Scene�̓�������Enter�����s����
		///
		void InsertBelowBack(std::string_view key);

		/**
		 * @brief  ���X�g�̍Ō㕔�̃V�[���ɑ}������       
		 * @param  key   Seene�̃C���X�^���X�Ɋ֘A�t����C�ӂ̕�����
		 * @param  flag�@Enter��ʂ����ǂ���
		 */
		void InsertBelowBack(std::string_view key, bool flag);

		/// ����
		/// ���X�g�̈�Ԍ��(�őO��)�̃V�[��������������
		/// @param[in] input �C���v�b�g�R���|�[�l���g�̎Q��
		void Input(Input::InputComponent& input);
		///
		/// �X�V
		/// ���X�g�̈�Ԍ��(�őO��)�̃V�[��������������
		///
		void Update();
		///
		/// �`��
		/// ���X�g�̑S�V�[������������
		///
		void Render() const;

	private:
		/// �V�[���̃��W�X�g��
		std::unordered_map<std::string, std::shared_ptr<Scene>>	_registry;
		/// �V�[���̃��X�g
		std::list<std::shared_ptr<Scene>> _scenes;


	};

}

