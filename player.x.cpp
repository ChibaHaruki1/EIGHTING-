//===================================
//
//�v���C���[�̐ݒ�����鏈��[player.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "main.h"
#include "player.x.h"
#include "rendererh.h"
#include "manager.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"
#include <time.h>
#include "DxLib.h"


//===================
//�R���X�g���N�^
//===================
CPlayerX::CPlayerX(int nPriority) : CCharacter(nPriority)
{
	SetJumpFlag(false);                                            //���ł��Ȃ��ɐݒ�
	SetGravity(CObjectX::F_INIT_NUMBER);                           //�d�͂̏�����

	//�e�L�X�g�t�@�C���ɓo�^���鎞�̗t�z��ԍ��̏�����
	m_nFiledCount = INIT_NUMBER;                                   //�n�ʂ̐������̏�����
	m_nTelephonCount = INIT_NUMBER;                                //�d���̐������̏�����

	//�e�L�X�g�t�@�C���ɓo�^���邵���S�Ă̔z��ԍ��̏�����
	m_nAllTelephonPoleCount = INIT_NUMBER;
	m_nAllFiledCount = INIT_NUMBER;

	m_ObjectNumber = CObjectX::N_INIT_NUMBER;                      //���݂̃I�u�W�F�N�g�̔ԍ��̏�����
							                              		   
	m_nFrameParticle = CObjectX::N_INIT_NUMBER;                    //�p�[�e�B�N���̃t���[���̏�����
	m_nPraticlesCount = CObjectX::N_INIT_NUMBER;                   //�p�[�e�B�N���̔z��J�E���g�̏�����
	m_nRandomCol = CObjectX::N_INIT_NUMBER;                        //������ۊǂ���ׂ̕ϐ�
							                              
	m_pMenyu = nullptr;                                            //���j���[�|�C���^�[�̏�����
	m_pLaserUI = nullptr;                                          //���[�U�[UI�̏�����
	m_pTalkText = nullptr;                                         //�b��UI�̏�����
	m_pBuyText = nullptr;                                          //�����e�L�X�g�̏�����
	m_nSelectShopCount = CObjectX::N_INIT_NUMBER;                  //SHOP�őI��ł��镨
	m_nBuyOrSendCount = CObjectX::N_INIT_NUMBER;                   //���������̑I���J�E���g�̏�����
	m_pSelectGage = nullptr;                                       //�I���Q�[�W�̏�����
	m_pSelectGage001 = nullptr;                                    //�I���Q�[�W001�̏����� 
	SpecialAttack = false;                                         //�K�E�Z���g���Ă��邩�ǂ����̏�����
	m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;           //���݂̃v���C���[�̏�Ԃ̐ݒ�
	m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;              //���݂̃t���O�̐ݒ�
	m_nAlpha = CObjectX::INIT_ALPHA;                               //�p�[�e�B�N���̃A���t�@�l�̐ݒ�

	m_nMotionFrame = CObjectX::N_INIT_NUMBER;                      //�e�������̃t���[���̏�����
	m_nMotionFrame001 = CObjectX::N_INIT_NUMBER;                   //�e001�������̃t���[���̏�����
	m_bPlayerMoveNext = false;                                     //���̃X�e�[�W�֍s�����̃v���C���[�̓����̔���p�̕ϐ��̏�����
	m_bNextStage = false;                                          //���̃X�e�[�W�ɍs�����ǂ����̕ϐ��̏�����

	//������ԏ����̏�����
	m_nFlayFrame = CObjectX::N_INIT_NUMBER;                        //��ԃt���[���̏�����
	m_bFly = false;                                                //���łȂ�

	m_nDieRandom = CObjectX::N_INIT_NUMBER;                        //���S���̕��������̏�����
	m_nRotNumber = CObjectX::N_INIT_NUMBER;                        //�����ԍ��̏�����
	m_nSpecialAttackCount = CObjectX::N_INIT_NUMBER;               //�K�E�Z�̃J�E���g�̏�����

	m_nNextStageFrame = CObjectX::N_INIT_NUMBER;                   //���̃X�e�[�W�ɍs���܂ł̃t���[���̏�����
	m_bLandingFlag = false;                                        //���n���ĂȂ�
	m_nLandingFrame = CObjectX::N_INIT_NUMBER;                     //���n���̎��̓����ւ̃t���[���̏�����

	m_pNowCreateUI = CManager2DUI::Create(CObject::TYPE_UI::NOWCREATE); //���݂̔z�u�I�u�W�F�N�g��UI�̐���

	//�������̕ۊǗp�ϐ��̏�����
	m_nFieldBlock = CObjectX::N_INIT_NUMBER;
	m_nGoUpBlock = CObjectX::N_INIT_NUMBER;
	m_nRoadBlock = CObjectX::N_INIT_NUMBER;
	m_nWallRoadBlock = CObjectX::N_INIT_NUMBER;
	m_nWallRoadBlock001 = CObjectX::N_INIT_NUMBER;
	m_nSmalBlock = CObjectX::N_INIT_NUMBER;
	m_nLaserCount = CObjectX::N_INIT_NUMBER;
	m_nSmalBlock001 = CObjectX::N_INIT_NUMBER;
}


//===================
//�f�X�g���N�^
//===================
CPlayerX::~CPlayerX()
{
	//mciSendStringA("close BGM", NULL, CObjectX::N_INIT_NUMBER, NULL);
}


//====================
//����������
//====================
HRESULT CPlayerX::Init()
{
	CCharacter::Init();                                                                             //�������������Ă�
	CCharacter::Lood();                                                                             //�e�L�X�g�t�@�C����ǂݍ��ޏ���
	SetRot(D3DXVECTOR3(CObjectX::F_INIT_NUMBER, -CObjectX::D3DX_PI_ORI, CObjectX::F_INIT_NUMBER));  //�����̒����i�E�����j
	SetPos(D3DXVECTOR3(CObjectX::F_INIT_NUMBER,CObjectX::F_INIT_NUMBER,CObjectX::F_INIT_NUMBER));   //�ʒu�̒���
	SetLife(LIFE);                                                                                  //���g�̃��C�t
	m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(false);                                       //�p�[�c�̏e�������\���ɐݒ�
	return S_OK;                                                                                    //������Ԃ�
}

