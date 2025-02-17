//======================================================
//
//�O���t�@�C������z�u����N���X�Ǘ�[object_set.h]
//Auther:Haruki Chiba
//
//======================================================


#pragma once


//======================================================
//�C���N���[�h
#include "main.h"
#include "stage_obj.h"


class CObjectSet
{
public:
	CObjectSet();   //�R���X�g���N�^
	~CObjectSet();  //�f�X�g���N�^
	HRESULT Init(); //����������

	//�X�e�[�W���̓ǂݍ��ފ֐����܂Ƃ߂�֐�
	void StageInformation(const char* pFileName);          //�X�e�[�W�I�u�W�F�N�g�̈ʒu�Ȃǂ�ǂݍ���
	void ResultScoreInformation(const char* pFileName);	  //���U���g�̃I�u�W�F�N�g�̈ʒu�Ȃǂ�ǂݍ���

	//�t�@�C���ɏ������ފ֐�
	void ResultScoreWrite(const char* pFileName);         //���U���g�X�R�A�̏���ǂݍ���

	//���ꂼ��̃I�u�W�F�N�g�̓ǂݍ��ݏ����{��������֐��itxt�t�@�C���̒��g�̏���ǂݍ��ށj
	void LoodTelephonPole(FILE* pFile);         //�d���̏��Ɋւ���f�[�^��ǂݍ��ފ֐�
	void LoodBlock(FILE* pFile);               //�u���b�N�̏��Ɋւ���f�[�^��ǂݍ��ފ֐�
	void LoodBreakHouse(FILE* pFile);          //��ꂽ�Ƃ̓ǂݍ��ݏ���
	void LoodResultScore(FILE* pFile);         //���U���g�̏��ǂݍ��ݐ���
	void LoodEnemy(FILE* pFile);               //�G�̓ǂݍ��ݏ���
	void LoodMotionInEnemy(FILE* pFile);       //���[�V�����t���̓G�̓ǂݍ��ݏ���
	void LoodCeiling(FILE* pFile);             //�V��̓ǂݍ��ݏ���

	void SetCreateCountInPlayer();             //���������v���C���[�ɓn�������֐�

	static CObjectSet* Create();               //���̐���

	//�擾�p�̊֐�
	const char* GetStratBlockName(CObjectX::TYPE type); //�u���b�N�̓ǂݍ��ޖ��O�̃p�X�̎擾����
	const char* GetEndBlockName(CObjectX::TYPE type);   //�u���b�N�̏I�����閼�O�̃p�X�̎擾����

	int& GetClearScore() { return m_nClearScore; }      //���݂̃X�R�A��ۊǂ���p�̕ϐ����擾


	//============================
	//�}�N����`
	static constexpr float CAMERA_PLUS_POS_X = 20.0f;       //�J������X���̈ʒu
	static constexpr float CAMERA_MINUS_POS_Z = -50.0f;     //�J������Z���̈ʒu
	static constexpr float CAMERA_UP_PLUS_POS_Y = 180.0f;   //�J�����̏㕔����Y���̒l�����Z����l
	static constexpr float CAMERA_DOWN_PLUS_POS_Y = 170.0f; //�J�����̉�������Y���̒l�����Z����l


private:
	//�}�N����`
	static constexpr int MAX_DATAMOJI = 200;    //������̔z��̍ő吔


	//====================================
	//SWITCH���Ɋւ���}�N��
	static constexpr int CASE_0 = 0;            //�P�[�X�ԍ��O��
	static constexpr int CASE_1 = 1;            //�P�[�X�ԍ��P��
	static constexpr int CASE_2 = 2;            //�P�[�X�ԍ��Q��


	//================================================
	//�e�L�X�g�t�@�C������ǂݍ��ގ��Ɏg�������o�ϐ�
	static int m_nClearScore;                   //���݂̃X�R�A��ۊǂ���p�̕ϐ�
	char m_aData[MAX_DATAMOJI];                 //�������ǂݎ��@


	//================================================
	//�e�L�X�g�t�@�C���̓ǂݏ����Ɏg�������o�ϐ�
	const char* m_aFieldBlockStratName;         //�n�ʗp�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aGoUpBlockStratName;	        //�オ��p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aRoadBlockStratName;	        //���p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aWallRoadBlockStratName;	    //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aWallRoadBlock001StratName;   //�ǌ����p�̃u���b�N001�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aSmallBlockStratName;	        //�������u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aSmallBlock001StratName;	    //�������u���b�N001�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aUpWallBlockStratName;	    //��ǃu���b�N�̓ǂݍ��ݗp�̖��O�ϐ�

	const char* m_aFieldBlockEndName;           //�n�ʗp�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aGoUpBlockEndName;     		//�オ��p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aRoadBlockEndName;     		//���p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aWallRoadBlockEndName;     	//�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aWallRoadBlock001EndName;     //�ǌ����p�̃u���b�N001�̏I���p�̖��O�ϐ�
	const char* m_aSmallBlockEndName;    		//�������u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aSmallBlock001EndName;    	//�������u���b�N001�̏I���p�̖��O�ϐ�
	const char* m_aUpWallBlockEndName;     		//��ǃu���b�N�̏I���p�̖��O�ϐ�


	//================================================
	//�ǂݍ��ރt�@�C���̕�����p�̃}�N����`
	static constexpr const char* TELEPHONPOLE = "data\\TEXT\\OBJECT\\TelephonPole.txt";   //�d��
	static constexpr const char* BLOCK = "data\\TEXT\\OBJECT\\Block.txt";                 //�u���b�N
	static constexpr const char* BLOCK_1 = "data\\TEXT\\OBJECT\\Block1.txt";              //�u���b�N1
	static constexpr const char* BLOCK_2 = "data\\TEXT\\OBJECT\\Block2.txt";              //�u���b�N2
	static constexpr const char* BREAKHOUSE = "data\\TEXT\\OBJECT\\BreakHouse.txt";       //��ꂽ��
	static constexpr const char* ENEMY = "data\\TEXT\\OBJECT\\Enemy.txt";                 //�G
	static constexpr const char* MOTIONINENEMY = "data\\TEXT\\OBJECT\\MotionEnemy.txt";   //���[�V�����t���̓G
	static constexpr const char* MOTIONINENEMY_1 = "data\\TEXT\\OBJECT\\MotionEnemy1.txt"; //���[�V�����t���̓G1
	static constexpr const char* CEILING = "data\\TEXT\\OBJECT\\Ceiling.txt";              //�V��


	//================================================
	//�������̃J�E���g
	int m_nFieldBlockCount;        //�n�ʗp�u���b�N�̐��������J�E���g����p�̕ϐ�
	int m_nGoUpBlockCount;         //�オ��p�u���b�N�̐��������J�E���g����p�̕ϐ�
	int m_nRoadBlockCount;         //���p�u���b�N�̐��������J�E���g����p�̕ϐ�
	int m_nWallRoadBlockCount;     //�ǌ����p�u���b�N�̐��������J�E���g����p�̕ϐ�
	int m_nWallRoadBlock001Count;  //�ǌ����p�u���b�N001�̐��������J�E���g����p�̕ϐ�
	int m_nSmalBlockCount;         //�������u���b�N�̐��������J�E���g����p�̕ϐ�
	int m_nSmalBlock001Count;      //�������u���b�N001�̐��������J�E���g����p�̕ϐ�

	int m_nLaserCount;             //���[�U�[�̐��������J�E���g����p�̕ϐ�
};
