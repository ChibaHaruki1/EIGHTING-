//============================================
//
//character�N���X�Ǘ�[character.h]
//Ajther: Chiba haruki
//
//============================================

#pragma once

//============================================
//�C���N���[�h
#include "objectX.h"
#include "model_prts.h"


//======================================================
//�L�����N�^�[�̊e�p�[�c�N���X
class CCharacter : public CObjectX
{
public:
	////���ʉ��ł���������
	//typedef enum
	//{
	//	NEUTRAL = 0, //�ҋ@
	//	WALK,        //����
	//	ACTION,      //
	//	JUMP,
	//}COMMON;

	//typedef enum
	//{
	//	BOSSJUMP1=4,
	//}BOSSMOTIONSTATE;

	//typedef enum
	//{
	//	BLOWAWAY=4,
	//}MOTIONSTATE;

	//�{�X�̃��[�V�����̎��
	typedef enum
	{
		BOSSNEUTRAL = 0, //�ҋ@
		BOSSWALK,        //����
		BOSSACTION,      //����
		BOSSJUMP,        //���
		BOSSIMPACT,      //���001
		BOSSATTACK,      //�U��
		BOSSDIE,         //���S
	}BOSSMOTIONSTATE;

	//�v���C���[�̃��[�V�����̎��
	typedef enum
	{
		NEUTRAL = 0, //�ҋ@
		WALK,        //����
		ACTION,      //����
		JUMP,        //���
		BLOWAWAY,    //�������
		DIE,         //���S
		SLOWSHOT,    //������茂��
		TITLE_JUMP,  //�^�C�g�����̔��
		LANDING,     //���n
		LOKING ,     //�T��(�^�C�g����)
	}MOTIONSTATE;

	CCharacter(int nPriority = DEFAULT_PRIORITY1);         //�R���X�g���N�^
	~CCharacter();                                         //�f�X�g���N�^
	HRESULT Init();                                        //����������
	void Uninit();                                         //�j������

	//�v���C���[
    void Lood();
	void UpdatePlayer();                                   //�v���C���[�̍X�V����
	void DrawPlayer(int NumPrts);                          //�v���C���[�̕`�揈��
	void MotionInfo();                                     //���[�V�����̏�����������
	void SetMotion(MOTIONSTATE motiontype);                //���[�V�������Ƃ̏���
	
	//�{�X
	void LoodBoss();
	void UpdateBoss();                                     //�{�X�̍X�V����
	void DrawBoss(int NumPrts);                            //�`�揈��
	void MotionInfoBoss();                                 //�{�X���[�V�����̏�����������
	void SetMotionBoss(BOSSMOTIONSTATE motiontype);        //�{�X���[�V�������Ƃ̏���

	MOTIONSTATE m_MotionState;                   //�v���C���[�̃��[�V�����̎�ނ̏�������
	BOSSMOTIONSTATE m_MotionStateBoss;           //�{�X�̃��[�V�����̎�ނ̏�������
	CModelPrts* m_pModelPrts[MAX_PARTS];          //���f���p�[�c�̏��̃|�C���^�[
	CModelPrts* m_pModelPrtsBoss[MAX_BOSSPARTS]; //���f���p�[�c�̏��̃|�C���^�[


	//=====================================
	//���̎擾
	CModelPrts* GetModelPrtasBoss(int nNumber) { return m_pModelPrtsBoss[nNumber]; } //�{�X�̃p�[�c�̏��̎擾
	//bool& GetMotionType() { return m_bMotionType; }                                  //�v���C���[�̃��[�V�����^�C�v�̎擾


	//=====================================
	//���̐ݒ�
	void SetMotionType(bool bMotionType) { m_bMotionType = bMotionType; }            //�v���C���[�̃��[�V�����^�C�v�̐ݒ�

	//==========================================
	//�}�N����`
	static constexpr  int MAX_KEYSET = 8;              //���[�V�����Ɏg���L�[�̐�


