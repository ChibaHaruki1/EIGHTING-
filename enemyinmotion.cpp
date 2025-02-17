//=========================================================================
//
//���[�V�����t���̓G�̏���[enemyinmotion.cpp]
//Auther;Haruki Chiba
//
//=========================================================================


//==============================
//�C���N���[�h
#include "enemyinmotion.h"
#include "manager.h"
#include <time.h>


//=============================
//�R���X�g���N�^
//=============================
CManagerEnemyInMotion::CManagerEnemyInMotion(int nPriority) : CEnemyCharacter(nPriority)
{
	m_nJumpFrame = CObjectX::N_INIT_NUMBER;   //��Ԃ܂ł̎��Ԃ̏�����
	JumpNumber = CObjectX::N_INIT_NUMBER;     //��Ԕԍ��̏�����
	JumpRecastTime = CObjectX::N_INIT_NUMBER; //��Ԃ܂ł̃��L���X�g�^�C���̏�����
}

//=============================
//�f�X�g���N�^
//=============================
CManagerEnemyInMotion::~CManagerEnemyInMotion()
{

}

//=============================
//����������
//=============================
HRESULT CManagerEnemyInMotion::Init()
{
	//�������ɐ���������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;                             //���s��Ԃ�
	}

	CEnemyCharacter::LoodEnemy(GetFileName());     //�ǂݍ��ރt�@�C���p�X��ݒ�
	//CEnemyCharacter::SetMotionEnemy(ENEMYWALK);  //���[�V�����̏�����

	return S_OK;                                   //������Ԃ�
}

//==============================
//�j������
//==============================
void CManagerEnemyInMotion::Uninit()
{
	CEnemyCharacter::Uninit(); //�e�p�[�c�̔j������
}

//==============================
//�X�V����
//==============================
void CManagerEnemyInMotion::Update()
{
	
}

//==============================
//�`�揈��
//==============================
void CManagerEnemyInMotion::Draw()
{
	//CEnemyCharacter::DrawEnemy(MAX_ENEMYPARTS, 1); //�`�揈��
}

//==============================
//��������
//==============================
CManagerEnemyInMotion* CManagerEnemyInMotion::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemyInMotion* pEnemyInMotion = nullptr; //���N���X�̃|�C���^�[

	if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		pEnemyInMotion = new CEnemyInMotion001(); //���I�m��
		pEnemyInMotion->SetFileName("Enemy001");  //�t�@�C���p�X�̐ݒ�
	}

	//�^�C�v�����[�V�����t���̓G002�̎�
	else if (type == CObjectX::TYPE::ENEMYINMOTION002)
	{
		pEnemyInMotion = new CEnemyInMotion002(); //���I�m��
		pEnemyInMotion->SetFileName("Enemy002");  //�t�@�C���p�X�̐ݒ�
	}

	//��񂪂��鎞
	if (pEnemyInMotion != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pEnemyInMotion->Init()))
		{
			pEnemyInMotion->SetPos(pos); //�ʒu�̓���
			return pEnemyInMotion;       //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//====================================================================================================================================
//�G001�̏���
//====================================================================================================================================

//=============================
//�R���X�g���N�^
//=============================
CEnemyInMotion001::CEnemyInMotion001(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	SetRot(D3DXVECTOR3(0.0f, -D3DX_PI_ORI, 0.0f)); //������ݒ�i�E�����j
	SetLife(MAX_LIFE);                             //���C�t�̐ݒ�
	m_nHitFrame = CObjectX::N_INIT_NUMBER;         //�����������Ƀt���[���̏�����
	m_bHit = false;                                //�������Ă��Ȃ��ɐݒ�
}

//=============================
//�f�X�g���N�^
//=============================
CEnemyInMotion001::~CEnemyInMotion001()
{

}


//==============================
//�X�V����
//==============================
void CEnemyInMotion001::Update()
{
	//�v���C���[������͈͓̔��ɗ�����X�V���������s����
	if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_1) == true)
	{
		//�����Ă��鎞
		if (GetLife() > CObjectX::N_INIT_NUMBER)
		{
			CEnemyCharacter::UpdateEnemy001();                                                       //���[�V�����̏����X�V����

			//�v���C���[�Ɠ������Ă��鎞
			if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_2) == true)
			{
				CEnemyCharacter::SetMotionEnemy001(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //���[�V�����̎�ނ�ݒ�

				SetAdjustFrame()++;     //�e�����ۂ̃t���[���𑝂₷

				//�t���[�����K�萔�ɒB������
				if (GetFrame() >= MAX_FRAME)
				{
					//�e�̐���
					CManagerBullet::Create(D3DXVECTOR3(
						this->GetPosPartsEnemy(CEnemyCharacter::PARTS_RIGHT_SHOLDER_WEAPON_NUMBER).x + CREATE_BULLET_PLUS_POS_X,
						this->GetPosPartsEnemy(CEnemyCharacter::PARTS_RIGHT_SHOLDER_WEAPON_NUMBER).y + CREATE_BULLET_PLUS_POS_Y,
						this->GetPosPartsEnemy(CEnemyCharacter::PARTS_RIGHT_SHOLDER_WEAPON_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, CObjectX::F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED),
						CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::ENEMYBULLET);

					SetFrame(CObjectX::N_INIT_NUMBER); //�t���[�����O�ɂ���
				}

				//�v���C���[���G�ɐڐG������
				if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_3) == true)
				{
					m_bHit = true; //�������������On�ɂ���
				}
			}

			//�v���C���[�Ɠ������ĂȂ���
			else
			{
				//�����̏�����
				GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x = CObjectX::F_INIT_NUMBER; //�p�[�c�̌����̏�����
				CEnemyBullet::SetAdditionPosY(CEnemyBullet::PLUS_ROT_Y);                                          //�e�̌����̏�����

				//���ł��Ȃ��Ƃ�
				if (GetJumpFlag() == false)
				{
					CEnemyCharacter::SetMotionEnemy001(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //���[�V�����̎�ނ�ݒ�

					//�W�����v�̃��L���X�g�^�C�����؂ꂽ��
					if (m_nJumpFrame == CObjectX::N_INIT_NUMBER)
					{
						TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);           //�v���C���[�Ɍ������悤�ɐݒ�
					}
				}
			}

			//�v���C���[���G�ɓ���������
			if (m_bHit == true)
			{
				PlayerBloWwaway();                        //�v���C���[�̐�����я������Ă�
			}

			Junp(TYPE::ENEMYINMOTION001, MAX_JUMP_POWER); //�W�����v�Əd�͏����֐����Ă�
			WhenCollisionBlock();                         //�n�ʗp�̃u���b�N�ɐG��Ă��鎞�̏���
			CObjectX::Update();                           //move�l�̍X�V
		}

		//���񂾎�
		else if (GetLife() <= CObjectX::N_INIT_NUMBER)
		{
			Die();                                        //���S���̏����֐����Ă�
		}
	}
}

