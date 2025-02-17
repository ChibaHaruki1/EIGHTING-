//===================================
//
//�w�i�̃N���X�Ǘ�[bg.h]
//Author:chiba haruki
//
//===================================


#pragma once


//===================================
//�C���N���[�h
#include "object2D.h"
#include "scene.h"


//==================================================================
//�w�i�̊Ǘ����N���X
class CManagerBg : public CObject2D
{
public:
	CManagerBg(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerBg()override;						   //�f�X�g���N�^
	HRESULT Init()override;						   //����������
	void Uninit()override;						   //�j������
	void  Update()override;						   //�X�V����
	void Draw()override;						   //�`�揈��

	static CManagerBg* Create(CScene::MODE mode);  //��������
};


//==================================================================
//�^�C�g���w�i
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);    //�R���X�g���N�^
	~CTitleBg()override;                           //�f�X�g���N�^
};


//==================================================================
//���U���g�w�i
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);   //�R���X�g���N�^
	~CResultBg()override;                          //�f�X�g���N�^
};


//==================================================================
//�Q�[���I�[�o�[�w�i
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CGameOverBg()override;                         //�f�X�g���N�^
	void Update()override;                          //�X�V����

private:
	static constexpr  int MAX_RAND = 100;           //�����̍ő吔
	static constexpr  int PROCESS_FRAME = 50;       //�������s���t���[����
	static constexpr  int ADJUSTMENT_FRAME = 20;    //�������s���t���[����

	static constexpr  int FIRST_NUMBER = 1;         //�ŏ��̔ԍ�

	static constexpr int ALPHA_0 = 155;             //�O�Ԗڂ̃A���t�@�l�̒l
	static constexpr int ALPHA_1 = 55;              //�P�Ԗڂ̃A���t�@�l�̒l

	static constexpr double ONE_QUARTER = 0.25;     //�S�iQUARTER�j���̂P�iONE�j
	static constexpr double TWO_QUARTER = 0.5;      //�S�iQUARTER�j���̂Q�iTWO�j
	static constexpr double THREE_QUARTER = 0.75;   //�S�iQUARTER�j���̂R�iTHREE�j
	static constexpr double NEXT_PLUS = 1;          //���̐����ֈڍs����ׂ̒l

	static constexpr float FIRST_SIZE_Y = 100.0f;                //���s���̂P�ڂ�Y���̒l
	static constexpr float FIRST_PLUS_SIZE1_Y = 100.0f;          //���s���̂Q�ڂ�Y���̒l�����Z����l
	static constexpr float SECOND_SIZE1_Y = 100.0f;              //���s���̂P�ڂ�Y���̒l
	static constexpr float SECOND_MINUS_SIZE1_Y = 100.0f;        //���s���̂Q�ڂ�Y���̒l�����Z����l
	static constexpr float THIRD_SIZE_X = 200.0f;                //��O�s���̂P�ڂ�X���̒l
	static constexpr float THIRD_MINUS_SIZE1_X = 200.0f;         //��O�s���̂Q�ڂ�X���̒l�����Z����l
	static constexpr float FOURTH_SIZE_X = 200.0f;               //��l�s���̂P�ڂ�X���̒l
	static constexpr float FOURTH_THIRD_PLUS_SIZE1_X = 200.0f;   //��l�s���̂Q�ڂ�X���̒l�����Z����l
};


//==================================================================
//�V���b�v���̔w�i
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CShopScreen()override;                         //�f�X�g���N�^
	HRESULT Init()override;                         //����������
	void Update()override;                          //�X�V����

	static CShopScreen* Create();                   //��������

private:
	static constexpr  int RED = 255;          //�ԐF
	static constexpr  int GREEN = 255;        //�ΐF
	static constexpr  int BLUE = 255;         //�F
	static constexpr  int ALPHA = 50;         //�A���t�@�l
};