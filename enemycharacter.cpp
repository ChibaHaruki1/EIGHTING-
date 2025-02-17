//==================================================
//
//�L�����N�^�[�̊e�p�[�c�̏���[enemycharacter.cpp]
//Auther: Haruki Chiba
//
//==================================================


//=============================
//�C���N���[�h
#include "enemycharacter.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//======================
CEnemyCharacter::CEnemyCharacter(int nPriority) : CObjectX(nPriority)
{
	//�G�̃p�[�c������
	for (int nCount = N_INIT_NUMBER; nCount < MAX_ENEMYPARTS; nCount++)
	{
		m_pLoodModelPrtsEnemy[nCount] = nullptr;               //�ǂݍ��ݗp�̓G�̃p�[�c�̏�����
		m_pModelPrtsEnemy001[nCount] = nullptr;                //�G001�̃p�[�c�̏�����
		m_pModelPrtsEnemy002[nCount] = nullptr;                //�G002�̃p�[�c�̏�����
		m_pSaveModelPrtInfo[nCount] = {};					   //���f���p�[�c�̕ۊǏ��̏�����
		m_pSaveModelPrtUpdateInfo001[nCount] = {};			   //�X�V�p���f���p�[�c�̕ۊǏ��̏�����
		m_pSaveModelPrtUpdateInfo002[nCount] = {};			   //�X�V�p���f���p�[�c�̕ۊǏ��̏�����
	}

	MotionCountEnemy001 = N_INIT_NUMBER;                       //�G001���[�V�������̃J�E���g��������
	MotionCountEnemy002 = N_INIT_NUMBER;                       //�G002���[�V�������̃J�E���g��������
	m_nNumParts = N_INIT_NUMBER;                               //�p�[�c���̏�����
	m_nEnemy001Parts = N_INIT_NUMBER;                          //�G001�̃p�[�c���̏�����
	m_nEnemy002Parts = N_INIT_NUMBER;                          //�G002�̃p�[�c���̏�����
	m_nEnemy001Frame = N_INIT_NUMBER;                          //�G001�̃��[�V�������̃t���[��
	m_nEnemy002Frame = N_INIT_NUMBER;                          //�G002�̃��[�V�������̃t���[��
	m_bMotionEnemyType = false;                                //���[�V�����^�C�v�̏�����
	m_MotionStateEnemy001 = ENEMYWALK;                         //���[�V������Ԃ̏�����
	m_MotionStateEnemy002 = ENEMYWALK;                         //���[�V������Ԃ̏�����
}


//======================
//�f�X�g���N�^
//======================
CEnemyCharacter::~CEnemyCharacter()
{

}


//=======================
//����������
//=======================
HRESULT CEnemyCharacter::Init()
{
	//�����������s������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}


//========================
//�j������
//========================
void CEnemyCharacter::Uninit()
{
	CObjectX::Uninit(); //�j���������Ă�
	
	//�ő�p�[�c������
	for (int nCount1 = N_INIT_NUMBER; nCount1 < MAX_ENEMYPARTS; nCount1++)
	{
		//=====================================================================================
		//����m_pLoodModelPrtsEnemy�œǂݎ��A�R�s�[���������Ȃ̂�Uninit()&delete�͂��ꂾ���Ă�

		//�p�[�c�̏�񂪂��鎞
		if (m_pLoodModelPrtsEnemy[nCount1] != nullptr)
		{
			m_pLoodModelPrtsEnemy[nCount1]->Uninit(); //�j������
			delete m_pLoodModelPrtsEnemy[nCount1];    //��������
			m_pLoodModelPrtsEnemy[nCount1] = nullptr; //���𖳂���
		}

		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy001[nCount1] != nullptr)
		{
			//delete m_pModelPrtsEnemy001[nCount1];    //��������
			m_pModelPrtsEnemy001[nCount1] = nullptr; //���𖳂���
		}

		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy002[nCount1] != nullptr)
		{
			//delete m_pModelPrtsEnemy002[nCount1];    //��������
			m_pModelPrtsEnemy002[nCount1] = nullptr; //���𖳂���
		}
	}
}

//========================
//�G001�̍X�V����
//========================
void CEnemyCharacter::UpdateEnemy001()
{
	MotionInfoEnemy001(); //���[�V�������s���������Ă�

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = N_INIT_NUMBER; nCount < m_nEnemy001Parts; nCount++)
	{
		//�p�[�c�̈ʒu�̍X�V
		GetPosPartsEnemy(nCount) = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount].pos.x + GetPos().x,
			m_pSaveModelPrtUpdateInfo001[nCount].pos.y + GetPos().y,
			m_pSaveModelPrtUpdateInfo001[nCount].pos.z + GetPos().z); //�e�p�[�c��ۊǒl�{���݂̈ʒu�ŏC��
	}
}

