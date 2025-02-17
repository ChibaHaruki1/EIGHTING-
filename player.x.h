//========================================
//
//�v���C���[�̃N���X�Ǘ�[player.h]
//Author:chiba haruki
//
//========================================


#pragma once


//========================================
//�C���N���[�h
#include "main.h"
#include "input.h"
#include "camera.h"
#include "collision.h"
#include "field.h"
#include "ui.h"
#include "2d_ui.h"
#include "character.h"


class CPlayerX : public CCharacter
{
public: //�A�N�Z�X�\

	CPlayerX(int nPriority = DEFAULT_PRIORITY1);                                    //�R���X�g���N�^
	~CPlayerX()override;                                                            //�f�X�g���N�^
	HRESULT Init()override;                                                         //����������
	void Uninit()override;                                                          //�j������
	void Update()override;                                                          //�X�V����
	void Draw()override;                                                            //�`�揈��
	//void ObjectArrangement();                                                     //�I�u�W�F�N�g�̔z�u�����i�����������t�@�C���ɏ������ށj
	void KeySet();                                                                  //�L�[���Ƃ̏������܂Ƃ߂�֐�
	void ShopKeySet();                                                              //���[�h��SHOP���̃L�[���Ƃ̏������܂Ƃ߂�֐�
	void BlockJudgement();                                                          //�u���b�N�Ƃ̔���
	void UIJudgement();                                                             //UI�Ƃ̔���
	void Random();                                                                  //�����_������
	void Praticles();                                                               //�p�[�e�B�N�����o������
	void NormalStateSummarizeFunction();                                            //�ʏ펞�̊֐����܂Ƃ߂�֐�
	void ShopStateSummarizeFunction();                                              //�X�ɖK�⎞�̊֐����܂Ƃ߂�֐�
	void CreateGun();                                                               //�e�̐����C���X�^���X���Ă�
	void InstanceMakeNull();                                                        //instance��nullptr�ɂ��鏈��
	void ShopInstanceMakeNullptr();                                                 //�V���b�v�Ŏg�p����C���X�^���X��nullptr�ɂ���
	void SelectGageUISize(float SIzeX, float SIze1X);                                //�I���Q�[�W�̑傫����ݒ肷��֐�
	void SelectGageUISizeCalculation(const char* aSelect, float SIzeX, float SIze1X);  //�I���Q�[�W�̑傫�����v�Z�i���Z�⌸�Z�Ȃǁj����֐�
	void BlowAway();
	void HitAttack();                                                               //����̍U�����󂯂��Ƃ��̏���
	void SceneMode(int nType);                                                      //scene�̕���
	void NextStageMotion();                                                         //���̃X�e�[�W�ɍs���Ǝ��̃��[�V��������		                    
	void NowCreateObjectUI();                                                       //���ݍ���Ă���I�u�W�F�N�g��UI���o������
	void NowCreateNumberObj();                                                      //�ԍ��ō��I�u�W�F�N�g���w�肷�鏈��

	static CPlayerX* Create();                                                      //��������


	//=====================================
	//CObjectX�Ŏg�p����p�̎擾
	int& GetTelephonPoleCount() { return m_nTelephonCount; }                        //�d���̔z����擾
	int& GetAllTelephonPoleCount() { return m_nAllTelephonPoleCount; }              //�S�Ă̓d���̔z����擾
	int& GetRotNumber() { return m_nRotNumber; }                                    //�v���C���[�̌����̔ԍ����擾


	//=====================================
	//�����������x���擾���Ȃ��Ă����悤�ɕۊǂ���p�̕ϐ��̐ݒ�
	void SetFieldBlockCount(int nFieldBlockCount) { m_nFieldBlock = nFieldBlockCount; }                 //�n�ʗp�u���b�N�̐������̐ݒ�
	void SetGoUpBlockCount(int nGoUpBlock) { m_nGoUpBlock = nGoUpBlock; }                              //�n�ʗp�u���b�N�̐������̐ݒ�
	void SetRoadBlockCount(int nRoadBlock) { m_nRoadBlock = nRoadBlock; }                              //���p�u���b�N�̐������̐ݒ�
	void SetWallRoadBlockCount(int nWallRoadBlock) { m_nWallRoadBlock = nWallRoadBlock; }              //�ǌ����p�u���b�N�̐������̐ݒ�
	void SetWallRoadBlock001Count(int nWallRoadBlock001) { m_nWallRoadBlock001 = nWallRoadBlock001; }  //�ǌ����p�u���b�N001�̐������̐ݒ�
	void SetSmalBlockCount(int nSmalBlock) { m_nSmalBlock = nSmalBlock; }                              //�������u���b�N�̐������̐ݒ�
	void SetSmalBlock001Count(int nSmalBlock001) { m_nSmalBlock001 = nSmalBlock001; }                  //�������u���b�N001�̐������̐ݒ�

	void SetLaserCount(int nLaserCount) { m_nLaserCount = nLaserCount; }                                //���[�U�[�̐������̐ݒ�


	//=====================================
	//�}�N����`
	static constexpr  int ROT_NUMBER_1 = 1; //�����ԍ��P��
	static constexpr  int ROT_NUMBER_2 = 2; //�����ԍ��Q��

	static constexpr  float MAX_MOVESPEED = 3.0f;                //���������炵�����̈ړ��ʂ̑���


private:
	//==========================================
	//�}�N����`
	static constexpr  int   MAX_TEXT_OBJECT = 2;                 //���z�u�c�[���ɐݒ肳��Ă�I�u�W�F�N�g�̐��[�P�i�O�X�^�[�g������j
	static constexpr  int   MAX_BUULET_SPEED = 30;               //�e�̑���
	static constexpr  int   INIT_NUMBER = -1;                    //�������̒l
	static constexpr  int   LIFE = 1;                            //���C�t

	static constexpr  float   ADJUST_SELECT_SIZEY = 160.0f;      //�I���Q�[�W��Y���̈ʒu�����Z����l
	static constexpr  float   MAX_GRAVITY = 50.0f;               //�d�͂̍ő�l
	static constexpr  float   DIE_POS_Y = 4000.0f;               //���S�ʒu�̐ݒ�l
	static constexpr  float   MAX_JUMPPAWER = 10.0f;             //��ԗ�
	static constexpr  float   MAX_SPECIALATTACKCOUNT = 60 * 0;  //�K�E�Z�̃��L���X�g�^�C��
	static constexpr  float   MAX_POS_NEXTSTAGE = 0.4f;          //���̃X�e�[�W�֍s�����̈ʒu�̏�Z�l


	//============================================
	//�V�[���Ɋւ���}�N����`
	static constexpr  int   SCENE_NEXT_STAGE = 1;                //���̃V�[���֍s�����̔ԍ�(���Ԓʂ�)
	static constexpr  int   SCENE_DEBUG_STAGE = 2;               //���̃V�[���֍s�����̔ԍ�(���炩���ߌ��߂��V�[����)
	static constexpr  int   SCENE_DIE_STAGE = 3;                 //���̃V�[���֍s�����̔ԍ�(���S���ɍs���V�[����)


	//============================================
	//�p�[�e�B�N���Ɋւ���}�N����`
	static constexpr int MIN_RANDOM = -50;                       //�����̍ŏ��l
	static constexpr int MAX_RANDOM = 100;                       //�����̍ő�l
	static constexpr int MAX_COL_RANDOM = 255;                   //�F�̗����̍ő�l
	static constexpr int MAX_PARTICLE_FRAME = 4;                 //�p�[�e�B�N���t���[���̍ő�l


	//============================================
	//���S���̃}�N����`
	static constexpr  int   MAX_DIE_COUNT = 180;                 //���S���̃J�E���g
	static constexpr  int   MIN_DIE_RANDOM = -1;                 //���S���̗����̍ŏ��l
	static constexpr  int   MAX_DIE_RANDOM = 3;                  //���S���̗����̍ő�l

	static constexpr float DIE_FRAME_REDUCTION = 0.1f;           //���S���̃t���[���̏k���l


	//============================================
	//�Ԃ���я������}�N����`
	static constexpr  int   BLOWAWAY_FRAME_1 = 40;               //���s�����̃t���[��
	static constexpr  int   BLOWAWAY_FRAME_2 = 90;               //���s�����̃t���[��

	static constexpr  float   BLOWAWAY_PLUS_POS_X = 20.0f;       //X���̔�ԋ���
	static constexpr  float   BLOWAWAY_PLUS_POS_Y = 30.0f;       //Y���̔�ԋ���


	//============================================
	//�s�����Ɋւ���}�N����`
	static constexpr int GUN_FRAME_MOTION = 60;                               //�e�����t���[��

	static constexpr float RIGHT_BULLET_PLUS_POS_X = 240.0f;                  //�e��X���̈ʒu�����Z����l
	static constexpr float LEFT_BULLET_MINUS_POS_X = -50.0f;                  //�e��X���̈ʒu�����Z����l
	static constexpr float ROT_NUMBER_1_SPECIAL_EFFECT_PLUS_POS_Y = 220.0f;   //�����ԍ��P�Ԃ̕K�E�Z�̃G�t�F�N�g��Y���̈ʒu�����Z����l
	static constexpr float ROT_NUMBER_2_SPECIAL_EFFECT_MINUS_POS_Y = -50.0f;  //�����ԍ��Q�Ԃ̕K�E�Z�̃G�t�F�N�g��Y���̈ʒu�����Z����l


