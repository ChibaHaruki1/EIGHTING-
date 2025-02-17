
//====================================================
//
//X�t�@�C���ǂݍ��݃N���X�Ǘ�[objectX.h]
//Auther:Chiba Haruki
//
//====================================================


#pragma once


#ifndef _OBJECTX_H_
#define _OBJECTX_H_


//====================================================
//�C���N���[�h
#include "objectmanagerX.h"
#include "input.h"
#include "collision.h"
#include "ui.h"


class CObjectX : public CObjectManagerX
{
public://�O������̃A�N�Z�X�\
	CObjectX(int nPriority = CObjectManagerX::DEFAULT_PRIORITY1);            //�R���X�g���N�^
	~CObjectX() override;                                                    //�f�X�g���N�^
	HRESULT Init()override;                                                  //����������
	void Uninit() override;                                                  //�j������
	void Update() override;                                                  //�X�V����
	void Draw() override;                                                    //�`�揈��
	void Size();                                                             //�RD���f���̃T�C�Y���擾���邽�߂̊֐�
	void Gravity();                                                          //�d�͏���
	void GravityTogether();                                                  //�d�͂𓯊������鏈��
	void Junp(TYPE type, float fJumpPwer);                                   //��ԏ���
	void TargetHeadingTowards(CObjectX* pObject, float MAX_SPEED);           //�ڕW�Ɍ���������
	HRESULT Lood();                                                          //���t�@�C���̓ǂݍ��݊֐��i�����œǂݍ��ރt�@�C���p�X��n���j
	void ObjectArrangement(CObjectX::TYPE type, CUI* pUI1);                  //�z�u�c�[��

	bool CollisionBossPrts();                                                //�v���C���[�ƃ{�X�̓����蔻��
	bool CollisionRightSelectPlayer(CObjectX* pObject);                      //�v���C���[�Ǝw�肵��obj�̓����蔻��i�P�́j�E��
	bool CollisionLeftSelectPlayer(CObjectX* pObject);                       //�v���C���[�Ǝw�肵��obj�̓����蔻��i�P�́j����
	bool CollisionPlayerSelect(CObjectX* pObject);                           //�v���C���[����obj�̓����蔻��
	bool CollisionPlayerInEnemy(CObjectX* pObject, float fMagnification);    //�v���C���[����obj�̓����蔻��+�����蔻��͈̔�


	//==================================================
	//���ꂼ��̏����ɕK�v�ȏ����擾����
	inline int& GetLife() { return m_nLife; }                                                                //���C�t���擾
	inline int& GetRandom() { return m_nRandom; }                                                            //�������擾
	inline int& GetFrame() { return m_nFrame; }                                                              //�t���[�����擾
	inline int& GetDieFrame() { return m_nDieFrame; }                                                        //���S���̃t���[�����ϑ�����p�̏����擾
	inline float& GetGravity() { return m_fGravity; }                                                        //�d�͂̏�������
	inline bool& GetJumpFlag() { return m_bJumpFlag; }                                                       //��Ԃ��ǂ����̃t���O���擾
	inline bool& GetOneFlag() { return m_bOneFlag; }                                                         //��x�����ʂ��t���O�̎擾
	inline const char* GetFileName() { return m_aFileName; }                                                 //�t�@�C���p�X�̎擾