//========================
//�G002�̍X�V����
//========================
void CEnemyCharacter::UpdateEnemy002()
{
	MotionInfoEnemy002(); //���[�V�������s���������Ă�

	
}

//========================
//�G�̕`�揈��
//========================
void CEnemyCharacter::DrawEnemy001(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;              //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();          //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                               //�ʒu�ƌ������擾����ׂ̕ϐ�

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
		if (m_pModelPrtsEnemy001[nCount] != nullptr)
		{
			m_pModelPrtsEnemy001[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//========================
//�G�̕`�揈��
//========================
void CEnemyCharacter::DrawEnemy002(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;              //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();          //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                               //�ʒu�ƌ������擾����ׂ̕ϐ�

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
		if (m_pModelPrtsEnemy002[nCount] != nullptr)
		{
			m_pModelPrtsEnemy002[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//======================
//�G�̃��[�h����
//======================
void CEnemyCharacter::LoodEnemy(const char* aSelect)
{
	int nCount = N_INIT_NUMBER;                      //�ŏ��̃p�[�c�����J�E���g���邽�߂̕ϐ�
	int nKeyCount = N_INIT_NUMBER;                   //���[�V�����̃L�[���J�E���g���邽�߂̕ϐ�
	int nModelPrtsCount = N_INIT_NUMBER;             //��������p�[�c���̃J�E���g���邽�߂̕ϐ�
	int nMotionCount = N_INIT_NUMBER;                //���[�V�����̐����J�E���g���邽�߂̕ϐ�
	int nKeySetCount = N_INIT_NUMBER;                //���[�V�����̃L�[�Z�b�g�̐����J�E���g���邽�߂̕ϐ�

	char aPrtsPass[MAX_PARTS_SEARCH];                //�e�p�[�c��ǂݎ��ۂ̃p�X��ǂݍ��ނ��߂̕ϐ�
	char m_aDataSearch[MAX_DATA_SEARCH];             //�K�v�ȏ���ǂݎ��ۂ̕������ǂ݂ނ��߂̕ϐ�
								      	             
								                     
	FILE* m_pFile = nullptr;                         //�t�@�C���|�C���^�[

	//�G�O�Ԗڂ�I��
	if (aSelect == "Enemy000")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy000.txt", "r"); //�t�@�C�����J��
	}

	//�G�P�Ԗڂ�I��
	else if (aSelect == "Enemy001")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy001.txt", "r"); //�t�@�C�����J��
	}

	else if (aSelect == "Enemy002")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy002.txt", "r"); //�t�@�C�����J��
	}

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
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					//���f���p�[�c�J�E���g���ő吔��菬������
					if (nModelPrtsCount < MAX_ENEMYPARTS)
					{
						//�p�[�c�̐���
						m_pLoodModelPrtsEnemy[nModelPrtsCount] = CModelPrts::Create(
							D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER),
							D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER), 
							&aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat()); 

						//���𓯊�������
						m_pLoodModelPrtsEnemy[nModelPrtsCount]->BindSize(GetMaxParts(nModelPrtsCount), GetMinParts(nModelPrtsCount), GetModelSizePartsEnemy(nModelPrtsCount));	
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

						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch); //����
							(void)fscanf(m_pFile,"%d",&m_nNumParts);     //�p�[�c���̏�����
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
									//�p�[�c�̃C���f�b�N�X��ǂݎ��
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetIndexPrts());
								}

								//�e�p�[�c���ǂ�����ǂݎ�����
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									//�e�p�[�c����ǂݎ��
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetIndexModelPrts());

									//�ǂݍ��񂾒l���[�P�̎�
									if (m_pLoodModelPrtsEnemy[nCount]->GetIndexModelPrts() == PARENT_NUMBER)
									{
										m_pLoodModelPrtsEnemy[nCount]->SetParent(nullptr); //���Ȃ�
									}

									//���̑�
									else
									{
										//�e�ł����������
										m_pLoodModelPrtsEnemy[nCount]->SetParent(m_pLoodModelPrtsEnemy[m_pLoodModelPrtsEnemy[nCount]->GetIndexModelPrts()]);
									}
								}

								//�ʒu��ǂݎ�����
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									//�ʒu�̓���
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetPos().x, &m_pLoodModelPrtsEnemy[nCount]->GetPos().y, &m_pLoodModelPrtsEnemy[nCount]->GetPos().z);
									m_pSaveModelPrtInfo[nCount].pos = m_pLoodModelPrtsEnemy[nCount]->GetPos();                //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfo[nCount].pos += LoodMotionSetEnemy[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									//�����̓���
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetRot().x, &m_pLoodModelPrtsEnemy[nCount]->GetRot().y, &m_pLoodModelPrtsEnemy[nCount]->GetRot().z);
									m_pSaveModelPrtInfo[nCount].rot = m_pLoodModelPrtsEnemy[nCount]->GetRot();                //������ۊǂ���
									//m_pSaveModelPrtInfo[nCount].rot += LoodMotionSetEnemy[0].KeySet[0].aKey[nCount].rot;
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
							fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile); //�t�@�C�����當�����ǂݍ���
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
								LoodMotionSetEnemy[nMotionCount].Loop = false; //���[�v���Ȃ�
							}

							//���̑�
							else
							{
								LoodMotionSetEnemy[nMotionCount].Loop = true;  //���[�v����
							}
						}

						//�L�[�̓ǂݍ��ݏ���
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) 
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                            //����
							(void)fscanf(m_pFile, "%d", &LoodMotionSetEnemy[nMotionCount].NumKey);	//�L�[�̐�������
						}

						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{

							//���[�v����
							while (nLoopNumber)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //����

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

								//�t���[����ǂݎ�����
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									//�t���[����������
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].Frame);
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
											fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile);  //�t�@�C�����當����ǂݎ��
										}

										//�ʒu��ǂݎ�����
										if (!strcmp(m_aDataSearch, "POS"))
										{
											//�ʒu�̓���
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, 
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z);
										}

										//������ǂݎ�����
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											//�����̓���
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, 
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z);
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

	//�G1�Ԗڂ�I�����Ă��鎞
	if (aSelect == "Enemy001")
	{
		int RightnCount = N_INIT_NUMBER; //for���p�̕ϐ�
		int LeftnCount = N_INIT_NUMBER;  //for���p�̕ϐ�

		m_nEnemy001Parts = m_nNumParts; //�p�[�c���̎擾

		for (int nLoodMotionSetEnemy = N_INIT_NUMBER;nLoodMotionSetEnemy< NUM_ENEMYMOTION; nLoodMotionSetEnemy++)
		{
			MotionSetEnemy001[nLoodMotionSetEnemy] = LoodMotionSetEnemy[nLoodMotionSetEnemy];
		}

		for (int nLoodModelPrtsEnemy = N_INIT_NUMBER; nLoodModelPrtsEnemy < MAX_ENEMYPARTS; nLoodModelPrtsEnemy++)
		{
			m_pModelPrtsEnemy001[nLoodModelPrtsEnemy] = m_pLoodModelPrtsEnemy[nLoodModelPrtsEnemy];
		}

		//�ő�p�[�c������
		for (int nCount = N_INIT_NUMBER; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo001[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //�l�𕡐�����
		}

		//�E���̈ʒu��̂̈ʒu�����Z����
		m_pSaveModelPrtUpdateInfo001[PARTS_RIGHT_SHOLDER_NUMBER].pos += m_pLoodModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//�����̈ʒu��̂̈ʒu�����Z����
		m_pSaveModelPrtUpdateInfo001[PARTS_LEFT_SHOLDER_NUMBER].pos += m_pLoodModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//�E������E���̕���܂�
		for (RightnCount = PARTS_RIGHT_SHOLDER_NUMBER; RightnCount <= PARTS_RIGHT_SHOLDER_WEAPON_NUMBER; RightnCount++)
		{
			//�����l�͌��݂̉E�p�[�c
			for (int nCount1 = RightnCount+ BEFORE_PARTS_COUNT; nCount1 < RightnCount; nCount1++)
			{
				//�J�E���g���E������̎�
				if (nCount1 >= PARTS_RIGHT_SHOLDER_NUMBER)
				{
					//�ʒu�����Z����,
					m_pSaveModelPrtUpdateInfo001[RightnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount1].pos.x, m_pSaveModelPrtUpdateInfo001[nCount1].pos.y, m_pSaveModelPrtUpdateInfo001[nCount1].pos.z);
				}
			}
		}

		//�������獶���̕���܂�
		for (LeftnCount = PARTS_LEFT_SHOLDER_NUMBER; LeftnCount <= PARTS_LEFT_SHOLDER_WEAPON_NUMBER; LeftnCount++)
		{
			//�����l�͌��݂̍��p�[�c
			for (int nCount2 = LeftnCount + BEFORE_PARTS_COUNT; nCount2 < LeftnCount; nCount2++)
			{
				//�J�E���g����������̎�
				if (nCount2 >= PARTS_LEFT_SHOLDER_NUMBER)
				{
					//�ʒu�����Z����
					m_pSaveModelPrtUpdateInfo001[LeftnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount2].pos.x, m_pSaveModelPrtUpdateInfo001[nCount2].pos.y, m_pSaveModelPrtUpdateInfo001[nCount2].pos.z);  
				}
			}
		}

		//�����g���񂷁i�����牺�Ȃ̂ō��̔ԍ��{�P�Ԗځj
		for (int nLowBody = PARTS_LEFT_MIDDLELEG_NUMBER; nLowBody <= PARTS_LEFT_WAIST_NUMBER + PARTS_LOWER_BODY_COUNT; nLowBody++)
		{
			//m_pSaveModelPrtUpdateInfo[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //�l�𕡐�����

			//������e�p�[�c����
			for (int nWaist = PARTS_LEFT_WAIST_NUMBER; nWaist < nLowBody; nWaist++)
			{
				m_pSaveModelPrtUpdateInfo001[nLowBody].pos.y += m_pSaveModelPrtInfo[nWaist].pos.y; ////���̕�����(���̈ʒu�[�e�p�[�c)
			}
		}
	}

	//�G002���I�����ꂽ��
	else if (aSelect == "Enemy002")
	{
		m_nEnemy002Parts = m_nNumParts; //�p�[�c���̎擾

		//�ő�p�[�c������
		for (int nCount = N_INIT_NUMBER; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo002[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //�l�𕡐�����
		}

		for (int nLoodModelPrtsEnemy = N_INIT_NUMBER; nLoodModelPrtsEnemy < MAX_ENEMYPARTS; nLoodModelPrtsEnemy++)
		{
			m_pModelPrtsEnemy002[nLoodModelPrtsEnemy] = m_pLoodModelPrtsEnemy[nLoodModelPrtsEnemy];
		}

	}
}

