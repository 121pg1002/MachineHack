///
/// @file    Game.cpp
/// @brief   �Q�[���N���X�̒�`
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "../source/Scene/SceneInGame.h"
#include "../source/Scene/SceneTeam.h"
#include "../source/Scene/SceneTitle.h"
#include "../source/Scene/SceneTeam.h"
#include "../source/Scene/ScenePrologue.h"
#include "../source/Scene/SceneEpilogue.h"
#include "../source/Scene/SceneAMG.h"
#include "../source/Scene/SceneMap.h"
#include "../source/Scene/SceneItem.h"
#include "../source/Scene/SceneLoading.h"
#include "../source/Scene/SceneSlideIn.h"
#include "../source/Scene/SceneSlideOut.h"
#include "../source/Actor/ActorServer.h"
#include "../source/Actor/ActorFactory.h"
#include "../source/Enemy/EnemyParameter.h"
#include "../source/Stage/StageParameter.h"
#include "../source/Gimmick/GimmickParameter.h"
#include "../source/Item/ItemParameter.h"
#include "../source/Effect/EffectServer.h"
#include "../source/UI/UIComponent.h"
#include "../source/UI/SpriteServer.h"
#include "../source/Gauge/GaugeEnemy.h"
#include "../source/Gauge/GaugePlayer.h"
#include "../source/Item/Item.h"
#include <DxLib.h>

AppFrame::Game::Game() {
}

AppFrame::Game::~Game() {
}
/// ������
bool AppFrame::Game::Initialize() {
    // ��ʃ��[�h�̂�ݒ�
    SetGraphMode(1920, 1080, 32);
    // �E�B���h�E���[�h�Ɏw�肷��
    ChangeWindowMode(true);

    // Dx���C�u����������
    if (DxLib_Init() == -1) {
        return false;
    }
    //�ǉ�

// ��ʂ̔w�i�F��ɐݒ肷��
    SetBackgroundColor(10, 10, 10);
    // �`����ʂ𗠂ɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    //Effekseer�̏�����
    MachineHuck::Effect::EffectServer::EffekseerInit();                     //�ǉ�

    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);

    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    // �}�e���A���̎��Ȕ����F���Â��F�ɂ���
#ifdef _DEBUG
    MATERIALPARAM material;
    material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
    material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
    material.Power = 20.0f;
    SetMaterialParam(material);
#endif



    // �C���v�b�g�R���|�[�l���g�̐���
    _input = std::make_unique<AppFrame::Input::InputComponent>();

    // �T�E���h�R���|�[�l���g�̐���
    _sound = std::make_unique<AppFrame::Sound::SoundComponent>(*this);

    // �A�N�^�[�T�[�o�[�̐���
    _actorServer = std::make_unique<MachineHuck::Actor::ActorServer>();

    // �A�N�^�[�t�@�N�g���[�̐���
    _actorFactory = std::make_unique<MachineHuck::Actor::ActorFactory>(*this);

    // �X�v���C�g�T�[�o�[�̐���
    _spriteServer = std::make_unique<MachineHuck::UI::SpriteServer>();

    // UI�R���|�[�l���g�̐���
    _ui = std::make_unique<MachineHuck::UI::UIComponent>(*this);

    //�A�C�e���R���|�[�l���g�̐���
    _itemCom = std::make_unique<MachineHuck::Item::Item>(*this);

    _gaugeBaseUi = std::make_unique<MachineHuck::Gauge::GaugeBase>(*this);
    _gaugePlayerUi = std::make_unique<MachineHuck::Gauge::GaugePlayer>(*this);
    _gaugeEnemyUi = std::make_unique<MachineHuck::Gauge::GaugeEnemy>(*this);


    // �A�Z�b�g�T�[�o�[�̐���
    _assetServer = std::make_unique<AppFrame::Asset::AssetServer>(*this);

    // �A�Z�b�g�T�[�o�[�̎擾
    auto& as = GetAssetServer();
    // �A�Z�b�g�̃J�����g�t�H���_�ݒ�
    as.ChangeCurrentPath("resource");

    // �g�p���鉹�̃e�[�u��
    const AppFrame::Asset::AssetServer::SoundMap soundToUsed{
      {"damage", {"damage.wav", true}},
      {"charging", {"se/�r�[���C�`���[�W.mp3", true}},
      {"push", {"se/����A�{�^������33.mp3", true}},
      {"bgm1", {"se/energy.mp3", false}},

      // {"bgm2", {"stage1.mid", false}},
     //{"save",{"se/se_save" ,true}}                          ,
    {"getitem",{"se/se_getitem.wav" ,true}}                    ,
    //{"store",{"se/se_store" ,true}}                        ,
    {"hacking",{"se/se_hacking.wav" ,true}}                    ,
    //{"hackerror",{"se/se_hackerror" ,true}}                ,
    {"dropoff",{"se/se_dropoff.wav" ,true}}                    ,
    {"damage"     ,   {"se/se_damage.wav" ,true}}              ,
    {"lackenergy" ,       {"se/se_lackenergy.wav" ,true}}      ,
    {"outofenergy",       {"se/se_outofenergy.wav" ,true}}     ,
    {"tackle"     ,   {"se/se_tackle.wav" ,true}}              ,
    //{"catch"      ,  {"se/se_catch" ,true}}                ,
    //{"alert"      ,  {"se/se_alert" ,true}}                ,
    {"exchange"   ,     {"se/se_exchange.wav" ,true}}          ,
    //{"switch"     ,   {"se/se_switch" ,true}}              ,
    //{"unlockgate" ,       {"se/se_unlockgate" ,true}}      ,
    //{"lockgate"   ,     {"se/se_lockgate" ,true}}          ,
    //{"breakwall"  ,      {"se/se_breakwall" ,true}}        ,
    //{"floordamage",        {"se/se_floordamage" ,true}}    ,
    //{"enemyhaunting",       {"se/se_enemyhaunting" ,true}} ,
    //{"dropdown"     ,   {"se/se_dropdown" ,true}}          ,
    //{"induct"       , {"se/se_induct" ,true}}              ,
    //{"outduct"      ,  {"se/se_outduct" ,true}}            ,
    {"openmap"      ,  {"se/se_openmap.wav" ,true}}            ,
    {"openitem"     ,  {"se/se_openitem.wav" ,true}}           ,
    {"close"        ,{"se/se_close.wav" ,true}}                ,

    //{"breakenemy" ,      {"se/se_breakenemy" ,true}}       ,
    //{"hitwall"    ,    {"se/se_hitwall" ,true}}            ,
    {"contact"    ,    {"se/se_contact.wav" ,true}}            ,
    //{"tackle"     ,   {"se/se_tackle" ,true}}              ,
    //{"catch"      ,   {"se/se_catch" ,true}}               ,
    //{"alert"      , {"se/se_alert", true}}                 ,
    {"footsteps"  ,     {"se/se_footsteps.wav", true}}
    };
    // ���̓ǂݍ���
    as.LoadSounds(soundToUsed);
    // �T�E���h�R���|�[�l���g�̎擾
    auto& sc = GetSoundComponent();
    sc.SetVolume("damage", 128);
    sc.SetVolume("push", 128);
