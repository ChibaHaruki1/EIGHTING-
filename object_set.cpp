//======================================================================
//
//�I�u�W�F�N�g�̏���Text�t�@�C������ǂݎ�鏈��
//Auther:Haruki Chiba[object_set.cpp]
//
//======================================================================


//============================
//�C���N���[�h
#include "object_set.h"
#include "manager.h"
#include "score.h"


//============================
//static�ϐ��̏�����
int CObjectSet::m_nClearScore = CObject::N_INIT_NUMBER;


//=========================
//�R���X�g���N�^
//=========================
CObjectSet::CObjectSet()
{
	//�ǂݍ��ރp�X�̖��O��ݒ�
	m_aFieldBlockStratName = "FIELDBLOCKSET";               //�n�ʗp�u���b�N�̖��O��ݒ�
	m_aGoUpBlockStratName = "GOUPBLOCKSET";                 //�オ��p�u���b�N�̖��O��ݒ�
	m_aRoadBlockStratName = "ROADBLOCKSET";                 //���p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlockStratName = "WALLROADBLOCKSET";         //�ǌ����p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlock001StratName = "WALLROADBLOCK001SET";   //�ǌ����p�u���b�N001�̖��O��ݒ�
	m_aSmallBlockStratName = "SMALLBLOCKSET";               //�������u���b�N�̖��O��ݒ�
	m_aSmallBlock001StratName = "SMALLBLOCK001SET";         //�������u���b�N001�̖��O��ݒ�
	m_aUpWallBlockStratName = "UPWALLBLOCKSET";             //��ǂ̖��O��ݒ�

	//�I������p�X�̖��O��ݒ�
	m_aFieldBlockEndName = "END_FIELDBLOCKSET";             //�n�ʗp�u���b�N�̖��O��ݒ�
	m_aGoUpBlockEndName = "END_GOUPBLOCKSET";				//�オ��p�u���b�N�̖��O��ݒ�
	m_aRoadBlockEndName = "END_ROADBLOCKSET";				//���p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlockEndName = "END_WALLROADBLOCKSET";		//�ǌ����p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlock001EndName = "END_WALLROADBLOCK001SET";	//�ǌ����p�u���b�N001�̖��O��ݒ�
	m_aSmallBlockEndName = "END_SMALLBLOCKSET";				//�������u���b�N�̖��O��ݒ�
	m_aSmallBlock001EndName = "END_SMALLBLOCK001SET";		//�������u���b�N001�̖��O��ݒ�
	m_aUpWallBlockEndName = "END_UPWALLBLOCKSET";			//��ǂ̖��O��ݒ�


	//�ǂݎ���ő吔����
	for (int nCount = CObject::N_INIT_NUMBER; nCount < MAX_DATAMOJI; nCount++)
	{
		m_aData[nCount] = {}; //�����̓ǂݎ��z��̏�����
	}

	m_nFieldBlockCount = CObject::N_INIT_NUMBER;       //�n�ʗp�u���b�N�̐������̏�����
	m_nGoUpBlockCount = CObject::N_INIT_NUMBER;        //�オ��p�u���b�N�̐������̏�����
	m_nRoadBlockCount = CObject::N_INIT_NUMBER;        //���p�u���b�N�̐������̏�����
	m_nWallRoadBlockCount = CObject::N_INIT_NUMBER;    //�ǌ����p�u���b�N�̐�������������
	m_nWallRoadBlock001Count = CObject::N_INIT_NUMBER; //�ǌ����p�u���b�N001�̐�������������
	m_nSmalBlockCount = CObject::N_INIT_NUMBER;        //�������u���b�N�̐�������������
	m_nSmalBlock001Count = CObject::N_INIT_NUMBER;     //�������u���b�N001�̐�������������
	m_nLaserCount = CObject::N_INIT_NUMBER;            //���[�U�[�̐������̏�����
}


//=========================
//�f�X�g���N�^
//=========================
CObjectSet::~CObjectSet()
{
	m_nClearScore = CObject::N_INIT_NUMBER; //�X�R�A�̏�����
}


