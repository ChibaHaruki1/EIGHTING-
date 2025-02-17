//===================================
//
//�w�i�̏����ݒ�[bg.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "bg.h"
#include "rendererh.h"
#include "manager.h"
#include <time.h>


//==========================
//�����t���R���X�g���N�^
//==========================
CManagerBg::CManagerBg(int nPriority) : CObject2D(nPriority)
{
	SetAlph(CObject2D::N_INIT_ALPHA_NUMBER); //�A���t�@�l��ݒ�
}


//======================
//�R���X�g���N�^
//======================
CManagerBg::~CManagerBg()
{

}


//======================
//�w�i�̏���������
//======================
HRESULT CManagerBg::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK; //������Ԃ�
}


//======================
//�w�i�̏I������
//======================
void CManagerBg::Uninit(void)
{
	CObject2D::Uninit(); //�j���������Ă�
}


//=======================
//�w�i�̍X�V����
//=======================
void CManagerBg::Update()
{
	CMain::VERTEX_2D* pVtx; //�o�[�e�N�X�̃|�C���^�[

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	GetBuffer()->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());
	pVtx[1].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());
	pVtx[2].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());
	pVtx[3].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());

	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}


//=====================
//�w�i�̕`�揈��
//=====================
void CManagerBg::Draw()
{
	CObject2D::Draw(); //�`�揈�����Ă�
}


//===================================
//�I�u�W�F�N�g����
//===================================
CManagerBg* CManagerBg::Create(CScene::MODE mode)
{
	CManagerBg* pBg = nullptr; //���N���X�̃|�C���^�[

	//�^�C�g����
	if (mode == CScene::MODE::MODE_TITLE)
	{
		pBg = new CTitleBg(INIT_PRIORITY);                                //���I�m��
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Title001.png");   //�t�@�C���p�X��ݒ�
	}

	//���U���g��														     
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pBg = new CResultBg();                                            //���I�m��
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Result.png");     //�t�@�C���p�X��ݒ�
	}

	//���S��
	else if (mode == CScene::MODE::MODE_GAMEOVER)
	{
		pBg = new CGameOverBg();                                          //���I�m��
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\SCREEN\\GameOver.jpg");  //�t�@�C���p�X��ݒ�
	}

	//������������������
	if (SUCCEEDED(pBg->Init()))
	{
		pBg->Lood(); //�e�N�X�`���̓ǂݍ��݊֐����Ă�
		return pBg;  //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//================================================================================================================================================
//�^�C�g���w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CTitleBg::CTitleBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CTitleBg::~CTitleBg()
{

}


//================================================================================================================================================
//���U���g�w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CResultBg::CResultBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CResultBg::~CResultBg()
{

}


//================================================================================================================================================
//�Q�[���I�[�o�[�w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CGameOverBg::CGameOverBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CGameOverBg::~CGameOverBg()
{

}

//=================================
//�X�V����
//=================================
void CGameOverBg::Update()
{
	SetRandom(FIRST_NUMBER + rand() % MAX_RAND);  //�����𐶐�
	GetFrame()++;                                 //�t���[���𑝂₷

	//�t���[�����K�萔�ȏ�s������
	if (GetFrame() >= PROCESS_FRAME)
	{
		//===============================================
		//���ŕ����i�S���邩��S�����̒l�Ōv�Z�j
		//===============================================

		if (GetRandom() >= FIRST_NUMBER && GetRandom() <= MAX_RAND* ONE_QUARTER)
		{
			SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, FIRST_SIZE_Y, CMain::SCREEN_HEIGHT + FIRST_PLUS_SIZE1_Y); //�傫���̐ݒ�
			SetAlph(N_INIT_ALPHA_NUMBER);  //alpha�l�̏�����
			SetFrame(N_INIT_NUMBER);       //�t���[���̏�����
		}

		else if (GetRandom() >= MAX_RAND * ONE_QUARTER + NEXT_PLUS && GetRandom() <= MAX_RAND* TWO_QUARTER)
		{
			SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, -SECOND_SIZE1_Y, CMain::SCREEN_HEIGHT - SECOND_MINUS_SIZE1_Y); //�傫���̐ݒ�
			SetAlph(N_INIT_ALPHA_NUMBER);  //�A���t�@�l�̏�����
			SetFrame(N_INIT_NUMBER);       //�t���[���̏�����
		}

		else if (GetRandom() >= MAX_RAND * TWO_QUARTER + NEXT_PLUS && GetRandom() <= MAX_RAND* THREE_QUARTER)
		{
			SetSIze(-THIRD_SIZE_X, CMain::SCREEN_WIDTH - THIRD_MINUS_SIZE1_X, F_INIT_NUMBER, CMain::SCREEN_HEIGHT);
			SetAlph(ALPHA_0);          //�A���t�@�l��������
			SetFrame(N_INIT_NUMBER);   //�t���[���̏�����
		}

		else
		{
			SetSIze(FOURTH_SIZE_X, CMain::SCREEN_WIDTH + FOURTH_THIRD_PLUS_SIZE1_X, F_INIT_NUMBER, CMain::SCREEN_HEIGHT);
			SetAlph(ALPHA_1);          //�A���t�@�l��������
			SetFrame(N_INIT_NUMBER);   //�t���[���̏�����
		}
	}

	//�t���[�����K��l�ȏ�֍s������
	else if (GetFrame() >= ADJUSTMENT_FRAME)
	{
		SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, F_INIT_NUMBER, CMain::SCREEN_HEIGHT);  //�傫���̐ݒ�
	}

	SetCol(CObject2D::RED, CObject2D::GREEN, CObject2D::BLUE,GetAlph());                   //�F�ݒ肷��
}


//===========================================================================================================================================================
//SHOP���̔w�i�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CShopScreen::CShopScreen(int nPriority) : CManagerBg(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Screen\\Yellow.png"); //�t�@�C���p�X��ݒ�
}


//=======================
//�f�X�g���N�^
//=======================
CShopScreen::~CShopScreen()
{

}


//=======================
//����������
//=======================
HRESULT CShopScreen::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, F_INIT_NUMBER, CMain::SCREEN_HEIGHT); //�傫����ݒ�
	SetCol(RED, GREEN, BLUE, ALPHA);                                                             //�F�ݒ肷��

	return S_OK; //������Ԃ�
}


//========================
//�X�V����
//========================
void CShopScreen::Update()
{
	
}


//========================
//��������
//========================
CShopScreen* CShopScreen::Create()
{
	CShopScreen* pText = new CShopScreen(CObject2D::INIT_PRIORITY); //���I�m��

    //�������ɐ���������
	if (SUCCEEDED(pText->Init()))
	{
		pText->Lood(); //�e�N�X�`���̓ǂݍ���
		return pText;  //����Ԃ�
	}
	return nullptr;    //����Ԃ�
}
