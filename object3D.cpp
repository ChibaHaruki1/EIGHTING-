//=========================================
//
//3D�I�u�W�F�N�g�̏���[object3D.cpp]
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//�C���N���[�h
#include "object3D.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//�����t���R���X�g���N�^
//=============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;                                              //�e�N�X�`���̃|�C���^�[�̏�����
	m_pVtxBuff = nullptr;                                              //�o�[�e�N�X�̃|�C���^�[�̏�����
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //�ʒu��������(�ʒu�𒲐��ł���j
	m_move = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ړ��ʂ�������(�ړ����x�𒲐��ł���j
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //����������������
	m_nLife = N_INIT_NUMBER;                                           //���C�t�̏�����
	m_nAlpha = N_INIT_ALPHA_NUMBER;                                    //�A���t�@�l�̏�����
	m_nFrame = N_INIT_NUMBER;                                          //�t���[���̏�����
	m_nRandom = N_INIT_NUMBER;                                         //�����̏�����
	m_fSizeX = F_INIT_NUMBER;                                          //X���̑傫���̏�����
	m_fSizeY = F_INIT_NUMBER;                                          //Y���̑傫���̏�����
	m_aFileName = nullptr;                                             //�t�@�C���p�X�̏�����
}


//=====================
//�f�X�g���N�^
//=====================
CObject3D::~CObject3D()
{

}


//=====================
//����������
//=====================
HRESULT CObject3D::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̎擾	

	//������
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�ʒu�̏�����
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�����̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_3D) * PVTX_NUMBER_OF, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[PVTX_NUMBER_0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_1].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_2].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_3].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);

	//�@���x�N�g���̐ݒ�
	pVtx[PVTX_NUMBER_0].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_1].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_2].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_3].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);

	//���_�J���[�̐ݒ�
	pVtx[PVTX_NUMBER_0].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[PVTX_NUMBER_1].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[PVTX_NUMBER_2].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[PVTX_NUMBER_3].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[PVTX_NUMBER_0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[PVTX_NUMBER_1].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
	pVtx[PVTX_NUMBER_3].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, CMain::MAX_TEXTURE_SIZE);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK; //������Ԃ�
}


//=====================================
//�r���{�[�h���̏������ݒ�
//=====================================
HRESULT CObject3D::BillboardInit()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̎擾

	//������
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);//�ʒu�̏�����
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //�����̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_3D) * PVTX_NUMBER_OF, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[1].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[3].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);
	pVtx[1].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);
	pVtx[2].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);
	pVtx[3].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);

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


//==================
//�I������
//==================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̏�񂪂��鎞
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release(); //��������
		m_pVtxBuff = nullptr;  //���𖳂���
	}

	//�e�N�X�`���̏�񂪂��鎞
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release(); //��������
		m_pTexture = nullptr;  //���𖳂���
	}
}


//==================
//�X�V����
//==================
void CObject3D::Update()
{
	//�ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//�ړ��ʂ��X�V�i����������j
	m_pos.x += (F_INIT_NUMBER - m_move.x) * UPDATE_MOVE; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_pos.y += (F_INIT_NUMBER - m_move.y) * UPDATE_MOVE; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_pos.z += (F_INIT_NUMBER - m_move.z) * UPDATE_MOVE; //���Ȃ��ق��������A�ʂ�ʂ铮��
}