	//==================================================
	//�e���̐ݒ�
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }                                                     //�ʒu�������Ɠ���������
	inline void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }                                                     //�����������Ɠ���������
	inline void SetLife(int nLife) { m_nLife = nLife; }                                                      //���C�t�������Ɠ���������
	inline void SetRandom(int nRandom) { m_nRandom = nRandom; }                                              //�����������Ɠ���������	
	inline void SetFrame(int nFrame) { m_nFrame = nFrame; }                                                  //�t���[���������Ɠ���������
	inline void SetDieFrame(int nDieFrame) { m_nDieFrame = nDieFrame; }                                      //���S���̃t���[���������Ɠ���������
	inline void SetGravity(float fGravity) { m_fGravity = fGravity; }                                        //�d�͂̒l�������Ɠ���������
	inline void SetGravityFlag(bool bGravityFlag) { m_bGravityFlag = bGravityFlag; }                         //�d�̓t���O�������Ɠ���������
	inline void SetJumpFlag(bool bJumpFlag) { m_bJumpFlag = bJumpFlag; }                                     //��Ԃ��ǂ����̐ݒ�
	inline void SetOneFlag(bool bOneFlag) { m_bOneFlag = bOneFlag; }                                         //��x�����ʂ������̃t���O�ݒ�
	inline void SetFileName(const char* aFileName) { m_aFileName = aFileName; }                              //�t�@�C���p�X�̐ݒ�


	//==================================================
	//�p�[�c���̈ʒu�̏����擾����
	inline D3DXVECTOR3& GetPosParts(int nNumber) { return m_posParts[nNumber]; }                       //�v���C���[�̊eparts��pos�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetPosPartsBoss(int nNumber) { return m_posPartsBoss[nNumber]; }               //�{�X�̊eparts��pos�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetPosPartsEnemy(int nNumber) { return m_posPartsEnemy[nNumber]; }             //�G�̊eparts��pos�̏���Ԃ��֐�


   //==================================================
   //�p�[�c���̃T�C�Y���擾����
	inline D3DXVECTOR3& GetModelSizeParts(int nNumber) { return m_ModelSizeParts[nNumber]; }           //�v���C���[�̃��f���̃T�C�Y���擾����
	inline D3DXVECTOR3& GetModelSizePartsBoss(int nNumber) { return m_ModelSizePartsBoss[nNumber]; }   //�{�X�̃��f���̃T�C�Y���擾����
	inline D3DXVECTOR3& GetModelSizePartsEnemy(int nNumber) { return m_ModelSizePartsEnemy[nNumber]; } //�G�̃��f���̃T�C�Y���擾����


   //==================================================
   //�v���C���[�̃��f���T�C�Y�̎擾
	inline D3DXVECTOR3& GetModelSize() { return m_ModelSize; }                                         //���f���̃T�C�Y���擾����
			

   //==================================================												  
   //�O���{���̎擾																				 
	inline D3DXVECTOR3& GetPos() { return m_pos; }                                                     //�h���N���X��pos�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetRot() { return m_rot; }                                                     //�h���N���X��rot�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetMove() { return m_move; }                                                   //�h���N���Xmove�̏���Ԃ�
						

   //==================================================												   
   //�����ɕK�v�ȕ��̏��̎擾																		  
	inline LPD3DXMESH& GetMesh() { return m_pMesh; }                                                   //mesh�̏���Ԃ�
	inline LPD3DXBUFFER& GetBuffMat() { return m_pBuffMat; }                                           //BuffMat�̏���Ԃ�
	inline DWORD& GetdwNumMat() { return m_dwNumMat; }                                                 //dwNumMat�̐��̏���Ԃ�
	inline D3DXMATERIAL* GetMat() { return m_pMat; }                                                   //Mat�̏���Ԃ�
	inline D3DXMATRIX& GetmtxWorld() { return m_mtxWorld; }                                            //���[���h�}�g���b�N�X�̏���Ԃ��֐�
																									   
	inline CCollision* GetCollision() { return m_pCollision; }                                         //�����蔻��̏���Ԃ��֐�


    //==================================================
    //�p�[�c���Ƃ̃T�C�Y�擾
	inline D3DXVECTOR3& GetMinParts(int nNumber) { return m_minParts[nNumber]; }                       //�p�[�c�̍ŏ��l�̎擾
	inline D3DXVECTOR3& GetMaxParts(int nNumber) { return m_maxParts[nNumber]; }                       //�p�[�c�̍ő�l�̎擾


	//==================================================
	//���̒l��ݒ�
	inline D3DXVECTOR3& SetAdjustPos() { return m_pos; }                                               //�ʒu�̒l��ύX���������̐ݒ�
	inline D3DXVECTOR3& SetAdjustRot() { return m_rot; }                                               //�����̒l��ύX���������̐ݒ�
	inline D3DXVECTOR3& SetAdjustMove() { return m_move; }                                             //�ړ��ʂ̒l��ύX���������̐ݒ�
	//inline SetPosPrts										                                          
															                                          
	inline int& SetAdjustLife() { return m_nLife; }                                                    //���C�t�̒l��ύX�������Ƃ��̐ݒ�
	inline int& SetAdjustDieFrame() { return m_nDieFrame; }                                            //���S���̃t���[�����ϑ�����p�̏����擾
	inline int& SetAdjustRandom() { return m_nRandom; }                                                //�����̒l��ύX���������̐ݒ�
	inline int& SetAdjustFrame() { return m_nFrame; }                                                  //�t���[���̒l��ύX���������̐ݒ�

	
													       
