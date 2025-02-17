//===========================================================================================================
//
//�L�����N�^�[�̊e�p�[�c�̏���[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================


//=============================
//�C���N���[�h
#include "character.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//=====================~
CCharacter::CCharacter(int nPriority) : CObjectX(nPriority)
{
	//�v���C���[�̃p�[�c������
	for (int nCount = N_INIT_NUMBER; nCount < MAX_PARTS; nCount++)
	{
		m_pModelPrts[nCount] = nullptr;                                                   //�v���C���[�̃p�[�c�̏�����
		SaveMotionPos[nCount] = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�e�p�[�c�̏ꏊ�̕ۊǏꏊ�̏�����
		m_pSaveModelPrtInfo[nCount] = {};                                                 //���f���p�[�c�̕ۊǏ��̏�����
	}

	//�{�X�̃p�[�c������
	for (int nCount1 = N_INIT_NUMBER; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_pModelPrtsBoss[nCount1] = nullptr;                                                   //�{�X�̃p�[�c�̏�����
		SaveMotionPosBoss[nCount1] = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�e�p�[�c�̏ꏊ�̕ۊǏꏊ�̏�����
		m_pSaveModelPrtInfoBoss[nCount1] = {};						                           //���f���p�[�c�̕ۊǏ��̏�����
	}

	m_nMotionFrameBoss = N_INIT_NUMBER;  //�{�X�̃��[�V�������̃t���[����������
	MotionCount = N_INIT_NUMBER;         //�v���C���[�̃��[�V�����J�E���g�̏�����
	MotionCountBoss = N_INIT_NUMBER;     //�{�X�̃��[�V�����J�E���g�̏�����
	m_bMotionType = false;               //�v���C���[�̃��[�V��������̏�����
	m_bMotionBossType = false;           //�{�X�̃��[�V��������̏�����
	m_MotionState = NEUTRAL;             //�v���C���[�̃��[�V�����̏�Ԃ̏�����
	m_MotionStateBoss = BOSSNEUTRAL;     //�{�X�̃��[�V������Ԃ̏�����
}


//======================
//�f�X�g���N�^
//======================
CCharacter::~CCharacter()
{

}


//=======================
//����������
//=======================
HRESULT CCharacter::Init()
{
	//�������ɐ������邩�ǂ���
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //�����Ԃ�
}


//========================
//�j������
//========================
void CCharacter::Uninit()
{
	CObjectX::Uninit(); //�j���������Ă�

	//�v���C���[�̃p�[�c����
	for (int nCount = N_INIT_NUMBER; nCount < MAX_PARTS; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Uninit();  //�j���������Ă�
			delete m_pModelPrts[nCount];     //�����폜����
			m_pModelPrts[nCount] = nullptr;  //���𖳂���
		}
	}

	//�{�X�̃p�[�c����
	for (int nCount1 = N_INIT_NUMBER; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsBoss[nCount1] != nullptr)
		{
			m_pModelPrtsBoss[nCount1]->Uninit();  //�j������
			delete m_pModelPrtsBoss[nCount1];     //�����폜����
			m_pModelPrtsBoss[nCount1] = nullptr;  //���𖳂���
		}
	}
}

//========================
//�v���C���[�X�V����
//========================
void CCharacter::UpdatePlayer()
{
	MotionInfo(); //���[�V�������s���������Ă�

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = N_INIT_NUMBER; nCount < MAX_PARTS - CREATE_GUN_COUNT; nCount++)
	{
		//�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
		GetPosParts(nCount) = D3DXVECTOR3(SaveMotionPos[nCount].x + CManager::GetScene()->GetPlayerX()->GetPos().x, SaveMotionPos[nCount].y + CManager::GetScene()->GetPlayerX()->GetPos().y, SaveMotionPos[nCount].z + CManager::GetScene()->GetPlayerX()->GetPos().z);
	}

	//�������̎�
	if (GetRot().y >= D3DX_PI_ORI_HALF)
	{
		int nRightHand = PLAYER_PARTS_RIGHTHAND_NUMBER; //�E��

		//�e�̊J�n�ԍ�����I���܂ŉ�
		for (int nGun = MAX_PARTS - CREATE_GUN_COUNT; nGun < MAX_PARTS; nGun++)
		{
			//�e�̈ʒu���E��ƌ��݂̈ʒu�Őݒ�
			GetPosParts(nGun) = D3DXVECTOR3(SaveMotionPos[nRightHand].x + CManager::GetScene()->GetPlayerX()->GetPos().x, SaveMotionPos[nRightHand].y + CManager::GetScene()->GetPlayerX()->GetPos().y, SaveMotionPos[nRightHand].z + CManager::GetScene()->GetPlayerX()->GetPos().z);
		}
	}

	//�E�����̎�
	else if (GetRot().y <= -D3DX_PI_ORI_HALF)
	{
		int nLeftHand = PLAYER_PARTS_LEFTHAND_NUMBER; //����

		//�e�̊J�n�ԍ�����I���܂ŉ�
		for (int nGun1 = MAX_PARTS - CREATE_GUN_COUNT; nGun1 < MAX_PARTS; nGun1++)
		{
			//�e�̈ʒu������ƌ��݂̈ʒu�Őݒ�
			GetPosParts(nGun1) = D3DXVECTOR3(-SaveMotionPos[nLeftHand].x + CManager::GetScene()->GetPlayerX()->GetPos().x, SaveMotionPos[nLeftHand].y + CManager::GetScene()->GetPlayerX()->GetPos().y, SaveMotionPos[nLeftHand].z + CManager::GetScene()->GetPlayerX()->GetPos().z);
		}
	}
}