//==================
//�T�C�Y�̐ݒ�
//==================
void CObject3D::SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X * HALF, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X * HALF, -SIZE_Y, SIZE_Z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=========================================
//�K�E�G�t�F�N�g�p�̃T�C�Y�̐ݒ�(X���p)
//=========================================
void CObject3D::SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X * HALF, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X * HALF, -SIZE_Y, SIZE_Z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=======================
//Y���p�̃T�C�Y�̐ݒ�
//=======================
void CObject3D::SetAdjustmentSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X * HALF, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, F_INIT_NUMBER, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X * HALF, F_INIT_NUMBER, SIZE_Z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//===================================================
//�F�̐ݒ菈��
//===================================================
void CObject3D::SetCol(int Red, int Green, int Blue,int& Alpha)
{
	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//===================================================
//�e�N�X�`���̑傫����ݒ肳����
//===================================================
void CObject3D::SetTexture(float SizeX, float Size1X)
{
	CMain::VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(SizeX, F_INIT_NUMBER);
	pVtx[2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
	pVtx[3].tex = D3DXVECTOR2(Size1X, CMain::MAX_TEXTURE_SIZE);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//================================
//�e�p�[�c���̓����蔻�菈���i�I���j
//================================
bool CObject3D::CollisionPrtsPlayer(float X, float Y, float Z)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = N_INIT_NUMBER; nCount < CObjectX::MAX_PARTS; nCount++)
	{
		//�v���C���[�̃p�[�c�ƈ����Ƃ̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount)) == true)
		{
			return true; //����
		}
	}
	return false;        //���s
}

//================================
//�e�p�[�c���̓����蔻�菈��
//================================
bool CObject3D::CollisionPrts1Left(float X, float Y, float Z)
{
	//�v���C���[�̍��p�[�c���̓����蔻�菈��
	for (int nCount = N_INIT_NUMBER; nCount < CCharacter::NUM_RIGHTLEFTPRTS; nCount++)
	{
		//�����`�̍��p�[�c�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_LEFT_SHOLDER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_LEFT_SHOLDER)) == true)
		{
			return true; //��������       
		}

		//���ӂƂ����`�̍��p�[�c�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_LEFT_THIGHS), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_LEFT_THIGHS)) == true)
		{
			return true; //��������        
		}
	}

	//����
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(CCharacter::PLAYER_PARTS_BODY_NUMBER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(CCharacter::PLAYER_PARTS_BODY_NUMBER)) == true)
	{
		return true;     //��������         
	}

	return false;        //�������Ă��Ȃ�
}

//================================
//�e�p�[�c���̓����蔻�菈��
//================================
bool CObject3D::CollisionPrts1Right(float X, float Y, float Z)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = N_INIT_NUMBER; nCount < CCharacter::NUM_RIGHTLEFTPRTS; nCount++)
	{
		//�E������̉E�p�[�c�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_SHOLDER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_SHOLDER)) == true)
		{
			return true; //��������
		}

		//�E�ӂƂ����`�̉E�p�[�c�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_THIGHS), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_THIGHS)) == true)
		{
			return true; //��������
		}
	}

	//����
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(CCharacter::PLAYER_PARTS_BODY_NUMBER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(CCharacter::PLAYER_PARTS_BODY_NUMBER)) == true)
	{
		return true;     //��������
	}

	return false;        //�������Ă��Ȃ�
}


//==================
//�`�揈��
//==================
void CObject3D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans;                        //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);
}

//===========================
//�r���{�[�h�`�揈��
//===========================
void CObject3D::DrawBillboard()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans;                        //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;                                 //�r���[�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾�擾�p;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�

	//�}�g���b�N�X�s��̒���
	m_mtxWorld._41 = F_INIT_NUMBER;
	m_mtxWorld._42 = F_INIT_NUMBER;
	m_mtxWorld._43 = F_INIT_NUMBER;

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);
}


//===========================
//�G�t�F�N�g���̕`�揈��
//===========================
void CObject3D::DrawEffect()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans;                        //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;                                 //�r���[�}�g���b�N�X

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾�擾�p;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�

	//�}�g���b�N�X�s��̒���
	m_mtxWorld._41 = F_INIT_NUMBER;
	m_mtxWorld._42 = F_INIT_NUMBER;
	m_mtxWorld._43 = F_INIT_NUMBER;

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, N_INIT_NUMBER);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//a�u�����f�B�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//======================================================
//�G�t�F�N�g���̕`�揈��(Z�o�b�t�@���������܂Ȃ�)
//======================================================
void CObject3D::DrawEffect1()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;          //�r���[�}�g���b�N�X

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, N_INIT_NUMBER);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//a�u�����f�B�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//===================================
//�e�N�X�`���t�@�C���̓ǂݍ���
//===================================
HRESULT CObject3D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	//�e�N�X�`���̃t�@�C�����Ȃ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}