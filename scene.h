//=====================================
//
//��ʑJ�ڂ̃N���X�Ǘ�[scene.h]
//Auther:Haruki Chiba
//
//=====================================


#pragma once


//=====================================
//�C���N���[�h
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "ui.h"
#include "player.x.h"
#include "object_set.h"
#include "block.h"
#include "fade.h"
#include "skydoom.h"


//=====================================
//���N���X
class CScene
{
public:

	//��ʂ̎��
	enum class MODE
	{
		MODE_TITLE = 0,                 //�^�C�g��
		MODE_GAME01,                    //�X�e�[�W�P
		MODE_GAME02,                    //�X�e�[�W�Q
		MODE_HIDEGAME,                  //���X�e�[�W
		MODE_RESULT,                    //���U���g
		MODE_GAMEOVER,                  //�Q�[���I�[�o�[
		MODE_MAX                        //�ő吔
	};						            
							            
	CScene();                           //�R���X�g���N�^
	virtual ~CScene();                  //�f�X�g���N�^
	virtual HRESULT Init();             //����������
	virtual void Uninit();              //�I������
	virtual void Update();              //�p���N���X�X�V����
	void AnyUpdate();                   //���̃N���X�����̏����̍X�V����

	static CScene* Create(MODE mode);   //mode�ɍ��킹�Đ���������


	//==================================
	//���̎擾
	inline MODE& GetMode() { return m_Mode; }               //���݃��[�h�̎擾
	inline CCamera* GetCamera() { return m_pCamera; }       //�J�����̏����擾
	inline CLight* GetLight() { return m_pLight; }          //�����̏����擾
	inline CPlayerX*& GetPlayerX() { return m_pPlayerX; }   //�v���C���[�̏����擾����

	inline int& GetFrame() { return m_nFrame; }


	//==================================
	//���̐ݒ�
	inline void SetFrame(int nFrame) { m_nFrame = nFrame; } //�t���[���̐ݒ�
	inline int& SetAdjustFrame() { return m_nFrame; }       //�t���[���̒���


	//===========================================================
	//���̎擾
	inline bool& GetOneSound() { return m_bOneSound; }      //�������Đ�����Ă��邩�ǂ����̔�����擾
	inline bool& GetOneScene() { return m_bOneScene; }      //�V�[���̈ړ����邩�ǂ����̏����擾
	inline bool& GetPlay() { return m_bPlay; }              //�V�ׂ邩�ǂ����̏����擾


	//===========================================================
	//���̐ݒ�
	inline void SetOneSound(bool bOneSound) { m_bOneSound = bOneSound; } //�����𐶐����邩�ǂ�����ݒ�
	inline void SetOneScene(bool bOneScene) { m_bOneScene = bOneScene; } //�V�[�����ړ����邩�ǂ�����ݒ�	
	inline void SetPlay(bool bPlay) { m_bPlay = bPlay; }                 //�V�ׂ邩�ݒ肷��


	//===========================================================
	//�}�N����`
	static constexpr int BATTLESHIP_NUMBER = 0;            //�V�[���p�̃o�g���V�b�v�̔ԍ�

private:
	CCamera* m_pCamera;        //�J�����̏��
	CLight* m_pLight;          //�����̏��
	CPlayerX* m_pPlayerX;      //�v���C���[�̃|�C���^�[
	MODE m_Mode;               //���݂̃��[�h�̊Ǘ��ϐ�

	int m_nFrame;              //�t���[����ۊǂ���p�̕ϐ�

	bool m_bOneSound;          //�P�񂾂������𗬂��ׂ̕ϐ�
	bool m_bOneScene;          //�P�񂾂��V�[���ړ�����ׂ̕ϐ�
	bool m_bPlay;              //�V�ׂ邩�ǂ����̔���p�ϐ�
};


//=====================================
//�X�e�[�W�P�̃N���X�Ǘ�
class CGame01 : public CScene
{
public:
	CGame01();               //�R���X�g���N�^
	~CGame01()override;      //�f�X�g���N�^
	HRESULT Init()override;  //����������
	void Uninit()override;   //�j������
	void Update()override;   //�X�V����
	void InitCreate();       //���������ɐ��������������܂Ƃ߂�֐�
	void CompileCreate();    //create�֐����܂Ƃ߂�֐�

private:
	//�}�N����`
	static constexpr int INIT_CAMERA_ADJUST_POS_Z = 500;   //�J������Z���̈ʒu��ݒ�
	static constexpr int UPDATE_CAMERA_ADJUST_POS_Z = 800; //�J������Z���̈ʒu��ݒ�
	static constexpr int MAX_FRAME = 180;                  //�t���[���̍ő吔