//==================
//�I������
//=================
void CPlayerX::Uninit()
{
	//instance��������
	InstanceMakeNull();

	CCharacter::Uninit(); //�p�[�c���Ƃ̔j������
}

//===============================================================================================================================================================================
//instance��nullptr�ɂ���
//===============================================================================================================================================================================
void CPlayerX::InstanceMakeNull()
{
	m_pTalkText = nullptr;      //�b���e�L�X�g�̏��𖳂���
						        
	m_pMenyu = nullptr;         //����̑I�����j���[�̏��𖳂���
						        
	m_pBuyText = nullptr;       //��������e�L�X�g�̏��𖳂���
							    
	m_pSelectGage = nullptr;    //�I���Q�[�W�̏��𖳂���

	m_pSelectGage001 = nullptr; //�I���Q�[�W001�̏����Ȃ���
}

//=======================================
//�V���b�v���̃|�C���^�[�̏�����
//=======================================
void CPlayerX::ShopInstanceMakeNullptr()
{
	//�I���Q�[�W�̏�񂪂��鎞
	if (m_pSelectGage != nullptr)
	{
		m_pSelectGage->Release();    //��������
		m_pSelectGage = nullptr;     //���𖳂���
	}

	//�I���Q�[�W001�̏�񂪂��鎞
	if (m_pSelectGage001 != nullptr)
	{
		m_pSelectGage001->Release(); //��������
		m_pSelectGage001 = nullptr;  //���𖳂���
	}

	//�����e�L�X�g�̏�񂪂��鎞
	if (m_pBuyText != nullptr)
	{
		m_pBuyText->Release();       //��������
		m_pBuyText = nullptr;        //���𖳂���
	}

	//���j���[�̏�񂪂��鎞
	if (m_pMenyu != nullptr)
	{
		m_pMenyu->Release();         //��������
		m_pMenyu = nullptr;          //���𖳂���
	}

	//�V���b�v���̔w�i�̏�񂪂��鎞
	if (CManager::GetInstance()->GetShopScreen() != nullptr)
	{
		CManager::GetInstance()->GetShopScreen()->Release();                   //��������
		CManager::GetInstance()->DesignationUninit2D(CObject2D::TYPE::SCREEN); //���𖳂���
	}

	m_nSelectShopCount = N_INIT_NUMBER;
}


//===============================================================================================================================================================================
//�X�V����
//===============================================================================================================================================================================
void CPlayerX::Update()
{
	//�����Ă��鎞
	if (GetLife() == LIFE)
	{
		CCharacter::UpdatePlayer();           //���[�V�����̍X�V

		if (GetPos().y <= -DIE_POS_Y)
		{
			SetLife(CObjectX::N_INIT_NUMBER); //���C�t�̏�����
		}

		//�d�͒l���K��l��荂����
		if (GetGravity() >= MAX_GRAVITY)
		{
			GetGravity() = MAX_GRAVITY;       //�d�͂̐ݒ�
		}

		//�V�ׂ��ԂɂȂ��Ă��鎞
		if (CManager::GetScene()->GetPlay() == true)
		{
			HitAttack();                      //����̍U�����󂯂����̏����֐����Ă�

			//�K�E�Z�J�E���g���K��l���Ⴂ��
			if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
			{
				m_nSpecialAttackCount++;      //�J�E���g��i�߂�
			}

			//�Q�[�W��manager����������Ă�����
			if (CManager::GetInstance()->GetPlayerHPGage() != nullptr)
			{
				//HP�Q�[�W���O�ȉ��̎�
				if (CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() <= CObjectX::N_INIT_NUMBER)
				{
					CManager::GetInstance()->GetPlayerHPGage()->GetSaveSizeX() = CObjectX::F_INIT_NUMBER;  //HP�Q�[�W�̃T�C�Y���O�ɂ���
					SetLife(CObjectX::N_INIT_NUMBER);                                                      //���C�t���O�ɐݒ�Ŏ��S����ɂ���
				}
			}

			//�������Ă��Ȃ���
			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				NormalStateSummarizeFunction(); //��p�̏������Ă�
			}

			//SHOP�Ŕ����������Ă��鎞
			else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE || m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
			{
				ShopStateSummarizeFunction();   //��p�̏������Ă�
			}

			//���̃X�e�[�W�֍s���Ƃ��̃v���[���[�̓�����On�̎�
			if (m_bPlayerMoveNext == true)
			{
				//SceneMode(1); //scene�̐؂�ւ�
				//return;		  //�����𔲂���
				NextStageMotion();
			}

			//����scene�ɍs���t���O��On�̎�
			if (m_bNextStage == true)
			{
				SceneMode(SCENE_NEXT_STAGE); //scene�̐؂�ւ�
				return;		                 //�����𔲂���
			}

			CObjectX::Update();              //���N���X�̊��N���X�̍X�V�������Ă�
		}

		//���n�܂łɕK�v�ȏ���
		else
		{
			BlockJudgement();                   //�n�ʂɐG��鎖�ł悤�₭�ړ��Ȃǂ��ł���悤�ɂ��邽�߃u���b�N�̓����蔻�菈�����Ă�
			Junp(TYPE::PLAYER, MAX_JUMPPAWER);  //�d�͏����֐����ĂԎ��ŗ�����悤�ɂ���
		}
	}

	//���񂾎�
	else if (GetLife() == CObjectX::N_INIT_NUMBER)
	{
		SetAdjustDieFrame()++;          //���S�t���[���𑝂₷
		//GetPos().y = -50.0f;          //�ʒu��Ⴍ����
		srand((unsigned)time(NULL));    //�����n���������

		//�����������ĂȂ���
		if (m_nDieRandom == CObjectX::N_INIT_NUMBER)
		{
			m_nDieRandom = MIN_DIE_RANDOM + rand() % MAX_DIE_RANDOM; //����������
		}

		//�̂̈ʒu��ݒ�
		m_pModelPrts[PLAYER_PARTS_BODY_NUMBER]->GetPos() += D3DXVECTOR3(GetDieFrame() * DIE_FRAME_REDUCTION * m_nDieRandom, CObjectX::F_INIT_NUMBER, GetDieFrame() * DIE_FRAME_REDUCTION * m_nDieRandom);

		CCharacter::Update();  //���N���X�̍X�V�������Ă�
		SetMotion(DIE);        //���[�V���������S�ɐݒ肷��

		//����̐��l
		if (GetDieFrame() >= MAX_DIE_COUNT)
		{
			SceneMode(SCENE_DIE_STAGE); //�V�[���̐ݒ�
			return;                     //�����𔲂���
		}
	}
	//SceneMode(SCENE_DEBUG_STAGE);         //�V�[����I��
}


