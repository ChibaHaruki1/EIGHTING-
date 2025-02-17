//=======================================
//
//�Q�[�W�Ɋւ��鏈��[gage.cpp]
//Ajther:Haruki Chiba
//
//=======================================


//===========================
//�C���N���[�h
#include "gage.h"
#include "manager.h"


//=======================================================================================================================================================
//�R���Q�[�W�̏���
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CFuelGage::CFuelGage(int nPriority) : CObject3D(nPriority)
{
	SetSizeY(MAX_SIZEY); //Y���̑傫���̐ݒ�
	m_bUse = false;      //�g���Ă��Ȃ��ɐݒ�
	m_bCharge = false;   //�Q�[�W�����܂��Ă��Ȃ��ɐݒ�
}

//===========================
//�f�X�g���N�^
//===========================
CFuelGage::~CFuelGage()
{
	
}

//===========================
//����������
//===========================
HRESULT CFuelGage::Init()
{
	//�����������s������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	
	CObject3D::SetSize(MAX_SIZEX, GetSizeY(), MAX_SIZEZ); //�傫����ݒ�

	return S_OK;										  //������Ԃ�
}

//============================
//�j������
//============================
void CFuelGage::Uninit()
{
	CObject3D::Uninit(); //�j������
}

//============================
//�X�V����
//============================
void CFuelGage::Update()
{
	//�ʒu��ݒ�
	SetPos(D3DXVECTOR3(CManager::GetScene()->GetPlayerX()->GetPos().x - ADJUST_POSX,
		CManager::GetScene()->GetPlayerX()->GetPos().y + ADJUST_POSY,
		CManager::GetScene()->GetPlayerX()->GetPos().z));


	CObject3D::SetAdjustmentSizeY(MAX_SIZEX, GetSizeY(), MAX_SIZEZ);                  //Y���p�̑傫����ݒ�
	CObject3D::SetCol(CObject3D::RED, CObject3D::GREEN, CObject3D::BLUE, GetAlpha()); //�F�̐ݒ�

	//�g���Ă��鎞�ƃQ�[�W�����^���̎�
	if (m_bUse == true && m_bCharge == true)
	{
		CManager::GetScene()->GetPlayerX()->GetMove().y += MAX_PLUS_PLAYER_MOVE;      //�v���C���[�̂⎲�̈ړ��ʂ𑝂₷

		//�v���C���[�̏d�͂��K��l��荂����
		if (CManager::GetScene()->GetPlayerX()->GetGravity() > MAX_PLAYER_GRAVITY)
		{
			CManager::GetScene()->GetPlayerX()->SetGravity(MAX_PLAYER_GRAVITY);       //�d�͂̐ݒ�
		}

		CManager::GetScene()->GetPlayerX()->SetGravityFlag(false);                    //�d��OFF

		//�A���t�@�l���K��l�ȊO�̎�
		if (GetAlpha() != MAX_ALPHA)
		{
			SetAlpha(MAX_ALPHA);                       //�A���t�@�l�̐ݒ�
		}

		//Y���̃T�C�Y���ŏ��l��荂����
		if (GetSizeY() > MIN_SIZEY)
		{
			SetAddjustSizeY() -= MAX_MAINAS_GAGESPEED; //Y���̑傫�������炷
		}
		else
		{
			SetSizeY(MIN_SIZEY);                       //Y���̑傫����������
			m_bCharge = false;                         //�`���[�W������
			m_bUse = false;                            //���g�p
		}
	}

	//�g���Ă��Ȃ���
	if (m_bUse == false)
	{
		//�A���t�@�l���O�ȏ�̎�
		if (GetAlpha() > 0)
		{
			SetAdjustAlpha() -= MINUS_ALPHA;          //�A���t�@�l�����炷
		}

		//Y���̃T�C�Y���ő�l���Ⴂ
		if (GetSizeY() < MAX_SIZEY)
		{
			SetAddjustSizeY() += MAX_PLUS_GAGESPEED;   //Y���̑傫���𑝂₷
		}
	}

	//�`���[�W�������̎�
	if (m_bCharge == false)
	{
		CManager::GetScene()->GetPlayerX()->SetGravityFlag(true); //�d��ON

		//Y���̑傫�����K��l��菬������
		if (GetSizeY() < MAX_SIZEY)
		{
			SetAddjustSizeY() += MAX_PLUS_GAGESPEED;              //Y���̑傫���𑝂₷
		}

		//Y���̑傫�����K��l�ȏ�̎�
		else if (GetSizeY() >= MAX_SIZEY)
		{
			m_bCharge = true;                                     //�`���[�W����
		}
	}

	CObject3D::Update();                                          //�X�V�������Ă�
}