	static constexpr float MINUS_ROT = -1.0f;              //�����̒l�̌��Z�l
	static constexpr float INIT_PLAYER_POS_Y = 2050.0f;    //�v���C���[��Y���̈ʒu��ݒ�


	//==================================================
	//�o�g���V�b�v�Ɋւ���}�N����`
	static constexpr float BATTLESHIP_0_POS_Y = 2000.0f;   //�o�g���V�b�v0��Y���̈ʒu
	static constexpr float BATTLESHIP_0_POS_Z = 100.0f;    //�o�g���V�b�v0��Z���̈ʒu

	static constexpr float BATTLESHIP_1_POS_X = 12700.0f;  //�o�g���V�b�v1��X���̈ʒu
	static constexpr float BATTLESHIP_1_POS_Y = 1900.0f;   //�o�g���V�b�v1��Y���̈ʒu


	//==================================================
	//��Ɋւ���}�N����`
	static constexpr int SKY_CREATE_NUMBER = 1; //��̐����ԍ�

	static constexpr float SKY_POS_Z = 200.0f;  //���Z���̈ʒu

	CFade* m_pFade;          //�t�F�[�h�̃|�C���^�[
};


//=====================================
//�X�e�[�W�Q�̃N���X�Ǘ�
class CGame02 : public CScene
{
public:                    
	CGame02();                                        //�R���X�g���N�^
	~CGame02()override;                               //�f�X�g���N�^
	HRESULT Init()override;                           //����������
	void Uninit()override;                            //�j������
	void Update()override;                            //�X�V����
	void CompileCreate();                             //create�֐����܂Ƃ߂�֐�

private:
	//�}�N����`
	static constexpr float PLUS_POS_X = 20.0f;        //X���̉��Z�l
	static constexpr float PLUS_POS_Y = 3.0f;         //Y���̉��Z�l
	static constexpr float BATTLESHOP_POS_Z = 100.0f; //�o�g���V�b�v��Z���̈ʒu


	//==================================================
	//���ʃ}�N����`
	static constexpr float POS_X = -1500.0f;          //X���̐����ʒu
	static constexpr float POS_Y = 200.0f;            //Y���̐����ʒu


	//==================================================
	//��Ɋւ���}�N����`
	static constexpr float SKY_POS_Z = 200.0f;        //���Z���̈ʒu


	//==================================================
	//����Ɋւ���}�N����`
	static constexpr float SCAFFOLD_POS_X = 4335.0f;  //�����X���̐����ʒu
	static constexpr float SCAFFOLD_POS_Y = -200.0f;  //�����Y���̐����ʒu


	//==================================================
	//�X�Ɋւ���}�N����`
	static constexpr float SHOP_POS_X = 200.0f; //�X��X���̐����ʒu
	static constexpr float SHOP_POS_Z = 150.0f; //�X��Z���̐����ʒu


	//==============================
	//�s�����̃}�N����`
	static constexpr int FRAME_1 = 80;           //���s��
	static constexpr int FRAME_2 = FRAME_1 + 1;  //���s��
	static constexpr int FRAME_3 = 300;          //��O�s��

};


////=====================================
////���X�e�[�W�̃N���X�Ǘ�
//class CHideGame : public CScene
//{
//public:
//	CHideGame();              //�R���X�g���N�^
//	~CHideGame()override;     //�f�X�g���N�^
//	HRESULT Init()override;   //����������
//	void Uninit()override;    //�j������
//	void Update()override;    //�X�V����
//	void CompileCreate();     //create�֐����܂Ƃ߂�֐�
//
//private:
//	//�}�N����`
//	static constexpr float POS_X = 1500.0f;      //X���̐����ʒu
//	static constexpr float PLUS_POS_X = 20.0f;   //X���̉��Z�l
//
//};


//=====================================
//�^�C�g���̃N���X�Ǘ�
class CTitle : public CScene
{
public:                   
	CTitle();               //�R���X�g���N�^
	~CTitle()override;      //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override;  //�j������
	void Update()override;  //�X�V����
	void Game();            //�^�C�g���Q�[�����

private:           
	CFade* m_pFade;  //�t�F�[�h�̃|�C���^�[
};


//=====================================
//���U���g�̃N���X�Ǘ�
class CResult : public CScene
{
public:                     
	CResult();              //�R���X�g���N�^
	~CResult()override;     //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override;  //�j������
	void Update()override;  //�X�V����
};


//=====================================
//�Q�[���I�[�o�[�N���X�Ǘ�
class CGameOver : public CScene
{
public: 
	CGameOver();             //�R���X�g���N�^
	~CGameOver()override;    //�f�X�g���N�^
	HRESULT Init()override;  //����������
	void Uninit()override;   //�j������
	void Update()override;   //�X�V����
};
