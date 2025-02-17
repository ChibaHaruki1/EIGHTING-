//================================
//
//�G�̏���[enemy.cpp]
//Auther:Chiba Haruki
//
//================================


//================================
//�C���N���[�h
#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "player.x.h"


//=========================
//�R���X�g���N�^
//=========================
CManagerEnemy::CManagerEnemy(int Priority) : CObjectX(Priority)
{

}


//=========================
//�f�X�g���N�^
//=========================
CManagerEnemy::~CManagerEnemy()
{

}


//=========================
//����������
//=========================
HRESULT CManagerEnemy::Init()
{
	//�������ɐ���������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}


//=========================
//�I������
//=========================
void CManagerEnemy::Uninit()
{
	CObjectX::Uninit(); //�j������
}


//=========================
//�X�V����
//=========================
void CManagerEnemy::Update()
{
	
}

//==========================
//�`�揈��
//==========================
void CManagerEnemy::Draw()
{
	CObjectX::Draw(); //�`�揈��
}

//==========================
//3D���f���̓G�̍쐬
//==========================
CManagerEnemy* CManagerEnemy::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemy* pManagerEnemy = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���G�̎�
	if (type == TYPE::ENEMY)
	{
		pManagerEnemy = new CEnemyX(); //���I�m��

		//������������������
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\BattleShip000.x"); //�t�@�C���p�X�̐ݒ�
		}
	}

	//�^�C�v���G001�̎�
	else if (type == TYPE::ENEMY001)
	{
		pManagerEnemy = new CEnemy001X(); //���I�m��

		//������������������
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy001.x"); //�t�@�C���p�X�̐ݒ�(��)
			pManagerEnemy->SetLife(CEnemy001X::MAX_ENEMY001_LIFE);        //���C�t�̐ݒ�
		}
	}

	//�^�C�v���G001�̎�
	else if (type == TYPE::ENEMY002)
	{
		pManagerEnemy = new CEnemy002X(); //���I�m��

		//������������������
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy002.x"); //�t�@�C���p�X�̐ݒ�(��)
			pManagerEnemy->SetLife(CEnemy002X::MAX_ENEMY002_LIFE);        //���C�t�̐ݒ�
		}
	}

	//��񂪂��鎞
	if (pManagerEnemy != nullptr)
	{
		pManagerEnemy->SetPos(pos); //�ʒu�������Ɠ���������
		pManagerEnemy->Lood();      //X�t�@�C���̓ǂݍ���
		pManagerEnemy->Size();      //�T�C�Y�̎擾
		return pManagerEnemy;       //����Ԃ�
	}

	return nullptr;                 //����Ԃ�
}


//=====================================================================================================================================
//�G�̏���
//=====================================================================================================================================

//=========================
//�R���X�g���N�^
//=========================
CEnemyX::CEnemyX(int Priority) : CManagerEnemy(Priority)
{
	SetLife(MAX_LIFE);
}

//=========================
//�f�X�g���N�^
//=========================
CEnemyX::~CEnemyX()
{

}

//=========================
//�X�V����
//=========================
void CEnemyX::Update()
{
	//TargetHeadingTowards(CManager::GetScene()->GetPlayerX(),2.0f);  //�v���C���[�Ɍ����������֐����Ă�

	//�v���C���[�Ɠ���������
	if (CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER) == true)
	{
		SetAdjustFrame()++;         //�e�����ۂ̃t���[���𑝂₷

		//�t���[�����K��l��荂����
		if (GetFrame() >= MAX_FARME)
		{
			CManagerBullet::Create(D3DXVECTOR3(GetPos().x + CREATE_BULLET_0_MINUS_POS_X, GetPos().y + CREATE_BULLET_PLUS_POS_Y, GetPos().z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED),
				SET_BULLET_LIFE, CObject3D::TYPE::BATTLESHIPBULLET);

			CManagerBullet::Create(D3DXVECTOR3(GetPos().x + CREATE_BULLET_1_PLUS_POS_X, GetPos().y + CREATE_BULLET_PLUS_POS_Y, GetPos().z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED),
				SET_BULLET_LIFE, CObject3D::TYPE::BATTLESHIPBULLET);

			SetFrame(N_INIT_NUMBER); //�t���[���̏�����
		}
	}

	//���C�t���s������
	if (GetLife() <= N_INIT_NUMBER)
	{
		//�����G�t�F�N�g���Ăԁi1�ځj
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));

		//�����G�t�F�N�g���Ăԁi2�ځj
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));

		//�X�R�A�����Z
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);       

		CObjectX::Release(); //���g�̍폜
		return;              //�����𔲂���
	}

	CObjectX::Update();      //�X�V����
}


//=====================================================================================================================================
//�G001�̏���
//=====================================================================================================================================

//=========================
//�R���X�g���N�^
//=========================
CEnemy001X::CEnemy001X(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//�f�X�g���N�^
//=========================
CEnemy001X::~CEnemy001X()
{

}

//=========================
//�X�V����
//=========================
void CEnemy001X::Update()
{
	SetAdjustRot().y += PLUS_ROT_Y; //Y���̌��������Z

	//�v���C���[�Ɠ���������
	if (CollisionPlayerSelect(this) == true)
	{
		//�v���C���[��HP�����
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * CManagerBossEffect::MAX_DAMAGE;
	}

	//���C�t���s������
	if (GetLife() <= N_INIT_NUMBER)
	{
		//�����G�t�F�N�g���Ă�
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE); //�X�R�A�����Z
		CObjectX::Release();                                           //���g�̍폜
		return;                                                        //�����𔲂���
	}
}


//=====================================================================================================================================
//�G002�̏���
//=====================================================================================================================================

//=========================
//�R���X�g���N�^
//=========================
CEnemy002X::CEnemy002X(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//�f�X�g���N�^
//=========================
CEnemy002X::~CEnemy002X()
{

}

//=========================
//�X�V����
//=========================
void CEnemy002X::Update()
{
	SetAdjustRot().x += PLUS_ROT_Y; //Y���̌��������Z

	Move();                        //�s�������֐����Ă�

	//�v���C���[�Ɠ���������
	if (CollisionPlayerSelect(this) == true)
	{
		//�v���C���[��HP�����
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * CManagerBossEffect::MAX_DAMAGE;
	}

	//���C�t���s������
	if (GetLife() <= N_INIT_NUMBER)
	{
		//�����G�t�F�N�g���Ă�
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));

		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE); //�X�R�A�����Z
		CObjectX::Release();                                           //���g�̍폜
		return;                                                        //�����𔲂���
	}
}


//=========================
//�s������
//=========================
void CEnemy002X::Move()
{
	SetAdjustFrame()++; //�t���[���𑝂₷

	//���s��
	if (GetFrame() <= ATTACKPATTEN_FRAME_1)
	{
		SetAdjustPos().y += ADJUST_POSY; //Y���̈ʒu�����Z
	}

	//���s��
	else if (GetFrame() <= ATTACKPATTEN_FRAME_2)
	{
		SetAdjustPos().y -= ADJUST_POSY; //Y���̈ʒu�����Z
	}

	//�I��
	else
	{
		SetFrame(N_INIT_NUMBER);         //�t���[���̏�����
	}
}