//=========================================
//
//�G�t�F�N�g�̃N���X�Ǘ�[efect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once

//=========================================
//�C���N���[�h
#include "object3D.h"
#include<memory>


//========================================================================================================
//�X�g���e�W�[�N���X���
class CEffectDirection
{
public:
	CEffectDirection();  //�R���X�g���N�^
	~CEffectDirection(); //�f�X�g���N�^

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                  //�e�N�X�`���i���W�j�̏��
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex);  //�G�t�F�N�g�̏���

	const char* GetEffectFileNamePass() { return m_aEffectFileName; }                               //�t�@�C���p�X���擾
	void SetEffectFileNamePass(const char* aEffectFieName) { m_aEffectFileName = aEffectFieName; }  //�t�@�C���p�X��ݒ�

private:
	//�}�N����`
	static constexpr int TexNumber_0 = 0;                 //�e�N�X�`���̔ԍ��O�Ԗ�
	static constexpr int TexNumber_1 = 1;                 //�e�N�X�`���̔ԍ��P�Ԗ�
	static constexpr int TexNumber_2 = 2;                 //�e�N�X�`���̔ԍ��Q�Ԗ�
	static constexpr int TexNumber_3 = 3;                 //�e�N�X�`���̔ԍ��R�Ԗ�
	static constexpr UINT BUFFNUMBE = 0U;                 //�o�b�t�@�̃��b�N���̔ԍ�

	static constexpr float TEXTURE_SIZE = 1.0f;           //�e�N�X�`���̑傫��

	static constexpr int INIT_LIFE = 0;                   //���C�t�̏����l
	static constexpr int MAX_EXPLOSION_LIFE = 8;          //�A�j���[�V�����̍X�V���鎞�̃��C�t

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine;               //���g�̃o�b�t�@�[
	int m_nLife;                                          //�e�N�X�`���̃��C�t�i�A�j���[�V�����p�́j
	const char* m_aEffectFileName;                        //�e�N�X�`���̃t�@�C���p�X

};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@��
class CThunder : public CEffectDirection
{
public:
	CThunder();   //�R���X�g���N�^
	~CThunder();  //�f�X�g���N�^		
};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@����
class CExplotion : public CEffectDirection
{
public:
	CExplotion();   //�R���X�g���N�^
	~CExplotion();  //�f�X�g���N�^						  
};


//========================================================================================================
//��
class CExplotionPillar : public CEffectDirection
{
public:
	CExplotionPillar();   //�R���X�g���N�^
	~CExplotionPillar();  //�f�X�g���N�^
};


//========================================================================================================
//����̉�
class CExplotionPillar001 : public CEffectDirection
{
public:
	CExplotionPillar001();   //�R���X�g���N�^
	~CExplotionPillar001();	 //�f�X�g���N�^
};


//========================================================================================================
//�X�g���e�W�[�p���@�j��
class CFormerDebris : public CEffectDirection
{
public:
	CFormerDebris();   //�R���X�g���N�^
	~CFormerDebris();  //�f�X�g���N�^
};


//========================================================================================================
//�X�g���e�W�[�p���@�K�E�Z
class CSourceSpecialAttack : public CEffectDirection
{
public:
	CSourceSpecialAttack();   //�R���X�g���N�^
	~CSourceSpecialAttack();  //�f�X�g���N�^
};