//==================================================================================================================================================
//������я���
//==================================================================================================================================================
void CPlayerX::BlowAway()
{
	m_nFlayFrame++;                  //��ԃt���[����i�߂�

	CCharacter::SetMotion(BLOWAWAY); //�Ԃ���у��[�V�����̐ݒ�

	//���s��
	if (m_nFlayFrame <= BLOWAWAY_FRAME_1)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += BLOWAWAY_PLUS_POS_X; //X���̈ʒu�𑝂₷
		CManager::GetScene()->GetPlayerX()->GetPos().y += BLOWAWAY_PLUS_POS_Y; //Y���̈ʒu�𑝂₷
	}

	//���s��
	else if (m_nFlayFrame <= BLOWAWAY_FRAME_2)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().y += BLOWAWAY_PLUS_POS_X-10.0f; //X���̈ʒu�𑝂₷
		CManager::GetScene()->GetPlayerX()->GetPos().x += BLOWAWAY_PLUS_POS_Y-10.0f; //Y���̈ʒu�𑝂₷
	}

	//�I��
	else
	{
		m_bFly = false;                         //��ԃt���O��Off�ɂ���
		m_nFlayFrame = CObjectX::N_INIT_NUMBER; //��ԃt���[���̏�����
	}
}


//==================================================================================================================================================
//����̍U�����󂯂����̏���
//==================================================================================================================================================
void CPlayerX::HitAttack()
{
	//�Ռ��j�G�t�F�N�g�̃C���X�^���X��񂪂��鎞
	if (CManager::GetInstance()->GetImpact() != nullptr)
	{
		//���������t���O��ON�̎�
		if (CManager::GetInstance()->GetImpact()->GetHitNumber() == CObjectX::N_INIT_NUMBER)
		{
			m_bFly = true; //���
		}
	}

	//��ԃt���O��ON�̎�
	if (m_bFly == true)
	{
		BlowAway();       //������я������Ă�
	}
}


//==================================================================================================================================================
//����scene����
//==================================================================================================================================================
void CPlayerX::SceneMode(int nType)
{
	//���̃X�e�[�W�ɍs���p�i�Q�[�����[�v�j
	if (nType == SCENE_NEXT_STAGE)
	{
		m_bNextStage = false; //���̃X�e�[�W�̃t���O��Off�ɂ���

		//���݂̃V�[������Q��
		switch (CManager::GetScene()->GetMode())
		{
			//�X�e�[�W�P�̎�
		case CScene::MODE::MODE_GAME01:
			CManager::SetMode(CScene::MODE::MODE_GAME02); //�X�e�[�W�Q�ɑJ��
			return;                                       //�����𔲂���

			//�X�e�[�W�Q�̎�
		case CScene::MODE::MODE_GAME02:
			CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ɑJ��
			return;                                       //�����𔲂���
		}
	}

	//�f�o�b�N�p
	else if (nType == SCENE_DEBUG_STAGE)
	{
		//Enter�L�[�������ꂽ���i�f�o�b�N�p�j
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_I) == true)
		{
			m_bNextStage = false; //���̃X�e�[�W�̃t���O��Off�ɂ���

			//���݂̃V�[������Q��
			switch (CManager::GetScene()->GetMode())
			{
				//�X�e�[�W�P�̎�
			case CScene::MODE::MODE_GAME01:
				CManager::SetMode(CScene::MODE::MODE_GAME02); //�X�e�[�W�Q�ɑJ��
				return;                                       //�����𔲂���

				//�X�e�[�W�Q�̎�
			case CScene::MODE::MODE_GAME02:
				CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ɑJ��
				return;                                       //�����𔲂���

				//�X�e�[�W�R�̎�
			case CScene::MODE::MODE_RESULT:
				CManager::SetMode(CScene::MODE::MODE_GAME01); //�X�e�[�W�P�ɑJ��
				return;                                       //�����𔲂���
			}
		}
	}

	//���S�������p
	else if (nType == SCENE_DIE_STAGE)
	{
		m_bNextStage = false;                                 //���̃X�e�[�W�̃t���O��Off�ɂ���
		CManager::SetMode(CScene::MODE::MODE_GAMEOVER);       //�Q�[���I�[�o�[�ɑJ��
		return;                                               //�����𔲂���
	}
}


//===============================================================================================================================================================================
//�ʏ��Ԏ��̊֐����܂Ƃ߂�֐�����
//===============================================================================================================================================================================
void CPlayerX::NormalStateSummarizeFunction()
{
	//�K�E�Z�̃J�E���g���K��l��荂����
	if (m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
	{
		Praticles();               //�p�[�e�B�N���̐��������֐����Ă�

		//�K�E�Z���J�E���g���K��l���Ⴂ��
		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHARGE); //BDM�𗬂�
		}
	}
	BlockJudgement();              //�I�u�W�F�N�g�Ƃ̓����蔻�菈���֐����Ă�
	UIJudgement();                 //UI�Ƃ̓����蔻�菈���֐����Ă�

	NowCreateNumberObj();          //�z�u�I�u�W�F�N�g��UI�𐶐����鏈���֐�
	NowCreateObjectUI();           //���ݍ���Ă���I�u�W�F�N�g��UI���o������

	//�K�E�Z�������Ă��Ȃ���
	if (SpecialAttack == false)
	{
		KeySet();                  //�L�[���Ƃ̏����֐����Ă�
	}
	else
	{
		//�e�����t���[�����O�ȏ�̎�
		if (m_nMotionFrame >= CObjectX::N_INIT_NUMBER)
		{
			m_nMotionFrame--;      //�t���[���𑝂₷
		}

		//�e�����t���[��001���O�ȏ�̎�
		if (m_nMotionFrame001 >= CObjectX::N_INIT_NUMBER)
		{
			m_nMotionFrame001--;   //�t���[���𑝂₷
		}

		//�����̃t���[�����O�ȉ��̎�
		else if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER)
		{
			SpecialAttack = false;     //�K�E�Z�t���O��Off�ɂ���
		}
	}
	Junp(TYPE::PLAYER, MAX_JUMPPAWER); //�W�����v�Əd�͏����֐����Ă�
}


