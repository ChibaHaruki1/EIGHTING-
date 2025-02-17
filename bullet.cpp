//==================================
//
//�e�̏���[bullet.h]
//Auther:Chiba Haruki
//
//==================================


//==================================
//�C���N���[�h
#include "main.h"
#include "manager.h"
#include "bullet.h"


//==============================================================================================================
//==================================================3D�e�̏���==================================================
//==============================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CManagerBullet::CManagerBullet(int nPriority) :CObject3D(nPriority)
{

}

//=====================
//�f�X�g���N�^
//=====================
CManagerBullet::~CManagerBullet()
{

}


//=====================
//����������
//=====================
HRESULT CManagerBullet::Init()
{
	//�������Ɏ��s�����Ƃ�
	if (FAILED(CObject3D::BillboardInit())) 
	{
		return E_FAIL; //���s��Ԃ�
	}

	SetRot(D3DXVECTOR3(CObject3D::F_INIT_NUMBER, INIT_ROTY, CObject3D::F_INIT_NUMBER)); //������ݒ�
	SetSizeX(MAX_BULLET3D_SIZE_X);                                //X���̑傫���̐ݒ�
	SetSize(GetSizeX(), MAX_BULLET3D_SIZE_Y, CObject3D::F_INIT_NUMBER);      //�T�C�Y�̒���
	return S_OK;                                                  //������Ԃ�
}


//=====================
//�I������
//=====================
void CManagerBullet::Uninit()
{
	CObject3D::Uninit();  //���N���X�̔j������
}


//=====================
//�X�V����
//=====================
void CManagerBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, CObject3D::CObject3D::N_INIT_NUMBER, GetPos());             //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                                                            //�G�t�F�N�g�̃��C�t�̐ݒ�
	CManager::GetInstance()->GetEffect()->SetCol(CObject3D::N_INIT_ALPHA_NUMBER, GREEN, CObject3D::CObject3D::N_INIT_NUMBER, GetAlpha()); //�F�̐ݒ�

	//�A���t�@�l���O���傫����
	if (GetAlpha() > CObject3D::N_INIT_NUMBER)
	{
		SetAdjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z����
	}

	SetAdjustLife()--; //���C�t�����炷

	//�������s����
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		//CallEffect(false);
		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@
}


//=====================
//�`�揈��
//=====================
void CManagerBullet::Draw()
{
	CObject3D::DrawBillboard(); //�`�揈�����Ă�
}


//====================
//�e�̈ʒu�̐ݒ菈��
//====================
void CManagerBullet::SetInfo(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	SetPos(pos);    //�e�̈ʒu�������Ɠ�������
	SetMove(move);  //�e�̈ړ��ʂ������Ɠ�������
	SetLife(nLife); //������ݒ肷��
}


//=========================
//�e�̐���
//=========================
CManagerBullet* CManagerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject::TYPE type)
{
	CManagerBullet* pBullet3D = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���e�̎�
	if (type == CObject3D::TYPE::BULLET)
	{
		pBullet3D = new CBullet3D(); //���I�m��

		//������������������
		if (SUCCEEDED(pBullet3D->Init()))
		{

		}
	}

	//�^�C�v���G�̒e�̎�
	else if (type == CObject3D::TYPE::ENEMYBULLET)
	{
		pBullet3D = new CEnemyBullet(); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CEnemyBullet::MAX_ENEMYBULLET_SIZE_X, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Y, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Z); //�T�C�Y�̐ݒ�
		}
	}

	//�^�C�v����͂̒e�̎�
	else if (type == CObject3D::TYPE::BATTLESHIPBULLET)
	{
		pBullet3D = new CEnemyBulletBattleShip(); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CEnemyBullet::MAX_ENEMYBULLET_SIZE_X, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Y, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Z); //�T�C�Y�̐ݒ�
		}
	}

	//�^�C�v���{�X�̒e�̎�
	else if (type == CObject3D::TYPE::BOSSBULLET)
	{
		pBullet3D = new CBossBullet(); //���I�m��

		//������������������
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CBossBullet::MAX_BOSSBULLET_SIZE_X, CBossBullet::MAX_BOSSBULLET_SIZE_Y, CBossBullet::MAX_BOSSBULLET_SIZE_Z);      //�T�C�Y�̐ݒ�
		}
	}

	//���𖳂���
	if (pBullet3D != nullptr)
	{
		pBullet3D->SetFileNamePass("data\\TEXTURE\\bullet001.png"); //�t�@�C���p�X��ݒ�
		pBullet3D->SetInfo(pos, move, nLife);                       //�e�̏��������Ɠ���
		pBullet3D->Lood();                                          //�e�N�X�`���̓ǂݍ���
		return pBullet3D;                                           //���𖳂���
	}

	return nullptr;                                                 //����Ԃ�
}