private:											       
	//�}�N����`									       
	 static constexpr int MAX_TEXTURE = 32;                  //�ۊǂł���ő�̃e�N�X�`���[��
	 static constexpr int MINUS_ROT = -1;                    //�����̒����l

	 static constexpr float HALF = 0.5f;                     //����
	 static constexpr float ENEMYINMOTION_PLUS_POS_X = 3.0f; //���[�V�����t���̓G��X���̈ʒu�̉��Z����l


	 //===========================================
	 //�I�u�W�F�N�g�z�u�̃}�N����`

	 static constexpr  float OBJECT_SET_PLUS_X = 1.0f;       //�I�u�W�F�N�g�̔z�u����X���̉E�̈ړ��̑���
	 static constexpr  float OBJECT_SET_MINUS_X = 1.0f;      //�I�u�W�F�N�g�̔z�u����X���̍��̈ړ��̑���
	 static constexpr  float OBJECT_SET_PLUS_Y = 1.0f;       //�I�u�W�F�N�g�̔z�u����Y���̏�̈ړ��̑���
	 static constexpr  float OBJECT_SET_MINUS_Y = 1.0f;      //�I�u�W�F�N�g�̔z�u����Y���̉��̈ړ��̑���
	 static constexpr float CREATE_PLUS_POS_X_1 = 600.0f;    //��������X���̈ʒu�̉��Z�l�P��
	 static constexpr float CREATE_PLUS_POS_X_2 = 100.0f;    //��������X���̈ʒu�̉��Z�l�Q��
	 static constexpr float CREATE_PLUS_POS_X_3 = 500.0f;    //��������X���̈ʒu�̉��Z�l�R��
	 static constexpr float CREATE_PLUS_POS_X_4 = 200.0f;    //��������X���̈ʒu�̉��Z�l�S��

	 static constexpr  float UI_SIZE = 50.0f;                //UI�T�C�Y�̐ݒ�


	 
													     
													     
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];          //�e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;                               //�}�g���b�N�X
												         
	D3DXMATERIAL* m_pMat;                                //�}�e���A���̃|�C���^
	LPD3DXMESH m_pMesh;                                  //���b�V���̂ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;                             //�o�b�t�@�ւ̃|�C���^
	DWORD m_dwNumMat;                                    //�}�e���A���̐�
												         
	//���f���T�C�Y�̎擾						            
	D3DXVECTOR3 min;                                     //���_�̍ŏ��l
	D3DXVECTOR3 max;                                     //���_�̍ő�l
	D3DXVECTOR3 m_ModelSize;                             //���f���̃T�C�Y���i�[
													     
	//�p�[�c���̈ʒu								     
	D3DXVECTOR3 m_posParts[MAX_PARTS];                    //���f���̈ʒu���i�[
	D3DXVECTOR3 m_posPartsBoss[MAX_BOSSPARTS];           //�{�X���f���̈ʒu���i�[
	D3DXVECTOR3 m_posPartsEnemy[MAX_ENEMYPARTS];         //�G���f���̈ʒu���i�[
													     
	//�p�[�c���Ƃ̃T�C�Y							     
	D3DXVECTOR3 m_minParts[MAX_PARTS];                     //���_�̍ŏ��l
	D3DXVECTOR3 m_maxParts[MAX_PARTS];                     //���_�̍ő�l
	D3DXVECTOR3 m_ModelSizeParts[MAX_PARTS];               //���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_ModelSizePartsBoss[MAX_BOSSPARTS];      //�{�X���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_ModelSizePartsEnemy[MAX_ENEMYPARTS];    //�G���f���̃T�C�Y���i�[
													     
	CCollision* m_pCollision;                             //�����蔻��֐��̃|�C���^�[
	D3DXVECTOR3 m_col;                                    //�F
	D3DXVECTOR3 m_pos;                                    //�ʒu
	D3DXVECTOR3 m_rot;                                    //����
	D3DXVECTOR3 m_move;                                   //�ړ���
	CUI* pUI;										     
													     
	int m_nLife;                                          //Life���i�[����ϐ��iHP�j
	int m_nRandom;                                        //�������i�[����ϐ�
	int m_nFrame;                                         //�t���[�����i�[����ϐ�
	int m_nDieFrame;                                      //���S�J�E���^�[
	float m_fGravity;                                     //�d�͉����x������
	float m_fAngle;                                       //�p�x���璷�������߂�p�̕ϐ�
	bool m_bGravityFlag;                                  //�d�͂�ON�ɂ��邩�ǂ���
	bool m_bJumpFlag;                                     //�W�����v�����Ă��邩�ǂ���
	bool m_bOneFlag;                                      //��񂾂�������ʂ��������p�̕ϐ�
	const char* m_aFileName;                              //x�t�@�C���̃p�X�n���悤�̕ϐ�
};

#endif // !_OBJECT3D_H_