//============================
//�{�X�̍X�V����
//============================
void CCharacter::UpdateBoss()
{
	MotionInfoBoss(); //���[�V�������s���������Ă�

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = N_INIT_NUMBER; nCount < MAX_BOSSPARTS-1; nCount++)
	{
		//�㔼�g
		if (nCount <= PLAYER_PARTS_LEFTHAND_NUMBER)
		{
			//�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
			GetPosPartsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + CManager::GetInstance()->GetBoss()->GetPos().x, SaveMotionPosBoss[nCount].y + CManager::GetInstance()->GetBoss()->GetPos().y+ BOSS_PLUS_POS_Y, SaveMotionPosBoss[nCount].z + CManager::GetInstance()->GetBoss()->GetPos().z);
		}

		//�����g
		else if (nCount >= BOSS_PARTS_WAIST_NUMBER)
		{
			//�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
			GetPosPartsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + CManager::GetInstance()->GetBoss()->GetPos().x, SaveMotionPosBoss[nCount].y + CManager::GetInstance()->GetBoss()->GetPos().y + BOSS_PLUS_POS_Y, SaveMotionPosBoss[nCount].z + CManager::GetInstance()->GetBoss()->GetPos().z);
		}
	}

	//�������̎�
	if (GetRot().y >= D3DX_PI_ORI_HALF)
	{
		int nRightHand = BOSS_PARTS_RIGHTHAND_NUMBER; //�E��

		//�e�̈ʒu���E��ƌ��݂̈ʒu�Őݒ�
		GetPosPartsBoss(BOSS_PARTS_GUN_NUMBER) = D3DXVECTOR3(SaveMotionPosBoss[nRightHand].x + CManager::GetInstance()->GetBoss()->GetPos().x, SaveMotionPosBoss[nRightHand].y + CManager::GetInstance()->GetBoss()->GetPos().y+ BOSS_PLUS_POS_Y, SaveMotionPosBoss[nRightHand].z + CManager::GetInstance()->GetBoss()->GetPos().z);
	}

	//�E�����̎�
	else if (GetRot().y <= -D3DX_PI_ORI_HALF)
	{
		int nLeftHand = BOSS_PARTS_LEFTHAND_NUMBER;  //����

		//�e�̈ʒu������ƌ��݂̈ʒu�Őݒ�
		GetPosPartsBoss(BOSS_PARTS_GUN_NUMBER) = D3DXVECTOR3(-SaveMotionPosBoss[nLeftHand].x + CManager::GetInstance()->GetBoss()->GetPos().x, SaveMotionPosBoss[nLeftHand].y + CManager::GetInstance()->GetBoss()->GetPos().y+ BOSS_PLUS_POS_Y, SaveMotionPosBoss[nLeftHand].z + CManager::GetInstance()->GetBoss()->GetPos().z);
	}

	/*D3DXVECTOR3 pos = CManager::GetInstance()->GetBoss()->GetPos();
	D3DXVECTOR3 posq = GetPos();*/

	//����̍X�V
	//int nCount1 = 5;
	//GetPosPartsBoss(17) = D3DXVECTOR3(SaveMotionPosBoss[nCount1].x + pos.x, SaveMotionPosBoss[nCount1].y + pos.y, SaveMotionPosBoss[nCount1].z + pos.z);     //����p�[�c��ۊǒl�{���݂̒l�ŏC��

}

