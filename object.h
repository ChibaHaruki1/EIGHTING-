//========================================
//
//�I�u�W�F�N�g�N���X�Ǘ�[object.h]
//Auther:Chiba Haruki
//
//========================================


#pragma once


//========================================
//�C���N���[�h
#include "main.h"


//�S�Ă��Ǘ�����̂ŉ��z�֐��i�������z�֐��j
class CObject
{
public:

	//���ꂼ��̃^�C�v
	enum class TYPE
	{
		NONE = 0,           //����
		ENEMY,              //�G
		PLAYER,             //�v���C���[
		BULLET,             //�ʏ�e
		SPECIALBULLET,      //�K�E�e
		BOSSBULLET,         //�{�X�̒e
		ENEMYBULLET,        //�G�̒e
		BATTLESHIPBULLET,   //�G�̒e
		BLOCK,              //�u���b�N
		ITEM,               //�A�C�e��
		SCORE,              //�X�R�A
		FIELD,              //�n��
		PRTICLES,           //�p�[�e�B�N��
		PRTICLES001,        //�p�[�e�B�N���P
		EFFECT,             //�G�t�F�N�g
		EXPLOSION,          //����
		EXPLOSION001,       //�����P
		THENDER,            //��
		FIRE,               //��
		PILLAROFFIRE,       //����̉�
		IMPACT,             //�Ռ��g
		DEBRIS,             //�j��
		SPECIALATTACK,      //�K�E�Z
		BOSSSPECIALATTACK,  //�{�X�̕K�E�Z

		//UI
		CLING,           //�I�u�W�F�N�g�ɂ�UI
		TELEPHONPOLEUI,  //�d����UI
		TELEPHONPOLEUI1, //�d����UI
		SCREEN,         //�w�i
		BUYSENDTEXT,    //�����e�L�X�g
		HP,             //HP�Q�[�W
		MP,             //MP�Q�[�W
		TALKTEXTR,       //�b��text
		BOSSHP,         //�{�XHP�Q�[�W
		BOSSMP,         //�{�XMP�Q�[�W
		FUELGAGE,       //�R���Q�[�W
		LASER,          //���[�U�[
		MAX,            //�ő吔
	};

	//UI�̃^�C�v
	enum class TYPE_UI
	{
		NONEUI = 0,      //����
		CLING,           //�I�u�W�F�N�g�ɂ�UI
		TELEPHONPOLEUI,  //�d����UI
		TELEPHONPOLEUI1, //�d����UI
		BUYTEXT,         //����text
		TALKTEXTR,       //�b��text
		LASER,           //���[�U�[
		NOWCREATE,       //����낤�Ƃ��Ă���UI
		SHOPMENU,
	};

	CObject(int nPriority = DEFAULT_PRIORITY);                                                    //�R���X�g���N�^
	virtual ~CObject();                                                                           //�f�X�g���N�^
	virtual HRESULT Init() = 0;                                                                   //����������
	virtual void Uninit() = 0;                                                                    //�I������
	virtual void Update() = 0;                                                                    //�X�V����
	virtual void Draw() = 0;                                                                      //�`�揈��
	static void ReleaseAll();                                                                     //�S�I�u�W�F�N�g�̉��
	static void UpdateAll();                                                                      //�S�I�u�W�F�N�g�̍X�V
	static void DrawAll();                                                                        //�S�I�u�W�F�N�g�̕`��
	inline static CObject* GetObject1(int nPri, int nIndex) { return m_apObject[nPri][nIndex]; }  //�I�u�W�F�N�g�擾
	inline TYPE GetType() { return m_type; }                                                      //�^�C�v�擾
	inline void SetType(TYPE type) { m_type = type; }                                             //�^�C�v�ݒ�
	void Release();

	//�}�N����`
	static constexpr  int DEFAULT_PRIORITY = 3;               //�`�揇�̏����l
	static constexpr  int MAX_PRIORITY_OBJ = 4;               //�`�揇�̍ő吔//�������g�̉��

	static constexpr int N_INIT_NUMBER = 0;                   //int�^�̏������̒l
	static constexpr float F_INIT_NUMBER = 0.0f;              //float�^�̏������̒l

	static constexpr UINT BUFF_NUMBE = 0U;                    //�o�b�t�@�̃��b�N���̔ԍ�
	static constexpr UINT STARTVERTEX = 0U;                   //�`�掞�̏��߂̃o�[�e�N�X�ԍ�
	static constexpr UINT STREAMNUMBER = 0U;                  //�X�g���[���ݒ莞�̔ԍ�
	static constexpr UINT PRIMITIVECOUNT = 2U;                //�`�掞��PrimitiveCount�̐ݒ�

	static constexpr int PVTX_NUMBER_0 = 0;                   //���_����pvtx�̔Ԗ�
	static constexpr int PVTX_NUMBER_1 = 1;                   //���_����pvtx�̂P�Ԗ�
	static constexpr int PVTX_NUMBER_2 = 2;                   //���_����pvtx�̂Q�Ԗ�
	static constexpr int PVTX_NUMBER_3 = 3;                   //���_����pvtx�̂R�Ԗ�
	static constexpr int PVTX_NUMBER_OF = 4;                  //pvtx�̊�{��

	static constexpr int INIT_PRIORITY = 0;                   //�v���C�I���e�B�̏����l
	static constexpr int N_INIT_COL_NUMBER = 255;             //�F�̏����l

	static constexpr int N_INIT_ALPHA_NUMBER = 255;           //�A���t�@�l�̏����l
	static constexpr int RED = 255;                           //�ԐF
	static constexpr int GREEN = 255;                         //�ΐF
	static constexpr int BLUE = 255;                          //�F

private:
	//�}�N����`
	static constexpr  int MAX_OBJECT = 500;                    //�I�u�W�F�N�g�̍ő吔

	static CObject* m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT]; //�S�I�u�W�F�N�g�̊Ǘ�

	int m_nPriority; //���g�̃v���C�I���e�B
	int m_nID;       //�������g��ID
	TYPE m_type;     //�I�u�W�F�N�g�^�C�v

};