//===============================================================================================================================================================================
//���������̊֐����܂Ƃ߂�֐�����
//===============================================================================================================================================================================
void CPlayerX::ShopStateSummarizeFunction()
{
	BlockJudgement();        //�u���b�N�Ƃ̓����蔻�菈���֐�
	ShopKeySet();            //�L�[���Ƃ̏���
}


//===============================================================================================================================================================================
//�����_������
//===============================================================================================================================================================================
void CPlayerX::Random()
{
	//�ŏ��l�{rand()%�ŏ��l���牽�����₷���@�i�T�������灓�U��������@�T�A�U�A�V�A�W�A�X�A�P�O�̍��v�U�ɂȂ�j
	//srand((unsigned)time(NULL));  //�����n���������
	SetRandom(MIN_RANDOM + rand() % MAX_RANDOM);  //�i�͈͎w��j
	m_nRandomCol = rand() % MAX_COL_RANDOM;       //�i�͈͎w��j
}


//===============================================================================================================================================================================
//�p�[�e�B�N�����o������
//===============================================================================================================================================================================
void CPlayerX::Praticles()
{
	Random();             //�����_���������Ă�
	m_nFrameParticle++;   //�t���[�������Z�����Ă���

	//�t���[��������̐��l�܂ōs������
	if (m_nFrameParticle >= MAX_PARTICLE_FRAME)
	{
		m_nFrameParticle = CObjectX::N_INIT_NUMBER; //�t���[��������������

		////�z��̍ő吔���ő吔��艺����
		//if (m_nPraticlesCount >= 0 && m_nPraticlesCount <= CInstance::MAX_OBJECT_DATA - 1)
		//{
		//	//�p�[�e�B�N���̐���
		//	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)GetPos().x + GetRandom(), GetPos().y+50.0f, CObjectX::F_INIT_NUMBER)); //�p�[�e�B�N���̐�������
		//	CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, 0, 0, m_nAlpha);//�F�̐ݒ�
		//	m_nPraticlesCount++; //�z���i�߂�
		//}

		////�ő吔�ɓ˓�
		//else
		//{
		//	m_nPraticlesCount = 0; //�z��J�E���g������������
		//}

		//�p�[�e�B�N���̐�������
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)GetPos().x + GetRandom(), GetPosParts(PLAYER_PARTS_BODY_NUMBER).y, CObjectX::F_INIT_NUMBER)); 

		//�F�̐ݒ�
		CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, CObjectX::N_INIT_NUMBER, CObjectX::N_INIT_NUMBER, m_nAlpha);
	}
}


