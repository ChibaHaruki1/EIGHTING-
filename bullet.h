//======================================
//
//�e�̃N���X�Ǘ�[bullet.h]
//Auther:Chiba Haruki
//
//======================================


#pragma once


//======================================
//�C���N���[�h
#include "object3D.h"


//============================================================================
//�e�̊Ǘ��̊��N���X
//============================================================================
class CManagerBullet : public CObject3D
{
public: //�O������A�N�Z�X�\
	CManagerBullet(int nPriority = DEFAULT_PRIORITY);               //�����t���R���X�g���N�^
	~CManagerBullet()override;                                      //�f�X�g���N�^
	HRESULT Init()override;                                         //����������
	void Uninit()override;                                          //�I������
	void Update()override;                                          //�X�V����
	void Draw()override;                                            //�`�揈��
	void SetInfo(D3DXVECTOR3 m_pos, D3DXVECTOR3 m_move, int nLife); //�e�̈ʒu�Ɋւ���ݒ菈��

	//�������z�֐��ɂ��邱�ƂŊ��N���X�̏��������̂܂܏�������
	virtual void CallEffect(bool bUse) = 0;  //�G�t�F�N�g�Ăԏ���
	virtual void CollisionOnObject() = 0; ;  //�I�u�W�F�N�g�Ƃ̓����蔻��

	static CManagerBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject3D::TYPE type); //3D�e�̐�������


	//============================
	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	 static constexpr  float MAX_BULLET3D_SIZE_X = 40.0f; //3D�e��X���̑傫��
	 static constexpr  float MAX_BULLET3D_SIZE_Y = 40.0f; //3D�e��Y���̑傫��
	 static constexpr  float MAX_BULLET3D_SIZE_Z = 40.0f; //3D�e��Z���̑傫��
	 static constexpr  int SET_BULLET_LIFE = 60;          //���C�t�̍ő吔

private: //�A�N�Z�X�s�\
    //�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	static constexpr int GREEN = 160;                     //�ΐF
	 static constexpr  int MINUS_ALPHA = 5;               //�A���t�@�l�����Z
	 static constexpr  float INIT_ROTY = 3.14f;           //�����̌���
};


//============================================================================
//�v���C���[�ʏ�e�̃N���X
class CBullet3D : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CBullet3D(int nPriority = DEFAULT_PRIORITY);   //�����t���R���X�g���N�^
	~CBullet3D()override;                          //�f�X�g���N�^
	//void Update()override;                       //�X�V����
	void CallEffect(bool bUse);                    //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                      //�I�u�W�F�N�g�Ƃ̓����蔻��

private: //�A�N�Z�X�s�\
	 //�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	static constexpr int MINUS_ENEMY000_LIFE = 1;              //�G000�̃��C�t�����炷�l
	static constexpr int MINUS_ENEMY001_LIFE = 1;              //�G001�̃��C�t�����炷�l
	static constexpr int MINUS_ENEMYMOTION001_LIFE = 1;        //���[�V�����t���̓G001�̃��C�t�����炷�l
	static constexpr int CREATE_PLUS_NUMBER = 1;               //���������擾����ۂ̐������Ɂ{�P����ׂ̒l

	static constexpr int BOSS_PARTS_RIGHT_THIGHS = 11;         //�{�X�̉E�������̃p�[�c�ԍ�
	static constexpr int BOSS_PARTS_RIGHT_KNEES = 12;          //�{�X�̉E�ӂ���͂��̃p�[�c�ԍ�
	static constexpr int BOSS_PARTS_RIGHT_FOOT = 13;           //�{�X�̉E���̃p�[�c�ԍ�

	static constexpr float  ADJUST_HIT_MOTIONENENY001 = 0.5f;  //���[�V�����t���̓G001�̓����蔻��̒����l
	static constexpr float  ADJUST_HIT_CAMERA_UP = 1.5f;       //�Ď��J�����㕔���̓����蔻��̒����l
	static constexpr float  MINUS_BOSS_HPGAGE = 0.01f;         //�{�X��HP�Q�[�W�����炷�l
	static constexpr float ADJUST_ENEMY001_HIT = 0.5f;         //�G001�̓����蔻��̒����l
	static constexpr float ADJUST_ENEMY002_HIT = 0.5f;         //�G002�̓����蔻��̒����l
};