//================================================================================================================================================
//�v���C���[�̒ʏ�e����
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CBullet3D::CBullet3D(int nPriority) : CManagerBullet(nPriority)
{

}

//======================
//�R���X�g���N�^
//======================
CBullet3D::~CBullet3D()
{

}

//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CBullet3D::CallEffect(bool bUse)
{
	//�����G�t�F�N�g�𐶐��i1�ځj
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION,CObject3D::N_INIT_NUMBER, GetPos());

	//�����G�t�F�N�g�𐶐��i2�ځj
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, GetPos());
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //���G�t�F�N�g���Ă�
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //�j�ЃG�t�F�N�g���Ă�


	//CManager::GetInstance()->GetExplosion()->SetEffect(GetPos());    //�����G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetExplosion001()->SetEffect(GetPos()); //�����G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetThander()->SetEffect(GetPos());      //���G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetDebris()->SetEffect(GetPos());       //�j�ЃG�t�F�N�g�̈ʒu��ݒ�
}

//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CBullet3D::CollisionOnObject()
{
	int SaveEnemy001Count = CManager::GetInstance()->GetEnemy001Count() + CREATE_PLUS_NUMBER;               //�G001�̐��������擾
	int SaveEnemy002Count = CManager::GetInstance()->GetEnemy002Count() + CREATE_PLUS_NUMBER;               //�G002�̐��������擾
	int SaveCameraUP = CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() + CREATE_PLUS_NUMBER;     //�J�����̏�̐��������擾
	int SaveMotionEnemy001Count = CManager::GetInstance()->GetMotionInEnemy001Count() + CREATE_PLUS_NUMBER; //���[�V�����t���̓G001�̐��������擾


	//�G001�̍��ꂽ������
	for (int nCount1 = CObject3D::N_INIT_NUMBER; nCount1 < SaveEnemy001Count; nCount1++)
	{
		//�G001�̏�񂪂��鎞
		if (CManager::GetInstance()->GetEnemy001(nCount1) != nullptr)
		{
			//�����蔻��
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy001(nCount1)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy001(nCount1)->GetModelSize() * ADJUST_ENEMY001_HIT, GetSizeX()) == true)
			{
				CManager::GetInstance()->GetEnemy001(nCount1)->SetAdjustLife() -= MINUS_ENEMY001_LIFE;          //�G�̃��C�t�����炷

				//�G�̃��C�t���O�ȉ��̎�
				if (CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() <= CObject3D::N_INIT_NUMBER)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY001, nCount1);        //�|�C���^�[��nullptr�ɂ���
				}

				CallEffect(false);      //�G�t�F�N�g�������Ă�
				SetLife(CObject3D::N_INIT_NUMBER); //���C�t���O�ɂ���
				return;                 //�����𔲂���
			}
		}
	}

	//�G002�̍��ꂽ������
	for (int nCount2 = CObject3D::N_INIT_NUMBER; nCount2 < SaveEnemy002Count; nCount2++)
	{
		//�G002�̏�񂪂��鎞
		if (CManager::GetInstance()->GetEnemy002(nCount2) != nullptr)
		{
			//�����蔻��
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy002(nCount2)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy002(nCount2)->GetModelSize() * ADJUST_ENEMY002_HIT, GetSizeX()) == true)
			{
				CManager::GetInstance()->GetEnemy002(nCount2)->SetAdjustLife() -= MINUS_ENEMY001_LIFE;          //�G�̃��C�t�����炷

				//�G�̃��C�t���O�ȉ��̎�
				if (CManager::GetInstance()->GetEnemy002(nCount2)->GetLife() <= CObject3D::N_INIT_NUMBER)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY002, nCount2);         //�|�C���^�[��nullptr�ɂ���
				}

				CallEffect(false);       //�G�t�F�N�g�������Ă�
				SetLife(CObject3D::N_INIT_NUMBER);  //���C�t���O�ɂ���
				return;                  //�����𔲂���
			}
		}
	}

	
	//�J�����̏㕔���̍��ꂽ������
	for (int nCamera = CObject3D::N_INIT_NUMBER; nCamera < SaveCameraUP; nCamera++)
	{
		//�J�����̏㕔���̏�񂪂��鎞
		if (CManager::GetInstance()->GetSurveillanceCameraUp(nCamera) != nullptr)
		{
			//�J�����Ƃ̓����蔻��
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetSurveillanceCameraUp(nCamera)->GetPos(),
				MAX_BULLET3D_SIZE_X * ADJUST_HIT_CAMERA_UP, MAX_BULLET3D_SIZE_Y * ADJUST_HIT_CAMERA_UP, MAX_BULLET3D_SIZE_Z * ADJUST_HIT_CAMERA_UP,
				CManager::GetInstance()->GetSurveillanceCameraUp(nCamera)->GetModelSize()))
			{
				CManager::GetInstance()->GetSurveillanceCameraUp(nCamera)->Release();                        //�J�����̏㕔���̍폜
				CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SURVEILLANCECAMERAUP, nCamera);  //�J�����|�C���^�[��nullptr�ɂ���

				//���[�U�[�̏�񂪂��鎞
				if (CManager::GetInstance()->GetLaser(nCamera) != nullptr)
				{
					CManager::GetInstance()->GetLaser(nCamera)->Release();                                   //���[�U�[������
					CManager::GetInstance()->DesignationUninit3D(CObject3D::TYPE::LASER, nCamera);           //���[�U�[�|�C���^�[��nullptr�ɂ���
				}

				SetLife(CObject3D::N_INIT_NUMBER); //���C�t���O�ɂ���
				return;                 //�����𔲂���
			}
		}
	}

	
	//���[�V�����t���̓G��001�̍��ꂽ������
	for (int nMotionInEnemy001 = CObject3D::N_INIT_NUMBER; nMotionInEnemy001 < SaveMotionEnemy001Count; nMotionInEnemy001++)
	{
		//���[�V�����t���̓G001�̏�񂪂��鎞
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			//�p�[�c������
			for (int nMotionEnemy001 = CObject3D::N_INIT_NUMBER; nMotionEnemy001 < CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetEnemy001PartsNumber(); nMotionEnemy001++)
			{
				//���[�V�����t���̓G001�̓����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPartsEnemy(nMotionEnemy001),
					GetSizeX(), MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePartsEnemy(nMotionEnemy001) * ADJUST_HIT_MOTIONENENY001))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->SetAdjustLife() -= MINUS_ENEMYMOTION001_LIFE; //���C�t�����炷

					//D3DXVECTOR3 Pos = CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(nMotionEnemy001);

					//���S������
					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= CObject3D::N_INIT_NUMBER)
					{
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //�|�C���^�[��nullptr�ɂ���
					}

					CallEffect(false);       //�G�t�F�N�g�������Ă�
					SetLife(CObject3D::N_INIT_NUMBER);  //���C�t���O�ɂ���
					return;                  //�����𔲂���
				}
			}
		}
	}

	//�{�X�̏�񂪂��鎞
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		//�{�X�̍ő�p�[�c������
		for (int nCount2 = CObject3D::N_INIT_NUMBER; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//�p�[�c�̕`�悪����Ă��鎞
			if (CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->GetDraw() == true)
			{
				//�{�X�Ƃ̓����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPartsBoss(nCount2),
					MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetBoss()->GetModelSizePartsBoss(nCount2), GetSizeX(), nCount2))
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= CMain::SCREEN_WIDTH * MINUS_BOSS_HPGAGE; //�{�X��HP�Q�[�W�����炷

					//�w���parts��`�悵�Ȃ��{��������O�������ɂ���(�E���S��)
					if (nCount2 == BOSS_PARTS_RIGHT_THIGHS || nCount2 == BOSS_PARTS_RIGHT_KNEES || nCount2 == BOSS_PARTS_RIGHT_FOOT)
					{
						CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->SetDraw(false); //�`������Ȃ��ɐݒ�
					}

					CallEffect(false);       //�G�t�F�N�g�������Ă�
					CObject3D::Release();    //���g�̉��
					return;                  //�����𔲂���
				}
			}
		}
	}
}