//===============================================================================================================================================================================
//�L�[���Ƃ̏������܂Ƃ߂�֐�
//===============================================================================================================================================================================
void CPlayerX::KeySet()
{

	//=================================================
	//�K�E�Z�̔���
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_K) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_RB) == true)
	{
		//���킪����ꂽ���ƕK�E�Z�J�E���g���K��l��荂����
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == true && m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
		{
			SpecialAttack = true;                             //�K�E�Z�t���O��On�ɂ���  
			m_nSpecialAttackCount = CObjectX::N_INIT_NUMBER;  //�K�E�Z�J�E���g�̏�����

			//�E�����̎�
			if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI)
			{
				//�K�E�Z�̃G�t�F�N�g�̐���
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

				m_nMotionFrame = CManager::GetInstance()->GetSpecialAttack()->GetLife();                    //���[�V�����̃��C�t�𓯊�������
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = CSpecialAttack::ROT_NUMBER_1; //�T�C�Y�̐ݒ�p�̔ԍ���n��

				 //�G�t�F�N�g�̏o���ʒu��ݒ�
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + ROT_NUMBER_1_SPECIAL_EFFECT_PLUS_POS_Y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).z));
			}

			//�������̎�
			else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI)
			{
				//�K�E�Z�̃G�t�F�N�g�̐���
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

				m_nMotionFrame001 = CManager::GetInstance()->GetSpecialAttack()->GetLife();                 //���[�V�����̃��C�t�𓯊�������
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = CSpecialAttack::ROT_NUMBER_2; //�T�C�Y�̐ݒ�p�̔ԍ���n��

				  //�G�t�F�N�g�̏o���ʒu��ݒ�
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + ROT_NUMBER_2_SPECIAL_EFFECT_MINUS_POS_Y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).z));
			}
		}
	}

	//=================================================
	//A�L�[�������ꂽ���i�����ꑱ�������j
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_LEFT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI;                               //�J�����̌����ɍ��킹�Č���
		SetAdjustMove().x -= sinf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //X���̈ړ��ʂ��J�����̌������猸�Z
		SetAdjustMove().z -= cosf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //Z���̈ړ��ʂ��J�����̌������猸�Z
		m_nRotNumber = ROT_NUMBER_1;                                                                            //�����ԍ��̐ݒ�

		//�����ĂȂ���
		if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //�������[�V����
		}
	}

	//=================================================
	//D�L�[�������ꂽ���i�����ꑱ�������j
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_RIGHT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI;                         //�J�����̌����ɍ��킹�Č���
		GetMove().x += sinf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //X���̈ړ��ʂ��J�����̌���������Z
		GetMove().z += cosf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //Z���̈ړ��ʂ��J�����̌���������Z
		m_nRotNumber = ROT_NUMBER_2;                                                                      //�����ԍ��̐ݒ�

		//�����ĂȂ���
		if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //�������[�V����
		}
	}

	//=================================================
	//���̑�
	else
	{
		//�����ĂȂ����Ɛ������łȂ���
		if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER && m_bFly == false)
		{
			SpecialAttack = false;                                   //�K�E�Z�t���O��Off�ɂ���  
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::NEUTRAL); //�ҋ@���[�V����
		}
	}

	//=================================================
	//space�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_SPACE) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT); //BDM�𗬂�

		//�E�����̎�
		if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI)
		{
			m_nMotionFrame = GUN_FRAME_MOTION;    //�e�����t���[����ݒ�

			//�e�̐ݒ�
			CManagerBullet::Create(D3DXVECTOR3(GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + RIGHT_BULLET_PLUS_POS_X, GetPosParts(PLAYER_PARTS_GUN_NUMBER).y, GetPosParts(PLAYER_PARTS_GUN_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //����
		}

		//�������̎�
		else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI)
		{
			m_nMotionFrame001 = GUN_FRAME_MOTION; //�e�����t���[����ݒ�

			//�e�̐ݒ�
			CManagerBullet::Create(D3DXVECTOR3(GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + LEFT_BULLET_MINUS_POS_X, GetPosParts(PLAYER_PARTS_GUN_NUMBER).y, GetPosParts(PLAYER_PARTS_GUN_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, CObjectX::F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //����
		}
	}

	//=================================================
	//X�L�[��A�{�^���������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_X) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetJumpFlag(true);                                       //���ł���ɐݒ�
	}

	//=================================================
	//�L�[��������ĂȂ��A�W�����v�����Ă��鎞
	else if (GetJumpFlag() == true)
	{
		//�R���Q�[�W�̏�񂪂��鎞
		if (CManager::GetInstance()->GetFuelGage() != nullptr)
		{
			//X�L�[�������ꂽ����Joy�L�[��A�L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_X) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
			{
				//�`���[�W���������Ă��鎞
				if (CManager::GetInstance()->GetFuelGage()->GetChage() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = true;   //�R���Q�[�W���g���Ă���ɐݒ�
				}
			}
			else
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false;  //�R���Q�[�W���g���Ă��Ȃ��ɐݒ�
				SetGravityFlag(true);                                      //�d��ON
			}
		}
	}

	//=================================================
	//�E���̏e�Ɋւ���t���[���̏���
	if (m_nMotionFrame >= CObjectX::N_INIT_NUMBER)
	{
		m_nMotionFrame--;                            //�e�����t���[�������炷
		SetMotion(CCharacter::MOTIONSTATE::ACTION);  //���A�N�V�����̐ݒ�
	}

	//=================================================
	//�����̏e�Ɋւ���t���[������
	if (m_nMotionFrame001 >= CObjectX::N_INIT_NUMBER)
	{
		m_nMotionFrame001--;                          //�e�����t���[��001�����炷
		SetMotion(CCharacter::MOTIONSTATE::ACTION);	  //���A�N�V�����̐ݒ�
	}
}


//===============================================================================================================================================================================
//�V���b�v���̃L�[���Ƃ̏������܂Ƃ߂�֐�
//===============================================================================================================================================================================
void CPlayerX::ShopKeySet()
{
	//=======================================================================================================================================================
	//�ʏ��Ԃ̎�
	//=======================================================================================================================================================
	if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
	{
		//F1�L�[��Joy�L�[�̂x�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			//�I���Q�[�W�P�ڂ𐶐�����
			if (m_pSelectGage == nullptr)
			{
				m_pSelectGage = CSelectGage::Create(); //�I���Q�[�W�̐���
			}

			//�I���Q�[�W��ڂ𐶐�����
			if (m_pSelectGage001 == nullptr)
			{
				m_pSelectGage001 = CSelectGage001::Create(); //�I���Q�[�W001�̐���

				//�I���Q�[�W001�̑傫����ݒ�
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //��ڂ̃Q�[�W�̑傫���ɍ��킹��
			}

			//�w�iUI�𐶐�����
			if (CManager::GetInstance()->GetShopScreen() == nullptr)
			{
				CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCREEN, N_INIT_NUMBER); //�w�i�̐���
			}

			//���������邩��UI�𐶐�����
			if (m_pBuyText == nullptr)
			{
				m_pBuyText = CBuyText::Create(); //�����e�L�X�g�̐���
			}

			m_PlayerState = CPlayerX::PLAYER_STATE::SHOP_MODE; //���[�h��ύX����
		}
	}

	//=======================================================================================================================================================
	//SHOP��Ԃ̎�
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE)
	{
		//�t���O��Ԃ��ʏ펞�̎�
		if (m_FlagSate == CPlayerX::PLAYER_STATE::NORMAI_MODE)
		{
			SelectGageUISize(MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP1_SELECT_GAGE_SIXE2_X); //�I���Q�[�W1�ڂ̑傫����ݒ肷��
			m_FlagSate = CPlayerX::PLAYER_STATE::SHOP_MODE;                                  //�t���O��Ԃ�X�̏�Ԃ֕ω�������
		}

		//������I�������Ƃ��i�O����X�^�[�g�������͂O�ɖ߂�j
		if (m_nBuyOrSendCount == CObjectX::N_INIT_NUMBER)
		{
			//Enter�L�[������������Joy�L�[�̂a�L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
			{
				SelectGageUISize(MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP2_SELECT_GAGE_SIXE2_X); //�傫����ݒ�
				m_PlayerState = CPlayerX::PLAYER_STATE::BUY_MODE;                                //���[�h�𔃂����[�h�ɐݒ�
			}
		}

		//S�L�[�������ꂽ����Joy�L�[���L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			SelectGageUISizeCalculation("Plus", MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X, MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X); //�T�C�Y�𒲐�����
			m_nBuyOrSendCount++;                                                                                       //�J�E���g��i�߂�

			//�I���O�̐��l�ɂȂ�����
			if (m_nBuyOrSendCount == MODE_SHOP_DOWN_COUNT)
			{
				SelectGageUISize(MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP1_SELECT_GAGE_SIXE2_X); //�傫����߂�
				m_nBuyOrSendCount = MODE_SHOP_DOWN_COUNT-MODE_SHOP_SELECT_COUNT;                           //�J�E���g������������

			}
		}

		//W�L�[�������ꂽ����Joy�L�[�̏�L�[�������ꂽ��
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			SelectGageUISizeCalculation("Minus", MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X, MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X); //�T�C�Y�𒲐�����
			m_nBuyOrSendCount--;                                                                                        //�J�E���g�����炷

			//�I���O�̐��l�ɂȂ�����
			if (m_nBuyOrSendCount == MODE_SHOP_UP_COUNT)
			{
				//�T�C�Y�𒲐�
				SelectGageUISize(MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X+ MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X+ MODE_SHOP1_SELECT_GAGE_SIXE2_X); 

				m_nBuyOrSendCount = MODE_SHOP_UP_COUNT+MODE_SHOP_SELECT_COUNT; //�J�E���g������������

			}
		}

		//�L�[�������ꂽ��
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;  //�v���C���[�̏�Ԃ�ʏ��Ԃɐݒ�
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;     //�t���O��Ԃ�ʏ�̏�Ԃɐݒ�
		}
	}

	//=======================================================================================================================================================
	//������Ԃ̎�
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
	{
		//���������邩��UI��j������
		if (m_pBuyText != nullptr)
		{
			m_pBuyText->Release(); //��������
			m_pBuyText = nullptr;  //���𖳂���
			return;                //�����𔲂���
		}

		//���j���[�𐶐�����
		if (m_pMenyu == nullptr)
		{
			m_pMenyu = CManager2DUI::Create(CObject::TYPE_UI::SHOPMENU); //���j���[�̐���
		}

		//F1�L�[�������ꂽ����Joy�L�[�̂`�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();                             //�|�C���^�[�̏����������֐����Ă�
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;   //�v���C���[�̏�Ԃ�ʏ��Ԃɐݒ�
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;      //�t���O��Ԃ�ʏ�̏�Ԃɐݒ�
		}

		//S�L�[���������Ƃ�
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				SelectGageUISizeCalculation("Plus", ADJUST_SELECT_SIZEY, ADJUST_SELECT_SIZEY); //�T�C�Y�𒲐�����

				//�I���Q�[�W001�̑傫����ݒ�
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount ++; //�I���J�E���g�𑝂₷

				//�I���J�E���g������̒l�ɂȂ�����
				if (m_nSelectShopCount >= MODE_BUY_DOWN_COUNT)
				{
					m_pSelectGage->GetSizeY() = MODE_BUY_SELECT_GAGE_SIXE1_Y;   //�I���Q�[�W�̂P�ڂ�Y���̑傫����ݒ�
					m_pSelectGage->GetSize1Y() = MODE_BUY_SELECT_GAGE_SIXE2_Y;  //�I���Q�[�W�̂Q�ڂ�Y���̑傫����ݒ�

					//�I���Q�[�W001�̑傫����ݒ�
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = MODE_BUY_DOWN_COUNT - MODE_BUY_SELECT_COUNT; //�I���J�E���g�̏�����
				}
			}
		}

		//W�L�[���������Ƃ�
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			//�I���Q�[�W�̏�񂪂��鎞
			if (m_pSelectGage != nullptr)
			{
				SelectGageUISizeCalculation("Minus", ADJUST_SELECT_SIZEY, ADJUST_SELECT_SIZEY); //�T�C�Y�𒲐�����

				//�I���Q�[�W001�̃T�C�Y�𒲐�
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount --; //�I���J�E���g������

				//�I���J�E���g������̒l�̎�
				if (m_nSelectShopCount == MODE_BUY_UP_COUNT)
				{
					int nCount = MODE_BUY_UP_COUNT + MODE_BUY_SELECT_COUNT;                        //���ڐ��̐ݒ�i�S�̂̍��ڐ��[�K��l�j

					 //�T�C�Y�̐ݒ�i���炩���ߐݒ肵���T�C�Y�{�����l*�񐔁j
					float fSizeY = MODE_BUY_SELECT_GAGE_SIXE1_Y + ADJUST_SELECT_SIZEY * nCount;   
					float fSize1Y = MODE_BUY_SELECT_GAGE_SIXE2_Y + ADJUST_SELECT_SIZEY * nCount;

					m_pSelectGage->GetSizeY() = fSizeY;   //�I���Q�[�W�̂P�ڂ�Y���̑傫����ݒ�
					m_pSelectGage->GetSize1Y() = fSize1Y; //�I���Q�[�W�̂Q�ڂ�Y���̑傫����ݒ�

					//�I���Q�[�W001�̃T�C�Y�𒲐�
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = nCount;         //�I���J�E���g��ݒ�
				}
			}
		}

		//Enter�L�[������������Joy�L�[��B�L�[�������ꂽ��
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
		{
			CreateGun(); //�e�̐��������֐����Ă�
		}
	}
}


