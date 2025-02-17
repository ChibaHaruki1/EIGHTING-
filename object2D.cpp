//=========================================
//
//�Q�c�I�u�W�F�N�g�̏���[object2D.cpp]
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//�C���N���[�h
#include "main.h"
#include "object2D.h"
#include "rendererh.h"
#include "manager.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "collision.h"
#include "score.h"


//=============================
//�����t���R���X�g���N�^
//=============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;                                              //�e�N�X�`���̃|�C���^�[�̏�����
	m_pVtxBuff = nullptr;                                              //�o�b�t�@�̃|�C���^�[�̏�����
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //�ʒu��������(�ʒu�𒲐��ł���j
	m_move = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ړ��ʂ�������(�ړ����x�𒲐��ł���j
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //����������������
	m_nRandom = N_INIT_NUMBER;                                         //�����̏�����
	m_nFrame = N_INIT_NUMBER;                                          //�t���[���̏�����
	m_nAlpha = N_INIT_NUMBER;                                          //�A���t�@�l�̏�����
	m_aFileName = nullptr;                                             //�t�@�C���p�X�̏�����
}


//=====================
//�f�X�g���N�^
//=====================
CObject2D::~CObject2D()
{

}


//=====================
//����������
//=====================
HRESULT CObject2D:: Init()
{
	CRenderer *pRenderer = CManager::GetRenderer(); //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice;                      //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_2D) * PVTX_NUMBER_OF, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	CMain::VERTEX_2D* pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[1].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, CMain::SCREEN_HEIGHT, F_INIT_NUMBER);
	pVtx[3].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, CMain::SCREEN_HEIGHT, F_INIT_NUMBER);

	//rhw�̐ݒ�
	pVtx[0].rhw = CMain::RHW;
	pVtx[1].rhw = CMain::RHW;
	pVtx[2].rhw = CMain::RHW;
	pVtx[3].rhw = CMain::RHW;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[1].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[2].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[3].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, F_INIT_NUMBER);
	pVtx[2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
	pVtx[3].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, CMain::MAX_TEXTURE_SIZE);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK; //������Ԃ�
}

//=====================
//�I��������������
//=====================
HRESULT CObject2D::SelectInit(int nPieces,float nTexture)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice;                      //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_2D) * PVTX_NUMBER_OF * nPieces, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetBuffer(), NULL);

	CMain::VERTEX_2D* pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//��������
	for (int nCutScore = N_INIT_NUMBER; nCutScore < nPieces; nCutScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
		pVtx[1].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
		pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
		pVtx[3].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);

		//rhw�̐ݒ�
		pVtx[0].rhw = CMain::RHW;
		pVtx[1].rhw = CMain::RHW;
		pVtx[2].rhw = CMain::RHW;
		pVtx[3].rhw = CMain::RHW;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
		pVtx[1].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
		pVtx[2].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
		pVtx[3].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV���W�ɒ��Ӂi����P�D�O���j
		pVtx[1].tex = D3DXVECTOR2(nTexture, F_INIT_NUMBER);
		pVtx[2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
		pVtx[3].tex = D3DXVECTOR2(nTexture, CMain::MAX_TEXTURE_SIZE);

		pVtx += PVTX_NUMBER_OF;                                  //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}


//=====================
//�I�������i�j���j
//=====================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release(); //��������
		m_pVtxBuff = nullptr;  //���𖳂���
	}
}


//=====================
//�X�V����
//=====================
void CObject2D::Update ()
{
	
}

//=====================
//�`�揈��
//=====================
void CObject2D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);
}

//=====================
//�����`�悷�鏈��
//=====================
void CObject2D::MultipleDraw(int nPieces)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //�f�o�C�X�̃|�C���^	

	UINT uStartVerTex = nPieces * PVTX_NUMBER_OF;

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, uStartVerTex, PRIMITIVECOUNT);
}



//==================
//�T�C�Y�̐ݒ�
//==================
void CObject2D::SetSIze(float SIZE_X, float SIZE1_X, float SIZE_Y, float SIZE1_Y)
{
	CMain::VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SIZE_X, SIZE_Y, F_INIT_NUMBER);
	pVtx[1].pos = D3DXVECTOR3(SIZE1_X, SIZE_Y, F_INIT_NUMBER);
	pVtx[2].pos = D3DXVECTOR3(SIZE_X, SIZE1_Y, F_INIT_NUMBER);
	pVtx[3].pos = D3DXVECTOR3(SIZE1_X, SIZE1_Y, F_INIT_NUMBER);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================
//�T�C�Y�̐ݒ�
//==================
void CObject2D::SetCol(int Red, int Green, int Blue, int Alph)
{
	CMain::VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//===============================
//�e�N�X�`���̓ǂݍ��ݏ���
//===============================
HRESULT CObject2D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̎擾

	//�e�N�X�`���̃t�@�C�����Ȃ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL; //���s��Ԃ�

	}

	return S_OK;       //������Ԃ�
}