//======================================================================================================================================================================
//�G�̒e�̏���
//======================================================================================================================================================================

//static�ϐ��̏�����
float CEnemyBullet::m_fAdditionPosY = PLUS_ROT_Y; //�ʒu�������ݒ�

//=====================
//�R���X�g���N�^
//=====================
CEnemyBullet::CEnemyBullet(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//�f�X�g���N�^
//=====================
CEnemyBullet::~CEnemyBullet()
{

}


//=====================
//�X�V����
//=====================
void CEnemyBullet::Update()
{
	//�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, CObject3D::N_INIT_NUMBER, GetPos());

	//�G�t�F�N�g�̃��C�t�̐ݒ�
	CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                                               

	//�F�̐ݒ�
	CManager::GetInstance()->GetEffect()->SetCol(CObject3D::N_INIT_NUMBER, CObject3D::N_INIT_NUMBER, BLUE, GetAlpha());    

	SetAdjustPos().y -= m_fAdditionPosY; //Y���̈ʒu�����炷

	//�A���t�@�l��0���傫����
	if (GetAlpha() > CObject3D::N_INIT_NUMBER)
	{
		SetAdjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z
	}

	SetAdjustLife()--; //�����J�E���g

	//�������s����
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CEnemyBullet::CallEffect(bool bUse)
{

}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CEnemyBullet::CollisionOnObject()
{
	//�v���C���[�̃p�[�c������
	for (int nCount2 = CObject3D::N_INIT_NUMBER; nCount2 < CObjectX::MAX_PARTS; nCount2++)
	{
		//�v���C���[�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosParts(nCount2),
			MAX_BULLET3D_SIZE_X * ADJUST_HIT, MAX_BULLET3D_SIZE_Y * ADJUST_HIT, CObject3D::F_INIT_NUMBER,
			CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount2), CObject3D::F_INIT_NUMBER))
		{
			//�v���C���[��HP�Q�[�W�����炷
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; 

			CallEffect(true);         //�G�t�F�N�g�������Ă�
			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂���
		}
	}
}