//===============================================================================================================================================================================
//�I���Q�[�W��UI�̃T�C�Y��ݒ肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISize(float fSIzeX,float fSIze1X)
{
	m_pSelectGage->GetSizeY() = fSIzeX;   //�I���Q�[�W�̂P�ڂ�Y���̑傫���������Ɠ���������
	m_pSelectGage->GetSize1Y() = fSIze1X; //�I���Q�[�W�̂Q�ڂ�Y���̑傫���������Ɠ���������

	//�I���Q�[�W�Q�ڂ̑傫���𓯊�������
	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
}

//===============================================================================================================================================================================
//�I���Q�[�W��UI�̃T�C�Y��ݒ肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISizeCalculation(const char* aSelect,float fSIzeX, float fSIze1X)
{
	//������Ŕ���
	if (aSelect == "Plus")
	{
		m_pSelectGage->SetAddjustSizeY() += fSIzeX;    //�I���Q�[�W�̂P�ڂ�Y���̑傫���������Ɠ����������Z����
		m_pSelectGage->SetAddjustSize1Y() += fSIze1X;  //�I���Q�[�W�̂Q�ڂ�Y���̑傫���������Ɠ����������Z����
	}
	else if (aSelect == "Minus")
	{
		m_pSelectGage->SetAddjustSizeY() -= fSIzeX;    //�I���Q�[�W�̂P�ڂ�Y���̑傫���������Ɠ����������Z����
		m_pSelectGage->SetAddjustSize1Y() -= fSIze1X;  //�I���Q�[�W�̂Q�ڂ�Y���̑傫���������Ɠ����������Z����
	}

	//�I���Q�[�W�Q�ڂ̑傫����ݒ�
	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
}


//===============================================================================================================================================================================
//���퐶������
//===============================================================================================================================================================================
void CPlayerX::CreateGun()
{
	//��Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_0)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //�`�悷��
		}
	}

	//��Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_1)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //�`�悷��
		}
	}

	//�O�Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_2)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //�`�悷��
		}
	}

	//�l�Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_3)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //�`�悷��
		}
	}

}

//===============================================================================================================================================================================
//�`�揈��
//===============================================================================================================================================================================
void CPlayerX::Draw()
{
	CCharacter::DrawPlayer(MAX_PARTS); //�p�[�c���Ƃ̕`�揈��
}

