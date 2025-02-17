//==========================================
//
//�X�e�[�W����event����������[enent.cpp]
//Auther:Haruki Chiba
//
//==========================================


//==========================================
//�C���N���[�h
#include "event.h"
#include "manager.h"
#include <time.h>


//============================
//�R���X�g���N�^
//============================
CEvent::CEvent()
{
	//�����ł���ő吔����
	for (int nCount = N_INIT_NUMBER; nCount < CInstance::MAX_RUBBLE; nCount++)
	{
		m_fDropSpeed[nCount] = F_INIT_NUMBER;                                     //���Ƃ��X�s�[�h�̏�����
		m_fDropPosY[nCount] = (float)(nCount * INIT_DROP_POS);                    //���Ƃ��ʒu���ǂ�ǂ񍂂�����i�ς݂����点��ׁj
	}															                  
																                  
	m_nCreateWoodenBoradsCounter = N_INIT_NUMBER;                                 //�����������̏�����
	m_nRandomRotX = N_INIT_NUMBER;                                                //�����̌����̗����̏�����
	m_nRandomRotY = N_INIT_NUMBER;                                                //�����̌����̗����̏�����
	m_nPosY = CREATE_WOODENBOARD_POSY;                                            //��������Y����pos�̏�����
	m_bOneflag = false;                                                           //��񂾂��ʂ��t���O�̏������i�g���ĂȂ��j
	m_bBossDirection = false;                                                     //�{�X���o����񂾂�����t���O�̏������i�g���ĂȂ��j
	m_bOneCreate = false;                                                         //�����t���O��Off�ɐݒ�

	mciSendStringA("open data\\BGM\\Bossbgm-Short.wav alias BGM", NULL, N_INIT_NUMBER, NULL); //�ݒ肵���������J���i�Đ��͕ʁj
}


//============================
//�f�X�g���N�^
//============================
CEvent::~CEvent()
{
	mciSendStringA("close BGM", NULL, N_INIT_NUMBER, NULL); //�ݒ肵�����������
}


//============================
//�X�V����
//============================
void CEvent::Update()
{
	//���݂̐��������ő吔��肷���Ȃ���
	if (m_nCreateWoodenBoradsCounter < CInstance::MAX_RUBBLE)
	{
		BossDirection();  //�{�X���̉��o�������Ă�
	}

	//�؂̔Q���������ꂽ��
	if (CManager::GetInstance()->GetWoodenBoardCount() > N_INIT_NUMBER)
	{
		//�܂��S�ė����؂��ĂȂ���
		if (m_bOneflag == false)
		{
			DropObj();  //�؂̔Q�𗎂Ƃ��������Ă�
		}

		//�؂̔Q�𐶐�����������
		for (int WoodenBoardCount = N_INIT_NUMBER; WoodenBoardCount < m_nCreateWoodenBoradsCounter; WoodenBoardCount++)
		{
			//�v���C���[�Ɩ؂̔̓����蔻��
			if (CManager::GetScene()->GetPlayerX()->CollisionPlayerSelect(CManager::GetInstance()->GetWoodenBoard(WoodenBoardCount)))
			{
					CManager::GetScene()->GetPlayerX()->GetMove().x += CPlayerX::MAX_MOVESPEED; //�v���C���[���t���։����o��
			}
		}
	}
}