	//==========================================
	//�v���C���[�Ɋւ���}�N��
	static constexpr int PLAYER_PARTS_BODY_NUMBER = 0;      //�̂̔ԍ�
	static constexpr int PLAYER_PARTS_RIGHT_SHOLDER = 2;    //�E���̔ԍ�
	static constexpr int PLAYER_PARTS_LEFT_SHOLDER = 6;     //�����̔ԍ�
	static constexpr int PLAYER_PARTS_RIGHT_THIGHS = 11;    //�E�������̔ԍ�
	static constexpr int PLAYER_PARTS_LEFT_THIGHS = 14;     //���������̔ԍ�
	static constexpr int PLAYER_PARTS_GUN_NUMBER = 17;      //�e�̔ԍ�
	static constexpr int PLAYER_PARTS_GUN001_NUMBER = 18;   //�e001�̔ԍ�
	static constexpr int NUM_MOTION = 11;                   //�v���C���[���[�V�����̑���
	static constexpr int NUM_RIGHTLEFTPRTS = 4;             //�v���C���[�̑��̃p�[�c��
	static constexpr int PLAYER_GUN_COUNT = 2;              //�e�̐�


	 //==========================================
	 //�{�X�Ɋւ���}�N��
	 static constexpr  int NUM_MOTIONBOSS = 10;         //�{�X�̃��[�V�����̑���
	 static constexpr  int NUM_RIGHTPRTSBOSS = 8;       //�{�X�̑��̃p�[�c��
	static constexpr float BOSS_PLUS_POS_Y = 200.0f;    //�{�X�̃p�[�c��Y���̈ʒu����ɏグ��ׂ̒l
	static constexpr int BOSS_PARTS_GUN_NUMBER = 17;    //�e�̔ԍ�
	static constexpr int BOSS_GUN_COUNT = 1;            //�e�̐�

private:
	//�}�N����`
	static constexpr int MAX_PARTS_SEARCH = 100;                     //�p�[�c�̎擾���̔z��̍ő吔
	static constexpr int MAX_DATA_SEARCH = 512;                      //�e�L�X�g�t�@�C���̓ǂݍ��ݎ��̔z��̍ő吔
	static constexpr int FGET_NUMBER_1 = 40;                         //fgets�֐��̓ǂݎ��l�P��
	static constexpr int FGET_NUMBER_2 = 20;                         //fgets�֐��̓ǂݎ��l�Q��
	static constexpr int PARENT_NUMBER = -1;                         //�e�p�[�c�̓ǂݍ��ݒl
		

	//========================================================
	//�v���C���[�Ɋւ���}�N����`
	static constexpr int PLAYER_PARTS_RIGHTHAND_NUMBER = 5;          //�E��̔ԍ�
	static constexpr int PLAYER_PARTS_LEFTHAND_NUMBER = 9;           //����̔ԍ�
	static constexpr int PLAYER_PARTS_WAIST_NUMBER = 10;             //���̔ԍ�
	static constexpr int PLAYER_PARTS_SHOULDER_FROM_HAND = 4;        //��������For�����񂷍�0,1,2,3�̏��i���A��r�A���r�A��j�ŉ񂷗p
	static constexpr int PLAYER_PARTS_RIGHT_SHOULDER_FROM_HAND = 2;  //�E������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A�E������͂Q�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int PLAYER_PARTS_LEFT_SHOULDER_FROM_HAND = 6;   //��������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A��������͂U�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int PLAYER_PARTS_LOWER_BODY_COUNT = 6;          //�����g�̃p�[�c��
	static constexpr int PLAYER_PARTS_HEAD_AND_BODY_COUNT = 2;       //���Ƒ̂̐�
	static constexpr int PLAYER_NEXT_PARTS_COUNT = 1;                //���̃p�[�c�J�E���g
	static constexpr int PLAYER_NEXT_MOTION_COUNT = 1;               //���[�V�������̍��������߂鎞�̎��̃��[�V�����J�E���g
	static constexpr int PLAYER_BEFORE_MOTION_COUNT = 1;             //���[�V�������̍������������̑O�̃��[�V�����J�E���g
	static constexpr int PLAYER_FIRST_KEYSET_NUMBER = 0;             //�ŏ��̃L�[�Z�b�g�̏��߂̔ԍ�
	static constexpr int CREATE_GUN_COUNT = 2;                       //�e�̌�
	 

