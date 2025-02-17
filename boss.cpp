//=====================================
//
//�{�X�̏���[boss.cpp]
//Auther:Haruki Chiba
//
//=====================================


//=====================================
//�C���N���[�h
#include "boss.h"
#include "manager.h"
#include <time.h>
#include <iostream>


//========================
//�R���X�g���N�^
//========================
CBoss::CBoss(int nPriority) : CCharacter(nPriority)
{
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::BOSSHP, CObjectX::N_INIT_NUMBER); //�{�X��HP�Q�[�W�̐���
	
	m_nCoolTime = CObjectX::N_INIT_NUMBER;        //�N�[���^�C���̏�����
	SetRandom(CObjectX::N_INIT_NUMBER);           //�����̏�����
	m_nSize = CObjectX::N_INIT_NUMBER;            //�z�񐔂̏�����
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;  //�ǂ���ɂ��邩�̏�����

	m_nSaveData.clear();                          //�ۊǗp�x�N�^�[�̏�����
	m_nDataX.clear();                             //�����̈ʒu�̏�����
	m_nDataY.clear();                             //�����̈ʒu�̏�����
							                      
	m_bOneCreateFlag = false;                     //�����t���O�̏�����
}

//========================
//�f�X�g���N�^
//========================
CBoss::~CBoss()
{
	//�ۊǗp�x�N�^�[�̔j��
	m_nSaveData.clear();         //��������
	m_nSaveData.shrink_to_fit(); //���𖳂���

	//X���p�̃x�N�^�[�̔j��
	m_nDataX.clear();            //��������
	m_nDataX.shrink_to_fit();    //���𖳂���

	//Y���p�̃x�N�^�[�̔j��
	m_nDataY.clear();            //��������
	m_nDataY.shrink_to_fit();    //���𖳂���
}

//========================
//����������
//========================
HRESULT CBoss::Init()
{
	//�x�N�^�[�̍ő吔����
	for (int nCount = CObjectX::N_INIT_NUMBER; nCount < MAX_VECTOR_SIZE; nCount++)
	{
		m_nSaveData.push_back((float)nCount); //nCount��float�^��cast���đ������
	}

	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //X���p�̕ϐ��ɑ��
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //Y���p�̕ϐ��ɑ��

	CCharacter::Init();                       //������
	CCharacter::LoodBoss();                   //���t�@�C���̓ǂݍ���
	CCharacter::SetMotionBoss(BOSSJUMP);      //���[�V�����̏����ݒ�
	return S_OK;                              //������Ԃ�
}

//========================
//�j������
//========================
void CBoss::Uninit()
{
	CCharacter::Uninit();  //�j������
}

//========================
//�X�V����
//========================
void CBoss::Update()
{
	CCharacter::UpdateBoss();    //���[�V�����̏����X�V����

	//�{�X�������Ă��鎞
	if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() > CObjectX::N_INIT_NUMBER)
	{
		Collision();             //���E�ǂ���ɂ��邩�������Ă���֐����Ă�
		AttackPatternSelect();   //�U���̎�ނ�I������֐����Ă�
	}

	//�{�X�����񂾎�
	else if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() <= CObjectX::N_INIT_NUMBER)
	{
		SetAdjustDieFrame()++;                                //���S�J�E���g�𑝂₷
		SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSDIE);  //���[�V�����̎�ނ�ݒ�

		//frame���K��l�ȏ�̎�
		if (GetDieFrame() >= DIE_FRAME)
		{
			//�{�X�́i���g�j�C���X�^���X�̏��𖳂���
			CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::BOSS, CObjectX::N_INIT_NUMBER); 
			CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ֈڍs
			return;                                       //�����𔲂���
		}
	}

	CObjectX::Update();                                   //���N���X�̊��N���X��m_move���X�V
}

