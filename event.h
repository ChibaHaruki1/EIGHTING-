//================================================================
//
//�X�e�[�W���̃C�x���g�����N���X[event.h]
//Auther:Haruki Chiba
//
//================================================================

#pragma once

//=====================
//�C���N���[�h
#include <vector>
#include "instance.h"

//=====================================================================================================
//event�̊��N���X
//=====================================================================================================
class CEvent
{
public:
	CEvent();                  //�f�X�g���N�^
	~CEvent();                 //�R���X�g���N�^
	void Update();             //�X�V����
	void DropObj();            //obj�̗��Ƃ�����
	void BossDirection();      //�{�X�̉��o����	
	void DropMeteorite();      //覐΂𗎂Ƃ�����
	void CreateEnemy();        //�G�̐���


	//==========================
	//���̎擾
	bool& GetBossDirection() { return m_bBossDirection; } //�{�X�̐���������Ă��邩�ǂ����̏����擾


	//==========================
	//�}�N����`
	 static constexpr  float CANERA_POSY = 400.0f;                //�J������Y���̈ʒu

private:
	//�}�N����`
	static constexpr int CANERA_POSZ = 1400;                    //�J������Z���̈ʒu
	static constexpr int RAND_ROTX = 15;                        //�؂̔R�̗��Ƃ��Ƃ��̌�����X���̒l
	static constexpr int RAND_ROTY = 31;                        //�؂̔R�̗��Ƃ��Ƃ��̌�����Y���̒l
	static constexpr int INIT_DROP_POS = 18;                    //�؂̔R�̗��Ƃ��ʒu�����炩���ߐݒ肷�邽�߂̒l
	static constexpr int BEFORE_NUMBER = 1;                     //�O�̔ԍ�

	static constexpr float ADJUST_ROT = 0.1f;                   //�����ŏo�����l�������ɒ����ׂ̒l
	static constexpr float EVENT_BOSS_FIGHT_POS = 3650.0f;      //�{�X��̎n�܂�ɂȂ�ʒu
	static constexpr float CREATE_BOSS_POSX = 4700.0f;          //�{�X������������X���̈ʒu
	static constexpr float CREATE_MOTIONINENEMY_POSX = 9500.0f; //���[�V�����t���̓G������������X���̈ʒu
	static constexpr float CREATE_MOTIONINENEMY_POSY = 5000.0f; //���[�V�����t���̓G������������Y���̈ʒu
	static constexpr float CREATE_WOODENBOARD_POSX = 3250.0f;   //�؂̔Q������������X���̈ʒu
	static constexpr float CREATE_WOODENBOARD_POSY = 350.0f;    //�؂̔Q������������Y���̈ʒu
	static constexpr float WOODENBOARD_DROPY = 10.0f;           //�؂̔Q�̗��Ƃ��ʒu�𑝂₷�l
	static constexpr float WOODENBOARD_PLUSY = 0.12f;           //�؂̔Q�̗��Ƃ����x�𑝂₷�l
	static constexpr float PLUS_POS_X = 500.0f;			        //�؂̔Q�̗��Ƃ����x�𑝂₷�l

	static constexpr int N_INIT_NUMBER = 0;                     //int�^�̏������̒l
	static constexpr float F_INIT_NUMBER = 0.0f;                //float�^�̏������̒l




	int m_nCreateWoodenBoradsCounter;            //�������鐔
	int m_nRandomRotX;                           //�����̃����_������ۊǂ���
	int m_nRandomRotY;                           //�����̃����_������ۊǂ���
	float m_nPosY;                               //��������Y����pos
	float m_fDropSpeed[CInstance::MAX_RUBBLE];   //���Ƃ����x�����߂�ϐ�
	float m_fDropPosY[CInstance::MAX_RUBBLE];    //���Ƃ��ʒu�����炩���ߌ��߂�ϐ�
	bool m_bBossDirection;                       //�{�X�̉��o��1�񂾂��o�����߂̏���
	bool m_bOneflag;                             //��񂾂�������ʂ��p�̕ϐ�
	bool m_bOneCreate;                           //��񂾂���������p�̕ϐ�
};
