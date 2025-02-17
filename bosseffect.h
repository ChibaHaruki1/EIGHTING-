//=========================================
//
//�{�X�p�G�t�F�N�g�̃N���X�Ǘ�[bossefect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once


//=========================
//�C���N���[�h
#include "object3D.h"


//========================================================================================================
//�X�g���e�W�[�N���X���
class CBossEffectDirection
{
public:
	CBossEffectDirection();   //�R���X�g���N�^
	~CBossEffectDirection();  //�f�X�g���N�^

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                 //�e�N�X�`���̐ݒ�
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex); //�e�N�X�`���̍X�V
	

	//===========================
	//���̎擾
	const char* GetFileNamePass() { return m_aEffectFileName; }                                                       //�t�@�C���p�X�̎擾


	//===========================
	//���̐ݒ�
	void SetFileNamePass(const char* aFilePass) { m_aEffectFileName = aFilePass; }                                    //�t�@�C���p�X�̐ݒ�

private:
	//�}�N����`
	static constexpr int N_INIT_NUMBER = 0;          //int�^�̏������̒l
	static constexpr float F_INIT_NUMBER = 0.0f;     //float�^�̏������̒l

	static constexpr float TEX_POS_Y = 1.0f;         //�e�N�X�`����Y���̈ʒu

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine;          //���g�̃o�b�t�@
	int m_nLife;                                     //�A�j���[�V�����̃��C�t�p�̕ϐ�
	const char* m_aEffectFileName;                   //�t�@�C���p�X
};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@�Ռ��j
class CAttackEffect : public CBossEffectDirection
{
public:
	CAttackEffect();   //�R���X�g���N�^
	~CAttackEffect();  //�f�X�g���N�^
};


//========================================================================================================
//�K�E�Z
class CSourceSpecialAttackBoss : public CBossEffectDirection
{
public:
	CSourceSpecialAttackBoss();   //�R���X�g���N�^
	~CSourceSpecialAttackBoss();  //�f�X�g���N�^
};


//========================================================================================================
//�{�X�G�t�F�N�g�Ǘ��̊��N���X
class CManagerBossEffect : public CObject3D
{
public: //�O������A�N�Z�X�\
	CManagerBossEffect(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerBossEffect();								   //�f�X�g���N�^
	HRESULT Init()override;								   //����������
	void Uninit()override;								   //�j������
	void Update()override;								   //�X�V����
	void Draw()override;								   //�`�揈��
	void SetEffect(D3DXVECTOR3 pos);                       //�G�t�F�N�g�̈ʒu�̐ݒ�

	static CManagerBossEffect* Create(D3DXVECTOR3 pos, TYPE type);  //���������i�p���N���X��TYPE�Ő�������j


	//=================================
	//���̎擾
	CBossEffectDirection* GetBossEffectDirection() { return m_pEffectDirection000; } //�X�g���e�W�[���N���X�̃|�C���^�[���擾
	int& GetRotNumber() { return m_nBossRotNumber; }                                 //���E�ǂ���̌����ɂȂ��Ă��邩�����Ŕ��肷������擾
	int& GetHitNumber() { return m_nHitNumber; }                                     //�Ռ��g�ɓ����������ǂ�������p�̕ϐ��̎擾


	//=================================
	//���̐ݒ�
	void SetRotNumber(int nRotNumber) { m_nBossRotNumber = nRotNumber; }             //���E�ǂ���̌����ɂȂ��Ă��邩�����Ŕ��肷�����ݒ�
	void SetHitNumber(int nHitNumber) { m_nHitNumber = nHitNumber; }                 //�Ռ��g�ɓ����������ǂ�������p�̕ϐ��̐ݒ�


	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	static constexpr  float MAX_BOSSANIMETION_TEX = 0.125f;     //�A�j���[�V�����̕�����
	static constexpr  float MAX_IMPACT_TEXTURESIZE = 1.0f;      //�Ռ��g�̃e�N�X�`���̑傫��
	static constexpr  float MAX_BOSSANIMATION_LIFE = 8;         //�A�j���[�V�����̍X�V���鎞�̃��C�t
	static constexpr  float MAX_BOSSSPECIALATTACK_X = 200.0f;   //�{�X�̕K�E�Z��Y���̑傫��
	static constexpr  float MAX_BOSSSPECIALATTACK_Y = 200.0f;   //�{�X�̕K�E�Z��Y���̑傫��
	static constexpr  float PLUS_POS_Y = 100.0f;                //�K�E�Z��Y���̈ʒu�𑫂����킹��ׂ̃}�N��
	static constexpr  float MAX_DAMAGE = 0.005f;                //�{�X�̕K�E�Z�̃_���[�W��
	static constexpr  float MAX_SIZEX = 40.0f;                  //�����̑傫��
	static constexpr  float MAX_SIZEY = 40.0f;                  //�����̑傫��
	static constexpr  float MAX_SIZEZ = 40.0f;                  //�����̑傫��

private:
	//�}�N����`
	static constexpr int INIT_HIT_NUMBER = -1;   //��������������ԍ��ŕԂ��ϐ��̏����l

	CBossEffectDirection* m_pEffectDirection000; //�X�g���e�W�[���N���X�̃|�C���^�[

	int m_nBossRotNumber; //�����ő傫����ς��邽�߂̕ϐ�
	int m_nHitNumber;     //��������������ԍ��ŕۊǂ���p�̕ϐ�

	double m_dLifeCount;  //�A�j���[�V�����̑��x
};


//========================================================================================================
//�Ռ��g�̃G�t�F�N�g����
class CImpact : public CManagerBossEffect
{
public:
	CImpact();              //�R���X�g���N�^
	~CImpact()override;     //�f�X�g���N�^
	void Update()override;  //�X�V����


	//================================
	//�}�N����`
	 static constexpr  int MAX_IMPACT_LIFE = 100;  //���C�t�̍ő�l

private:
	//�}�N����`
	static constexpr int HIT_NUMBER_0 = 0;       //�O�Ԗڂ̓��������ԍ�
	static constexpr int HIT_NUMBER_1 = 1;       //�P�Ԗڂ̓��������ԍ�

	static constexpr  float PLUS_SIZEX = 4.0f;   //�����̑傫�������Z����l
	static constexpr  float PLUS_SIZEY = 1.0f;   //�����̑傫�������Z����l

	static constexpr float ADJUST_SIZE_X = 1.5f; //�����蔻�莞��X���̑傫���𒲐�����p�̒l
	static constexpr float ADJUST_SIZE_Y = 1.1f; //�����蔻�莞��Y���̑傫���𒲐�����p�̒l
	static constexpr float SIZE_Z = 40.0f;       //�����蔻�莞��Z���̑傫��
};


//========================================================================================================
//�K�E�Z�̃G�t�F�N�g����
class CBossSpecialAttack : public CManagerBossEffect
{
public:
	CBossSpecialAttack();           //�R���X�g���N�^
	~CBossSpecialAttack()override;  //�f�X�g���N�^
	void Update()override;          //�X�V����

	//==========================
	//�}�N����`
	static constexpr float MAX_SPECIALATTACK_SIZEX = 200.0f; //�����̑傫��
	static constexpr float MAX_SPECIALATTACK_SIZEY = 200.0f; //�����̑傫��
	static constexpr int MAX_BOSSSPZECIALATTACK_LIFE = 120;  //���C�t�̍ő�l

	static constexpr int ROT_NUMBER_1 = 1;                   //�P�Ԗڂ̌����̔ԍ�
	static constexpr int ROT_NUMBER_2 = 2;                   //�Q�Ԗڂ̌����̔ԍ�

private:
	//�}�N����`
	static constexpr  int MINUS_ALPHA = 5;                    //�A���t�@�l�����Z���Ă����l

	static constexpr  float ADJUST_SIZE_X = 0.8f;             //�K�E�Z�̓����蔻��̏�Z�����l
	static constexpr  float MAXIMUM_SIZEX = 2000.0f;          //�T�C�Y�����Z���Ă������̍ő�l
	static constexpr  float PLUS_SIZEX = 20.0f;               //�����̑傫�������Z����l
	static constexpr  float ADJUST_PLAYER_POSY = 1.5f;        //�v���C���[��pos.y�̈ʒu�̒l�𒲐�����l

	static constexpr  double ANIMETION_DLLIFE = 0.3;          //�A�j���[�V�����̑����̒����l
};