//======================================================================================================================================================================
//��͂̒e�̏���
//======================================================================================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CEnemyBulletBattleShip::CEnemyBulletBattleShip(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//�f�X�g���N�^
//=====================
CEnemyBulletBattleShip::~CEnemyBulletBattleShip()
{

}


//=====================
//�X�V����
//=====================
void CEnemyBulletBattleShip::Update()
{
	SetAdjustFrame()++; //�t���[���𑝂₷

	//�t���[�����K��l��荂����
	if (GetFrame() >= MAX_FRAME)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, CObject3D::N_INIT_NUMBER, GetPos()); //�G�t�F�N�g�i�O�Ձj�𐶐�����
		CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                                     //�G�t�F�N�g�̃��C�t��ݒ�
		CManager::GetInstance()->GetEffect()->SetCol(CObject3D::N_INIT_NUMBER, CObject3D::N_INIT_NUMBER, BLUE, GetAlpha());       //�F�̐ݒ�
		SetFrame(CObject3D::N_INIT_NUMBER);                                                                            //�t���[���̏�����

		//�A���t�@�l��0���傫����
		if (GetAlpha() > CObject3D::N_INIT_NUMBER)
		{
			SetAdjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z
		}
	}

	SetAdjustPos().y += MINUS_POS_Y;         //Y���̈ʒu�����炷

	SetAdjustLife()--;                       //�����J�E���g

	//�������s����
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		CallEffect(false);                   //�G�t�F�N�g�������Ă�
								             
		CObject3D::Release();                //���g�̉��
		return;                              //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}							             
								             
	CObject3D::Update();                     //���N���X�̍X�V�������Ă�
	CollisionOnObject();                     //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CEnemyBulletBattleShip::CallEffect(bool bUse)
{

}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CEnemyBulletBattleShip::CollisionOnObject()
{
	//�̂̓����蔻��݂̂ŏ������y������
	D3DXVECTOR3 pos = CManager::GetScene()->GetPlayerX()->GetPosParts(CObject3D::N_INIT_NUMBER);

	//�v���C���[�̓����蔻��
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), pos,
		MAX_BULLET3D_SIZE_X * ADDJUST_HIT, MAX_BULLET3D_SIZE_Y * ADDJUST_HIT, MAX_BULLET3D_SIZE_Z,
		CManager::GetScene()->GetPlayerX()->GetModelSizeParts(CObject3D::N_INIT_NUMBER), CObject3D::F_INIT_NUMBER) == true)
	{
		//�v���C���[��HP�Q�[�W�����炷
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; 

		CallEffect(true);         //�G�t�F�N�g�������Ă�
		CObject3D::Release();     //���g�̉��
		return;                   //�����𔲂���
	}
}