//===============================================
//���S���̏���
//===============================================
void CEnemyInMotion001::Die()
{
	SetAdjustDieFrame()++; //���S�t���[���𑝂₷

	//srand((unsigned)time(NULL));  //�����n���������

	//���s��
	if (GetDieFrame() <= ATTACKPATTEN1_FRAME_1)
	{
		//�����G�t�F�N�g���Ă�
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, GetPos());
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, GetPos());


		//�����G�t�F�N�g�̑傫����ݒ�
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
	}

	//���s��
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_2)
	{

	}

	//��O�s��
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_3)
	{
		SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //�����̐���

		//�����G�t�F�N�g���Ă�
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));


		//�����G�t�F�N�g�̑傫����ݒ�
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
	}

	//��l�s��
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_4)
	{

	}

	//��܍s��
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_5)
	{
		SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //�����̐���

		//�����G�t�F�N�g���Ă�
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));


		//�����G�t�F�N�g�̑傫����ݒ�
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
	}

	//��Z�s��
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_6)
	{

	}

	//�掵�s��
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_7)
	{

		SetRandom(-MIN_RANDOM2 + rand() % MAX_RANDOM2); //�����̐���

		//�����G�t�F�N�g���Ă�
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));


		//�����G�t�F�N�g�̑傫����ݒ�
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, CObjectX::F_INIT_NUMBER);
	}

	//�I��
	else
	{
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);  //�X�R�A�����Z
		CObjectX::Release();                                            //���g���폜
		return;                                                         //�����𔲂���
	}
}

//===============================================
//�v���C���[���G�ɓ���������
//===============================================
void CEnemyInMotion001::PlayerBloWwaway()
{
	m_nHitFrame++;  //���������t���[���𑝂₷

	//���������u��
	if (m_nHitFrame <= ATTACKPATTEN2_FRAME_1)
	{
		//�v���C���[��HP�����
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * MAX_DAMAGE;
	}

	//���s��
	else if (m_nHitFrame <= ATTACKPATTEN2_FRAME_2)
	{

		//�������̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_1)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x += PLAYER_MOVE;  //�E�Ɉړ�
		}

		//�E�����̎�
		else if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_2)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x -= PLAYER_MOVE;  //���Ɉړ�
		}
	}

	//�I��
	else
	{
		m_nHitFrame = CObjectX::N_INIT_NUMBER; //hitframe��������
		m_bHit = false;                        //�������������off�ɂ���
	}
}

