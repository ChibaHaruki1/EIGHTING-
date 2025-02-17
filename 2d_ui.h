//===================================
//
//2D_UI�̃N���X�Ǘ�[2d_ui.h]
//Author:chiba haruki
//
//===================================


#pragma once


//======================================
//�C���N���[�h
#include "main.h"
#include "object2D.h"


//======================================
//�QDUI�̃}�l�[�W���[�Ǘ��N���X
class CManager2DUI : public CObject2D
{
public:
	CManager2DUI(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManager2DUI();                                 //�f�X�g���N�^
	HRESULT Init()override;                          //����������
	void Uninit()override;                           //�j������
	void Update()override;                           //�X�V����
	void Draw()override;                             //�`�揈��

	static CManager2DUI* Create(TYPE_UI TypeUI);     //��������
	static CManager2DUI* NowCreate(int nNumber);     //���ݍ���Ă���I�u�W�F�N�gUI�̐�������

private:
	//�}�N����`
	static constexpr int CRETAE_NUMBER_0 = 0;        //��������ԍ��O�Ԗ�
	static constexpr int CRETAE_NUMBER_1 = 1;        //��������ԍ��P�Ԗ�
};


//==================================================================
//����낤�Ƃ��Ă���I�u�W�F�N�g��UI�N���X
class CNowCreateUI : public CManager2DUI
{
public:
	CNowCreateUI(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CNowCreateUI()override;                         //�f�X�g���N�^
	HRESULT Init()override;                          //����������

private:
	//�}�N����`
	static constexpr  float SIZEX = 100.0f;          //�T�C�Y��X���̑傫��
	static constexpr  float SIZEY = 100.0f;          //�T�C�Y��Y���̑傫��
};


//==================================================================
//�X�̃��j���[�ꗗUI�N���X
class CShopMenu : public CManager2DUI
{
public:
	CShopMenu(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CShopMenu()override;						  //�f�X�g���N�^
	HRESULT Init()override;						  //����������

private:
	//�}�N����`
	static constexpr  float SIZEX = 600.0f;        //�T�C�Y��X���̑傫��
	static constexpr  float SIZEY = 700.0f;        //�T�C�Y��Y���̑傫��
};


//==================================================================
//BuyText�\��UI�N���X
class CBuyText : public CManager2DUI
{
public:
	CBuyText(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CBuyText()override;						 //�f�X�g���N�^
	HRESULT Init()override;						 //����������

	static CBuyText* Create();                   //��������

private:
	//�}�N����`
	static constexpr  int ALPHA = 200;             //�A���t�@�l
	static constexpr  float SIZEX = 600.0f;        //�T�C�Y��X���̑傫��
};


//==================================================================
//�I�Ԏ���UI�N���X
class CSelectGage : public CObject2D
{
public:
	CSelectGage(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CSelectGage()override;							//�f�X�g���N�^
	HRESULT Init()override;							//����������
	void Uninit()override;							//�j������
	void Update()override;							//�X�V����
	void Draw()override;							//�`�揈��


	//========================================
	//�����擾
	float& GetSizeX() { return m_fSizeX; }          //�I���Q�[�W��X���̑傫���̎擾
	float& GetSizeY() { return m_fSizeY; }          //�I���Q�[�W��y���̑傫�����擾
	float& GetSize1X() { return m_fSize1X; }        //�I���Q�[�W001��x���̑傫���̎擾
	float& GetSize1Y() { return m_fSize1Y; }        //�I���Q�[�W001��y���̑傫���̎擾


	//=========================================
	//����ݒ�
	float& SetAddjustSizeX() { return m_fSizeX; }     //�I���Q�[�W��X���̑傫���̐ݒ�
	float& SetAddjustSize1X() { return m_fSize1X; }   //�I���Q�[�W��y���̑傫����ݒ�
	float& SetAddjustSizeY() { return m_fSizeY; }     //�I���Q�[�W001��x���̑傫���̐ݒ�
	float& SetAddjustSize1Y(){ return m_fSize1Y; }    //�I���Q�[�W001��y���̑傫���̐ݒ�

	static CSelectGage* Create();                     //��������

private:
	//�}�N����`
	 static constexpr  float SIZE1X = 600.0f;        //�I���Q�[�W�Q�Ԗڂ�X���̑傫��
	 static constexpr  float SIZEY = 50.0f;          //�I���Q�[�W�P�Ԗڂ�Y���̑傫��
	 static constexpr  float SIZE1Y = 150.0f;        //�I���Q�[�W�Q�Ԗڂ�Y���̑傫��
											       
	 static constexpr  int ALPHA = 100;              //�A���t�@�l

	float m_fSizeX;                                //�I���Q�[�W�̂P�Ԗ�X���̑傫����ۊǂ���p�̕ϐ�
	float m_fSizeY;                                //�I���Q�[�W�̂P�Ԗ�y���̑傫����ۊǂ���p�̕ϐ�
	float m_fSize1X;                               //�I���Q�[�W�̂Q�Ԗ�x���̑傫����ۊǂ���p�̕ϐ�
	float m_fSize1Y;                               //�I���Q�[�W�̂Q�Ԗ�y���̑傫����ۊǂ���p�̕ϐ�
};


//==================================================================
//�I�Ԏ���UI�N���X
class CSelectGage001 : public CSelectGage
{
public:
	CSelectGage001(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CSelectGage001()override;						   //�f�X�g���N�^
	HRESULT Init()override;							   //����������
	void Update()override;							   //�X�V����

	static CSelectGage001* Create();                   //��������
};