	//========================================================
	//�{�X�Ɋւ���}�N����`
	static constexpr int BOSS_PARTS_BODY_NUMBER = 0;                 //�̂̔ԍ�
	static constexpr int BOSS_PARTS_RIGHTHAND_NUMBER = 5;            //�E��̔ԍ�
	static constexpr int BOSS_PARTS_LEFTHAND_NUMBER = 9;             //����̔ԍ�
	static constexpr int BOSS_PARTS_WAIST_NUMBER = 10;               //���̔ԍ�
	static constexpr int BOSS_PARTS_SHOULDER_FROM_HAND = 4;          //��������For�����񂷍�0,1,2,3�̏��i���A��r�A���r�A��j�ŉ񂷗p
	static constexpr int BOSS_PARTS_RIGHT_SHOULDER_FROM_HAND = 2;    //�E������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A�E������͂Q�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int BOSS_PARTS_LEFT_SHOULDER_FROM_HAND = 6;     //��������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A��������͂U�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int BOSS_PARTS_LOWER_BODY_COUNT = 6;            //�����g�̃p�[�c��
	static constexpr int BOSS_PARTS_HEAD_AND_BODY_COUNT = 2;         //���Ƒ̂̐�
	static constexpr int BOSS_NEXT_PARTS_COUNT = 1;                  //���̃p�[�c�J�E���g
	static constexpr int BOSS_NEXT_MOTION_COUNT = 1;                 //���[�V�������̍��������߂鎞�̎��̃��[�V�����J�E���g
	static constexpr int BOSS_BEFORE_MOTION_COUNT = 1;               //���[�V�������̍������������̑O�̃��[�V�����J�E���g
	static constexpr int BOSS_FIRST_KEYSET_NUMBER = 0;               //�ŏ��̃L�[�Z�b�g�̏��߂̔ԍ�



	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}Key;

	//�L�[�Z�b�g�̍\����
	typedef struct
	{
		int Frame;                 //�t���[����
		Key aKey[MAX_PARTS];        //�L�[��(�p�[�c���m��)
	}KeySet;

	//���[�V�����̍\����
	typedef struct
	{
		bool Loop;                  //���[�V���������[�v���邩�ǂ�������p
		int NumKey;                 //�L�[�̑���
		KeySet KeySet[MAX_KEYSET];  //���[�V�����̃L�[�Z�b�g�i���[�V�������̃L�[�Z�b�g�̐��j
	}MotionSet;

	//���[�V���������m�ۂ���\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}SAVEMODELINFO;

	//�L�����N�^�[�̏���ۊǂ���ϐ�
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_PARTS], m_pSaveModelPrtInfoBoss[MAX_BOSSPARTS];   //���f���p�[�c�̏��̃|�C���^�[
	D3DXVECTOR3 SaveMotionPos[MAX_PARTS], SaveMotionPosBoss[MAX_BOSSPARTS];                 //�e�p�[�c�̈ʒu�����m�ۂ���ϐ�
	D3DXVECTOR3 SaveMotionRot[MAX_PARTS], SaveMotionRotBoss[MAX_BOSSPARTS];                 //�e�p�[�c�̌��������l������ϐ�
	MotionSet MotionSetPlayer[NUM_MOTION], MotionSetBoss[NUM_MOTIONBOSS];                  //�e���[�V�����̎�ނ��i�[����ϐ�

	int m_nMotionFrameBoss;            //���[�V�������̃t���[�����J�E���g���邽�߂̕ϐ�
	int MotionCount, MotionCountBoss;  //���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)

	bool m_bMotionType, m_bMotionBossType;       //����ȃ��[�V�������ǂ����𔻒肷��ׂ̕ϐ�
};