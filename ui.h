//==========================================
//
//UI�̃N���X�Ǘ�[ui.h]
//Author:chiba haruki
//
//==========================================


#pragma once


//==========================================
//�C���N���[�h
#include "object3D.h"
#include <cstdio>


//======================================================
//UI�̃}�l�[�W���[�Ǘ��N���X
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);      //�R���X�g���N�^
	~CUI()override;							    //�f�X�g���N�^
	HRESULT Init()override;					    //����������
	void Uninit()override;					    //�j������
	void Update()override;					    //�X�V����
	void Draw()override;					    //�`�揈��
	virtual void Hit() = 0;                     //�����蔻�菈��

	static CUI* Create(CObject3D::TYPE typeui); //��������

private:
	//�}�N����`
	static constexpr int CREATE_PRIORITY = 0;   //�������̃v���C�I���e�B�̔ԍ�
};


//======================================================
//���݂̔z�u�����I�u�W�F�N�g�̏ꏊ��UI���o���N���X�Ǘ�
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CCreateInObject()override;                         //�f�X�g���N�^
	void Hit()override {};                              //�����蔻�菈��
};


//======================================================
//����낤�Ƃ��Ă���I�u�W�F�N�g��UI�������N���X�Ǘ�
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CTalkText()override;                         //�f�X�g���N�^
	HRESULT Init()override;                       //����������
	void Draw()override;                          //�`�揈��
	void Hit()override {};                        //�����蔻�菈��

private:
	//�}�N����`
	static constexpr  float SIZEX = 40.0f; //X���̑傫��
	static constexpr  float SIZEY = 40.0f; //Y���̑傫��
	static constexpr  float SIZEZ = 40.0f; //Z���̑傫��
};


//======================================================
//�Ď��J��������ł郌�[�U�[�N���X
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);       //�R���X�g���N�^
	~CLaserCamare()override;                              //�f�X�g���N�^
	HRESULT Init()override;                               //����������
	void Update()override;                                //�X�V����
	void Draw()override;                                  //�`�揈��
	void Hit()override;                                   //�����蔻�菈��


	//===========================
	//�}�N����`
	static constexpr  float SIZEX = 80.0f;                 //X���̑傫��
	static constexpr  float SIZEY = 20.0f;                 //Y���̑傫��
	static constexpr  float SIZEZ = 20.0f;                 //Z���̑傫��
	static constexpr  float ADJUST_ADDJUST_SIZE = 1.3f;   //�v���C���[�Ƃ̓����蔻�莞�̏�Z�l


	static 	constexpr float TOTALVALUE_X = SIZEY * ADJUST_ADDJUST_SIZE; //X���p�̓����蔻��p�̍��v�l
	static 	constexpr float TOTALVALUE_Y = SIZEX * ADJUST_ADDJUST_SIZE; //Y���p�̓����蔻��p�̍��v�l
	static 	constexpr float TOTALVALUE_Z = SIZEZ * ADJUST_ADDJUST_SIZE; //Z���p�̓����蔻��p�̍��v�l

private:
	//�}�N����`
	static constexpr int MIN_RANDOM = 1; //�����̍ŏ��l
	static constexpr int MAX_RANDOM = 2; //�����̍ő�l

	static constexpr  float ADJUST_POSY = 20.0f;          //Y���̈ʒu�̒����l
	static constexpr  float ADJUST_POSZ = 35.0f;          //Z���̈ʒu�̒����l
	static constexpr  float ADJUST_ROTY = 0.54f;          //Y���̌����̒����l
	static constexpr  float ADJUST_ROTZ = 1.54f;          //Z���̌����̒����l
	static constexpr  float ADJUST_CREATE_POSX = 300.0f;  //X���̐����ʒu�̒����l
	static constexpr  float ADJUST_CREATE_POSY = 300.0f;  //Y���̐����ʒu�̒����l
};