//===============================================================================================================================================================================
//�u���b�N�̓����蔻��
//===============================================================================================================================================================================
void CPlayerX::BlockJudgement()
{
	int nInitNumber = CObjectX::N_INIT_NUMBER; //�����l

	//=================================
	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = nInitNumber; nCount < m_nFieldBlock; nCount++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			//�����蔻��
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.05f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y + CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}

					//���n���Ă��Ȃ���
					if (m_bLandingFlag == false)
					{
						m_nLandingFrame++; //���n�t���[����ݒ�

						SetMotion(MOTIONSTATE::LANDING); //���n���[�V�����̐ݒ�

						//���n�t���[�����K��l��荂����
						if (m_nLandingFrame >= MAX_LANDING_FRAME)
						{
							m_bLandingFlag = true;                     //���n���Ă���ɐݒ�
							m_nLandingFrame = CObjectX::N_INIT_NUMBER; //���n�t���[���̏�����
							CManager::GetScene()->SetPlay(true);       //�V�ׂ�ɐݒ�
						}
					}
				}
			}
		}
	}

	//=================================
	//�オ��p�̃u���b�N�̐���������
	for (int nCount1 = nInitNumber; nCount1 < m_nGoUpBlock; nCount1++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetGoUpBlock(nCount1) != nullptr)
		{
			//�����蔻��
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize().y + CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//=================================
	//���p�u���b�N����
	for (int nCount2 = nInitNumber; nCount2 < m_nRoadBlock; nCount2++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			//�����蔻��
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether();//�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//=================================
	//�ǌ����p�u���b�N����
	for (int nCount3 = nInitNumber; nCount3 < m_nWallRoadBlock; nCount3++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			if (GetCollision() ->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//=================================
	//�ǌ���001�p�u���b�N����
	for (int nCount4 = nInitNumber; nCount4 < m_nWallRoadBlock001; nCount4++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			//��ɏ���Ă��鎞
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				//�R���Q�[�W���g���Ă��鎞
				if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
				}

				GravityTogether(); //�d�͂̓���

				//�ʒu�̓���
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;

				//���ł���
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
				}
			}
		}
	}

	//=================================
	//�������u���b�N����
	for (int nCount5 = nInitNumber; nCount5 < m_nSmalBlock; nCount5++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetSmallBlock(nCount5) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize() * 1.3f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//=================================
	//�������u���b�N001����
	for (int nCount7 = nInitNumber; nCount7 < m_nSmalBlock001; nCount7++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetSmallBlock001(nCount7) != nullptr)
		{
			//��ɏ���Ă��鎞
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				//�R���Q�[�W���g���Ă��鎞
				if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
				}

				GravityTogether(); //�d�͂̓���

				//�ʒu�̓���
				GetPos().y = CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos().y;


				//���ł���
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
				}
			}

			//���ɓ������Ă��鎞
			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				//���ł���
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
				}
			}
		}
	}

	////��ǃu���b�N����
	//for (int nCount6 = 0; nCount6 < CManager::GetInstance()->GetUpWallBlockCount() + 1; nCount6++)
	//{
	//	if (CManager::GetInstance()->GetUpBlock(nCount6) != nullptr)
	//	{
	//		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//		{
	//			//GetPos().x = 100.0f;
	//		}
	//		else
	//		{
	//			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//			{
	//				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
	//				GravityTogether();
	//				GetPos().y = CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize().y + CManager::GetInstance()->GetUpBlock(nCount6)->GetPos().y;//y���̈ʒu��ݒ�
	//				if (GetJumpFlag() == true)
	//				{
	//					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
	//				}
	//			}
	//			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//			{
	//				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
	//				GravityTogether();
	//				SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
	//			}
	//		}
	//	}
	//}

	
	//=================================
	//�{�X��̑���
	if (CManager::GetInstance()->GetFinalBlock() != nullptr)
	{
		//��ɏ���Ă��鎞
		if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFinalBlock()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalBlock()->GetModelSize(), GetMove()) == true)
		{
			//�R���Q�[�W���g���Ă��鎞
			if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
			}

			GravityTogether(); //�d�͂̓���

			//�ʒu�̓���
			GetPos().y = CManager::GetInstance()->GetFinalBlock()->GetModelSize().y + CManager::GetInstance()->GetFinalBlock()->GetPos().y;

			//���ł���
			if (GetJumpFlag() == true)
			{
				SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
			}
		}
	}

	//=================================
	//�{�X��̓V��
	if (CManager::GetInstance()->GetFinalCeiling() != nullptr)
	{
		//���ɓ������Ă��鎞
		if (GetCollision()->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize(), GetMove()) == true)
		{
			//SetPos(D3DXVECTOR3(GetPos().x,GetPos().y-100.0f,GetPos().z));
			SetGravityFlag(true);//�d��ON
			////���ɓ������Ă��鎞
			//if (GetCollision()->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize(), GetMove()) == true)
			//{
			//	SetGravityFlag(true);//�d��ON
			//	//CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CObjectX::F_INIT_NUMBER;
			//}
			//else
			//{
			//	CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CEvent::CANERA_POSY;    //�J�����̂x���̒l��ݒ�
			//}
		}
		//else
		//{
		//	CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CEvent::CANERA_POSY;    //�J�����̂x���̒l��ݒ�
		//}
	}

	//=================================
	//�o�g���V�b�v�Ƃ̓����蔻��
	if (CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP) != nullptr)
	{
		//�����蔻��
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetModelSize() * ADJUST_HIT_BATTLE) == true)
		{
			//NextStageMotion();
			m_bPlayerMoveNext = true; //����scene�֍s���t���t��ON�ɂ���
		}
	}

	//=================================
	//SHOP�Ƃ̓����蔻��
	if (CManager::GetInstance()->GetShop() != nullptr)
	{
		//�����蔻��
		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize(), GetMove()) == true)
		{

		}

		//�~�̓����蔻��
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize() * 1.5f) == true)
		{
			//�b��text�̏�񂪂Ȃ���
			if (m_pTalkText == nullptr)
			{
				m_pTalkText = CUI::Create(CObject3D::TYPE::TALKTEXTR); //����

				//�ʒu�̐ݒ�
				m_pTalkText->GetPos() = D3DXVECTOR3(CManager::GetInstance()->GetShop()->GetPos().x, CManager::GetInstance()->GetShop()->GetPos().y + 150.0f, CManager::GetInstance()->GetShop()->GetPos().z); //�ʒu�̏�����
			}

			//�v���C���[�̏�Ԃ��ʏ��Ԃ̎�
			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				ShopKeySet(); //�X�p�̃L�[�Z�b�g�����֐����Ă�
			}
		}

		//�������Ă��Ȃ���
		else
		{
			//�b��text�̏�񂪂��鎞
			if (m_pTalkText != nullptr)
			{
				m_pTalkText->Release(); //��������
				m_pTalkText = nullptr;  //���𖳂���
			}
		}
	}
}