//===============================================
//�v���C���[�ɑ΂���@�̂ƒe�̒�������
//===============================================
void CEnemyInMotion001::AdjustmentBulletAndRot()
{
	//�������̎�
	if (GetRot().y >= D3DX_PI_ORI_HALF)
	{
		//�v���C���[�̌������������̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_1)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x += ADJUST_PRTAS_ROTX; //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() -= ADJUST_BULLET_ROTY;                               //�e��X���̌��������Z����
		}

		//�v���C���[�̌������E�����̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_2)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x -= ADJUST_PRTAS_ROTX; //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() += ADJUST_BULLET_ROTY;                               //�e��X���̌��������Z����
		}
	}

	//�E�����̎�
	else if (GetRot().y <= -D3DX_PI_ORI_HALF)
	{
		//�v���C���[�̌������������̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_1)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x -= ADJUST_PRTAS_ROTX; //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() += ADJUST_BULLET_ROTY;                               //�e��X���̌��������Z����
		}

		//�v���C���[�̌������E�����̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_2)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x += ADJUST_PRTAS_ROTX; //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() -= ADJUST_BULLET_ROTY;                               //�e��X���̌��������Z����
		}
	}

	Correctionrot(); //�������C������֐����Ă�
}

//===============================================
//�v���C���[�ɑ΂���@�̂ƒe�̒�������
//===============================================
void CEnemyInMotion001::WhenCollisionBlock()
{
	int nFieldCount = CManager::GetInstance()->GetFieldBlockCount() + 1;              //�n�ʗp�u���b�N�̐�����
	int nRoadBlock = CManager::GetInstance()->GetRoadBlockCount() + 1;                //���p�u���b�N�̐�����
	int nWallRoadBlock = CManager::GetInstance()->GetWallRoadBlockCount() + 1;        //�ǌ����p�u���b�N�̐�����
	int nWallRoadBlock001 = CManager::GetInstance()->GetWallRoadBlock001Count() + 1;  //�ǌ����p�u���b�N001�̐�����

	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = CObjectX::N_INIT_NUMBER; nCount < nFieldCount; nCount++)
	{
		//�G�̍ő�p�[�c������
		for (int nEnemyCount = CObjectX::N_INIT_NUMBER; nEnemyCount < MAX_ENEMYPARTS; nEnemyCount++)
		{
			//�n�ʗp�u���b�N�̏�񂪂��鎞
			if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
			{
				//���
				if (JumpNumber == JUMP_NUMBER_MINUS_1)
				{
					//���@�ƒn�ʗp�u���b�N������������
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * ADJUST_FIELD_BLOCK, GetMove()) == true)
					{
						//���L���X�g�^�C�����O�ȉ��̎�
						if (JumpRecastTime <= CObjectX::N_INIT_NUMBER)
						{
							m_nJumpFrame++;                //��ԃt���[���𑝂₷

							SetMotionEnemy001(ENEMYJUMP);  //�W�����v���[�V�����̐ݒ�

							//�W�����v�t���[�����K��l��荂����
							if (m_nJumpFrame >= MAX_JUMPFRAME)
							{
								SetJumpFlag(true);                       //���
								m_nJumpFrame = CObjectX::N_INIT_NUMBER;  //�t���[���̏�����
								JumpNumber++;                            //�W�����v�i���o�[�𑝂₷�i���͔�΂Ȃ��ɐݒ�j

								return;                                  //�����𔲂���
							}
						}

						//���L���X�g�^�C�����O�ȏ�̎�
						else if (JumpRecastTime >= 0)
						{
							JumpRecastTime--; //���炷
						}
						return; //�����𔲂���
					}
					else
					{
						//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
						if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
						{
							GravityTogether(); //�d�͂𓯊�������

							//y���̈ʒu��ݒ�
							GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
								CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
						}
					}
				}

				//��΂Ȃ�
				else if (JumpNumber == JUMP_NUMBER_0)
				{
					//���@�ƒn�ʗp�u���b�N������������
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
					{
						JumpRecastTime = MAX_JUMPRECASTTIME; //���L���X�g�^�C���̐ݒ�
						JumpNumber = JUMP_NUMBER_MINUS_1;    //�W�����v�i���o�[�̐ݒ�i���͔�Ԃɐݒ�j
						return;                              //�����𔲂���
					}

					else
					{
						//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
						if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
						{
							GravityTogether(); //�d�͂𓯊�������

							//y���̈ʒu��ݒ�
							GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
								CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;

							SetJumpFlag(false); //��΂Ȃ�
						}
					}
				}
			}
		}
	}

	//���p�u���b�N����
	for (int nCount2 = CObjectX::N_INIT_NUMBER; nCount2 < nRoadBlock; nCount2++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			//�������Ă��鎞
			if (GetCollision()->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * ADJUST_BLOCK, GetMove()) == true)
			{

			}

			else
			{
				//��ɓ������Ă��鎞
				if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether();  //�d�͂̓���

					//y���̈ʒu��ݒ�
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					SetJumpFlag(false); //�W�����v�t���O��Off
				}
			}
		}
	}

	//�ǌ����p�u���b�N����
	for (int nCount3 = CObjectX::N_INIT_NUMBER; nCount3 < nWallRoadBlock; nCount3++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			//�������Ă��鎞
			if (GetCollision()->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize() * ADJUST_BLOCK, GetMove()) == true)
			{

			}

			else
			{
				//��ɓ������Ă��鎞
				if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether(); //�d�͂̓���

					//y���̈ʒu��ݒ�
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;

					SetJumpFlag(false); //�t���O��Off�ɂ���
				}
			}
		}
	}

	//�ǌ���001�p�u���b�N����
	for (int nCount4 = CObjectX::N_INIT_NUMBER; nCount4 < nWallRoadBlock001; nCount4++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			//��ɓ������Ă��鎞
			if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				GravityTogether();  //�d�͂̓���

				//y���̈ʒu��ݒ�
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;


				SetJumpFlag(false); //�t���O��Off�ɂ���
			}
		}
	}
}