//========================
//�v���C���[�̕`�揈��
//========================
void CCharacter::DrawPlayer(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld(); //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                      //�ʒu�ƌ������擾����ׂ̕ϐ�

	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = N_INIT_NUMBER; nCount < NumPrts; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//========================
//�{�X�̕`�揈��
//========================
void CCharacter::DrawBoss(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();  //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                       //�ʒu�ƌ������擾����ׂ̕ϐ�

	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = N_INIT_NUMBER; nCount < NumPrts; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsBoss[nCount] != nullptr)
		{
			m_pModelPrtsBoss[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}


//======================
//���[�h����
//======================
void CCharacter::Lood()
{
	int nCount = N_INIT_NUMBER;                      //�ŏ��̃p�[�c�����J�E���g���邽�߂̕ϐ�
	int nKeyCount = N_INIT_NUMBER;                   //���[�V�����̃L�[���J�E���g���邽�߂̕ϐ�
	int nModelPrtsCount = N_INIT_NUMBER;             //��������p�[�c���̃J�E���g���邽�߂̕ϐ�
	int nMotionCount = N_INIT_NUMBER;                //���[�V�����̐����J�E���g���邽�߂̕ϐ�
	int nKeySetCount = N_INIT_NUMBER;                //���[�V�����̃L�[�Z�b�g�̐����J�E���g���邽�߂̕ϐ�

	char aPrtsPass[MAX_PARTS_SEARCH];                //�e�p�[�c��ǂݎ��ۂ̃p�X��ǂݍ��ނ��߂̕ϐ�
	char m_aDataSearch[MAX_DATA_SEARCH];             //�K�v�ȏ���ǂݎ��ۂ̕������ǂ݂ނ��߂̕ϐ�
								         
	FILE* m_pFile = nullptr;                         //�t�@�C���|�C���^�[

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normal.txt", "r"); //�t�@�C�����J��

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	int nLoopNumber = CObjectX::WHILE_NUMBER;  //���[�v�̏����l

	//���[�v
	while (nLoopNumber)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		//���̕�����ǂݎ������
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//���[�v
			while (nLoopNumber)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c�̎擾

					//���f���p�[�c�J�E���g���ő吔��菬������
					if (nModelPrtsCount < MAX_PARTS)
					{
						//��񂪂Ȃ���
						if (m_pModelPrts[nModelPrtsCount] == nullptr)
						{
							//�p�[�c�̐���
							m_pModelPrts[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER), 
								D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER),
								&aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());

							//���𓯊�������
							m_pModelPrts[nModelPrtsCount]->BindSize(GetMaxParts(nModelPrtsCount), GetMinParts(nModelPrtsCount), GetModelSizeParts(nModelPrtsCount));                                                        
						}
						nModelPrtsCount++; //�z���i�߂�
					}
				}

				//�I������
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //�����𔲂���
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//���[�v
					while (nLoopNumber)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						//�I������
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //�����𔲂���
						}

						//�����𑱍s���������
						if (m_aDataSearch[N_INIT_NUMBER] == '#')
						{
							continue; //���s
						}

						//�p�[�c�̏��̓ǂݍ���
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//���[�v
							while (nLoopNumber)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

								//�I������
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //�����𔲂���
								}

								//�C���f�b�N�X��ǂݎ�����
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->GetIndexPrts()); //�p�[�c�̃C���f�b�N�X��ǂݎ��
								}

								//�e�p�[�c���ǂ�����ǂݎ�����
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->GetIndexModelPrts()); //�e�p�[�c����ǂݎ��

									//�ǂݍ��񂾒l���[�P�̎�
									if (m_pModelPrts[nCount]->GetIndexModelPrts() == PARENT_NUMBER)
									{
										m_pModelPrts[nCount]->SetParent(nullptr); //��񖳂�
									}

									//���̑�
									else
									{
										m_pModelPrts[nCount]->SetParent(m_pModelPrts[m_pModelPrts[nCount]->GetIndexModelPrts()]); //�e�ł����������
									}
								}

								//�ʒu�̓ǂݍ��ݏ���
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									//�ʒu�̓���
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->GetPos().x, &m_pModelPrts[nCount]->GetPos().y, &m_pModelPrts[nCount]->GetPos().z);
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrts[nCount]->GetPos();                     //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfo[nCount].pos += MotionSetPlayer[0].KeySet[0].aKey[nCount].pos;  
								}

								//�����̓ǂݍ��ݏ���
								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									//�����̓���
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->GetRot().x, &m_pModelPrts[nCount]->GetRot().y, &m_pModelPrts[nCount]->GetRot().z);
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrts[nCount]->GetRot();                     //������ۊǂ���
									//m_pSaveModelPrtInfo[nCount].rot += MotionSetPlayer[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //�ǂݎ��p�[�c�̔ԍ��𑝂₷
						}

					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = N_INIT_NUMBER; //���[�v���邩�ǂ����̔���p�ϐ�

					//���[�v
					while (nLoopNumber)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						//�����𑱍s�������
						if (m_aDataSearch[N_INIT_NUMBER] == '#')
						{
							continue;                                      //���s
							fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile);  //�t�@�C�����當�����ǂݍ���
						}

						//�I������
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //�����𔲂���
						}

						//���[�v���ǂ������肷�����
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //����
							(void)fscanf(m_pFile, "%d", &LoopType);     //���[�v���邩�ǂ�������

							//�ǂݍ��񂾒l���O�̎�
							if (LoopType == N_INIT_NUMBER)
							{
								MotionSetPlayer[nMotionCount].Loop = false; //���[�v���Ȃ�
							}

							//���̑�
							else
							{
								MotionSetPlayer[nMotionCount].Loop = true;  //���[�v����
							}
						} 

						//�L�[�̓ǂݍ��ݏ���
						else if (!strcmp(m_aDataSearch, "NUM_KEY"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                         //����
							(void)fscanf(m_pFile, "%d", &MotionSetPlayer[nMotionCount].NumKey);  //�L�[�̐�������
						}

						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							//���[�v
							while (nLoopNumber)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[N_INIT_NUMBER] == '#')
								{
									fgets(m_aDataSearch, FGET_NUMBER_2, m_pFile); //�t�@�C�����當�����ǂݍ���
									continue;                          //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //�����𔲂���
								}

								//�t���[����ǂݎ�����
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									//�t���[����������
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].Frame);
								}
									
								//�L�[�̒��g�̏���ǂݎ�����
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//���[�v
									while (nLoopNumber)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[N_INIT_NUMBER] == '#')
										{
											continue;                                      //�����𑱂���
											fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile);  //�t�@�C�����當�����ǂݍ���
										}

										//�ʒu�̏���ǂݎ�����
										if (!strcmp(m_aDataSearch, "POS"))
										{
											//�ʒu�̓���
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z);
											//GetPos() = MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nCount].pos;
										}

										//�����̏���ǂݎ�����
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											//�����̓���
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z);
										}

										//�I������
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //�����𔲂���
										}
									}
									nKeyCount++;   //�L�[�J�E���g�̉��Z
								}
							}
							nKeyCount = N_INIT_NUMBER;   //�L�[�J�E���g��������
							nKeySetCount++;            //�f�[�^�̉��Z
						}
					}
					nKeySetCount = N_INIT_NUMBER; //�J�E���g�̏�����
					nMotionCount++;             //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile); //�t�@�C�������
			break;           //�����𔲂���
		}
	}

	//=================================================================================================================================================================
	//�e�p�[�c�̈ʒu�̎擾
	//=================================================================================================================================================================

	//�������܂ł̈ʒu���擾����
	for (int nCount = N_INIT_NUMBER; nCount < PLAYER_PARTS_SHOULDER_FROM_HAND; nCount++)
	{
		//���݂̃p�[�c�̎��̃p�[�c����(��̏ꍇ�A�������r���牺�r�����̏��ɂȂ邪�A�r�͎�̏��܂ł���Ȃ��̂Ō��݂̃p�[�c�{�P�ő��₵�Ă���)
		for (int Next = N_INIT_NUMBER; Next < nCount + PLAYER_NEXT_PARTS_COUNT; Next++)
		{
			//�E���̃p�[�c��
			SaveMotionPos[nCount + PLAYER_PARTS_RIGHT_SHOULDER_FROM_HAND] += m_pSaveModelPrtInfo[Next + PLAYER_PARTS_RIGHT_SHOULDER_FROM_HAND].pos;

			//�����̃p�[�c��
			SaveMotionPos[nCount + PLAYER_PARTS_LEFT_SHOULDER_FROM_HAND] += m_pSaveModelPrtInfo[Next + PLAYER_PARTS_LEFT_SHOULDER_FROM_HAND].pos;
		}

		SaveMotionPos[nCount + PLAYER_PARTS_RIGHT_SHOULDER_FROM_HAND] += m_pModelPrts[PLAYER_PARTS_BODY_NUMBER]->GetPos(); //�ʒu�����Z
		SaveMotionPos[nCount + PLAYER_PARTS_LEFT_SHOULDER_FROM_HAND] += m_pModelPrts[PLAYER_PARTS_BODY_NUMBER]->GetPos();  //�ʒu�����Z
	}

	//�����g��parts�̈ʒu���擾(�����牺�Ȃ̂ō��ԍ��{�P)
	for (int nCount1 = PLAYER_PARTS_WAIST_NUMBER + PLAYER_NEXT_PARTS_COUNT; nCount1 <= PLAYER_PARTS_LOWER_BODY_COUNT + PLAYER_PARTS_WAIST_NUMBER ; nCount1++)
	{
		SaveMotionPos[nCount1] += m_pModelPrts[nCount1]->GetPos();         //�����g�̊e�p�[�c

		//���Ɛe�p�[�c����
		for (int PARENT = PLAYER_PARTS_WAIST_NUMBER; PARENT < nCount1; PARENT++)
		{
			SaveMotionPos[nCount1].y += m_pModelPrts[PARENT]->GetPos().y;  //���̕�����(���̈ʒu�[�e�p�[�c)
		}
	}

	//���Ƒ̂̈ʒu���擾����
	for (int nCount2 = N_INIT_NUMBER; nCount2 < PLAYER_PARTS_HEAD_AND_BODY_COUNT; nCount2++)
	{
		SaveMotionPos[nCount2] += m_pModelPrts[nCount2]->GetPos(); //�ʒu�����Z
		//GetPosParts(nCount2) = D3DXVECTOR3(SaveMotionPos[nCount2].x + GetPos().x, SaveMotionPos[nCount2].y + GetPos().y + 20.0f, SaveMotionPos[nCount2].z + GetPos().z); //�p�[�c�̈ʒu���C��
	}

	////�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	//for (int nCount3 = 0; nCount3 < NUM_RIGHTLEFTPRTS*2; nCount3++)
	//{
	//	GetPosParts(nCount3 + 2) = D3DXVECTOR3(SaveMotionPos[nCount3 + 2].x + GetPos().x, SaveMotionPos[nCount3 + 2].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 2].z + GetPos().z);      //�p�[�c�̈ʒu���C��
	//	GetPosParts(nCount3 + 10) = D3DXVECTOR3(SaveMotionPos[nCount3 + 10].x + GetPos().x, SaveMotionPos[nCount3 + 10].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 10].z + GetPos().z);  //�p�[�c�̈ʒu���C��
	//}
}