//===============================
//�G001�̃��[�V�������s��
//===============================
void CEnemyCharacter::MotionInfoEnemy001()
{

	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = N_INIT_NUMBER; nModelCount < m_nEnemy001Parts; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy001[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountEnemy001 != MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
			{
				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Movepos = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001 + NEXT_MOTION_COUNT].aKey[nModelCount].pos - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].pos;

				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
				Moverot = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001 + NEXT_MOTION_COUNT].aKey[nModelCount].rot - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].rot;
			}
			else
			{
				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Movepos = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].pos;

				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].rot;
			}


			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].Frame; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			rot = Moverot / (float)MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].Frame; //�����̈ʒu���v�Z�ł����������Ɖ��Z������

			//���[�V��������ԂŃ��[�v���I�t�̎�
			if (MotionSetEnemy001[ENEMYJUMP].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃL�[�Z�b�g���Ō�̎�
				if (m_MotionStateEnemy001 == ENEMYJUMP && MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
				{
					MotionSetEnemy001[ENEMYJUMP].KeySet[MotionCountEnemy001].Frame = N_INIT_NUMBER; //���[�V�����t���[��������������
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);     //�ʒu������������
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);     //����������������
				}
			}

			//���[�V�������U���Ń��[�v���I�t�̎�
			if (MotionSetEnemy001[ENEMYATTACK].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃL�[�Z�b�g���Ō�̎�
				if (m_MotionStateEnemy001 == ENEMYATTACK && MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
				{
					MotionSetEnemy001[ENEMYATTACK].KeySet[MotionCountEnemy001].Frame = N_INIT_NUMBER; //���[�V�����t���[��������������
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                   //�ʒu������������
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                   //����������������
				}
			}

			//���[�V���������S�Ń��[�v���I�t�̎�
			if (MotionSetEnemy001[ENEMYDIE].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃL�[�Z�b�g���Ō�̎�
				if (m_MotionStateEnemy001 == ENEMYDIE && MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
				{
					MotionSetEnemy001[ENEMYDIE].KeySet[MotionCountEnemy001].Frame = N_INIT_NUMBER; //���[�V�����t���[����������
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                //�ʒu������������
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                //����������������
				}
			}

			//�����̕��������Z
			m_pModelPrtsEnemy001[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrtsEnemy001[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}
	
	m_nEnemy001Frame++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_nEnemy001Frame == MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].Frame)
	{
		m_nEnemy001Frame = N_INIT_NUMBER; //�t���[����������
		MotionCountEnemy001++;            //���[�V�����̃J�E���g�𑝉�

	    //���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey)
		{
			MotionCountEnemy001 = N_INIT_NUMBER; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountEnemy001 + NEXT_MOTION_COUNT == MotionSetEnemy001[m_MotionStateEnemy001].NumKey && MotionSetEnemy001[m_MotionStateEnemy001].Loop == N_INIT_NUMBER)
		{
			//����ȍs���̏I���
			m_bMotionEnemyType = false; //���[�V�����̔����off�ɂ���
			//MotionCountEnemy001=1;
			//SetMotionBoss(NEUTRAL);   //���[�V�����̏��̐؂�ւ�
		}
	}
}

//===============================
//�G002�̃��[�V�������s��
//===============================
void CEnemyCharacter::MotionInfoEnemy002()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = N_INIT_NUMBER; nModelCount < m_nEnemy002Parts; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy002[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountEnemy002 != MotionSetEnemy002[m_MotionStateEnemy002].NumKey - BEFORE_MOTION_COUNT)
			{
				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Movepos = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002 + NEXT_MOTION_COUNT].aKey[nModelCount].pos - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].pos;

				//���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
				Moverot = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002 + NEXT_MOTION_COUNT].aKey[nModelCount].rot - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].rot;
			}
			else
			{
				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Movepos = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionSetEnemy002[m_MotionStateEnemy002].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].pos;

				//�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionSetEnemy002[m_MotionStateEnemy002].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].rot;
			}


			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].Frame; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			rot = Moverot / (float)MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].Frame; //�����̈ʒu���v�Z�ł����������Ɖ��Z������


			//�����̕��������Z
			m_pModelPrtsEnemy002[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrtsEnemy002[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}

	m_nEnemy002Frame++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_nEnemy002Frame == MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].Frame)
	{
		m_nEnemy002Frame = N_INIT_NUMBER;  //�t���[����������
		MotionCountEnemy002++;             //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountEnemy002 == MotionSetEnemy002[m_MotionStateEnemy002].NumKey)
		{
			MotionCountEnemy002 = N_INIT_NUMBER; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountEnemy002 + NEXT_MOTION_COUNT == MotionSetEnemy002[m_MotionStateEnemy002].NumKey && MotionSetEnemy002[m_MotionStateEnemy002].Loop == N_INIT_NUMBER)
		{
			//����ȍs���̏I���
			m_bMotionEnemyType = false; //���[�V�����̔����off�ɂ���
		}
	}
}

