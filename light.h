//=======================================
//
//�����N���X�Ǘ�[light.h]
//Auther:Haruki Chiba
//
//=======================================


#pragma once


//=======================================
//�C���N���[�h
#include "main.h"


class CLight
{
public:
	CLight();         //�R���X�g���N�^
	~CLight();        //�f�X�g���N�^
	HRESULT Init();   //����������
	void Uninit();    //�j������
	void Update();    //�X�V����

private:
	//�}�N����`
	static constexpr int N_INIT_NUMBER = 0;          //int�^�̏������̒l  
	static constexpr float F_INIT_NUMBER = 0.0f;     //float�^�̏������̒l

	static constexpr float ZERO_LIGHT_POS_Z = 1.2f;  //�O�Ԗڂ�Z���̈ʒu
	static constexpr float ONE_LIGHT_POS_Z = 0.8f;   //�P�Ԗڂ�Z���̈ʒu
	static constexpr float TWO_LIGHT_POS_X = 1.0f;   //�Q�Ԗڂ�X���̈ʒu
	static constexpr float THREE_LIGHT_POS_X = 1.0f; //�R�Ԗڂ�X���̈ʒu
	static constexpr float ALL_LIGHT_POS_Y = 1.0f;   //�S�Ă�Y���̈ʒu

	static constexpr float RED = 1.0f;               //�ԐF
	static constexpr float GREEN = 1.0f;             //�ΐF
	static constexpr float BLUE = 1.0f;              //�F
	static constexpr float ALPHA = 1.0f;             //�A���t�@�l

	static const int MAX_LIGHT = 4; //�����̍ő吔
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //�����̏��
};