//======================================================================================================================================================================
//�{�X�̒e�̏���
//======================================================================================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CBossBullet::CBossBullet(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//�f�X�g���N�^
//=====================
CBossBullet::~CBossBullet()
{
	
}


//=====================
//�X�V����
//=====================
void CBossBullet::Update()
{
	//�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, CObject3D::N_INIT_NUMBER, GetPos());       

	//�F�̐ݒ�
	CManager::GetInstance()->GetEffect()->SetCol(CObject3D::N_INIT_NUMBER, CObject3D::N_INIT_NUMBER, BLUE, GetAlpha());      

	SetAdjustPos().y -= MINUS_POSY;      //Y���̈ʒu�����Z����

	//�A���t�@�l��0���傫����
	if (GetAlpha() > CObject3D::N_INIT_NUMBER)
	{
		SetAdjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z
	}

	SetAdjustLife()--; //���C�t�����炷

	//�������s����
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CBossBullet::CallEffect(bool bUse)
{
	//����̉��G�t�F�N�g���Ă�
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PILLAROFFIRE, CObject3D::N_INIT_NUMBER, GetPos());
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CBossBullet::CollisionOnObject()
{
	//�v���C���[�̃p�[�c������
	for (int nCount2 = CObject3D::N_INIT_NUMBER; nCount2 < CObjectX::MAX_PARTS; nCount2++)
	{
		//�v���C���[�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosParts(nCount2),
			MAX_BULLET3D_SIZE_X * ADJUST_HIT, MAX_BULLET3D_SIZE_Y * ADJUST_HIT, CObject3D::F_INIT_NUMBER,
			CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount2), CObject3D::F_INIT_NUMBER))
		{
			//�v���C���[��HP�Q�[�W�����炷
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; 

			CallEffect(true);         //�G�t�F�N�g�������Ă�
			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂���
		}
	}
}