//======================
//�{�X�̃��[�h����
//======================
void CCharacter::LoodBoss()
{
	int nCount = N_INIT_NUMBER;                       //�ŏ��̃p�[�c�����J�E���g���邽�߂̕ϐ�
	int nKeyCount = N_INIT_NUMBER;                    //���[�V�����̃L�[���J�E���g���邽�߂̕ϐ�
	int nModelPrtsCount = N_INIT_NUMBER;              //��������p�[�c���̃J�E���g���邽�߂̕ϐ�
	int nMotionCount = N_INIT_NUMBER;                 //���[�V�����̐����J�E���g���邽�߂̕ϐ�
	int nKeySetCount = N_INIT_NUMBER;                 //���[�V�����̃L�[�Z�b�g�̐����J�E���g���邽�߂̕ϐ�

	char aPrtsPass[MAX_PARTS_SEARCH];                 //�e�p�[�c��ǂݎ��ۂ̃p�X��ǂݍ��ނ��߂̕ϐ�
	char m_aDataSearch[MAX_DATA_SEARCH];              //�K�v�ȏ���ǂݎ��ۂ̕������ǂ݂ނ��߂̕ϐ�
								                      
	FILE* m_pFile = nullptr;                          //�t�@�C���|�C���^�[

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normalBoss.txt", "r"); //�t�@�C�����J��

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	int nLoopNumber = CObjectX::WHILE_NUMBER;  //���[�v�̏����l

	//���[�v
	while (nLoopNumber)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		//���̕������ǂݍ��܂ꂽ��
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//���[�v
			while (nLoopNumber)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					//���f���p�[�c�J�E���g���ő吔��菬�����Ƃ�
					if (nModelPrtsCount < MAX_BOSSPARTS)
					{
						//�p�[�c�̐���
						m_pModelPrtsBoss[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER),
							D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER), 
							&aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());

						//���𓯊�������
						m_pModelPrtsBoss[nModelPrtsCount]->BindSize(GetMaxParts(nModelPrtsCount), GetMinParts(nModelPrtsCount), GetModelSizePartsBoss(nModelPrtsCount));		

						nModelPrtsCount++; //�z���i�߂�
					}
				}

				//�I������
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //�����𔲂���
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//���[�v
					while (nLoopNumber)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						//�I������
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //�����𔲂���
						}

						//�R�����g��ǂݍ��񂾎�
						if (m_aDataSearch[N_INIT_NUMBER] == '#')
						{
							continue; //���s
						}
						
						//�p�[�c�̏��̓ǂݍ���
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//���[�v
							while (nLoopNumber)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

								//�I������
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //�����𔲂���
								}

								//�C���f�b�N�X��ǂݎ�����
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetIndexPrts()); //�p�[�c�̃C���f�b�N�X��ǂݎ��
								}

								//�e�p�[�c���ǂ�����ǂݎ�����
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetIndexModelPrts()); //�e�p�[�c����ǂݎ��

									//�ǂݍ��񂾒l���[�P�̎�
									if (m_pModelPrtsBoss[nCount]->GetIndexModelPrts() == PARENT_NUMBER)
									{
										m_pModelPrtsBoss[nCount]->SetParent(nullptr); //��񖳂�
									}

									//���̑�
									else
									{
										m_pModelPrtsBoss[nCount]->SetParent(m_pModelPrtsBoss[m_pModelPrtsBoss[nCount]->GetIndexModelPrts()]); //�e�ł����������
									}
								}

								//�ʒu�̓ǂݎ�����
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									//�ʒu�̓���
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetPos().x, &m_pModelPrtsBoss[nCount]->GetPos().y, &m_pModelPrtsBoss[nCount]->GetPos().z);
									m_pSaveModelPrtInfoBoss[nCount].pos = m_pModelPrtsBoss[nCount]->GetPos();                //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfoBoss[nCount].pos += MotionSetBoss[0].KeySet[0].aKey[nCount].pos;
								}

								//�����̏���ǂݎ�����
								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									//�����̓���
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetRot().x, &m_pModelPrtsBoss[nCount]->GetRot().y, &m_pModelPrtsBoss[nCount]->GetRot().z);
									m_pSaveModelPrtInfoBoss[nCount].rot = m_pModelPrtsBoss[nCount]->GetRot();                //������ۊǂ���
									//m_pSaveModelPrtInfoBoss[nCount].rot += MotionSetBoss[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //�ǂݎ��p�[�c�̔ԍ��𑝂₷
						}

					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = N_INIT_NUMBER; //���[�v���邩�ǂ����̔���p�ϐ�

					//���[�v
					while (nLoopNumber)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						//�R�����g��ǂݍ��񂾎�
						if (m_aDataSearch[N_INIT_NUMBER] == '#')
						{
							continue;                                     //���s
							fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile); //�t�@�C�����當����ǂݍ���
						}

						//�I������
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //�����𔲂���
						}

						//���[�v���邩�ǂ����ǂݎ�����
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //����
							(void)fscanf(m_pFile, "%d", &LoopType);     //���[�v���邩�ǂ�������

							//�ǂݍ��񂾒l���O�̎�
							if (LoopType == N_INIT_NUMBER)
							{
								MotionSetBoss[nMotionCount].Loop = false; //���[�v���Ȃ�
							}

							//���̑�
							else
							{
								MotionSetBoss[nMotionCount].Loop = true;  //���[�v����
							}
						}

						//�L�[�̓ǂݎ�����
						else if (!strcmp(m_aDataSearch, "NUM_KEY"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                       //����
							(void)fscanf(m_pFile, "%d", &MotionSetBoss[nMotionCount].NumKey);  //�L�[�̐�������
						}

						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							//���[�v
							while (nLoopNumber)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[N_INIT_NUMBER] == '#')
								{
									fgets(m_aDataSearch, FGET_NUMBER_2, m_pFile); //�t�@�C�����當����ǂݎ��
									continue;                                     //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //�����𔲂���
								}

								//�t���[����ǂݍ��ޏ���
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									//�t���[����������
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].Frame); 
								}

								//�L�[�̒��g�̏���ǂݎ�����
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//���[�v
									while (nLoopNumber)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[N_INIT_NUMBER] == '#')
										{
											continue;                                     //�����𑱂���
											fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile); //�t�@�C�����當����ǂݎ��
										}

										//�ʒu��ǂݎ�����
										if (!strcmp(m_aDataSearch, "POS"))
										{
											//�ʒu�̓���
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); 
										}

										//������ǂݎ�����
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											//�����̓���
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); 
										}

										//�I������
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //�����𔲂���
										}
									}
									nKeyCount++; //�L�[�J�E���g�̉��Z
								}
							}
							nKeyCount = N_INIT_NUMBER;  //�L�[�J�E���g�̏�����
							nKeySetCount++;           //�f�[�^�̉��Z
						}
					}
					nKeySetCount = N_INIT_NUMBER; //�J�E���g�̏�����
					nMotionCount++;             //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile); //�t�@�C�������
			break;           //�����𔲂���
		}
	}

	//=================================================================================================================================================================
	//�e�p�[�c�̈ʒu�̎擾
	//=================================================================================================================================================================
	
	//�������܂ł̈ʒu���擾����
	for (int nCount = N_INIT_NUMBER; nCount < BOSS_PARTS_SHOULDER_FROM_HAND; nCount++)
	{
		//���݂̃p�[�c�̎��̃p�[�c����
		for (int nNext = N_INIT_NUMBER; nNext < nCount + BOSS_NEXT_PARTS_COUNT; nNext++)
		{
			//�e�p�[�c�̈ʒu�𑫂����킹��
			 
			//�E���̃p�[�c��
			SaveMotionPosBoss[nCount + BOSS_PARTS_RIGHT_SHOULDER_FROM_HAND] += m_pModelPrtsBoss[nNext + BOSS_PARTS_RIGHT_SHOULDER_FROM_HAND]->GetPos(); 

			//�����̃p�[�c��
			SaveMotionPosBoss[nCount + BOSS_PARTS_LEFT_SHOULDER_FROM_HAND] += m_pModelPrtsBoss[nNext + BOSS_PARTS_LEFT_SHOULDER_FROM_HAND]->GetPos(); 
		}

		//�̂̈ʒu�𑫂����킹��
		SaveMotionPosBoss[nCount + BOSS_PARTS_RIGHT_SHOULDER_FROM_HAND] += m_pModelPrtsBoss[BOSS_PARTS_BODY_NUMBER]->GetPos(); //�ʒu�����Z
		SaveMotionPosBoss[nCount + BOSS_PARTS_LEFT_SHOULDER_FROM_HAND] += m_pModelPrtsBoss[BOSS_PARTS_BODY_NUMBER]->GetPos();  //�ʒu�����Z
	}

	//�����g��parts�̈ʒu���擾(�����牺)
	for (int nCount1 = BOSS_PARTS_WAIST_NUMBER + BOSS_NEXT_PARTS_COUNT; nCount1 <= BOSS_PARTS_LOWER_BODY_COUNT + BOSS_PARTS_WAIST_NUMBER; nCount1++)
	{
		SaveMotionPosBoss[nCount1] += m_pModelPrtsBoss[nCount1]->GetPos();             //�����g�̊e�p�[�c

		//���Ɛe�p�[�c����
		for (int PARENT = BOSS_PARTS_WAIST_NUMBER; PARENT < nCount1; PARENT++)
		{
			SaveMotionPosBoss[nCount1].y -= m_pModelPrtsBoss[PARENT]->GetPos().y;      //���̕�����
		}
	}

	//���Ƒ̂̈ʒu���擾
	for (int nCount2 = N_INIT_NUMBER; nCount2 < BOSS_PARTS_HEAD_AND_BODY_COUNT; nCount2++)
	{
		SaveMotionPosBoss[nCount2] += m_pModelPrtsBoss[nCount2]->GetPos();                                                                  //�ʒu�����Z
	//	GetPosPartsBoss(nCount2) = D3DXVECTOR3(SaveMotionPosBoss[nCount2].x, SaveMotionPosBoss[nCount2].y, SaveMotionPosBoss[nCount2].z); //�ʒu���C��
	}

	////�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	//for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTSBOSS; nCount3++)
	//{
	//	GetPosPartsBoss(nCount3 + 2) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 2].x + GetPos().x, SaveMotionPosBoss[nCount3 + 2].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 2].z + GetPos().z);      //�ʒu���C��
	//	GetPosPartsBoss(nCount3 + 10) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 10].x + GetPos().x, SaveMotionPosBoss[nCount3 + 10].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 10].z + GetPos().z);  //�ʒu���C��
	//}
}