//=========================
//����������
//=========================
HRESULT CObjectSet::Init()
{
	//���݂̃��[�h��ǂݎ��
	switch (CManager::GetScene()->GetMode())
	{
		//�X�e�[�W�P�̎�
	case CScene::MODE::MODE_GAME01:
		StageInformation(TELEPHONPOLE);   //�d���̓ǂݍ���
		StageInformation(BLOCK);          //�u���b�N�̓ǂݍ���
		StageInformation(BREAKHOUSE);     //��ꂽ�Ƃ̓ǂݍ���
		StageInformation(ENEMY);          //�G�̓ǂݍ���
		StageInformation(MOTIONINENEMY);  //���[�V�����t���̓G�̓ǂݍ���

		break; //�����𔲂���


		//�X�e�[�W�Q�̎�
	case CScene::MODE::MODE_GAME02:
		StageInformation(BLOCK_1);       //�u���b�N1�̓ǂݍ���
		StageInformation(CEILING);       //�V��̓ǂݍ���

		break; //�����𔲂���


		//���X�e�[�W�̎�
	case CScene::MODE::MODE_HIDEGAME:
		StageInformation(BLOCK_2);         //�u���b�N2�̓ǂݍ���
		StageInformation(MOTIONINENEMY_1); //�G�̓ǂݍ���

		break; //�����𔲂���


		//���U���g���̎�
	case CScene::MODE::MODE_RESULT:
		ResultScoreWrite("data\\TEXT\\ResultScore.txt");          //���U���g�X�R�A�̏�������
		ResultScoreInformation("data\\TEXT\\ResultScore.txt");    //���U���g�X�R�A�̓ǂݍ���

		return S_OK; //������Ԃ�
	}

	//���݂̃��[�h��ǂݎ��
	switch (CManager::GetScene()->GetMode())
	{
		//���U���g
	case CScene::MODE::MODE_RESULT:

		return S_OK; //������Ԃ�

		//���̑�
	default:
		SetCreateCountInPlayer(); //�v���C���[�ɐ�������n������

		return S_OK; //������Ԃ�
	}
	
	return E_FAIL;   //���s��Ԃ�
}


//================================================================================
//�X�e�[�W�P�Ԗڂ���`�̃I�u�W�F�N�g�̏���ݒ�
//================================================================================
void CObjectSet::StageInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	//�O���t�@�C���ǂݍ��� (����)
	while (CObjectX::WHILE_NUMBER)
	{
		(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

		//�R�����g��ǂݍ��񂾎�
		if (m_aData[CObject::N_INIT_NUMBER] == '#')
		{
			continue; //���s
		}

		//���̕�������������
		if (!strcmp(m_aData, "END_SCRIPT"))
		{
			fclose(pFile);        //�t�@�C�������
			pFile = nullptr;      //�t�@�C���̏��𖳂���
			break;                //�����𔲂���
		}


		//===============================================================================================================================
		//�����񂩂�ǂݎ��֐���I�ԏ���
		//===============================================================================================================================

		//�d��
		if (pFileName == TELEPHONPOLE)
		{
			LoodTelephonPole(pFile);  //�d���̏���ǂݎ��
		}

		//�u���b�N
		else if (pFileName == BLOCK || pFileName == BLOCK_1 || pFileName == BLOCK_2)
		{
			LoodBlock(pFile);         //�u���b�N�̏���ǂݎ��
		}

		//��ꂽ��
		else if (pFileName == BREAKHOUSE)
		{
			LoodBreakHouse(pFile);    //��ꂽ�Ƃ̏���ǂݎ��
		}

		//�G
		else if (pFileName == ENEMY)
		{
			LoodEnemy(pFile);         //�G�̏���ǂݍ���
		}

		//���[�V�����t���̓G
		else if (pFileName == MOTIONINENEMY || pFileName == MOTIONINENEMY_1)
		{
			LoodMotionInEnemy(pFile); //���[�V�����t���̓G�̏���ǂݍ���
		}

		//�V��
		else if (pFileName == CEILING)
		{
			LoodCeiling(pFile);       //�V��
		}
	}
}

//================================================================================
//���U���g�X�R�A�̏���ǂݍ���
//================================================================================
void CObjectSet::ResultScoreInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	LoodResultScore(pFile); //���U���g�X�R�A�̓ǂݍ��ݏ������Ă�

	fclose(pFile);          //�t�@�C�������
}

//================================================================================
//���U���g�X�R�A�̏�����������
//================================================================================
void CObjectSet::ResultScoreWrite(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "w"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	fprintf(pFile, "%d", m_nClearScore); //��������������

	fclose(pFile);                       //�t�@�C�������
}


//=================================
//�d���̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodTelephonPole(FILE* pFile)
{
	float PosX, PosY, PosZ = CObject::F_INIT_NUMBER;         //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	///���ꂪ������Ă�����
	if (!strcmp(m_aData, "TELEPHONPOLESET"))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_TELEPHONPOLESET"))
			{
				m_nLaserCount++;                    //���[�U�[�̐������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //�d���̔z���i�߂�
				CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //���ꂽ�S�̐����J�E���g����[�����₷

				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				 //�d���̐���
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX, PosY, PosZ));                                   

				//�Ď��J�����̏�̕����̐���
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX + CAMERA_PLUS_POS_X, PosY + CAMERA_UP_PLUS_POS_Y, PosZ + CAMERA_MINUS_POS_Z));

				//�Ď��J�����̉��̕����̐���
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX + CAMERA_PLUS_POS_X, PosY + CAMERA_DOWN_PLUS_POS_Y, PosZ + CAMERA_MINUS_POS_Z));

				//���[�U�[�̐���
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::LASER, CObject::N_INIT_NUMBER, D3DXVECTOR3(PosX, PosY, PosZ));
			}
		}
	}
}

