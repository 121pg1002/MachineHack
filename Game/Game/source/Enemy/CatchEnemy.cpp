#include "CatchEnemy.h"
#include "AppFrame.h"
#include "../Actor/ActorServer.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugePlayer.h"
#include "../Gauge/GaugeEnemy.h"
#include "../Flag/FlagData.h"
#include "EnemyParameter.h"


namespace MachineHuck::Enemy {

	//�ÓI�ȃ����o�\�ϐ������̉�������
	int CatchEnemy::StateBase::_huckNoDamageTime;

	CatchEnemy::CatchEnemy(AppFrame::Game& game) : EnemyBase{ game } {

		_r = 0.0;
		_huckR = 0.0;
		_catchR = 0.0;
		//_minXZ = { -200.0, -100.0 };
		//_maxXZ = { 200.0, 100.0 };
		//_lmin = { 0.0, -100.0, 0.0 };
		//_lmax = { 0.0, 100.0, 0.0 };
		_status = STATUS::WAIT;
		_searchRange = 0.0;
		_huckingRange = 0.0;
		_catchRange = 0.0;
		//_gaugeBase->Init();
		//_gaugeEnemy->Init(*this);


	}

	void CatchEnemy::LoadJson(const std::string& filePath) {

		auto eParam = std::make_unique<EnemyParameter>();
		eParam->LoadEnemyParam(filePath);

		//2�߂̒l�����x��
		_r = eParam->GetEnemyParam("r", 0);
		_r = 150.0;
		//_huckR = eParam->GetEnemyParam("r", 1);
		_huckR = 200.0;

		_catchR = 300.0;

		_collisionR = 50.0;

		_catchRange = eParam->GetEnemyParam("searchrange", 1);
		_searchRange = eParam->GetEnemyParam("searchrange", 1);
		_huckingRange = eParam->GetEnemyParam("searchrange", 0);////////���Ƃ肠�����A��

	}

	void CatchEnemy::Update() {

		//���S���ł͂Ȃ�
		if (_status != STATUS::DYING) {


			if (GetActorState() == ActorState::Hucking) {
				_status = STATUS::ISHUCKING;
			}
			else if (IsHucked()) {
				_status = STATUS::ISHUCKED;
			}
			else if (GetActorState() == ActorState::Active) {

				if (_status != STATUS::CHASE) {
					_status = STATUS::SEARCH;
				}

				//if (_status != STATUS::WAIT) 
				//{
				   // _status = STATUS::WALK;
				//}
			}
		}

		if (_status != STATUS::DYING && _status != STATUS::CHASE) {
			Move("CatchEnemy", _routine, 2.0, _numRange);
		}

		if (_status == STATUS::ISHUCKED) {
			SetShadowMapflg(TRUE);
		}
		else
		{
			SetShadowMapflg(FALSE);
		}

		_state->Update();

		//// ���[���h�s��̌v�Z
		ComputeWorldTransform();

		// ���f���̍X�V
		_modelAnime->Update();

	}

	void CatchEnemy::HuckedRotation(double lx, double ly) {


		//�������̌X���Əc�����̌X���̑傫��
		double length = sqrt(lx * lx + ly * ly);
		if (length < 0.3) {
			// ���͂������������瓮���Ȃ��������Ƃɂ���
			length = 0.0;
		}
		else {
			length = 5.0;
		}

		//�������Əc�����̊p�x
		double rad = atan2(ly, lx);

		//x�������̈ړ���
		auto dirX = std::cos(rad) * length;

		//z�������̈ړ���
		auto dirZ = std::sin(rad) * length;

		Math::Vector2 direction = { dirX, dirZ };


		if (direction.Length() > 0.0) {

			auto yRot = std::atan2(direction.GetX(), direction.GetZ());

			Math::Vector4 rot = { 0.1, yRot, 0.0 };
			SetRotation(rot);

			//�ړ����Ă����猸�炷
			//GetGaugeBase().Update(*this);
			//GetGaugeEnemy().Update(*this);
			GetGame().GetGaugeBaseUI().Update();
			GetGame().GetGaugeEnemyUI().Update();

		}



	}