//===============================
//�v���C���[���[�V�������s��
//===============================
void CCharacter::MotionInfo()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_PARTS; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrts[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCount != MotionSetPlayer[m_MotionState].NumKey - PLAYER_BEFORE_MOTION_COUNT)
			{
				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount + PLAYER_NEXT_MOTION_COUNT].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos; 

				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
				Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount + PLAYER_NEXT_MOTION_COUNT].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot;                 
			}
			else
			{
				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Movepos = MotionSetPlayer[m_MotionState].KeySet[PLAYER_FIRST_KEYSET_NUMBER].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - PLAYER_BEFORE_MOTION_COUNT].aKey[nModelCount].pos;

				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetPlayer[m_MotionState].KeySet[PLAYER_FIRST_KEYSET_NUMBER].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - PLAYER_BEFORE_MOTION_COUNT].aKey[nModelCount].rot;
			}

			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame; //�ʒu���������ʒu����t���[��������
			rot = Moverot / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame; //��������������������t���[��������

			//�����̕��������Z
			m_pModelPrts[nModelCount]->GetPos() += pos;                                      //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrts[nModelCount]->GetRot() += rot;                                      //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}
	
	SetAdjustFrame()++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (GetFrame() == MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame)
	{
		SetFrame(N_INIT_NUMBER);   //�t���[����������
		MotionCount++; //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCount == MotionSetPlayer[m_MotionState].NumKey)
		{
			MotionCount = N_INIT_NUMBER; //�J�E���g��������
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCount + PLAYER_NEXT_MOTION_COUNT == MotionSetPlayer[m_MotionState].NumKey && MotionSetPlayer[m_MotionState].Loop == N_INIT_NUMBER)
		{
			//����ȍs���̏I���
			m_bMotionType = false; //���[�V�����̔����off�ɂ���
			//SetMotion(NEUTRAL);    //���[�V�����̏��̐؂�ւ�
		}
	}
}