//============================
//�`�揈��
//============================
void CFuelGage::Draw()
{
	CObject3D::Draw(); //�`�揈�����Ă�
}

//============================
//��������
//============================
CFuelGage* CFuelGage::Create()
{
	CFuelGage* pFuelGage = new CFuelGage(); //���I�m��

	//��񂪂��鎞
	if (pFuelGage != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pFuelGage->Init()))
		{
			pFuelGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage000.png"); //�t�@�C���p�X�̐ݒ�
			pFuelGage->Lood();                                                     //�e�N�X�`���̓ǂݍ���
			return pFuelGage;                                                      //����Ԃ�
		}
	}

	return nullptr;                                                                //����Ԃ�
}


//=======================================================================================================================================================
//�Q�[�W�}�l�[�W���[����
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CManagerGage::CManagerGage(int nPriority) : CObject2D(nPriority)
{
	m_fHPSizeX = MAX_PLAYER_HP_SIZE;       //�v���C���[��HP�̐ݒ�
	m_fBossHPSizeX = CMain::SCREEN_WIDTH;  //�{�X��HP�̐ݒ�
	m_fSaveSizeX = CObject3D::F_INIT_NUMBER;          //�Z�[�uHP�̐ݒ�
}

//===========================
//�f�X�g���N�^
//===========================
CManagerGage::~CManagerGage()
{

}

//===========================
//����������
//===========================
HRESULT CManagerGage::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}

//======================
//�I������
//======================
void CManagerGage::Uninit(void)
{
	CObject2D::Uninit(); //�j���������Ă�
}


//=======================
//�X�V����
//=======================
void CManagerGage::Update()
{
	
}


//=====================
//�`�揈��
//=====================
void CManagerGage::Draw()
{
	CObject2D::Draw(); //�`�揈�����Ă�
}


//===================================
//�Q�[�W�̐���
//===================================
CManagerGage* CManagerGage::Create(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���v���C���[��HP�̎�
	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGage(CRETAE_PRIORITY);                                                       //���I�m��
		CreateLeave(type);                                                                                       //�c��HP�Q�[�W�̐���
		CManager::GetInstance()->GetCreateObjectInstnace(TYPE::FUELGAGE, CObject3D::N_INIT_NUMBER, pManagerGage->GetPos());  //�R���Q�[�W�̐���
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage000.png");                                //�t�@�C���p�X�̐ݒ�
	}

	//�^�C�v���{�X��HP�̎�
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGage(CRETAE_PRIORITY);                                                         //���I�m��
		CreateLeave(type);                                                                                       //�c��HP�Q�[�W�̐���
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\BossHpGage.png");                                //�t�@�C���p�X��ݒ�
	}

	//��񂪂��鎞
	if (pManagerGage != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pManagerGage->Init()))
		{
			pManagerGage->Lood(); //�e�N�X�`���̓ǂݍ���
			return pManagerGage;  //����Ԃ�
		}
	}

	return nullptr;               //����Ԃ�
}

//===================================
//�c���Q�[�W�̐���
//===================================
CManagerGage* CManagerGage::CreateLeave(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���v���C���[��HP�̎�
	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGageLeave(CRETAE_LEAVE_PRIORITY);                //���I�m��
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage001.png");    //�t�@�C���p�X�̐ݒ�
	}

	//�^�C�v���{�X��HP�̎�
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGageLeave(CRETAE_LEAVE_PRIORITY);                  //���I�m��
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\BloackGage000.png"); //�t�@�C���p�X�̐ݒ�
	}

	//��񂪂��鎞
	if (pManagerGage != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pManagerGage->Init()))
		{
			pManagerGage->Lood(); //�e�N�X�`���̓ǂݍ���
			return pManagerGage;  //����Ԃ�
		}
	}

	return nullptr;               //����Ԃ�
}