//====================================================================
//�����蔻��ō��E�̂ǂ���ɂ��邩���肷��֐�
//====================================================================
void CBoss::Collision()
{
	//�E���ɂ��鎞
	if (CollisionRightSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//���E�i���o�[���[�P�̎�
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_RIGHT_NUMBER; //�ԍ���ݒ�
		}
	}

	//�����ɂ��鎞
	else if (CollisionLeftSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//���E�i���o�[���[�P�̎�
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_LEFT_NUMBER; //�ԍ���ݒ�
		}
	}

	//�{�X�ɓ���������
	if (CollisionBossPrts() == true)
	{
		//�v���C���[��HP�Q�[�W�����炷
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_TOUCH_DAMAGE;
	}
}

//==============================
//�U���̎�ނ�I�����鏈��
//==============================
void CBoss::AttackPatternSelect()
{
	//�U���̃N�[���^�C�����߂�����
	if (m_nCoolTime >= COOLTIME)
	{
		//�������O�̎�
		if (GetRandom() == DROP_ATTACK_NUMBER)
		{
			AttackPattern();    //�����U�����Ă�
		}

		//�������P�̎�
		else if (GetRandom() == FIRE_ATTACK_NUMBER)
		{
			AttackPattern001(); //���U�����Ă�
		}

		//�������Q�̎�
		else if (GetRandom() == SPECIAL_ATTACK_NUMBER)
		{
			SpecialAttack();    //�K�E�Z���Ă�
		}
	}

	//�N�[���^�C����
	else
	{
		//�������R�̎��i�S�Ă̍U���p�^�[�������s�j
		if (GetRandom() == NONE_ATTACK_NUMBER)
		{
			//srand((unsigned)time(NULL));  // �����n���������
			//SetRandom(rand() % 3);
			SetRandom(CObjectX::N_INIT_NUMBER); //������������
		}

		m_nCoolTime++;    //�N�[���^�C���𑝂₷
	}
}

//==============================
//�s���ɂ܂�镨�̏�����
//==============================
void CBoss::StatusInit()
{
	CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSNEUTRAL); //���[�V�����̎�ނ�ݒ�

	//vector�̏�����
	m_nDataX.clear();          //���g�̑S�폜
	m_nDataX.shrink_to_fit();  //�L���p�V�e�B�̍폜�i�������j

	m_nDataY.clear();          //���g�̑S�폜
	m_nDataY.shrink_to_fit();  //�L���p�V�e�B�̍폜�i�������j

	//vector�̒l�擾�i�R�s�[�j
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //�����p�̈ʒu�̏�����
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //�����p�̈ʒu�̏�����

	//�����o�ϐ��̏�����
	SetFrame(CObjectX::N_INIT_NUMBER);             //�t���[���̏�����
	SetAdjustRandom()++;                           //�����𑝂₷
	m_nCoolTime = CObjectX::N_INIT_NUMBER;         //�N�[���^�C���̏�����
	m_nSize = CObjectX::N_INIT_NUMBER;             //vector�̔z�񐔂�������
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;   //���E�̂ǂ���ɋ��邩�̏�����
	m_bOneCreateFlag = false;                      //�Ռ��g���o���t���O�̏�����
}

//==============================
//�~���U��
//==============================
void CBoss::AttackPattern()
{
	SetAdjustFrame()++; //�t���[�������Z

	//���s��
	if (GetFrame() <= ATTACKPATTEN1_FRAME_1)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK);                      //���[�V�����̎�ނ�ݒ�
		
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_1);  //�v���C���[�Ɍ������悤�ɐݒ�
	}

	//���s��
	else if (GetFrame()<= ATTACKPATTEN1_FRAME_2)
	{
		SetAdjustRot().y = CObjectX::F_INIT_NUMBER;                                            //Y���̌����̏�����
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSIMPACT);                    //���[�V�����̎�ނ�ݒ�
		SetAdjustPos().y += PopY() * MAX_MOVE_SPEED;                                           //Y���̈ʒu��ۊǂ��Ă���l����Ɉړ�
	}																						   
																							   
	//��O�s��																				   
	else if (GetFrame() <= ATTACKPATTEN1_FRAME_3)											   
	{																						   
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));       //Y���p�̈ʒu�̏�����
	}

	//��l�s��
	else if (GetFrame()<= ATTACKPATTEN1_FRAME_4)
	{
		SetAdjustPos().y -= PopY() * MAX_DROP_MOVE_Y_SPEED_1;                                 //Y���̈ʒu��ۊǂ��Ă���l�����Ɉړ�
	}

	//�Ռ��g
	else  if (GetFrame() <= ATTACKPATTEN1_FRAME_5)
	{
		//�t���O��off�̎�
		if (m_bOneCreateFlag == false)
		{
			//�Ռ��g�𐶐�
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::IMPACT, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER)); 

			//�Ռ��g�G�t�F�N�g���Ă�
			CManager::GetInstance()->GetImpact()->SetEffect(GetPos());                                                                        

			m_bOneCreateFlag = true; //�t���O��On�ɂ��Ēʂ�Ȃ�����
		}
	}

	//�I��
	else
	{
		SetAdjustPos().y = CObjectX::F_INIT_NUMBER; //Y���̈ʒu��������
		SetAdjustRot().y = CObjectX::F_INIT_NUMBER; //Y���̌�����������
		StatusInit();                               //������
	}
}