	//============================================
	//�V���b�v���̃}�N����`
	static constexpr int MODE_SHOP_SELECT_COUNT = 2;                           //���ڐ��i�����A����̂Q���Ȃ̂łQ�j
	static constexpr int MODE_SHOP_UP_COUNT = -1;                              //�I���Q�[�W����ɍs�������߂鎞�̔ԍ�
	static constexpr int MODE_SHOP_DOWN_COUNT = 2;                             //�I���Q�[�W�����ɍs�������߂鎞�̔ԍ�

	static constexpr float  MODE_SHOP_SELECT_GAGE_SIXE1_X = 50.0f;             //�I���Q�[�W�P�ڂ�X���̑傫��
	static constexpr float  MODE_SHOP1_SELECT_GAGE_SIXE2_X = 270.0f;           //�P��ڂ̑I���Q�[�W�P�ڂ�X���̑傫��
	static constexpr float  MODE_SHOP2_SELECT_GAGE_SIXE2_X = 150.0f;           //�Q��ڂ̑I���Q�[�W�Q�ڂ�X���̑傫��

	static constexpr float  MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X = 400.0f;        //�V���b�v���̑I���Q�[�W��X���̑傫���𑝉�


	//=============================================
	//���������̃}�N����`
	static constexpr int MODE_BUY_SELECT_COUNT = 4;                            //���ڐ�
	static constexpr int MODE_BUY_UP_COUNT = -1;                               //�I���Q�[�W����ɍs�������߂鎞�̔ԍ�
	static constexpr int MODE_BUY_DOWN_COUNT = 4;                              //�I���Q�[�W�����ɍs�������߂鎞�̔ԍ�

	static constexpr float  MODE_BUY_SELECT_GAGE_SIXE1_Y = 50.0f;              //�I���Q�[�W�P�ڂ�y���̑傫��
	static constexpr float  MODE_BUY_SELECT_GAGE_SIXE2_Y = 150.0f;             //�I���Q�[�W�Q�ڂ�y���̑傫��


	//=============================================
	//�e�̐����}�N����`
	static constexpr int CREATE_GUN_NUMBER_0 = 0; //�e�̐����ԍ��O��
	static constexpr int CREATE_GUN_NUMBER_1 = 1; //�e�̐����ԍ��P��
	static constexpr int CREATE_GUN_NUMBER_2 = 2; //�e�̐����ԍ��Q��
	static constexpr int CREATE_GUN_NUMBER_3 = 3; //�e�̐����ԍ��R��


	//=============================================
	//�����蔻��}�N����`
	static constexpr int MAX_LANDING_FRAME = 60;     //���n���̃t���[���̍ő�l
	static constexpr int NEXT_STAGE_BATTLESHIP = 1;  //���̃X�e�[�W�֍s���p�̃o�g���V�b�v�̔ԍ�

	static constexpr float ADJUST_HIT_BATTLE = 1.1f; //�o�g���V�b�v�̓����蔻��̒����l


	//=============================================
	//�o�g���V�b�v�̃}�N����`
	static constexpr int ATTACKPATTEN_FRAME_1 = 1;   //���s��
	static constexpr int ATTACKPATTEN_FRAME_2 = 180; //���s��

	static constexpr float PLUS_POS_Y = 100.0f;      //���g��Y���̈ʒu�̉��Z�l
	static constexpr float MINUS_POS_Z = -250.0f;    //���g��Z���̈ʒu�̌��Z�l


	//=============================================
	//�����I�u�W�F�N�g�̃}�N����`
	static constexpr int CREATE_FIELDBLOCK = 0;      //�n�ʗp�u���b�N�̐����ԍ�
	static constexpr int CREATE_TELEPHONPOLE = 1;    //�d���̐����ԍ�
	static constexpr int CREATE_GOUPBLOCK = 2;       //�オ��p�u���b�N�̐����ԍ�


	//�v���C���[�̏��
	enum class PLAYER_STATE
	{
		NORMAI_MODE,  //�ʏ���
		SHOP_MODE,    //�X�Řb���Ă�����
		BUY_MODE,     //�������
		SEND_MODE,    //������
	};

	//�C���X�^���X
	CUI* m_pTalkText;                    //�u�b���vtextUI
	CUI* m_pLaserUI;                     //���[�U�[UI
	CManager2DUI* m_pNowCreateUI;        //���u�����Ƃ��Ă���I�u�W�F�N�g��UI
	CManager2DUI* m_pMenyu;              //���j���[UI
	CBuyText* m_pBuyText;                //[�����A����]textUI
	CSelectGage* m_pSelectGage;          //�I�����̃Q�[�WUI
	CSelectGage001* m_pSelectGage001;    //�I�����̃Q�[�WUI