//==============================
//���[�V�����̐ݒ�
//==============================
void CEnemyCharacter::SetMotionEnemy001(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateEnemy001 != motiontype && m_bMotionEnemyType == false) //���݂̃��[�V�����ƈ������
	{
		m_MotionStateEnemy001 = motiontype;     //���[�V������ݒ�
		MotionCountEnemy001 = N_INIT_NUMBER;    //���[�V�����̃J�E���g��������
		m_nEnemy001Frame = N_INIT_NUMBER;       //�t���[���̃J�E���g�̏�����

		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			//�p�[�c�̏�񂪂��鎞
			if (m_pModelPrtsEnemy001[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy001[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                                //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrtsEnemy001[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);						        //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrtsEnemy001[nModelCount]->GetPos() += MotionSetEnemy001[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos; //���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrtsEnemy001[nModelCount]->GetRot() += MotionSetEnemy001[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot; //���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}


//==============================
//���[�V�����̐ݒ�
//==============================
void CEnemyCharacter::SetMotionEnemy002(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateEnemy002 != motiontype && m_bMotionEnemyType == false) //���݂̃��[�V�����ƈ������
	{
		m_MotionStateEnemy002 = motiontype;   //���[�V������ݒ�
		MotionCountEnemy002 = N_INIT_NUMBER;  //���[�V�����̃J�E���g��������
		m_nEnemy002Frame = N_INIT_NUMBER;     //�t���[���̃J�E���g�̏�����

		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			//�p�[�c�̏�񂪂��鎞
			if (m_pModelPrtsEnemy002[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy002[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                                //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrtsEnemy002[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);						        //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrtsEnemy002[nModelCount]->GetPos() += MotionSetEnemy002[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos; //���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrtsEnemy002[nModelCount]->GetRot() += MotionSetEnemy002[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot; //���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}
