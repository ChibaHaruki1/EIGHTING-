//=============================================
//
//�p�[�e�B�N���̃N���X�Ǘ�[particles.h]
//Author:chiba haruki
//
//=============================================


#pragma once


//=============================================
//�C���N���[�h
#include "object3D.h"


//====================================================================
//�p�[�e�B�N��001�̃N���X
class CParticles001 : public CObject3D
{
public:
	CParticles001(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CParticles001()override;						  //�f�X�g���N�^
	HRESULT Init()override;							  //����������
	void Uninit()override;							  //�j������
	void Update()override;							  //�X�V����
	void Draw()override;							  //�`�揈��

	static CParticles001* Create(D3DXVECTOR3 pos);    //��������

private:
	//�}�N����`
	static constexpr  int MAX_PARTICLES001_LIFE = 60;  //�p�[�e�B�N��001�̃��C�t
	static constexpr int CREATE_PRIORITY = 2;          //�������̃v���C�I���e�B�̔ԍ�

	static constexpr  float SIZEX = 10.0f;             //X���̑傫��
	static constexpr  float SIZEY = 10.0f;             //X���̑傫��
	static constexpr  float SIZEZ = 10.0f;             //X���̑傫��
	static constexpr  float PLUS_POSY = 2.0f;          //Y���̑����l
};
