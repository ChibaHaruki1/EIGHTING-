//==========================================
//
//�����_���[�N���X�Ǘ�[renderer.h]
//Auther:Chiba Haruki
//
//==========================================

#pragma once

//==========================================
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "objectmanagerX.h"
#include "objectX.h"

class CRenderer
{
public:
	CRenderer();                                                   //�R���X�g���N�^
	~CRenderer();                                                  //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);    //����������
	void Uninit();                                                 //�j������
	void Update();                                                 //�X�V����
	void Draw();                                                   //�`�揈��
	void DrawFPS();                                                //FPS��`�悷�鏈��


	//==================================
	//���̎擾
	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }  //�RD�f�o�C�X���擾
	inline bool& GetPause() { return m_bPause; }                   //�|�[�Y�����ǂ����̔�����擾
	inline bool& GetDrawShader() { return m_bDrawShader; }         //�V�F�[�_�[���g�����ǂ����̔�����擾
																   
private:					

	//=====================================
	//FPS�Ɋւ���}�N����`
	static constexpr int MAX_STR = 10;                             //FPS�\�����̕�����̍ő吔
	static constexpr int DRAW_LONG_TEXT = -1;                      //�`��̃e�L�X�g�̃J�E���g�i�������[�P�̎�null�ɂȂ莩���������j


	//=====================================
	//�t�H���g�Ɋւ���}�N����`
	static constexpr int FONT_HEIGHT = 18;                         //����
	static constexpr int FONT_WIDTH = 0;                           //��
	static constexpr int FONT_WEIGHT = 0;                          //�d��
	static constexpr int FONT_MIPLEVELS = 0;                       //�𑜓x(�Ⴍ�Ȃ��Ă���)


	//=====================================
	//��ʃN���A�Ɋւ���}�N����`
	static constexpr int CLEAR_STENCIL = 0;                        //�X�e���V���l

	static constexpr float CLEAR_Z = 1.0f;                         //Z�l

	LPDIRECT3D9 m_pD3D;                                            //Direct3D�̎�v���
	LPDIRECT3DDEVICE9 m_pD3DDevice;                                //Direct3D�f�o�C�X
	LPD3DXFONT m_pFont;                                            //�t�H���g�̏��
	bool m_bPause;                                                 //�|�[�Y�����ǂ����̔��������p�̕ϐ�
	bool m_bDrawShader;                                            //�V�F�[�_�[��`�悷�邩�ǂ���
};