//============================
//�{�X��̉��o����
//============================
void CEvent::BossDirection()
{
	//�v���C���[����������Ă�����
	if (CManager::GetScene()->GetPlayerX() != nullptr)
	{
		//�v���C���[��pos������̏ꏊ�֍s������
		if (CManager::GetScene()->GetPlayerX()->GetPos().x >= EVENT_BOSS_FIGHT_POS)
		{
			//�{�X�̉��o���܂��̎�
			if (m_bBossDirection == false)
			{
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BOSS, N_INIT_NUMBER,
					D3DXVECTOR3(CREATE_BOSS_POSX, F_INIT_NUMBER, F_INIT_NUMBER));                                             //�{�X�𐶐�
				CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);                                  //�w��̉������~�߂�
				mciSendStringA("play BGM", NULL, 0, NULL);                                                                    //�J���ꂽ�������Đ�����i�J����ĂȂ��Ɛ������Ȃ��j         
				m_bBossDirection = true;                                                                                      //���o�t���O��true�ɂ��A�ʂ�Ȃ�����
			}

			//�J�����̈ʒu��ύX
			CManager::GetScene()->GetCamera()->GetAdjustmentPosZ() = CANERA_POSZ;    //�J�����̂y���̒l��ݒ�
			CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CANERA_POSY;    //�J�����̂x���̒l��ݒ�

			m_nPosY += WOODENBOARD_DROPY;         //���Ƃ��ʒu�𑝂₷
			m_nRandomRotX = rand() % RAND_ROTX;   //�w���̌����𗐐��Œ���
			m_nRandomRotY = rand() % RAND_ROTY;   //�x���̌����𗐐��Œ���

			CManager::GetInstance()->CreateRubble(CObjectX::STRATEGYTYPE::WODDENBORAD, 
				D3DXVECTOR3(CREATE_WOODENBOARD_POSX, m_nPosY, F_INIT_NUMBER));                                                                //�؂̔Q���o��
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().y = (float)m_nRandomRotY * ADJUST_ROT;   //�x���̌�����ݒ�
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().x = (float)m_nRandomRotX * ADJUST_ROT;   //�w���̌�����ݒ�
			m_nCreateWoodenBoradsCounter++; //�z��J�E���g��i�߂�
		}
	}
}


//============================
//���Ƃ�����
//============================
void CEvent::DropObj()
{
	//�؂̔Q���������ꂽ������
	for (int nCount = N_INIT_NUMBER; nCount < m_nCreateWoodenBoradsCounter; nCount++)
	{
		//���������؂̔Q�̈ʒu���ݒ肵���ʒu���傫���i�����j��
		if (CManager::GetInstance()->GetWoodenBoard(nCount)->GetPos().y >= m_fDropPosY[nCount])
		{
			m_fDropSpeed[nCount] += WOODENBOARD_PLUSY;                                             //���Ƃ����x�𑝂₷
			CManager::GetInstance()->GetWoodenBoard(nCount)->SetAdjustMove().y -= m_fDropSpeed[nCount];  //�؂̔Q�𗎂Ƃ�
		}

		//���������؂̔Q�̈ʒu���ݒ肵���ʒu��菬������
		else
		{
			//for���̃J�E���g���ő吔���s������
			if (nCount == CInstance::MAX_RUBBLE - BEFORE_NUMBER)
			{
				m_bOneflag = true; //�t���O��ON�ɂ���
			}
		}
	}
}


//============================
//覐΂𗎂Ƃ�����
//============================
void CEvent::DropMeteorite()
{

}


//================================
//���[�V�����t���̓G�̐�������
//================================
void CEvent::CreateEnemy()
{
	//�v���C���[������̏ꏊ�֍s������
	if (CManager::GetScene()->GetPlayerX()->GetPos().x >= CREATE_MOTIONINENEMY_POSX)
	{
		//�����t���O��Off�̎�
		if (m_bOneCreate == false)
		{
			//���[�V�����t���̓G�̐���
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, N_INIT_NUMBER, D3DXVECTOR3(CREATE_MOTIONINENEMY_POSX, CREATE_MOTIONINENEMY_POSY, F_INIT_NUMBER));
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, N_INIT_NUMBER, D3DXVECTOR3(CREATE_MOTIONINENEMY_POSX+ PLUS_POS_X, CREATE_MOTIONINENEMY_POSY, F_INIT_NUMBER));
			m_bOneCreate = true; //On�ɂ�����
		}
	}
}