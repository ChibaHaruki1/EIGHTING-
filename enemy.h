//==================================
//
//�G�̃N���X�Ǘ�[enemy.h]
//Auther:Chiba Haruki
//
//==================================


#pragma once


//==================================
//�C���N���[�h
#include "objectX.h"
#include "enemycharacter.h"


//==========================================================
//�G�̃}�l�[�W���[�Ǘ��N���X
class CManagerEnemy : public CObjectX
{
public:
	CManagerEnemy(int nPriority = CObject::DEFAULT_PRIORITY);            //�����t���R���X�g���N�^
	~CManagerEnemy()override;                                            //�f�X�g���N�^
	HRESULT Init()override;                                              //����������
	void Uninit()override;                                               //�I������
	void Update() override;                                              //�X�V����
	void Draw()override;                                                 //�`�揈��
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type);  //��������
};


//==========================================================
//�G�̃N���X
class CEnemyX : public CManagerEnemy
{
public:
	CEnemyX(int nPriority = DEFAULT_PRIORITY1);        //�R���X�g���N�^
	~CEnemyX()override;                                //�f�X�g���N�^
	void Update()override;                             //�X�V����

private:
	//�}�N����`
	static constexpr  int MAX_LIFE = 1;                             //���C�t�̍ő�l
	static constexpr  int PLUS_SCORE = 1000;                        //���Z����X�R�A�l
	static constexpr  int MAX_BUULET_SPEED = 30;                    //�e�̑���
	static constexpr  int SET_BULLET_LIFE = 120;                    //���C�t�̍ő吔

	static constexpr  float COLLISION_RANGE_PLAYER = 65.0f;         //�v���C���[�Ƃ̓�����͈͂�ݒ�
	static constexpr  float MAX_SPPED = 2.0f;                       //�ړ����x
	static constexpr  float MAX_ENEMY_DAMAGE = 0.001f;              //�_���[�W��
	static constexpr  float MAX_FARME = 60.0f;                      //�t���[���̍ő吔
	static constexpr  float CREATE_BULLET_0_MINUS_POS_X = -250.0f;  //���߂ɐ��������e��X���̈ʒu�����Z����l
	static constexpr  float CREATE_BULLET_1_PLUS_POS_X = 350.0f;    //���ɐ��������e��X���̈ʒu�����Z����l
	static constexpr  float CREATE_BULLET_PLUS_POS_Y = 70.0f;       //���������e��Y���̈ʒu�����Z����l
	static constexpr  float EXPLOSION_EFFECT_PLUS_POS_Y = 50.0f;    //�����G�t�F�N�g��Y���̈ʒu�����Z����l
};


//==========================================================
//�G001�̃N���X
class CEnemy001X : public CManagerEnemy
{
public:
	CEnemy001X(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemy001X()override; 							//�f�X�g���N�^
	void Update()override;							//�X�V����


	//=======================
	//�}�N����`
	 static constexpr  int MAX_ENEMY001_LIFE = 3;                  //���C�t�̍ő�l
													               
private:											               
	//�}�N����`									                  
	 static constexpr  int PLUS_SCORE = 100;                       //�X�R�A�̉��Z�l
													               
	 static constexpr  float MAX_DAMAGE = 0.005f;                  //�v���C���[�ɗ^����_���[�W��
	 static constexpr  float PLUS_ROT_Y = 0.1f;                     //Y���̌��������Z����l
	 static constexpr  float EXPLOSION_EFFECT_PLUS_POS_Y = 50.0f;  //�����G�t�F�N�g��Y���̈ʒu�����Z����l
};


//==========================================================
//�G002�̃N���X
class CEnemy002X : public CManagerEnemy
{
public:
	CEnemy002X(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemy002X()override; 							//�f�X�g���N�^
	void Update()override;							//�X�V����
	void Move();                                    //�s������


	//=======================
	//�}�N����`
	 static constexpr  int MAX_ENEMY002_LIFE = 3;                  //���C�t�̍ő�l
													               
													               
private:											               
	//�}�N����`										              
	 static constexpr  int PLUS_SCORE = 200;                       //�X�R�A�̉��Z�l

	 static constexpr  float ATTACKPATTEN_FRAME_1 = 30.0f;	                      //���s�����̃t���[��
	 static constexpr  float ATTACKPATTEN_FRAME_2 = ATTACKPATTEN_FRAME_1 * 2.0f;  //���s�����̃t���[��
													               
	 static constexpr  float MAX_DAMAGE = 0.005f;                  //�v���C���[�ɗ^����_���[�W��
	 static constexpr  float PLUS_ROT_Y = 0.1f;                     //Y���̌��������Z����l
	 static constexpr  float ADJUST_POSY = 10.0f;                  //Y���̈ʒu�����Z����l
	 static constexpr  float EXPLOSION_EFFECT_PLUS_POS_Y = 50.0f;  //�����G�t�F�N�g��Y���̈ʒu�����Z����l
};