//==============================
//���U��
//==============================
void CBoss::AttackPattern001()
{
	SetAdjustFrame()++; //�t���[�����Z

	//���s��
	if (GetFrame() <= ATTACKPATTEN2_FRAME_1)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK);                       //���[�V�����̎�ނ�ݒ�
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_2);   //�v���C���[�Ɍ������悤�ɐݒ�
	}

	//���s��
	else if (GetFrame() <= ATTACKPATTEN2_FRAME_2)
	{
		SetAdjustRot().y = CObjectX::F_INIT_NUMBER;                         //Y���̌�����������
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSATTACK); //���[�V�����̎�ނ�ݒ�
		SetAdjustPos().y += PopY() * MAX_DROP_MOVE_Y_SPEED_2;               //Y���̈ʒu��ۊǂ��Ă���l����Ɉړ�     
	}

	//��O�s��
	else if (GetFrame() <= ATTACKPATTEN2_FRAME_3)
	{
		//�e�̐���(�e�ɃG�t�F�N�g���Ăԏ��������Ă��邽�߃G�t�F�N�g��ύX���������͒e�̏�����������)
		CManagerBullet::Create(D3DXVECTOR3(GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).x+ CREATE_BULLET_PLUS_POS_X, GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).y, GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * CObjectX::N_INIT_NUMBER, CObjectX::F_INIT_NUMBER, -cosf(GetRot().y) * CObjectX::N_INIT_NUMBER), CManagerBullet::SET_BULLET_LIFE,CObject3D::TYPE::BOSSBULLET);
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));      //Y���p�̈ʒu�̏�����
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX));      //X���p�̈ʒu�̏�����
	}

	//��l�s��
	else if (GetFrame() <= ATTACKPATTEN2_FRAME_4)
	{
		SetAdjustPos().y -= PopY() * MAX_DROP_MOVE_Y_SPEED_2;   //Y���̈ʒu��ۊǂ��Ă���l�����Ɉړ� 

		//���ɂ��鎞
		if (m_nWhichSideNumber == WICHI_SIDE_LEFT_NUMBER)
		{
			SetAdjustRot().y = D3DX_PI_ORI;                     //Y���̌�����ݒ�
			SetAdjustMove().x -= PopX() * MAX_MOVE_SPEED_SIDE;  //Y���̈ړ��ʂ����Z�ݒ�
		}

		//�E�ɂ��鎞
		else if (m_nWhichSideNumber == WICHI_SIDE_RIGHT_NUMBER)
		{
			SetAdjustRot().y = -D3DX_PI_ORI;                    //Y���̌�����ݒ�
			SetAdjustMove().x += PopX() * MAX_MOVE_SPEED_SIDE;  //Y���̈ړ��ʂ����Z�ݒ�
		}
	}

    //�I��
	else
	{
		SetAdjustPos().y = CObjectX::F_INIT_NUMBER; //Y���̈ʒu��������
		SetAdjustRot().y = CObjectX::F_INIT_NUMBER; //Y���̌�����������
		StatusInit();                               //������
	}
}

