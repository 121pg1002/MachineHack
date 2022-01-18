/*****************************************************************//**
 * @file   ModelAnimComponent.h
 * @brief  �A�j���[�V�������f���p�̃R���|�[�l���g
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include "ModelComponent.h"
#include <string_view>
#include <unordered_map> 
#include "AppFrame.h"
namespace Math = AppFrame::Math;


namespace MachineHuck::Model {
	///
/// @class   ModelAnimComponent
/// @brief   �A�j���[�V�������f���p�̃R���|�[�l���g�N���X�̐錾
///
	class ModelAnimeComponent : public ModelComponent {
	public:
		///
		/// �R���X�g���N�^.
		///
		ModelAnimeComponent(Actor::Actor& owner);
		/// �f�X�g���N�^
		virtual ~ModelAnimeComponent() override;

		/// ������
		void Init() override;

		/// �A�j���[�V�����̓o�^
		/// @param[in] key �C�ӂ̕�����L�[
		/// @param[in] animIndex �֘A�t����A�j���C���f�b�N�X
		void Register(std::string_view key, int animIndex);

		/// �X�V
		void Update() override;

		/// �`��
		void Draw() override;

		/// �`���^����p
		void Draw(const Actor::Actor& owner, bool isHit, double range, bool select);

		//AABB�p
		void Draw(const Actor::Actor& owner, Math::Vector4 position);

		///
		/// �A�j���[�V�����̕ύX.
		/// @param[in] newAnimIndex �A�j���C���f�b�N�X
		///
		void ChangeAnime(std::string_view key, bool repeate = false);

		/// �A�j���[�V�������J��Ԃ����񐔂̎擾
		/// @return �J��Ԃ�����
		///
		int GetRepeatedCount() const { return _repeatedCount; }
		///
		/// �A�j���[�V�����̑����Ԃ��擾.
		/// @return ������
		///
		float GetPlayTime() const { return _playTime; }
		/// �A�j���[�V�����̑����Ԃ��擾
		/// @return ������
		float GetPlayProgress() const { return _playTime / _totalTime; }

		/// �Đ����Ԃ̊|���ݒ�
		/// @param[in] timeRate �Đ����Ԃ̊|��
		void SetTimeRate(float timeRate) { _timeRate = timeRate; }
		float GetTimeRate() { return _timeRate; }


	private:
		std::unordered_map<std::string, int> _registry;
		int _animIndex{ -1 };
		int _attachIndex{ -1 };
		float _playTime{ 0 };
		float _totalTime{ 0 };
		float _timeRate{ 1.f };
		int _repeatedCount{ 0 };
		bool _repeate{ false };
	};
}