//============================================================================
//�G�̒ʏ�e�̃N���X
class CEnemyBullet : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CEnemyBullet(int nPriority = DEFAULT_PRIORITY);  //�����t���R���X�g���N�^
	~CEnemyBullet()override;                         //�f�X�g���N�^
	void Update()override;                           //�X�V����
	void CallEffect(bool bUse);                      //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                        //�I�u�W�F�N�g�Ƃ̓����蔻��


	//============================
	//���̎擾
	static float& GetAdditionPosY() { return m_fAdditionPosY; }                             //���݂�Y���̈ʒu���擾


	//============================
	//���̐ݒ�
	static void SetAdditionPosY(float fAdditionPosY) { m_fAdditionPosY = fAdditionPosY; }   //���݂�Y���̈ʒu��ݒ�
	static float& SetAddjustAdditionPosY() { return m_fAdditionPosY; }                      //�l��ύX�������Ƃ��̐ݒ�


	//============================
	//�}�N����`
	 static constexpr  float PLUS_ROT_Y = 7.0f;               //Y���̌��������Z���Ă���
	 static constexpr  float MAX_ENEMYBULLET_SIZE_X = 40.0f;  //X���̑傫��
	 static constexpr  float MAX_ENEMYBULLET_SIZE_Y = 40.0f;  //Y���̑傫��
	 static constexpr  float MAX_ENEMYBULLET_SIZE_Z = 40.0f;  //Z���̑傫��

private: //�O������A�N�Z�X�s�\
    //�}�N����`
	 static constexpr  int BLUE = 200;                        //�F
	 static constexpr  int MINUS_ALPHA = 5;                   //�A���t�@�l�����Z
													         
	 static constexpr  float ADJUST_HIT = 0.5;                //�����蔻��̒����l
	 static constexpr  float  MINUS_PLAYER_HPGAGE = 0.05f;    //�v���C���[��HP�Q�[�W�����炷�l
														     
	static float m_fAdditionPosY;                             //rot.y�ɒl��ǉ����Ă������߂̕ϐ�
};


//============================================================================
//�G�̒ʏ�e�̃N���X
class CEnemyBulletBattleShip : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CEnemyBulletBattleShip(int nPriority = DEFAULT_PRIORITY);  //�����t���R���X�g���N�^
	~CEnemyBulletBattleShip()override;                         //�f�X�g���N�^
	void Update()override;                                     //�X�V����
	void CallEffect(bool bUse);                                //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                                  //�I�u�W�F�N�g�Ƃ̓����蔻��


	//============================
	//�}�N����`
	static constexpr float PLUS_ROT_Y = 7.0f;                  //Y���̌��������Z���Ă���
	static constexpr float MAX_ENEMYBULLET_SIZE_X = 40.0f;     //X���̑傫��
	static constexpr float MAX_ENEMYBULLET_SIZE_Y = 40.0f;     //Y���̑傫��
	static constexpr float MAX_ENEMYBULLET_SIZE_Z = 40.0f;     //Z���̑傫��

private: //�O������A�N�Z�X�s�\
	//�}�N����`
	static constexpr  int BLUE = 200;                          //�F
	static constexpr  int MINUS_ALPHA = 5;                     //�A���t�@�l�����Z
	static constexpr  int SET_BULLET_LIFE = 90;                //���C�t�̍ő�l
	static constexpr int MAX_FRAME = 10;                       //�t���[���̍ő吔
														       
	static constexpr  float ADDJUST_HIT = 1.0;                 //�����蔻��̒����l
	static constexpr  float  MINUS_PLAYER_HPGAGE = 0.05f;      //�v���C���[��HP�Q�[�W�����炷�l
	static  constexpr float MINUS_POS_Y = -2.5f;               //Y���̈ʒu�����Z���Ă����l
	
};


//============================================================================
//�{�X�̒ʏ�e�̃N���X
class CBossBullet : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CBossBullet(int nPriority = DEFAULT_PRIORITY);        //�����t���R���X�g���N�^
	~CBossBullet()override;                               //�f�X�g���N�^
	void Update()override;                                //�X�V����
	void CallEffect(bool bUse);                           //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                             //�I�u�W�F�N�g�Ƃ̓����蔻��


	//============================
	//�}�N����`
	static constexpr float MAX_BOSSBULLET_SIZE_X = 40.0f; //X���̑傫��
	static constexpr float MAX_BOSSBULLET_SIZE_Y = 40.0f; //Y���̑傫��
	static constexpr float MAX_BOSSBULLET_SIZE_Z = 40.0f; //Z���̑傫��


private: //�O������A�N�Z�X�s�\
	//�}�N����`
	static constexpr int BLUE = 200;                      //�F
	static constexpr int MINUS_ALPHA = 5;                 //�A���t�@�l�����Z
														  
	static constexpr float  MINUS_PLAYER_HPGAGE = 0.05f;  //�v���C���[��HP�Q�[�W�����炷�l
	static constexpr float  MINUS_POSY = 2.0f;            //Y���̈ʒu�����Z����l
	static constexpr float PLUS_POS_Y = 200.0f;           //�G�t�F�N�g��Y���̐����ʒu�����Z����l
	static constexpr float ADJUST_HIT = 0.5f;             //�����蔻�莞�̒����l
};