//=======================================================================================================================================================
//�K�E�Z�̏���
//=======================================================================================================================================================
void CBoss::SpecialAttack()
{
	SetAdjustFrame()++; //�t���[�����Z

	//���s��
	if (GetFrame() <= ATTACKPATTEN3_FRAME_1)
	{
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_3);  //�v���C���[�Ɍ������悤�ɐݒ�
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSACTION);                    //���[�V�����̎�ނ�ݒ�
	}

	//���s��
	else if (GetFrame() <= ATTACKPATTEN3_FRAME_2)
	{

	}

	//��O�s��
	else if (GetFrame() <= ATTACKPATTEN3_FRAME_3)
	{
		//�����t���O��Off�̎�
		if (m_bOneCreateFlag == false)
		{
			//�K�E�Z�̃G�t�F�N�g�̐���
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::BOSSSPECIALATTACK, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

			//�����̏�����
			if (GetRot().y <= -D3DX_PI_ORI_HALF)
			{
				//�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(CBossSpecialAttack::ROT_NUMBER_1);

				//�ʒu���e�ɐݒ�
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).x + SHOT_IN_GUM_PLUS_POS_X,
					GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).y - CCharacter::BOSS_PLUS_POS_Y,
					GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).z));
			}

			//�����̏�����
			else if (GetRot().y >= D3DX_PI_ORI_HALF)
			{
				//�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(CBossSpecialAttack::ROT_NUMBER_2);

				//�ʒu���e�ɐݒ�
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3
				(
					GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).x,
					GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).y - CCharacter::BOSS_PLUS_POS_Y,
					GetPosPartsBoss(CCharacter::BOSS_PARTS_GUN_NUMBER).z));

			}

			m_bOneCreateFlag = true; //�����t���OOn�ɂ���
		}
	}

	//�I��
	else if (CManager::GetInstance()->GetBossSpecialAttack()->GetAlpha() < CObjectX::N_INIT_NUMBER)
	{
		SetAdjustPos().y = CObjectX::F_INIT_NUMBER; //Y���̈ʒu��������
		SetAdjustRot().y = CObjectX::F_INIT_NUMBER; //Y���̌�����������
		StatusInit();                               //������
	}
}


//=======================================================================================================================================================
//  �X�^�b�N�\���̏���
//=======================================================================================================================================================

//============================
//�X�^�b�N��X�l���폜
//============================
float CBoss::PopX()
{
	int nSize = m_nDataX.size() + MINUS_SIZE_COUNT;       //�T�C�Y�̐ݒ�

	//�傫�����O�ȏ�̎�
	if (nSize > CObjectX::N_INIT_NUMBER)
	{
		nSize--;                                          //�傫�������炷
		m_nDataX.erase(m_nDataX.end()+ MINUS_SIZE_COUNT); //���ꂼ��̔z���X���̒l��Ԃ�
		return m_nDataX[nSize];                           //����Ԃ�
	}

	return CObjectX::N_INIT_NUMBER;                       //�O��Ԃ�
}

//============================
//�X�^�b�N��Y�l���폜
//============================
float CBoss::PopY()
{
	int nSize = m_nDataY.size() + MINUS_SIZE_COUNT;        //�T�C�Y�̐ݒ�

	//�T�C�Y���O�ȏ�̎�
	if (nSize > CObjectX::N_INIT_NUMBER)
	{
		nSize--;                                           //�T�C�Y�����炷
		m_nDataY.erase(m_nDataY.end() + MINUS_SIZE_COUNT); //���ꂼ��̔z���X���̒l��Ԃ�
		return m_nDataY[nSize];                            //����Ԃ�
	}

	return CObjectX::N_INIT_NUMBER;                        //�O��Ԃ�
}

//========================
//�`�揈��
//========================
void CBoss::Draw()
{
	CCharacter::DrawBoss(MAX_BOSSPARTS); //�p�[�c���Ƃ̕`�揈��
}

//========================
//��������
//========================
CBoss* CBoss::Create(D3DXVECTOR3 pos)
{
	CBoss* pBoss = new CBoss(); //���I�m��

	//������������������
	if (SUCCEEDED(pBoss->Init()))
	{
		pBoss->SetPos(pos);     //�ʒu�������Ɠ���������
		return pBoss;           //����Ԃ�
	}						    
							    
	return nullptr;             //����Ԃ�
}