	void CatchEnemy::Input(AppFrame::Input::InputComponent& input) {
		_state->Input(input);
	}

	void CatchEnemy::Draw() {
		// ���̃g�Q�ׂ̈̃A���t�@�e�X�g�ݒ�
		MV1SetMaterialDrawAlphaTest(_modelAnime->GetHandle(), 3, TRUE, DX_CMP_LESS, 200);
#ifdef _DEBUG
		//auto pos = _position;
		//pos.y += 40;
		//DrawSphere3D(pos, 50, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		_modelAnime->Draw(*this, _isHit, _searchRange, true);
		_modelAnime->Draw(*this, _isHit, _huckingRange, false);
		_modelAnime->Draw(*this, _catchR, _catchRange);
		_modelAnime->DrawCircle(*this, _collisionR);
		_modelAnime->Draw(*this, GetActorServer().GetPosition("Player"));

		//_gaugeBase->Draw(*this);
#endif
		_state->Draw();

		//_gaugeEnemy->Draw(*this);
	}

	void CatchEnemy::StateBase::Draw() {

		if (_owner.GetStatus() != STATUS::ISHUCKED) {
			_owner.GetModelAnime().Draw();
		}
		else {
			_owner.GetModelAnime().SpecificDraw(); //!<	�n�b�L���O���̓���`���~����
		}
	}

	// �ҋ@
	void CatchEnemy::StateSearch::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	void CatchEnemy::StateSearch::Update() {

		//_owner.LockOn();
		if (_owner._position.GetY() > 0) {
			auto posY = _owner._position.GetY() - 5;
			//Math::Vector4 _pos = { 0.0, _pos_y, 0.0 };
			_owner._position = { _owner.GetPosition().GetX(), posY, _owner.GetPosition().GetZ() };
		}
		else {
			Math::Vector4 pos = { _owner.GetPosition().GetX(), 0.0, _owner.GetPosition().GetZ() };
			_owner._position = pos;
			_owner._state->GoToState("Idle");
		}
	}

	//�ҋ@
	void CatchEnemy::StateIdle::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	void CatchEnemy::StateIdle::Update() {


		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			_owner._state->GoToState("IsHucking");
		}

