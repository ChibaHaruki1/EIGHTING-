//==============================================
//
//�G��character�N���X�Ǘ�[enemycharacter.h]
//Ajther: Chiba haruki
//
//==============================================


#pragma once


//==============================================
//�C���N���[�h
#include "objectX.h"
#include "model_prts.h"


class CEnemyCharacter : public CObjectX
{
public:

	//�G�̃��[�V�����̎��
	typedef enum
	{
		ENEMYWALK = 0,  //����
		ENEMYJUMP,      //���
		ENEMYATTACK,    //�U��
		ENEMYDIE,       //���S

	}ENEMYMOTIONSTATE;

	CEnemyCharacter(int nPriority = DEFAULT_PRIORITY1);        //�R���X�g���N�^
	~CEnemyCharacter();                                        //�f�X�g���N�^
	HRESULT Init();                                            //����������
	void Uninit();                                             //�j������

	void UpdateEnemy001();                                     //�G001�̍X�V����
	void DrawEnemy001(int NumPrts);                            //�G001�̕`�揈��
	void MotionInfoEnemy001();                                 //�G001�̃��[�V�����̏�����������

	void UpdateEnemy002();                                     //�G002�̍X�V����
	void DrawEnemy002(int NumPrts);                            //�G002�̕`�揈��
	void MotionInfoEnemy002();                                 //�G002�̃��[�V�����̏�����������

	void LoodEnemy(const char* aSelect);                       //���f����ǂݍ��ޏ����{�����擾���鏈��


	//===========================
	//���̎擾
	CModelPrts* GetEnemy001ModelParts(int nNumber) { return m_pModelPrtsEnemy001[nNumber]; }
	int& GetEnemy001PartsNumber() { return m_nEnemy001Parts; } //�G001�̃p�[�c���̎擾


	//===========================
	//���̐ݒ�
	void SetMotionEnemy001(ENEMYMOTIONSTATE motiontype);                       //�G001���[�V�������Ƃ̏���
	void SetMotionEnemy002(ENEMYMOTIONSTATE motiontype);                       //�G002���[�V�������Ƃ̏���
	void SetMotionType(bool bMotionType) { m_bMotionEnemyType = bMotionType; } //���[�V�����^�C�v�̐ݒ�


	//===========================
	//�G001�Ɋւ���}�N����`
	static constexpr  int PARTS_BODY_NUMBER = 0;                  //�̂̔ԍ�
	static constexpr  int PARTS_RIGHT_SHOLDER_WEAPON_NUMBER = 4;  //�E���̕���̔ԍ�


private:
	//�}�N����`		
	static constexpr int MAX_PARTS_SEARCH = 100;                  //�p�[�c�̎擾���̔z��̍ő吔
	static constexpr int MAX_DATA_SEARCH = 512;                   //�e�L�X�g�t�@�C���̓ǂݍ��ݎ��̔z��̍ő吔
	static constexpr int MAX_ENEMYKEYSET = 5;                     //���[�V�����Ɏg���L�[�̐�
	static constexpr int NUM_ENEMYMOTION = 10;                    //���[�V�����̐�
	static constexpr int BEFORE_PARTS_COUNT = -1;                 //�O�̃p�[�c�J�E���g
	static constexpr int HALF = 2;                                //int�^�̎��̔���
	static constexpr int FGET_NUMBER_1 = 40;                      //fgets�֐��̓ǂݎ��l�P��
	static constexpr int FGET_NUMBER_2 = 20;                      //fgets�֐��̓ǂݎ��l�Q��
	static constexpr int PARENT_NUMBER = -1;                      //�e�p�[�c�̓ǂݍ��ݒl


	//============================================
	//�G001�Ɋւ���}�N����`
	static constexpr  int PARTS_RIGHT_SHOLDER_NUMBER = 2;         //�E���̔ԍ�
	static constexpr  int PARTS_LEFT_SHOLDER_NUMBER = 5;          //�����̔ԍ�
	static constexpr  int PARTS_LEFT_SHOLDER_WEAPON_NUMBER = 7;   //�����̕���̔ԍ�
	static constexpr  int PARTS_LEFT_WAIST_NUMBER = 8;            //���̔ԍ�
	static constexpr  int PARTS_LEFT_MIDDLELEG_NUMBER = 9;        //���̒��Ԃ̃p�[�c�ԍ�
	static constexpr  int PARTS_LOWER_BODY_COUNT = 7;             //�����g�̃p�[�c��
	static constexpr  int NEXT_MOTION_COUNT = 1;                  //���[�V�������̍��������߂鎞�̎��̃��[�V�����J�E���g
	static constexpr  int BEFORE_MOTION_COUNT = 1;                //���[�V�������̍������������̑O�̃��[�V�����J�E���g


	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}Key;

	//�L�[�Z�b�g�̍\����
	typedef struct
	{
		int Frame;                 //�t���[����
		Key aKey[MAX_ENEMYPARTS];  //�L�[��(�p�[�c���m��)
	}KeySet;

	//���[�V�����̍\����
	typedef struct
	{
		bool Loop;                        //���[�V���������[�v���邩�ǂ�������p
		int NumKey;						  //�L�[�̑���
		KeySet KeySet[MAX_ENEMYKEYSET];	  //���[�V�����̃L�[�Z�b�g�i���[�V�������̃L�[�Z�b�g�̐��j
	}MotionSet;

	//���[�V���������m�ۂ���\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}SAVEMODELINFO;


	//==============================================
	//�L�����N�^�[�̏���ۊǂ���ϐ�
	ENEMYMOTIONSTATE m_MotionStateEnemy001, m_MotionStateEnemy002; //�G�̃��[�V�����̎�ނ̏�������

	//���f���p�[�c�̏��̃|�C���^�[
	CModelPrts* m_pLoodModelPrtsEnemy[MAX_ENEMYPARTS], * m_pModelPrtsEnemy001[MAX_ENEMYPARTS], * m_pModelPrtsEnemy002[MAX_ENEMYPARTS];

	//���f���p�[�c�̕ۊǗp���̕ϐ�
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_ENEMYPARTS], m_pSaveModelPrtUpdateInfo001[MAX_ENEMYPARTS], m_pSaveModelPrtUpdateInfo002[MAX_ENEMYPARTS];

	//�e���[�V�����̎�ނ��i�[����ϐ�
	MotionSet LoodMotionSetEnemy[NUM_ENEMYMOTION],MotionSetEnemy001[NUM_ENEMYMOTION], MotionSetEnemy002[NUM_ENEMYMOTION];

	int MotionCountEnemy001;    //�G001���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)
	int m_nEnemy001Parts;       //�G001�̃p�[�c��
	int m_nEnemy001Frame;       //�G001�̃��[�V�������̃t���[��

	int MotionCountEnemy002;    //�G002���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)
	int m_nEnemy002Parts;       //�G002�̃p�[�c��
	int m_nEnemy002Frame;       //�G002�̃��[�V�������̃t���[��

	int m_nNumParts;            //�p�[�c��
	bool m_bMotionEnemyType;    //����ȃ��[�V�������ǂ���
};