//=================================
//��ꂽ�Ƃ̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodBreakHouse(FILE* pFile)
{
	float PosX, PosY, PosZ = CObject::F_INIT_NUMBER;    //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "BREAKHOUSESET"))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_BREAKHOUSESET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BREAKHOUSE, CObject::N_INIT_NUMBER, D3DXVECTOR3(PosX, PosY, PosZ)); //��ꂽ�Ƃ̐���
			}
		}
	}
}

//=================================
//�V��̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodCeiling(FILE* pFile)
{
	float PosX, PosY, PosZ = CObject::F_INIT_NUMBER;     //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "CEILINGSET"))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_CEILINGSET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALCEILLING, D3DXVECTOR3(PosX, PosY, PosZ)); //�{�X��̑���
			}
		}
	}
}

//=================================
//�G�̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodEnemy(FILE* pFile)
{
	int nNumber = CObject::N_INIT_NUMBER;               //�����ԍ�
	float PosX, PosY, PosZ = CObject::F_INIT_NUMBER;    //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "ENEMYSET"))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_ENEMYSET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData);    //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);      //�O�Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%d", &nNumber);   //��������G�̏T�ނ�ԍ��Ŏ擾

				//�ԍ��Ŕ���
				switch (nNumber)
				{
				case CASE_0:
					//�G�̐���
					CManagerEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CObjectX::TYPE::ENEMY);                                 
					break; //�����𔲂���

				case CASE_1:
					//�G001�̐���
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, CObject::N_INIT_NUMBER, D3DXVECTOR3(PosX, PosY, PosZ));
					break; //�����𔲂���

				case CASE_2:
					//�G002�̐���
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY002, CObject::N_INIT_NUMBER, D3DXVECTOR3(PosX, PosY, PosZ));
					break; //�����𔲂���
				}
			}
		}
	}
}

//==============================================
//���[�V�����t���̓G�̏���ǂݍ��ޏ���
//==============================================
void CObjectSet::LoodMotionInEnemy(FILE* pFile)
{
	int nNumber = CObject::N_INIT_NUMBER;                //�����ԍ�
	float PosX, PosY, PosZ = CObject::F_INIT_NUMBER;     //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "MOTIONENEMYSET"))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_MOTIONENEMYSET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData);    //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);      //�O�Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%d", &nNumber);   //��������G�̏T�ނ�ԍ��Ŏ擾

				//�ԍ��Ŕ���
				switch (nNumber)
				{
				case CASE_0:
					//�G001�̐���
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, CObject::N_INIT_NUMBER, D3DXVECTOR3(PosX, PosY, PosZ));
					break; //�����𔲂���

				case CASE_1:
					//�G002�̐���
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION002, CObject::N_INIT_NUMBER, D3DXVECTOR3(PosX, PosY, PosZ)); 
					break; //�����𔲂���
				}
			}
		}
	}
}

//========================================
//�u���b�N�̏���ǂݍ��ޏ���
//========================================
void CObjectSet::LoodBlock(FILE* pFile)
{
	float PosX, PosY, PosZ = CObject::F_INIT_NUMBER;         //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//===========================================
	//�n�ʗp�u���b�N�̓ǂݍ���
	if (!strcmp(m_aData, m_aFieldBlockStratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aFieldBlockEndName))
			{
				m_nFieldBlockCount++;               //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FIELDBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //�n�ʗp�u���b�N�̐���
			}
		}
	}

	//===========================================
	//�オ��p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aGoUpBlockStratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aGoUpBlockEndName))
			{
				m_nGoUpBlockCount++;                     //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::GOUPBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //�オ��p�u���b�N�̐���
			}
		}
	}

	//===========================================
	//���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aRoadBlockStratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aRoadBlockEndName))
			{
				m_nRoadBlockCount++;                     //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::ROADBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //���p�u���b�N�̐���
			}
		}
	}

	//===========================================
	//�ǌ����p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aWallRoadBlockStratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aWallRoadBlockEndName))
			{
				m_nWallRoadBlockCount++;            //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //�ǌ����p�u���b�N�̐���
			}
		}
	}

	//===========================================
	//�ǌ����p�u���b�N001�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aWallRoadBlock001StratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aWallRoadBlock001EndName))
			{
				m_nWallRoadBlock001Count++;         //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK001, D3DXVECTOR3(PosX, PosY, PosZ)); //�ǌ����p�u���b�N001�̐���
			}
		}
	}

	//===========================================
	//�������u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aSmallBlockStratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aSmallBlockEndName))
			{
				m_nSmalBlockCount++;                //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //�������u���b�N�̐���
			}
		}
	}

	//===========================================
	//�������u���b�N001�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aSmallBlock001StratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData);     //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aSmallBlock001EndName))
			{
				m_nSmalBlock001Count++;             //�������𑝂₷
				break;                              //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK001, D3DXVECTOR3(PosX, PosY, PosZ)); //�������u���b�N001�̐���
			}
		}
	}

	//===========================================
	//��̕Ǘp�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aUpWallBlockStratName))
	{
		//���[�v(��������)
		while (CObjectX::WHILE_NUMBER)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aUpWallBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::UPWALLBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //��ǂ̃u���b�N�̐���
			}
		}
	}
}