//===============================
//�{�X�̃��[�V�������s��
//===============================
void CCharacter::MotionInfoBoss()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_BOSSPARTS; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsBoss[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountBoss != MotionSetBoss[m_MotionStateBoss].NumKey - BOSS_BEFORE_MOTION_COUNT)
			{
				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + BOSS_NEXT_MOTION_COUNT].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;

				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + BOSS_NEXT_MOTION_COUNT].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;
			}
			else
			{
				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[BOSS_FIRST_KEYSET_NUMBER].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - BOSS_BEFORE_MOTION_COUNT].aKey[nModelCount].pos;

				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[BOSS_FIRST_KEYSET_NUMBER].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - BOSS_BEFORE_MOTION_COUNT].aKey[nModelCount].rot;
			}

			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			rot = Moverot / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame; //�����̈ʒu���v�Z�ł����������Ɖ��Z������

			//���[�V�����������Ń��[�v���I�t�̎�
			if (MotionSetBoss[BOSSWALK].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃ��[�V�����J�E���g���L�[�Z�b�g���Ō�̎�
				if (m_MotionStateBoss == BOSSWALK && MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey - BOSS_BEFORE_MOTION_COUNT)
				{
					MotionSetBoss[BOSSWALK].KeySet[MotionCountBoss].Frame = N_INIT_NUMBER;  //���[�V�����t���[����������
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);         //�ʒu��������
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);         //������������
				}
			}

			//���[�V���������S�Ń��[�v���I�t�̎�
			if (MotionSetBoss[BOSSDIE].Loop == false)
			{
				//���[�V�����̏�Ԃ����S�Őݒ肳��Ă��鎞�ƃ��[�V�����J�E���g�L�[�Z�b�g���Ō�̎�
				if (m_MotionStateBoss == BOSSDIE && MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey - BOSS_BEFORE_MOTION_COUNT)
				{
					MotionSetBoss[BOSSDIE].KeySet[MotionCountBoss].Frame = N_INIT_NUMBER;   //���[�V�����t���[����������
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);         //�ʒu��������
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);         //������������
				}
			}

			//�����̕��������Z
			m_pModelPrtsBoss[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrtsBoss[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}

	m_nMotionFrameBoss++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_nMotionFrameBoss == MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = N_INIT_NUMBER; //�J�E���g��������
		MotionCountBoss++;                  //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = N_INIT_NUMBER; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountBoss + BOSS_NEXT_MOTION_COUNT == MotionSetBoss[m_MotionStateBoss].NumKey && MotionSetBoss[m_MotionStateBoss].Loop == N_INIT_NUMBER)
		{
			//����ȍs���̏I���
			m_bMotionBossType = false; //���[�V�����̔����off�ɂ���
			//SetMotionBoss(BOS);      //���[�V�����̏��̐؂�ւ�
		}
	}
}