//========================================================================================================
//�G�t�F�N�g�Ǘ��̊��N���X
//========================================================================================================
class CManagerEffect : public CObject3D
{
public:
	CManagerEffect(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerEffect();								   //�f�X�g���N�^
	HRESULT Init()override;							   //����������
	void Uninit()override;							   //�j������
	void Update()override;							   //�X�V����
	void Draw()override;							   //�`�揈��
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerEffect* Create(D3DXVECTOR3 pos, TYPE type); //��������


	//============================
	//���̎擾
	CEffectDirection* GetEffectDirection() { return m_pEffectDirection000; } //�X�g���e�W�[���N���X�̃|�C���^�[���擾


protected://�p���N���X�̂݃A�N�Z�X�\

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	static constexpr  int SET_BULLET_LIFE = 42;            //���C�t�̍ő吔
	static constexpr  int MINUS_ALPHA = 5;                 //�A���t�@�l�̌��Z�l
	static constexpr  float m_fSepecialAttackX = 200.0f;   //�K�E�Z��X���̑傫��
	static constexpr  float m_fSepecialAttackY = 200.0f;   //�K�E�Z��Y���̑傫��

private:
	//�}�N����`
	static constexpr int EXCLUSION_EFFECT_NUMBER = -1; //�G�t�F�N�g�̔ԍ��̔��肩��̏��O�l
	static constexpr int IF_EFFECTNUMBER = 1;          //�G�t�F�N�g�i���o�[�̏������̒l
	static constexpr double MIN_DLIFECOUNT = 0.0;      //�A�j���[�V�������C�t�̍ŏ��l

	static constexpr int FIRE_ALPHA = 200;             //�t�@�C�A�[�G�t�F�N�g�̃A���t�@�l
	static constexpr int FIRE_LIFE = 60;               //�t�@�C�A�[�G�t�F�N�g�̃��C�t

	int m_nEffectNumber;                               //�Ō�ɃG�t�F�N�g���ĂԂ��ǂ���
	double m_dLifeCount;                               //�A�j���[�V�����̑��x
	float m_fMaxTex;                                   //�e�N�X�`���̍ő�̃T�C�Y
	CEffectDirection* m_pEffectDirection000;           //�X�g���e�W�[���N���X�̃|�C���^�[
};


//========================================================================================================
//���R�n�̃G�t�F�N�g�N���X
class CNatureEffect : public CManagerEffect
{
public:
	CNatureEffect();            //�R���X�g���N�^
	~CNatureEffect()override;   //�f�X�g���N�^


	//=========================
	//�}�N����`
	static constexpr  float THANDER_SIZEX = 70.0f;  //���G�t�F�N�g��X���̑傫��
	static constexpr  float THANDER_SIZEY = 70.0f;  //���G�t�F�N�g��Y���̑傫��
	static constexpr  float MAX_THANDER_TEX = 1.0f; //�A�j���[�V�����̕�����
};


//========================================================================================================
//1�ڂ̔����G�t�F�N�g
class CExplosion : public CManagerEffect
{
public:
	CExplosion();          //�R���X�g���N�^
	~CExplosion()override; //�f�X�g���N�^


	//=========================
	//�}�N����`
	static constexpr  float EXPLSION_SIZEX = 90.0f;                 //�����G�t�F�N�g��X���̑傫��
	static constexpr  float EXPLSION_SIZEY = 90.0f;                 //�����G�t�F�N�g��Y���̑傫��
	static constexpr  float MAX_EXPLOSION_TEX = 0.125f;             //�A�j���[�V�����̕�����
	static constexpr  double MAX_EXPLOSION_ANIMETION_SPEED = 0.6;   //�A�j���[�V�����̑���
};


//========================================================================================================
//��ڂ̔����G�t�F�N�g
class CExplosion001 : public CManagerEffect
{
public:
	CExplosion001();           //�R���X�g���N�^
	~CExplosion001()override;  //�f�X�g���N�^


	//=========================
	//�}�N����`
	static constexpr  float EXPLSION001_SIZEX = 90.0f;                 //�����G�t�F�N�g��X���̑傫��
	static constexpr  float EXPLSION001_SIZEY = 90.0f;                 //�����G�t�F�N�g��Y���̑傫��
	static constexpr  float MAX_EXPLOSION001_TEX = 0.125f;             //�A�j���[�V�����̕�����
	static constexpr  double MAX_EXPLOSION001_ANIMETION_SPEED = 0.6;   //�A�j���[�V�����̑���
};


//========================================================================================================
//���G�t�F�N�g
class CFire : public CManagerEffect
{
public:
	CFire();              //�R���X�g���N�^
	~CFire()override;	  //�f�X�g���N�^
	void Draw()override;  //�`�揈��


	//=========================
	//�}�N����`
	static constexpr  float FIRE_SIZEX = 92.0f;                 //���G�t�F�N�g��X���̑傫��
	static constexpr  float FIRE_SIZEY = 190.0f;                //���G�t�F�N�g��Y���̑傫��
	static constexpr  float MAX_FIRE_TEX = 0.125f;              //�A�j���[�V�����̕�����
	static constexpr  double MAX_FIRE_ANIMETION_SPEED = 0.5;    //�A�j���[�V�����̑���

private:
	//�}�N����`
	static constexpr  int FIRELIFE = 120; //���C�t�̍ő吔
};


//========================================================================================================
//����̉�
class CPillarOfFire : public CManagerEffect
{
public:
	CPillarOfFire();           //�R���X�g���N�^
	~CPillarOfFire()override;  //�f�X�g���N�^
	HRESULT Init()override;    //����������
	void Update()override;     //�X�V����


	//=========================
	//�}�N����`
	static constexpr  float PILLAROFFIRE_SIZEX = 200.0f;                 //����̉��G�t�F�N�g��X���̑傫��
	static constexpr  float PILLAROFFIRE_SIZEY = 600.0f;                 //����̉��G�t�F�N�g��Y���̑傫��
	static constexpr  float PILLAROFFIRE_SIZEZ = 40.0f;                  //����̉��G�t�F�N�g��Z���̑傫��
	static constexpr  float MAX_PILLAROFFIRE_TEX = 0.125f;               //�A�j���[�V�����̕�����
	static constexpr  double MAX_PILLAROFFIRE_ANIMETION_SPEED = 0.5;     //�A�j���[�V�����̑���

private:
	//�}�N����`
	static constexpr  int PILLARFIRELIFE = 180;           //�t�@�C�A�̃��C�t
	static constexpr  int MINUS_ALPHA = 5;                //�A���t�@�l�̌��Z�l

	static constexpr  double  D_LIFECOUNT = 0.5;          //�A�j���[�V�������C�t�̒����l

	static constexpr float ADJUST_PLAYER_HP_GAGE = 0.01f; //�v���C���[��HP�Q�[�W�̌���𒲐�����l
};


//========================================================================================================
//�e�̋O���ɂ��G�t�F�N�g
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CEffect()override;							//�f�X�g���N�^
	HRESULT Init()override;						//����������
	void Uninit()override;						//�j������
	void Update()override;						//�X�V����
	void Draw()override;						//�`�揈��
	
	static CEffect* Create(D3DXVECTOR3 pos);    //��������

private:
	//�}�N����`
	static constexpr  int SET_EFFECT_LIFE = 30; //���C�t�̍ő吔

	static constexpr  float SIZEX = 40.0f;      //X���̑傫��
	static constexpr  float SIZEY = 40.0f;      //Y���̑傫��

	static constexpr int CREATE_PRIORITY = 0;   //�������̃v���C�I���e�B�̔ԍ�
};


//========================================================================================================
//�j�ЃG�t�F�N�g�̃N���X
class CDebris : public CManagerEffect
{
public:
	CDebris();              //�R���X�g���N�^
	~CDebris()override;     //�f�X�g���N�^
	void Update()override;  //�X�V����


	//=========================
	//�}�N����`
	static constexpr  float MAX_DEBRIS_TEX = 1.0f; //�A�j���[�V�����̕�����


private:
	//�}�N����`
	static constexpr  int DEBRISLIFE = 10;         //���C�t�̍ő吔

	static constexpr  float SIZEX = 50.0f;         //X���̑傫��
	static constexpr  float PLUS_SIZEX = 4.0f;     //X���̑傫���𑝂₷�l

};


//========================================================================================================
//�K�E�Z�̃N���X
class CSpecialAttack : public CManagerEffect
{
public:
	CSpecialAttack();                               //�R���X�g���N�^
	~CSpecialAttack()override;                      //�f�X�g���N�^
	void Update()override;                          //�X�V����
	void HitEnemy();                                //�G�Ƃ̓����蔻�菈��


	//==========================
	//���̎擾
	int& GetRotNumber() { return m_nRotNumber; }    //���݂̌�����ԍ��Ŏ擾����


	//=========================
	//�}�N����`
	static constexpr  int ROT_NUMBER_1 = 1;                 //�����ԍ��P
	static constexpr  int ROT_NUMBER_2 = 2;                 //�����ԍ��Q

	static constexpr  float SPECIALATTACK_SIZEX = 200.0f;   //�K�E�Z�G�t�F�N�g��X���̑傫��
	static constexpr  float SPECIALATTACK_SIZEY = 200.0f;   //�K�E�Z�G�t�F�N�g��Y���̑傫��
	static constexpr  float MAX_SPECIALATTACK_TEX = 0.125f; //�A�j���[�V�����̕�����


private:
	//�}�N����`
	static constexpr  int SPECIALATTACKLIFE = 180;      //���C�t�̍ő吔
	static constexpr  int MINUS_ALPHA = 5;              //�A���t�@�l�̌��Z�l

	static constexpr double D_LIFECOUNT = 0.3;          //�A�j���[�V�������C�t�̒����l

	static constexpr  float MAXIMUM_SIZEX = 2000.0f;    //�T�C�Y�����Z���Ă������̍ő�l
	static constexpr  float MAX_DAMAGE_BOSS = 0.00005f; //�T�C�Y�����Z���Ă������̍ő�l
	static constexpr  float PLUS_SIZEX = 30.0f;         //X���̑傫���𑝂₷�l


	int m_nRotNumber;                                   //�����ő傫����ς��邽�߂̕ϐ�
};