//===============================================================================================================================================================================
//UI�̓����蔻��
//===============================================================================================================================================================================
void CPlayerX::UIJudgement()
{
	int nInitNumber = CObjectX::N_INIT_NUMBER; //�����l

	//���[�U�[�̐�����
	for (int nLaser = nInitNumber; nLaser < m_nLaserCount; nLaser++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetLaser(nLaser) != nullptr)
		{
			//�v���C���[�̊e�p�[�c���̓����蔻�菈��
			for (int nCount = nInitNumber; nCount < CObjectX::MAX_PARTS; nCount++)
			{
				//�����蔻�菈��
				if (GetCollision()->ColiisionBox3D(CManager::GetInstance()->GetLaser(nLaser)->GetPos(), GetPosParts(nCount),
					CLaserCamare::TOTALVALUE_X, CLaserCamare::TOTALVALUE_Y, CLaserCamare::TOTALVALUE_Z, GetModelSizeParts(nCount)) == true)
				{
					CManager::GetInstance()->GetLaser(nLaser)->Hit();                             //���[�U�[�̓����������̏������Ă�
					CManager::GetInstance()->GetLaser(nLaser)->Release();                         //���[�U�[���폜����
					CManager::GetInstance()->DesignationUninit3D(CObject3D::TYPE::LASER, nLaser); //���[�U�[�|�C���^�[��nullptr�ɂ���
					return;                                                                       //�����𔲂���
				}
			}
		}
	}
}

//=====================================================================
//���̃X�e�[�W�ɍs�����̃��[�V��������(��ɃX�y�[�X�V�b�v�̏���)
//=====================================================================
void CPlayerX::NextStageMotion()
{
	m_nNextStageFrame++;        //�t���[���𑝂₷

	SetPos(D3DXVECTOR3(
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos().x,
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos().y + PLUS_POS_Y,
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos().z + MINUS_POS_Z));
	//GetPos().y= CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos().y;

	//���s��
	if (m_nNextStageFrame <= ATTACKPATTEN_FRAME_1)
	{
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetRot().y = -D3DX_PI_ORI;  //Y���̌�����ݒ�
	}

	//���s��
	else if (m_nNextStageFrame <= ATTACKPATTEN_FRAME_2)
	{
		//X���̈ړ�
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->SetAdjustPos().x += (float)m_nNextStageFrame * MAX_POS_NEXTSTAGE;
		SetAdjustPos().x += (float)m_nNextStageFrame * MAX_POS_NEXTSTAGE;
	}

	//�I��
	else
	{
		m_bNextStage = true; //����scene�֍s���t���t��ON�ɂ���
	}
}

//===============================================================================================================================================================================
//���f���̎擾
//===============================================================================================================================================================================
CPlayerX* CPlayerX::Create()
{
	CPlayerX* pPlayerX = new CPlayerX(); //���I�m��

	//�������ɐ���������
	if (SUCCEEDED(pPlayerX->Init()))
	{
		pPlayerX->SetType(TYPE::PLAYER); //�^�C�v��PLAYER�ɐݒ�
		return pPlayerX;                 //�v���C���[�̏���Ԃ�
	}

	return nullptr; //����Ԃ�
}


//===============================================================================================================================================================================
//���ݍ���Ă���I�u�W�F�N�g��UI���o������
//===============================================================================================================================================================================
void CPlayerX::NowCreateObjectUI()
{
	//�P�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_1) == true)
	{
		//���̑Ώۂ̃I�u�W�F�N�g�̔ԍ����O�ȉ�
		if (m_ObjectNumber <= CObjectX::N_INIT_NUMBER)
		{
			m_ObjectNumber = MAX_TEXT_OBJECT; //������Ă��鐔�ɂ���
		}
		else
		{
			m_ObjectNumber--;                 //���炷
		}

		//��񂪂��鎞
		if (m_pNowCreateUI != nullptr)
		{
			m_pNowCreateUI->Release(); //��������
			m_pNowCreateUI = nullptr;  //���𖳂���
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}

		//��񂪂Ȃ���
		if (m_pNowCreateUI == nullptr)
		{
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}
	}

	//�Q�L�[�������ꂽ��
	else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_2) == true)
	{
		//�I�u�W�F�N�g�i���o�[����������Ă��鐔�ȏ�̎�
		if (m_ObjectNumber >= MAX_TEXT_OBJECT)
		{
			m_ObjectNumber = CObjectX::N_INIT_NUMBER; //������
		}
		else
		{
			m_ObjectNumber++;   //���₷
		}

		//��񂪂��鎞
		if (m_pNowCreateUI != nullptr)
		{
			m_pNowCreateUI->Release(); //��������
			m_pNowCreateUI = nullptr;  //����Ԃ�
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}

		//��񂪂Ȃ���
		if (m_pNowCreateUI == nullptr)
		{
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}
	}
}

//===============================================================================================================================================================================
//�ԍ��ō��I�u�W�F�N�g���w�肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::NowCreateNumberObj()
{
	//�d������鎞�̂�m_pLaserUI���K�v

	switch (m_ObjectNumber)
	{
	case CREATE_FIELDBLOCK:
		CObjectX::ObjectArrangement(TYPE::FIELDBLOCK, nullptr);                //�n�ʂ̔z�u����
		break;

	case CREATE_TELEPHONPOLE:
		CObjectX::ObjectArrangement(CObjectX::TYPE::TELEPHONPOLE, m_pLaserUI); //�d���̔z�u����
		break;

	case CREATE_GOUPBLOCK:
		CObjectX::ObjectArrangement(TYPE::GOUPBLOCK, nullptr);                 //�オ��p�u���b�N�̔z�u����
		break;
	}
}