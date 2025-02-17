//=======================================
//
//3D�I�u�W�F�N�g�N���X�Ǘ�[object3D.h]
//Auther:Chiba Haruki
//
//=======================================


#pragma once


//=======================================
//�C���N���[�h
#include "object.h"

class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = DEFAULT_PRIORITY);                             //�R���X�g���N�^
	~CObject3D() override;                                                   //�f�X�g���N�^
	HRESULT Init() override;                                                 //����������
	HRESULT BillboardInit();                                                 //�r���{�[�h���̏������ݒ�
	void Uninit() override;                                                  //�j������
	void Update()override;                                                   //�X�V����
	void Draw() override;                                                    //�`�揈��
	void DrawBillboard();                                                    //�r���{�[�h�̕`�揈��
	void DrawEffect();                                                       //�G�t�F�N�g�p�̕`�揈��
	void DrawEffect1();                                                      //�G�t�F�N�g001�p�̕`�揈��
	void SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z);                  //�T�C�Y�𒲐����鏈��
	void SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z);            //�G�t�F�N�g�ppolygon�̃T�C�Y�𒲐����鏈��
	void SetAdjustmentSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z);       //Y���p�̃T�C�Y�𒲐����鏈��
	void SetCol(int Red, int Green, int Blue, int& Alpha);                   //�F�Ɋւ���ݒ�
	void SetTexture(float SizeX, float Size1X);                              //�e�N�X�`���̃T�C�Y��ݒ肷��

	//�����蔻�菈��(�|���S���Ƃ̓����蔻��)
	bool CollisionPrts1Right(float X, float Y, float Z);     //�p�[�c���̓����蔻��@�E��
	bool CollisionPrts1Left(float X, float Y, float Z);      //�p�[�c���̓����蔻��@����
	bool CollisionPrtsPlayer(float X, float Y, float Z);     //�p�[�c���̓����蔻��@�S��

	HRESULT Lood();                                          //�e�N�X�`���t�@�C���̓ǂݍ���


	//==================================================
	//���̎擾
	inline LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; } //�o�b�t�@�̎擾
	inline LPDIRECT3DTEXTURE9& GetTexture() { return m_pTexture; }     //�e�N�X�`���̎擾
	inline int& GetLife() { return m_nLife; }                          //���C�t�̎擾
	inline int& GetAlpha() { return m_nAlpha; }                        //�A���t�@�l���擾
	inline int& GetFrame() { return m_nFrame; }                        //�t���[�����擾
	inline int& GetRandom() { return m_nRandom; }                      //�������擾
	inline float& GetSizeX() { return m_fSizeX; }                      //X���̑傫�����擾
	inline float& GetSizeY() { return m_fSizeY; }                      //Y���̑傫�����擾


	//==================================================
	///�O���{���̎擾
	inline D3DXVECTOR3& GetPos() { return m_pos; }                     //�ʒu�̎擾
	inline D3DXVECTOR3& GetMove() { return m_move; }                   //�ړ��ʂ̎擾
	inline D3DXVECTOR3& GetRot() { return m_rot; }                     //�����̎擾


	//==================================================
	//�e���̐ݒ�
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }                             //�ʒu�������Ɠ���������
	inline void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }                             //�����������Ɠ���������
	inline void SetMove(D3DXVECTOR3 move) { m_move = move; }                         //�ړ��ʂ������Ɠ���������
	inline void SetLife(int nLife) { m_nLife = nLife; }                              //���C�t�������Ɠ���������
	inline void SetAlpha(int nAlpha) { m_nAlpha = nAlpha; }                          //�A���t�@�l�������Ɠ���������
	inline void SetFrame(int nFrame) { m_nFrame = nFrame; }                          //�t���[���������Ɠ���������
	inline void SetRandom(int nRandom) { m_nRandom = nRandom; }                      //�����������Ɠ���������
	inline void SetSizeX(float fSizeX) { m_fSizeX = fSizeX; }                        //X���̑傫���������Ɠ���������
	inline void SetSizeY(float fSizeY) { m_fSizeY = fSizeY; }                        //X���̑傫���������Ɠ���������
	inline void SetFileNamePass(const char* aFileName) { m_aFileName = aFileName; }  //�t�@�C���p�X�������Ɠ���������
	

	//==================================================
	//���̒l���v���Đݒ�
	D3DXVECTOR3& SetAdjustPos() { return m_pos; }                             //�ʒu�̒l��ύX�������Ƃ��̐ݒ�
																	          
	inline int& SetAdjustLife() { return m_nLife; }                           //���C�t�̒l��ύX�������Ƃ��̐ݒ�
	inline int& SetAdjustAlpha() { return m_nAlpha; }                         //�A���t�@�l�̕ύX�������Ƃ��̐ݒ�
	inline int& SetAdjustFrame() { return m_nFrame; }                         //�t���[���̒l��ύX�������Ƃ��̐ݒ�
																	          
	inline float& SetAddjustSizeX() { return m_fSizeX; }                      //X���̒l��ύX�������Ƃ��̐ݒ�
	inline float& SetAddjustSizeY() { return m_fSizeY; }                      //Y���̒l��ύX�������Ƃ��̐ݒ�


private:
	//�}�N����`
	static constexpr float UPDATE_MOVE = 0.5f;                                //�ړ��ʂ̍X�V�l
	static constexpr float HALF = 0.5f;                                       //����

	LPDIRECT3DTEXTURE9 m_pTexture;                                            //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;                                       //���_�o�b�t�@�̃|�C���^
										                                      
	D3DXVECTOR3 m_pos;                                                        //�ʒu
	D3DXVECTOR3 m_move;                                                       //�ړ���
	D3DXVECTOR3 m_rot;                                                        //����
	D3DXMATRIX m_mtxWorld;                                                    //�}�g���b�N�X
						                                                      
	int m_nLife;                                                              //���C�t��ۊǂ���p�̕ϐ�
	int m_nAlpha;                                                             //�A���t�@�l��ۊǂ���p�̕ϐ�
	int m_nFrame;                                                             //�t���[����ۊǂ���p�̕ϐ�
	int m_nRandom;                                                            //������ۊǂ���p�̕ϐ�
					                                                          
	float m_fSizeX;                                                           //�����̃T�C�Y�̒����p�ϐ�
	float m_fSizeY;                                                           //�����̃T�C�Y�̒����p�ϐ�
							                                                  
	const char* m_aFileName;                                                  //�t�@�C���p�X��ۊǂ���p�̕ϐ�
};