#ifdef _DEBUG
    sc.SetMute(false);
#else
    sc.SetMute(false);
#endif

    // �V�[���T�[�o�[�𐶐����^�C�g���𐶐����čŏ��̃V�[���Ƃ��ēo�^
    _sceneServer = std::make_unique<AppFrame::Scene::SceneServer>("AMG", std::make_shared<MachineHuck::Scene::SceneAMG>(*this));


    _sceneServer->Register("Team", std::make_shared<MachineHuck::Scene::SceneTeam>(*this));
    _sceneServer->Register("Title", std::make_shared<MachineHuck::Scene::SceneTitle>(*this));
    _sceneServer->Register("Prologue", std::make_shared<MachineHuck::Scene::ScenePrologue>(*this));
    _sceneServer->Register("Epilogue", std::make_shared<MachineHuck::Scene::SceneEpilogue>(*this));
    _sceneServer->Register("Map", std::make_shared<MachineHuck::Scene::SceneMap>(*this));
    _sceneServer->Register("Item", std::make_shared<MachineHuck::Scene::SceneItem>(*this));
    _sceneServer->Register("Loading", std::make_shared<MachineHuck::Scene::SceneLoading>(*this));
    _sceneServer->Register("SlideIn", std::make_shared<MachineHuck::Scene::SceneSlideIn>(*this));
    _sceneServer->Register("SlideOut", std::make_shared<MachineHuck::Scene::SceneSlideOut>(*this));

    // �C���Q�[���𐶐����ăV�[���Ƃ��ēo�^
    _sceneServer->Register("InGame", std::make_shared<MachineHuck::Scene::SceneInGame>(*this));

    _enemyParam = std::make_unique<MachineHuck::Enemy::EnemyParameter>();
    _stageParam = std::make_unique<MachineHuck::Stage::StageParameter>();
    _gParam = std::make_unique<MachineHuck::Gimmick::GimmickParameter>();
    _iParam = std::make_unique<MachineHuck::Item::ItemParameter>();


    return true;
}
/// ���s
void AppFrame::Game::Run() {
    // ���C�����[�v
    while (_state != State::Quit) {

        if (CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }

        Input(*_input);  // ����
        Update(); // �X�V
        Render(); // �`��
    }
}
/// ��~
void AppFrame::Game::Shutdown() {                                                     //�ǉ�
    //Effekseer�I������
    MachineHuck::Effect::EffectServer::EndEffekseer();            //�ǉ�
                                                                                      // Dx���C�u�����I��
    DxLib_End();
}
/// ����
void AppFrame::Game::Input(AppFrame::Input::InputComponent& input) {
    // Windows ���L�̖ʓ|�ȏ��������C�u�����ɂ�点��
    if (ProcessMessage() == -1) {
        _state = State::Quit;  // -1 ���Ԃ��Ă����̂ŃQ�[�����I������
    }
    // ���͏�Ԃ̍X�V
    _input->Update();
    if (_input->GetJoypad().Exit()) {
        _state = State::Quit;  // ESC�����ꂽ�̂ŃQ�[�����I������
    }
    _sceneServer->Input(*_input);    // �V�[���T�[�o�[�̓��͏��������s
}
/// �X�V
void AppFrame::Game::Update() {
    _sceneServer->Update(); // �V�[���T�[�o�[�̍X�V���������s
}
/// �`��
void AppFrame::Game::Render() {
    ClearDrawScreen();      // ��ʂ��N���A����
    _sceneServer->Render(); // �V�[���T�[�o�[�̕`�揈�������s
    ScreenFlip();           // ����ʂ�\������
}
/// �A�N�^�[�T�[�o�[�̎擾
//ActorServer& Game::GetActorServer() const {
//  return _sceneServer->GetScene().GetActorServer();
//}