		for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++)
		{
			//!< �v���C���[�ł͂Ȃ������玟��
			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//�G����`�Ńv���C���[���_
				if (_owner._collision->FanToPoint(_owner, **i, _owner.GetR(), _owner.GetSearchRange())) {
					_owner._state->GoToState("CatchPre");
					_owner._status = STATUS::CHASE;
				}

			}
		}
	}

	//�v���C���[����������̍U���O
	void CatchEnemy::StateCatchPre::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
	}

	//void CatchEnemy::StateCatchPre::Input(AppFrame::Input::InputComponent& input) {
	//
	//	//if(input.)

	//}

	void CatchEnemy::StateCatchPre::Update() {

		//�n�b�L���O����Ă��邩
		if (_owner.IsHucked()) {

			auto rot = _owner.GetRotation();

			//z����0�x�Ƃ���
			auto nine = DX_PI * 90.0 / 180.0;

			//��l���̉�]�����͔��Ό����̂��߃}�C�i�X
			Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };


		}
		else {//�ʏ펞

			//�����̂݃v���C���[�̕��Ɍ���
			auto player = _owner.GetActorServer().GetPosition("Player");
			auto dif = player - _owner.GetPosition();

			auto rotY = std::atan2(dif.GetX(), dif.GetZ());
			Math::Vector4 rot = { 0.5, rotY, 0.0 };
			_owner.SetRotation(rot);

			auto length = dif.Length_XZ();

			//�L���b�`�͈͓̔��v���C���[������Ȃ�U���ҋ@���Ԃ����炷
			if (length < _owner._catchR) {
				_catchPreTime--;
			}
			else {
				_catchPreTime = 20;
			}

			//�U���ҋ@���Ԃ�0�ɂȂ�����
			if (_catchPreTime < 0) {

				_owner._state->GoToState("Catch");

			}



		}



	}


	bool CatchEnemy::StateCatchPre::IsLoseSight() {

		auto player = _owner.GetActorServer().GetPosition("Player");
		auto range = player - _owner.GetPosition();
		auto length = range.Length();

		//player�Ǝ����̈ʒu�̍������G�͈͂��z���Ă�����
		if (length > _owner.GetR()) {
			return true;
		}
		else {
			return false;
		}

	}

	void CatchEnemy::StateCatch::Enter() {


		_catchTime = 60;

		//�n�b�L���O����Ă���ꍇ
		if (_owner.GetStatus() == STATUS::ISHUCKED) {

			//�Q�[�W����
	/*		_owner.GetGaugeBase().DownGauge(20);
			_owner.GetGaugeEnemy().DownGauge(20);*/
			_owner.GetGame().GetGaugeBaseUI().DownGauge(20);
			_owner.GetGame().GetGaugeEnemyUI().DownGauge(20);

			//auto player = _owner.GetActorServer().GetDir("Player");

			//auto rot = _owner.GetRotation();

			////z����0�x�Ƃ���
			//auto nine = DX_PI * 90.0 / 180.0;

			//�d�l�����6m/s
			//auto length = 600.0;

			////��l���̉�]�����͔��Ό����̂��߃}�C�i�X
			//Math::Vector4 move = { std::cos(-rot.GetY() + nine), 0.0, std::sin(-rot.GetY() + nine) };

			////������ݒ�
			//_owner.SetRotation(rot);

			////�ڐ��̐�ɖڕW������
			//auto forward = move * length;


			//_norm = forward.Normalize();



		}
		//else {

		//	//�ǐՒ�
		//	auto player = _owner.GetActorServer().GetPosition("Player");
		//	player = { player.GetX(), 0.0, player.GetZ() };
		//	auto dif = player - _owner.GetPosition();
		//	//auto length = dif.Length_XZ();

		//	auto rotY = std::atan2(dif.GetX(), dif.GetZ());
		//	Math::Vector4 rot = { 0.0, rotY, 0.0 };
		//	_owner.SetRotation(rot);


		//}

		_owner.GetModelAnime().ChangeAnime("Catch", true);
	}

	void CatchEnemy::StateCatch::Update() {

		if (_catchTime < 0) {
			_owner._state->GoToState("CatchAfter");
		}
		else {

			////�n�b�L���O����Ă��邩(�ǐՎ��̍s�����Ȃ�)
			if (_owner.IsHucked()) {

				for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

					//!< �G�ł͂Ȃ������玟��
					if ((*i)->GetTypeId() != TypeId::Enemy) {

						continue;

					}
					else {

						//�n�b�L���O����Ă����玟��	
						if ((*i)->IsHucked()) {
							continue;
						}
						else {

							//����(�n�b�L���O���̃L���b�`)�̐�`�Ƒ���G�l�~�[�̓_
							if (_owner._collision->FanToPoint(_owner, **i, _owner._catchR, _owner._catchRange)) {

								(*i)->SetActorState(ActorState::Dead);

							}

						}

					}
				}


			}//�������ǐՏ�Ԃ̂Ƃ�
			else {

				//���G���Ԓ��ƃ_���[�W�t���O���I���̂Ƃ��́A�ʂ��Ȃ�
				if (Flag::FlagData::GetNoDamageFlag() == false && Flag::FlagData::GetDamageFlag() == false) {

					//�n�b�L���O�̖��G���Ԓ��ƃn�b�L���O�_���[�W�t���O���I���̂Ƃ��͒ʂ��Ȃ�
					if (Flag::FlagData::GetHuckDamageFlag() == false && Flag::FlagData::GetHuckNoDamageFlag() == false) {

						for (auto i = _owner.GetActorServer().GetActors().begin(); i != _owner.GetActorServer().GetActors().end(); i++) {

							if ((*i)->GetTypeId() != TypeId::Enemy) {

								//�v���C���[�ł͂Ȃ������玟��
								if ((*i)->GetTypeId() != TypeId::Player) {
									continue;
								}
								else {
									//�v���C���[���n�b�L���O��Ԃ�
									if ((*i)->IsHucked()) {

										continue;
									}
									else {

										//�v���C���[���_�œG�̐�`�̓����蔻��
										if (_owner._collision->FanToPoint(_owner, **i, _owner._catchR, _owner._catchRange)) {

											//�v���C���[�̃Q�[�W������������
										//	(*i)->GetGaugeBase().DownGauge(15);
										//	(*i)->GetGaugePlayer().DownGauge(15);
											(*i)->GetGame().GetGaugeBaseUI().DownGauge(15);
											(*i)->GetGame().GetGaugePlayerUI().DownGauge(15);

											//�v���C���[�𖳓G���Ԃɂ���
											//_invincibleTime = true;

											//�v���C���[�̃_���[�W�t���O��ݒ�
											Flag::FlagData::SetDamageFlag(true);

											////�v���C���[���_���[�W��ԂɕύX
											(*i)->GetState().GoToState("Damage");

										}

									}


								}
							}
							else {


								//if (!Flag::FlagData::GetHuckNoDamageFlag()) {

									//�G�G�l�~�[���n�b�L���O����Ă��邩
								if ((*i)->IsHucked()) {

									//�n�b�L���O����Ă���G���_�œG�̐�`�Ƃ̓����蔻��
									if (_owner._collision->FanToPoint(_owner, **i, _owner._catchR, _owner._catchRange)) {

										//�n�b�L���O����Ă���G�̃Q�[�W������������
										//(*i)->GetGaugeBase().DownGauge(15);
										//(*i)->GetGaugeEnemy().DownGauge(15);
										(*i)->GetGame().GetGaugeBaseUI().DownGauge(15);
										(*i)->GetGame().GetGaugeEnemyUI().DownGauge(15);

										//�n�b�L���O����Ă���G���_���[�W��ԂɕύX
										(*i)->GetState().PushBack("Damage");

										Flag::FlagData::SetHuckDamageFlag(true);
									}


								}
								else {
									continue;
								}

								//}


							}


						}

					}


				}



			}



		}

		_catchTime--;

	}

	void CatchEnemy::StateCatchAfter::Enter() {
		_owner.GetModelAnime().ChangeAnime("Idle", true);
		_catchAfterTime = 120;
	}

	void CatchEnemy::StateCatchAfter::Update() {

		//�n�b�L���O���ɑ̗͂�0�ɂȂ�����
		//if (_owner.GetGaugeBase().IsGaugeZero(_owner)) {
		if (_owner.GetGame().GetGaugeBaseUI().IsGaugeZero(_owner)) {
			_owner._state->GoToState("Die");

			for (auto&& actor : _owner.GetActorServer().GetActors()) {

				if (actor->GetTypeId() != TypeId::Player) {
					continue;
				}
				else {
					actor->SetActorState(ActorState::Active);
				}

			}

		}
		else {

			if (_owner.GetStatus() == STATUS::ISHUCKING) {
				_owner._state->GoToState("IsHucking");
				//_loseSightTime = 60;
			}
			else if (_owner.GetStatus() == STATUS::ISHUCKED) {
				_owner._state->GoToState("IsHucked");
			}

		}

		//_invincibleTime = false;
		////�v���C���[�̖��G���Ԃ����Z�b�g
		//Flag::FlagData::SetNoDamageTime(_invincibleTime);

		if (_catchAfterTime < 0) {

			_owner._state->GoToState("CatchPre");

		}
		else {
			_catchAfterTime--;
		}

	}

	void CatchEnemy::StateFallPre::Enter() {



	}

	void CatchEnemy::StateFallPre::Update() {

		auto holePos = _owner.GetHolePos();
		//Math::Vector4 holePos = { holePos.GetX, static_cast<double>(holePosVECTOR.y), static_cast<double>(holePosVECTOR.z) };
		auto dif = holePos - _owner.GetPosition();

		_norm = dif.Normalize() * 5;

		if (_owner.IsHucked()) {

			auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
			Flag::FlagData::SetHeadPos(headPos);
			//_owner.SetHuckedMove(_norm);

		}

		_owner._position = _owner.GetPosition() + _norm;

		// ���[���h�s��̍X�V
		_owner.ComputeWorldTransform();


		if (holePos.GetX() - 3.0 < _owner.GetPosition().GetX() && _owner._position.GetX() < holePos.GetX() + 3.0 && holePos.GetZ() - 3.0 < _owner.GetPosition().GetZ() && _owner._position.GetZ() < holePos.GetZ() + 3.0) {

			_owner.GetState().GoToState("Fall");

		}

	}

	void CatchEnemy::StateFall::Enter() {

		_owner.GetModelAnime().ChangeAnime("Fall");
	}

	void CatchEnemy::StateFall::Update() {

		if (_owner.GetModelAnime().GetRepeatedCount() > 0) {

			//���Ƃ̓����蔻�������
			_owner.SetFallFlag(true);

		}

		if (_owner.GetFallFlag()) {

			//���ɗ��Ƃ�
			Math::Vector4 difY = { 0.0, -10.0, 0.0 };
			_owner._position = _owner.GetPosition() + difY;
			auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head");
			Flag::FlagData::SetHeadPos(headPos);

		}

		//_fallCount--;

		if (_owner.GetPosition().GetY() < -500.0) {


			//�n�b�L���O��Ԃ�
			if (_owner.IsHucked()) {

				//�����ɓ����Ă����ꏊ�̈ʒu��ݒ�
				auto warpAfterPos = Flag::FlagData::GetWarpAfterPos();

				Math::Vector4 pos = { static_cast<double>(warpAfterPos.x), static_cast<double>(warpAfterPos.y), static_cast<double>(warpAfterPos.z) };



				for (auto&& actor : _owner.GetActorServer().GetActors()) {

					if (actor->GetTypeId() != TypeId::Player) {
						continue;
					}
					else {

						actor->SetActorState(ActorState::Active);

						actor->GetState().GoToState("Idle");
						//auto warpAfterPos = Flag::FlagData::GetWarpAfterPos();
						actor->SetPosition(pos);
					}

				}

			}

			_owner.SetActorState(ActorState::Dead);


		}

	}

	//bool CatchEnemy::StateRun::IsViewPlayer() {
	//
	//	_owner.GetPosition();
	//
	//}

	//���S
	void CatchEnemy::StateDie::Enter() {
		_owner.GetModelAnime().ChangeAnime("Die");
	}

	void CatchEnemy::StateDie::Update() {
		auto cnt = _owner.GetModelAnime().GetRepeatedCount();
		if (cnt > 0) {
			_owner.SetActorState(ActorState::Dead);
		}
		auto handle = _owner.GetModelAnime().GetHandle();
		auto progress = _owner.GetModelAnime().GetPlayProgress();
		auto num = MV1GetMeshNum(handle);
		for (auto i = 0; i < num; ++i) {
			MV1SetMeshOpacityRate(handle, i, 1.f - progress);
		}
	}

	//�_���[�W
	void CatchEnemy::StateDamage::Enter() {
		_owner.GetModelAnime().ChangeAnime("Damage", true);
	}

	void CatchEnemy::StateDamage::Update() {

		if (_owner.GetModelAnime().GetRepeatedCount() > 0) {

			_owner._state->PopBack();

		}

	}


	void CatchEnemy::StateHucking::Enter()
	{
		_owner.GetModelAnime().ChangeAnime("Hucking", false);
	}

	void CatchEnemy::StateHucking::Update()
	{
		//// �n�b�L���O���ꂽ���m�F
		//_owner.HitCheckFrom();


		if (_owner.GetStatus() == STATUS::ISHUCKING)
		{
			auto player = _owner.GetActorServer().GetPosition("Player");

			if (player.GetX() - 1 < _owner._position.GetX() && _owner._position.GetX() < player.GetX() + 1 && player.GetZ() - 1 < _owner._position.GetZ() && _owner._position.GetZ() < player.GetZ() + 1/* && player.GetY() - 1 < 200.0 && 200.0 < player.GetY() + 1*/)
			{
				_owner.SetActorState(ActorState::Hucked);
				_owner._state->GoToState("IsHucked");

				auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head"); //!< �{���̃L���b�`�̓��̃t���[��������(��)
				Flag::FlagData::SetHeadPos(headPos);
			}
		}



	}


	void CatchEnemy::StateHucked::Enter() {
		_owner.GetModelAnime().ChangeAnime("Attack");
	}

	void CatchEnemy::StateHucked::Input(AppFrame::Input::InputComponent& input) {

		auto& joypad = input.GetJoypad();
		auto& key = input.GetKeyBoard();
		_lx = 0.0, _ly = 0.0;

		// �E�ړ��ƍ��ړ�
		if (joypad.LHorison() != 0.0)
		{
			_lx = input.GetJoypad().LHorison() / 1000.0;
		}
		else if (key.Button_D() != 0)
		{
			_lx = 1.0;
		}
		else if (key.Button_A() != 0)
		{
			_lx = -1.0;
		}

		// �O�i�ƌ��
		if (input.GetJoypad().LVertical() != 0.0)
		{
			_ly = input.GetJoypad().LVertical() / 1000.0;
		}
		else if (key.Button_W() != 0)
		{
			_ly = 1.0;
		}
		else if (key.Button_S() != 0)
		{
			_ly = -1.0;
		}

		if (input.GetJoypad().Button_RT()) {

			_owner._state->GoToState("Catch");
		}

	}

	void CatchEnemy::StateHucked::Update() {
		//// �n�b�L���O���ꂽ���m�F
		//_owner.HitCheckFrom();
		//if (_owner.GetActorState() != ActorState::Hucked)
		//{
		//	_owner._state->GoToState("Run");
		//	_owner._status = STATUS::CHASE;
		//}
		if (_lx != 0.0 || _ly != 0.0) {
			_owner.GetModelAnime().ChangeAnime("Walk", true);//����ꂽ�Ƃ��Ɉړ�����
		}
		else {
			_owner.GetModelAnime().ChangeAnime("Idle", true);
		}


		auto headPos = _owner.GetModelAnime().GetHeadPos("Character1_Head"); //!< �{���̃L���b�`�̓��̃t���[��������(��)
		Flag::FlagData::SetHeadPos(headPos);

		if (Flag::FlagData::GetHuckDamageFlag()) {

			//�_���[�W�t���O���I�t��
			Flag::FlagData::SetHuckDamageFlag(false);

			//���G�t���O���I����
			Flag::FlagData::SetHuckNoDamageFlag(true);

			_huckNoDamageTime = 120;

		}

		_huckNoDamageTime--;

		//���G���Ԃ��I������猳�ɖ߂�
		if (_huckNoDamageTime < 0 && Flag::FlagData::GetHuckNoDamageFlag()) {
			Flag::FlagData::SetHuckNoDamageFlag(false);
		}


		//�ړ����Ƀt���A�̕ǂƂ̔�������
		//Math::Vector4 oldPos = _owner.GetPosition();

		//�n�b�L���O���̌����ݒ�
		//_owner.HuckedRotation(_lx, _ly);

		//�O�t���[���̍��W��ۑ�
		auto oldPos = _owner.GetPosition();

		//�n�b�L���O���̈ړ���ݒ�
		_owner.HuckedMove(_lx, _ly);


		
		//�󂹂�ǂƓ������Ă��邩
		if (_owner.GetCollision().CollisionBrokenWall(_owner)) {
			_owner._position = oldPos;
		}

		//���Ɠ������Ă��邩
		if (_owner.GetCollision().CollisionHole(_owner)) {
			_owner.GetState().GoToState("FallPre");
		}

		////�n�ʂƐG��Ă��邩�ǂ���
		if (!_owner.GetFallFlag()) {

			////�n�ʂƐG��Ă��邩�ǂ���
			_owner.CollisionFloor(oldPos, _owner.GetR());
		}
		//	Math::Vector4 zero = { 0.0, 0.0, 0.0 };
		//	//��l���̃J�����Ɉړ��ʂ𑗂�
		//	_owner.SetHuckedMove(zero);
		//}
		//else {
		//}

				//���[�v���ォ
		if (!_warping) {

			auto dxPos = _owner.WarpFloor(_owner);

			//�t�F�[�h�p�ɕۑ�
			_fadePos = { dxPos.x, dxPos.y, dxPos.z };

			//���݈ʒu�̃X�e�[�W�ԍ��̃��[�v�i�r���b�V���ɓ��������ꍇ
			if (dxPos.x != 0.0f && dxPos.z != 0.0f) {

				//�X���C�h�t���O���I����
				if (!Flag::FlagData::GetSlideFlag()) {

					Flag::FlagData::SetFadeOutFlag(true);

				}
				else {
					Flag::FlagData::SetSlideOut(true);
				}

				//Math::Vector4 pos = { dxPos.x, dxPos.y, dxPos.z };

				//_position = pos;
				//_owner._position = _fadePos;

				//_camera->SetRefleshPosition(_position);
				//_camera->SetRefleshTarget(_position);

				if (!_warping) {

					_warping = true;
					_waitFrame = 5;

					//_fadeflag = true;

				}
				//else {
				//	_warping = false;
				//}

				//�����Ƀt�F�[�h�C������

			}


		}
		else {

			if (_waitFrame == 4) {
				_owner._position = _fadePos;
			}

			if (_waitFrame == 0) {
				if (!Flag::FlagData::GetSlideFlag()) {

					Flag::FlagData::SetFadeInFlag(true);
				}
				else {
					Flag::FlagData::SetSlideIn(true);
					Flag::FlagData::SetSlideFlag(false);
				}

			}

			if (!_owner.WarpingFloor() && _waitFrame < 0) {

				//_position = _fadePos;
				_warping = false;
				auto position = _owner.GetPosition();
				Flag::FlagData::SetWarpAfterPos(ToDX(position));

			}


		}

		_waitFrame--;

		//�Q�[�W��0���ǂ���
		if (_owner.GetGame().GetGaugeBaseUI().IsGaugeZero(_owner)) {

			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;

			Flag::FlagData::SetHuckDamageFlag(false);
			Flag::FlagData::SetHuckNoDamageFlag(false);

			for (auto&& actor : _owner.GetActorServer().GetActors()) {

				if (actor->GetTypeId() != TypeId::Player) {
					continue;
				}
				else {

					actor->SetActorState(ActorState::Active);
				}

			}

		}

		//�n�b�L���O����Ă��邩�ǂ���
		if (!_owner.IsHucked())
		{
			_owner._state->GoToState("Die");
			_owner._status = STATUS::DYING;
		}


	}

}