//=======================================================================================================================================================
//�v���C���[�̃Q�[�W�̏���
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CPlayerHPGage::CPlayerHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX(); //�v���C���[��HP�̑傫���̐ݒ�
}

//===========================
//�f�X�g���N�^
//===========================
CPlayerHPGage::~CPlayerHPGage()
{

}

//===========================
//����������
//===========================
HRESULT CPlayerHPGage::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetPlayerHPSizeX(), SIZE_Y, SIZE_Y1); //�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�

	return S_OK;       //������Ԃ�
}

//===========================
//�X�V����
//===========================
void CPlayerHPGage::Update()
{
	//���݂�HP�Q�[�W��荂����
	if (m_fSaveSizeX > GetPlayerHPSizeX())
	{
		m_fSaveSizeX -= MINUS_HPSIZEX;       //���X��HP�Q�[�W�����炷
	}

	//���݂�HP�Q�[�W���Ⴂ��
	else if (m_fSaveSizeX <= GetPlayerHPSizeX())
	{
		m_fSaveSizeX = GetPlayerHPSizeX();   //���݂�HP�Q�[�W�Ɠ���������
	}

	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, m_fSaveSizeX, MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z); //���炩�Ɍ����Ă���悤�Ɍ�����
}


//=======================================================================================================================================================
//�{�X�̃Q�[�W�̏���
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CBossHPGage::CBossHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetBossHPSizeX(); //�{�X��HP�̑傫���̐ݒ�
}

//===========================
//�f�X�g���N�^
//===========================
CBossHPGage::~CBossHPGage()
{

}


//===========================
//����������
//===========================
HRESULT CBossHPGage::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�
	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetBossHPSizeX(), (CMain::SCREEN_HEIGHT - ADJUST_POSY), CMain::SCREEN_HEIGHT);

	return S_OK;       //������Ԃ�
}

//===========================
//�X�V����
//===========================
void CBossHPGage::Update()
{
	//���݂�HP�Q�[�W��荂����
	if (m_fSaveSizeX > GetBossHPSizeX())
	{//���炳�ꂽ���������炷
		m_fSaveSizeX -= MINUS_HPSIZEX;   //���X��HP�Q�[�W�����炷
	}

	//���݂�HP�Q�[�W��菬������
	else if (m_fSaveSizeX <= GetBossHPSizeX())
	{
		m_fSaveSizeX = GetBossHPSizeX(); //���݂�HP�Q�[�W�Ɠ���������
	}

	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, m_fSaveSizeX, (CMain::SCREEN_HEIGHT + MINUS_SIZE_X1), CMain::SCREEN_HEIGHT); //���炩�Ɍ����Ă���悤�Ɍ�����
}


//=======================================================================================================================================================
//�v���C���[��HP�Q�[�W���c������
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CPlayerHPGageLeave::CPlayerHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX(); //�v���C���[��HP�̑傫���̐ݒ�
}

//===========================
//�f�X�g���N�^
//===========================
CPlayerHPGageLeave::~CPlayerHPGageLeave()
{

}


//===========================
//����������
//===========================
HRESULT CPlayerHPGageLeave::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�
	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetPlayerHPSizeX(), MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z);

	return S_OK;       //������Ԃ�
}


//=======================================================================================================================================================
//�{�X��HP�Q�[�W���c������
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CBossHPGageLeave::CBossHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = CObject3D::N_INIT_NUMBER; //HP�̏�����
}

//===========================
//�f�X�g���N�^
//===========================
CBossHPGageLeave::~CBossHPGageLeave()
{

}


//===========================
//����������
//===========================
HRESULT CBossHPGageLeave::Init()
{
	//�����������s���邩����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�
	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetBossHPSizeX(), (CMain::SCREEN_HEIGHT + CBossHPGage::MINUS_SIZE_X1), CMain::SCREEN_HEIGHT);

	return S_OK;       //������Ԃ�
}