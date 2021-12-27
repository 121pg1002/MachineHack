///
/// @file    ModelAnimComponent.cpp
/// @brief   �A�j���[�V�������f���p�̃R���|�[�l���g
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "ModelAnimComponent.h"
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/Actor.h"
#include <numbers>
//namespace Model {
  ModelAnimeComponent::ModelAnimeComponent(Actor& owner) : ModelComponent{ owner } {
  }

  ModelAnimeComponent::~ModelAnimeComponent() {
    MV1DetachAnim(_handle, _attachIndex);
  }

  ///
  /// ������.
  ///
  void ModelAnimeComponent::Init() {
  }
  void ModelAnimeComponent::Register(std::string_view key, int animIndex) {
    if (_registry.contains(key.data())) {
      _registry.erase(key.data());
    }
    _registry.emplace(key, animIndex);
  }
  /// �X�V
  void ModelAnimeComponent::Update() {
    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(_handle, _attachIndex, _playTime);

    // ���[���h�s��X�V
    ModelComponent::Update();

    // �Đ����Ԃ�i�߂�
    _playTime += (1.f * _timeRate);

    if (_playTime >= _totalTime) {
      if (_repeate) {
        // ���s�[�g�Đ�����
        _playTime = 0.0f;
        ++_repeatedCount;
      }
      else {
        // ���s�[�g�Đ��Ȃ�
        _repeatedCount = 1;
        _playTime = _totalTime;
      }
    }
  }
  ///
  /// �`��.
  ///
  void ModelAnimeComponent::Draw() {
    MV1DrawModel(_handle);
  }

  void ModelAnimeComponent::Draw(const Actor& owner, bool _isHit, double range)
  {
#ifdef _DEBUG
    math::Vector4 lmax = owner.GetLMax() + owner.GetPosition();
    math::Vector4 lmin = owner.GetLMin() + owner.GetPosition();

    DrawLine3D(ToDX(lmin), ToDX(lmax), GetColor(255, 0, 0));

    auto _pos = owner.GetPosition();

    auto dir = owner.GetRotation();

    //atan2�́A���v���𐳂Ƃ��Ď������Ă��邽�߁A�������t�ƂȂ邽�ߕ������}�C�i�X�ɂ��Ă���
    auto _rot_y = -dir.GetY();

    //z����0�x�Ƃ��邽��
    auto Nine = std::numbers::pi / 180.0 * 90.0;
    ////�~�ʂ̕����x�N�g��
    //double endAngle = 45.0;
    //double halfAngle = endAngle / 2.0;
    //double Rad = std::numbers::pi / 180.0 * endAngle;
    ////auto   halfRad = std::numbers::pi / 180.0 * halfAngle;

    //math::Vector4 _move = { std::cos(Rad), 0.0, std::sin(Rad) };
    //auto pos = owner.GetPosition();
    //auto target = pos + _move * owner.Get_r() * 2.0;
    //DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 0, 255));

    //
    //auto zero = 0.0;
    //_move = { std::cos(zero), 0.0, std::sin(zero) };
    //target = pos + _move * owner.Get_r() * 2.0;
    //DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 0, 255));


   // auto pos1 = act1.GetPosition();
   //DrawLine3D(ToDX(pos1), ToDX(pos), GetColor(255, 255, 0));
    ///�~�̂�����͂�Ă��@
    //if (_isHit == true) 
    //{
    //    for (double i = 0.0; i < 720.0; i++)
    //    {
    //        double radian = std::numbers::pi / 180.0 * i/2.0;
    //        double x = owner.Get_r() * std::cos(radian);
    //        double z = owner.Get_r() * std::sin(radian);
    //        math::Vector4 t = { x, 0.0, z };
    //        math::Vector4 newpos = owner.GetPosition() + t;
    //        DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));

    //    }
    //
    //}
    //else 
    //{
    //    for (double i = 0.0; i < 720.0; i++)
    //    {
    //        double radian = std::numbers::pi / 180.0 * i/2.0;
    //        double x = owner.Get_r() * std::cos(radian);
    //        double z = owner.Get_r() * std::sin(radian);
    //        math::Vector4 t = { x, 0.0, z };
    //        math::Vector4 newpos = owner.GetPosition() + t;
    //        DrawPixel3D(ToDX(newpos), GetColor(255, 255, 0));

    //    }
    //
    //}
        //�Ԃ��~�̕`��
    for (double i = 0.0; i < 720.0; i++)
    {
      double radian = std::numbers::pi / 180.0 * i / 2.0;
      double x = owner.Get_r() * std::cos(radian);
      double z = owner.Get_r() * std::sin(radian);
      math::Vector4 t = { x, 0.0, z };
      math::Vector4 newpos = owner.GetPosition() + t;
      DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));

    }

    //hucking������
    if (_isHit)
    {

      //�p�x

      auto Angle = range;
      auto Rad = std::numbers::pi / 180.0 * Angle;
      auto SRad = -Rad + _rot_y + Nine;
      auto ERad = Rad + _rot_y + Nine;

      //double endAngle = 120.0;
      //double Rad = std::numbers::pi / 180.0 * endAngle;
      //Rad = Rad + _rot_y;
      ////�ʂ̍����̐�
      math::Vector4 _move = { std::cos(ERad), 0.0, std::sin(ERad) };
      auto target = owner.GetPosition() + _move * owner.Get_r();
      DrawLine3D(ToDX(_pos), ToDX(target), GetColor(255, 0, 0));

      //auto startAngle = 30.0;
      //Rad = std::numbers::pi / 180.0 * startAngle;
      //Rad = Rad + _rot_y;
      ////�ʂ̉E���̐�
      _move = { std::cos(SRad), 0.0, std::sin(SRad) };
      target = owner.GetPosition() + _move * owner.Get_r();
      DrawLine3D(ToDX(_pos), ToDX(target), GetColor(255, 0, 0));

      auto yAngle = 180.0 / std::numbers::pi * _rot_y;
      //�~��
     //for(double i = yAngle; i < abs(yAngle + Angle); i++)
     //{
     //        double radian = std::numbers::pi / 180.0 * i/2.0;
     //        radian = radian + _rot_y;
     //        double x = owner.Get_r() * std::cos(radian);
     //        double z = owner.Get_r() * std::sin(radian);
     //        math::Vector4 t = { x, 0.0, z };
     //        math::Vector4 newpos = owner.GetPosition() + t;
     //        DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));
     //}

     //for (double i = yAngle; i < abs(yAngle - Angle); i--)
     //{
     //    double radian = std::numbers::pi / 180.0 * i / 2.0;
     //    radian = radian + _rot_y;
     //    double x = owner.Get_r() * std::cos(radian);
     //    double z = owner.Get_r() * std::sin(radian);
     //    math::Vector4 t = { x, 0.0, z };
     //    math::Vector4 newpos = owner.GetPosition() + t;
     //    DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));
     //}

    }
    else //�n�b�L���O���s��
    {
      //�p�x

      auto Angle = range;
      auto Rad = std::numbers::pi / 180.0 * Angle;
      auto SRad = -Rad + _rot_y + Nine;
      auto ERad = Rad + _rot_y + Nine;

      //double endAngle = 120.0;
      //double Rad = std::numbers::pi / 180.0 * endAngle;
      //Rad = Rad + _rot_y;
      ////�ʂ̍����̐�
      math::Vector4 _move = { std::cos(ERad), 0.0, std::sin(ERad) };
      auto target = owner.GetPosition() + _move * owner.Get_r();
      DrawLine3D(ToDX(_pos), ToDX(target), GetColor(255, 255, 0));

      //auto startAngle = 30.0;
      //Rad = std::numbers::pi / 180.0 * startAngle;
      //Rad = Rad + _rot_y;
      ////�ʂ̉E���̐�
      _move = { std::cos(SRad), 0.0, std::sin(SRad) };
      target = owner.GetPosition() + _move * owner.Get_r();
      DrawLine3D(ToDX(_pos), ToDX(target), GetColor(255, 255, 0));

      auto yAngle = 180.0 / std::numbers::pi * _rot_y;
      //for (double i = startAngle; i < endangle; (endAngle- startAngle/100)��1������) 
      //{
      // //auto target = _pos + Get_r() * std::cos(i);
      //   auto target2 = _pos + Get_r() * std::cos(i-1);
      //    DrawTriangle3D(ToDX(_pos), ToDX(target), ToDX(target2), GetColor(255, 255, 0), true);
      //}
    }




#endif
  }

  /// �A�j���[�V�����̕ύX
  void ModelAnimeComponent::ChangeAnime(std::string_view key, bool repeate) {
    auto newAnimIndex = _registry[key.data()];

    if (_animIndex == newAnimIndex) {
      return;
    }
    _animIndex = newAnimIndex;

    // �A�j���[�V�������f�^�b�`����
    MV1DetachAnim(_handle, _attachIndex);
    // �V�����A�j���[�V�������A�^�b�`����
    _attachIndex = MV1AttachAnim(_handle, newAnimIndex, -1, FALSE);
    // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
    _totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);

    _playTime = 0.0f;
    _repeatedCount = 0;
    _repeate = repeate;
  }
//}
