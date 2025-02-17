//=======================================
//
//�X�R�A�̃N���X�Ǘ�[score.h]
//Author:chiba haruki
//
//=======================================

#pragma once

//=======================================
//�C���N���[�h
#include "object2D.h"
#include "scene.h"


//============================================================
//�X�R�A�̊Ǘ��N���X
class CManagerScore : public CObject2D
{
public://�O������̃A�N�Z�X�\

	//�e�\���̂̒�`
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		bool bUse;       //�g�p���Ă��邩�ǂ���
	}Score;

	CManagerScore(int nPriority = DEFAULT_PRIORITY);               //�R���X�g���N�^
	~CManagerScore()override;                                      //�f�X�g���N�^
	 HRESULT Init()override;                                       //������
	 void Uninit()override;                                        //�I������
	 void Update() override;                                       //�X�V����
	 void Draw()override;                                          //�`�揈��
	 void SetScorepos(D3DXVECTOR3 pos);                            //�X�R�A�̈ʒu�ݒ菈��
	 void SetScore(int nScore);                                    //�X�R�A�̐ݒ菈��
	 void AddScore(int nValue);                                    //�X�R�A�̃J�E���g��������
	 void InitAddScore(int nValue);                                //�X�R�A�̃J�E���g��������
	 void PosScore(void);                                          //�X�R�A�̐ݒ菈��
	 static  CManagerScore* Create(CScene::MODE mode, int Number); //�X�R�A�̐�������

	 //�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	  static constexpr  int MAX_SCORE = 10;             //�X�R�A�̍ő吔
	  static constexpr  float DIVISION_SCORE = 0.1f;    //�X�R�A�̍ő吔
	  static constexpr  int DIGIT = 10;                 //���Ǘ��p
	  static constexpr  int MAX_SIZE_X = 20;            //�X�R�A��X���̑傫��
	  static constexpr  int MAX_SIZE_Y = 40;            //�X�R�A��Y���̑傫��
	  static constexpr  int MAX_TEXTURE_SIZEX = 10;     //�X�R�A��X���̑傫��
	  static constexpr  float FMAX_SCORE = 10.0f;       //�X�R�A�̍ő吔(float�^)
	  static constexpr  float PLUSSCORE_POSX = 40.0f;   //�X�R�A��X���̑���������l
	  static constexpr  float CORE_POSX = 900.0f;       //�X�R�A��X���̈ʒu
	  static constexpr  float CORE_POS1X = 40.0f;       //�X�R�A��X���̈ʒu
	  static constexpr  float SCORE_POSY = 40.0f;       //�X�R�A��Y���̈ʒu

private:
	//�}�N����`
	static constexpr int MOVE_PVTX = 4;             //�o�[�e�N�X�̈ړ��l
	static constexpr int INIT_DIGIT = 1;            //���Ǘ��p�̏����l
	static constexpr int BEFORE_DIGIT = 1;          //�O�̌�

	static constexpr float ADJUST_TEX_POS_X = 1.0f; //�e�N�X�`����X���̈ʒu�̒����l
	static constexpr float ADJUST_TEX_POS_Y = 1.0f; //�e�N�X�`����Y���̈ʒu�̒����l

	Score m_aScore[MAX_SCORE];                      //�X�R�A�̏��
	int m_nSocre;                                   //�X�R�A�̒l��ۊǂ���p
	float m_fPosX;                                  //�X�R�A�̏������ʒu(x)�̍X�V
	float m_fPosY;                                  //�X�R�A�̏������ʒu(x)�̍X�V
};


//============================================================
//�Q�[���X�R�A
class CGameScore : public CManagerScore
{
public:
	CGameScore(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CGameScore()override;                         //�f�X�g���N�^
};


//============================================================
//���U���g�X�R�A�N���X
class CResultScore : public CManagerScore
{
public:
	CResultScore(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CResultScore()override;                         //�f�X�g���N�^
};