//===============================================
//�������C��
//===============================================
void CEnemyInMotion001::Correctionrot()
{
	//�����Z���Ă����ϐ��̒l������̈ʒu�͈͓̔��̎�
	if (CEnemyBullet::GetAdditionPosY() <= -CEnemyBullet::PLUS_ROT_Y && CEnemyBullet::GetAdditionPosY() >= -CEnemyBullet::PLUS_ROT_Y+ PLUS_ROT_Y)
	{
		//GetRot().y = -D3DX_PI_ORI;  //�������t�ɐݒ�
		SetRot(D3DXVECTOR3(GetRot().x, -D3DX_PI_ORI, GetRot().z));

		//�����̏�����
		GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));

		//�e�̏o������𒲐�
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::PLUS_ROT_Y * MULTIPLICATIOB_ADJUST_BULLET_ROTY);   
	}

	else if (CEnemyBullet::GetAdditionPosY() >= CEnemyBullet::PLUS_ROT_Y * IF_ADJUST_BULLET_ROTY && CEnemyBullet::GetAdditionPosY() <= CEnemyBullet::PLUS_ROT_Y * IF_ADJUST_BULLET_ROTY+1.0f)
	{
		//GetRot().y = D3DX_PI_ORI; //�������t�ɐݒ�
		SetRot(D3DXVECTOR3(GetRot().x, D3DX_PI_ORI, GetRot().z));

		//�����̏�����
		GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->SetRot(D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

		//�e�̏o������𒲐�
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::PLUS_ROT_Y * MULTIPLICATIOB_ADJUST_BULLET_ROTY);
	}
}


//==============================
//�`�揈��
//==============================
void CEnemyInMotion001::Draw()
{
	CEnemyCharacter::DrawEnemy001(MAX_ENEMYPARTS); //�`�揈��
}


//====================================================================================================================================
//�G002�̏���
//====================================================================================================================================

//=============================
//�R���X�g���N�^
//=============================
CEnemyInMotion002::CEnemyInMotion002(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	SetLife(1);         //���C�t�̐ݒ�
}

//=============================
//�f�X�g���N�^
//=============================
CEnemyInMotion002::~CEnemyInMotion002()
{

}

//=============================
//�X�V����
//=============================
void CEnemyInMotion002::Update()
{
	//�v���C���[������͈͓̔��ɗ�����X�V���������s����
	if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_1) == true)
	{
		//�����Ă��鎞
		if (GetLife() > CObjectX::N_INIT_NUMBER)
		{
			CEnemyCharacter::UpdateEnemy001();                                                 //���[�V�����̏����X�V����

			//�v���C���[�Ɠ������Ă��鎞
			if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_2) == true)
			{
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
					CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * DAMAGE;   //HP�Q�[�W�����炷
			}

			//�������Ă��Ȃ���
			else
			{
				//CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //���[�V�����̎�ނ�ݒ�

				TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);            //�v���C���[�Ɍ������悤�ɐݒ�
			}

			CObjectX::Update();                                                                 //move�l�̍X�V
		}
	}
}

//==============================
//�`�揈��
//==============================
void CEnemyInMotion002::Draw()
{
	CEnemyCharacter::DrawEnemy002(MAX_ENEMYPARTS); //�`�揈��
}