	//�\���̂̃C���X�^���X
	PLAYER_STATE m_PlayerState;          //���݂̃v���C���[�̏��
	PLAYER_STATE m_FlagSate;             //���݂̃t���O��

	//==========================================
	//�e�L�X�g�t�@�C���ɓo�^���鎞�̔z��ԍ�
	int m_nFiledCount;                   //�t�B�[���h�̔z���i�߂�ׂ̃J�E���g
	int m_nTelephonCount;                //�d���̔z���i�߂�ׂ̃J�E���g�{text����ĂԂƂ��ɃC���X�^���X���̔z���o�^����������n��


	//==========================================
	//�e�L�X�g�t�@�C���ɓo�^���邵���S�Ă̔z��ԍ�
	int m_nAllTelephonPoleCount;         //�d���̍��̍��ꂽ����ۊǂ���
	int m_nAllFiledCount;                //�t�B�[���h�̍��̍��ꂽ����ۊǂ���


	//==========================================
	//�p�[�e�B�N���Ɋւ���ϐ�
	int m_nAlpha;                        //�p�[�e�B�N���̓����x�������_���Ō��߂�ϐ�
	int m_nFrameParticle;                //���t���[�����ϑ�����ׂ̕ϐ�
	int m_nPraticlesCount;               //�p�[�e�B�N���̔z����J�E���g����ׂ̕ϐ�
	int m_nRandomCol;                    //������ۊǂ���ׂ̕ϐ�


	//==========================================
	//�v���C���[�Ɋւ���ϐ�
	int m_nMotionFrame;                  //�e��łۂ̃J�E���g
	int m_nMotionFrame001;               //�e�����ۂ̃J�E���g
	int m_ObjectNumber;                  //���݂̃I�u�W�F�N�g�̎�ނ̔ԍ���ۊǂ���ϐ�
	bool m_bPlayerMoveNext;              //���̃X�e�[�W�֍s�����̃v���C���[�̓����̔���p�̕ϐ�
	bool m_bNextStage;                   //���̃X�e�[�W�֍s���ׂ̔�������p�̕ϐ�
	bool SpecialAttack;                  //�K�E�Z���g���Ă���Ƃ��͓����Ȃ�


	//==========================================
	//SHOP�Ɋւ���ϐ�
	int m_nSelectShopCount;              //���𔃂����J�E���g����ׂ̕ϐ�
	int m_nBuyOrSendCount;               //���������邩��I������Ƃ��ɔ��ʂ���悤�̕ϐ�


	//==========================================
	//������я����ɕK�v�ȕϐ�
	int m_nFlayFrame;                    //������Ԏ��Ԃ��ϑ�
	int m_nDieRandom;                    //���S���̃t���[����ۊǂ���ϐ�
	int m_nRotNumber;                    //�v���C���[�̌����̔ԍ���ۊ�
	int m_nSpecialAttackCount;           //�K�E�Z�̌��Ă鎞�Ԃ��ϑ�����p�̕ϐ�
	bool m_bFly;                         //���@���������ł��邩�ǂ����̔���ׂ̈̕ϐ��i���[�V�����̍��G������邽�߁j


	//==========================================
	//�X�y�[�X�V�b�v�����ɕK�v�ȕϐ�
	int m_nNextStageFrame;               //���̃X�e�[�W�ɍs���܂ł̃t���[��
	int m_nLandingFrame;                 //���n���̃t���[��
	bool m_bLandingFlag;                 //���n�������ǂ����̔���p�ϐ�


	//===========================================
	//�������̎擾�p
	int m_nFieldBlock;                   //�n�ʗp�u���b�N�̐�������ۊǂ���p�̕ϐ�
	int m_nGoUpBlock;                    //�オ��p�̃u���b�N�̐�������ۊǂ���p�̕ϐ�
	int m_nRoadBlock;                    //���p�u���b�N�̐�������ۊǂ���p�̕ϐ�
	int m_nWallRoadBlock;                //�ǌ����p�u���b�N�̐�������ۊǂ���p�̕ϐ�
	int m_nWallRoadBlock001;             //�ǌ����p�u���b�N001�̐�������ۊǂ���p�̕ϐ�
	int m_nSmalBlock;                    //�������u���b�N�̐�������ۊǂ���p�̕ϐ�
	int m_nSmalBlock001;                 //�������u���b�N001�̐�������ۊǂ���p�̕ϐ�

	int	m_nLaserCount;                   //���[�U�[�̐�������ۊǂ���p�̕ϐ�
};