//================================
//�v���C���[�̃��[�V�����̐ݒ�
//================================
void CCharacter::SetMotion(MOTIONSTATE motiontype)
{
	//���݂̃��[�V�����ƈ������
	if (m_MotionState != motiontype && m_bMotionType == false)
	{
		m_MotionState = motiontype;      //���[�V������ݒ�
		MotionCount = N_INIT_NUMBER;     //���[�V�����̃J�E���g��������
		SetFrame(N_INIT_NUMBER);         //�t���[����������

		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_PARTS; nModelCount++)
		{
			//���f���p�[�c�̏�񂪂��鎞
			if (m_pModelPrts[nModelCount] != nullptr)
			{
				m_pModelPrts[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                            //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrts[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);                            //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrts[nModelCount]->GetPos() += MotionSetPlayer[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos; //���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrts[nModelCount]->GetRot() += MotionSetPlayer[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot; //���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}


//================================
//�{�X�̃��[�V�����̐ݒ�
//================================
void CCharacter::SetMotionBoss(BOSSMOTIONSTATE motiontype)
{
	//���݂̃��[�V�����ƈ������
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false)
	{
		m_MotionStateBoss = motiontype;       //���[�V������ݒ�
		MotionCountBoss = N_INIT_NUMBER;      //���[�V�����̃J�E���g��������
		m_nMotionFrameBoss = N_INIT_NUMBER;   //�t���[���̃J�E���g�̏�����
		
		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_BOSSPARTS; nModelCount++)
		{
			//���f���p�[�c�̏�񂪂��鎞
			if (m_pModelPrtsBoss[nModelCount] != nullptr)
			{
				m_pModelPrtsBoss[nModelCount]->SetPos(m_pSaveModelPrtInfoBoss[nModelCount].pos);                        //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrtsBoss[nModelCount]->SetRot(m_pSaveModelPrtInfoBoss[nModelCount].rot);					    //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrtsBoss[nModelCount]->GetPos() += MotionSetBoss[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos;	//���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrtsBoss[nModelCount]->GetRot() += MotionSetBoss[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot;	//���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}