//================================================
//result�X�R�A�̏���ǂݍ���
//================================================
void CObjectSet::LoodResultScore(FILE* pFile)
{
	(void)fscanf(pFile, "%d", &m_nClearScore); //��Ԗڂ̒l���i�[

	CManagerScore::Create(CScene::MODE::MODE_RESULT, m_nClearScore); //���U���g�X�R�A�̐���
}


//==========================================
//�u���b�N�̓ǂݍ��ޖ��O�̃p�X�̎擾����
//==========================================
const char* CObjectSet::GetStratBlockName(CObjectX::TYPE type)
{
	//�^�C�v���n�ʗp�u���b�N�̎�
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockStratName;           //���O��Ԃ�
	}

	//�^�C�v���オ��悤�u���b�N�̎�
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockStratName;            //���O��Ԃ�
	}

	//�^�C�v�����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockStratName;            //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockStratName;        //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N001�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001StratName;     //���O��Ԃ�
	}

	//�^�C�v���������u���b�N�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockStratName;           //���O��Ԃ�
	}

	//�^�C�v���������u���b�N001�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001StratName;        //���O��Ԃ�
	}

	//��ǂ̎�
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockStratName;          //���O��Ԃ�
	}

	return nullptr; //����Ԃ�
}


//==========================================
//�u���b�N�̏I�����閼�O�̃p�X�̎擾����
//==========================================
const char* CObjectSet::GetEndBlockName(CObjectX::TYPE type)
{
	//�^�C�v���n�ʗp�u���b�N�̎�
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockEndName;           //���O��Ԃ�
	}

	//�^�C�v���オ��悤�u���b�N�̎�
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockEndName;            //���O��Ԃ�
	}

	//�^�C�v�����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockEndName;            //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockEndName;        //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N001�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001EndName;     //���O��Ԃ�
	}

	//�^�C�v���������u���b�N�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockEndName;           //���O��Ԃ�
	}

	//�^�C�v���������u���b�N001�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001EndName;        //���O��Ԃ�
	}

	//��ǂ̎�
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockEndName;          //���O��Ԃ�
	}

	return nullptr; //����Ԃ�
}


//========================================
//���������v���C���[�ɓn�������֐�
//========================================
void CObjectSet::SetCreateCountInPlayer()
{
	CManager::GetScene()->GetPlayerX()->SetFieldBlockCount(m_nFieldBlockCount);               //�n�ʗp�u���b�N�̐��������擾
	CManager::GetScene()->GetPlayerX()->SetGoUpBlockCount(m_nGoUpBlockCount);                 //�オ��p�u���b�N�̐��������擾
	CManager::GetScene()->GetPlayerX()->SetRoadBlockCount(m_nRoadBlockCount);                 //���p�u���b�N�̐��������擾
	CManager::GetScene()->GetPlayerX()->SetWallRoadBlockCount(m_nWallRoadBlockCount);         //�ǌ����p�u���b�N�̐��������擾
	CManager::GetScene()->GetPlayerX()->SetWallRoadBlock001Count(m_nWallRoadBlock001Count);   //�ǌ����p�u���b�N�̐��������擾
	CManager::GetScene()->GetPlayerX()->SetSmalBlockCount(m_nSmalBlockCount);                 //�������u���b�N�̐��������擾
	CManager::GetScene()->GetPlayerX()->SetSmalBlock001Count(m_nSmalBlock001Count);           //�������u���b�N001�̐��������擾

	CManager::GetScene()->GetPlayerX()->SetLaserCount(m_nLaserCount);                         //���[�U�[�̐��������擾
}


//========================================
//text�t�@�C���̏��𐶐�
//========================================
CObjectSet* CObjectSet::Create()
{
	CObjectSet* m_pObjectSet = new CObjectSet(); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(m_pObjectSet->Init()))
	{
		return m_pObjectSet; //����Ԃ�
	}

	return nullptr; //����Ԃ�
}