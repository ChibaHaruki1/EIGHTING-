//==================================
//
//ブロックの処理[block.cpp]
//Auther:Chiba Haruki
//
//==================================


//==================================
//インクルード
#include"manager.h"
#include "rendererh.h"
#include "block.h"
#include <string>


//==================================
//staticメンバー変数の初期化
int CManagerBlock::m_nCreateCount = CObjectX::N_INIT_NUMBER; //初期化


//==================================
//文字列の設定
std::string u8NormalBlockText = u8"ブロックの情報設定";      //日本語対応
std::string u8NormalBlockNumberText = u8"番目の";            //日本語対応


//====================================================================================================================================
//ストラテジー基底クラス
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlockXStrategy::CBlockXStrategy()
{
	m_aBlockFile = nullptr; //ファイルパスの初期化
}

//============================
//デストラクタ
//============================
CBlockXStrategy::~CBlockXStrategy()
{

}


//====================================================================================================================================
//ブロック000
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock000::CBlock000()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block002.x"); //ファイルパス設定
}

//============================
//デストラクタ
//============================
CBlock000::~CBlock000()
{

}


//====================================================================================================================================
//ブロック001
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock001::CBlock001()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block004.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CBlock001::~CBlock001()
{

}


//====================================================================================================================================
//ブロック002
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock002::CBlock002()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block005.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CBlock002::~CBlock002()
{

}


//====================================================================================================================================
//ブロック003
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock003::CBlock003()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block003.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CBlock003::~CBlock003()
{

}


//====================================================================================================================================
//ブロック004
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock004::CBlock004()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block006.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CBlock004::~CBlock004()
{

}


//====================================================================================================================================
//ブロック005
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock005::CBlock005()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block007.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CBlock005::~CBlock005()
{

}


//====================================================================================================================================
//ブロック006
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CBlock006::CBlock006()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\Block008.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CBlock006::~CBlock006()
{

}


//====================================================================================================================================
//次のステージへ行く用obj
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CSpaceBattleShip::CSpaceBattleShip()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\SpaceBattleship000.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CSpaceBattleShip::~CSpaceBattleShip()
{

}


//====================================================================================================================================
//最終ステージ用のブロック
//====================================================================================================================================

//============================
//コンストラクタ
//============================
CFinalBlock::CFinalBlock()
{
	SetBlockFileNamePass("data\\XFILE\\BLOCK\\FianlStage.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CFinalBlock::~CFinalBlock()
{

}


//============================================================================================================================================================
//ブロックの管理者処理
//============================================================================================================================================================

//============================
//コンストラクタ
//============================
CManagerBlock::CManagerBlock(int nPriority) : CObjectX(nPriority)
{
	m_pBlockXStrategy = nullptr; //ストラテジー基底クラスのポインターの初期化
}

//============================
//デストラクタ
//============================
CManagerBlock::~CManagerBlock()
{
	//ストラテジー基底クラスのポインターの情報がある時
	if (m_pBlockXStrategy != nullptr)
	{
		delete m_pBlockXStrategy;     //情報を消す
		m_pBlockXStrategy = nullptr;  //情報を無くす
	}
}

//============================
//初期化処理
//============================
HRESULT CManagerBlock::Init()
{
	//初期化に成功した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}

//============================
//破棄処理
//============================
void CManagerBlock::Uninit()
{
	CObjectX::Uninit(); //破棄処理
}

//============================
//更新処理
//============================
void CManagerBlock::Update()
{
	//CObjectX::Update(); //更新処理
}

//============================
//描画処理
//============================
void CManagerBlock::Draw()
{
	CObjectX::Draw(); //描画処理
}

//============================================================================
//各クラスの生成処理
//============================================================================
CManagerBlock* CManagerBlock::Create(D3DXVECTOR3 pos, STRATEGYTYPE type)
{
	CManagerBlock* pManagerBlock = nullptr; //基底クラスのポインター

	//タイプが地面用ブロックの時
	if (type == STRATEGYTYPE::FIELDBLOCK)
	{
		pManagerBlock = new CFiledBlock(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock000();  //ストラテジー継承クラス
		}

	}

	//タイプが上に上がる用ブロックの時
	else if (type==STRATEGYTYPE::GOUPBLOCK)
	{
		pManagerBlock = new CGoUpBlock(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock001();  //ストラテジー継承クラス
		}
	}

	//タイプが道用ブロックの時
	else if (type == STRATEGYTYPE::ROADBLOCK)
	{
		pManagerBlock = new CRoadBlock(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock002();  //ストラテジー継承クラス
		}
	}

	//タイプが壁兼道用ブロックの時か壁兼道用ブロック001の時
	else if (type == STRATEGYTYPE::WALLROADBLOCK|| type == STRATEGYTYPE::WALLROADBLOCK001)
	{
		pManagerBlock = new CWallRoadBlock(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock003();  //ストラテジー継承クラス
		}
	}

	//タイプが小さいブロックの時か小さいブロック001の時
	else if (type == STRATEGYTYPE::SMALLBLOCK||type== STRATEGYTYPE::SMALLBLOCK001)
	{
		pManagerBlock = new CSmallBlock(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock004();  //ストラテジー継承クラス
		}
	}

	//タイプが上壁用ブロックの時
	else if (type == STRATEGYTYPE::UPWALLBLOCK)
	{
		pManagerBlock = new CUpWallBlock(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock005();  //ストラテジー継承クラス
		}
	}

	//タイプがバトルシップの時
	else if (type == STRATEGYTYPE::SPECEBATTLESHIP000)
	{
		pManagerBlock = new CSpaceBattleShip000(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CSpaceBattleShip();  //ストラテジー継承クラス
		}
	}

	//タイプが最終ステージブロックの時
	else if (type == STRATEGYTYPE::FINALBLOCK)
	{
		pManagerBlock = new CScaffold(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CFinalBlock();  //ストラテジー継承クラス
		}
	}

	//タイプが最終ステージ天井の時
	else if (type == STRATEGYTYPE::FINALCEILLING)
	{
		pManagerBlock = new CCeiling(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CFinalBlock1();                                             //ストラテジー継承クラス
			pManagerBlock->m_pBlockXStrategy->SetBlockFileNamePass("data\\XFILE\\BLOCK\\FianlStageCeiling.x"); //ファイルパスの設定
		}
	}

	//タイプが木の板群の時
	else if (type == STRATEGYTYPE::WODDENBORAD)
	{
		pManagerBlock = new CWoodenBorad(); //継承クラスを動的確保する

		//初期化に成功した時
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CRubble();                                                 //ストラテジー継承クラス
			pManagerBlock->m_pBlockXStrategy->SetBlockFileNamePass("data\\XFILE\\StageObj\\wooden_boards.x"); //ファイルパスの設定
		}
	}

	//情報があるかどうかを判定する
	if (pManagerBlock != nullptr)
	{
		pManagerBlock->SetFileName(pManagerBlock->m_pBlockXStrategy->GetBlockFileNamePass()); //ファイルパスをストラテジー基底クラスの物と同期させる
		pManagerBlock->GetPos() = pos; //位置の同期
		pManagerBlock->Lood();         //ｘファイルを読み込む
		pManagerBlock->Size();         //大きさの読み取り
		return pManagerBlock;          //情報を返す
	}

	return nullptr; //無を返す
}

//==================================
//textファイルに書き込む処理
//==================================
void CManagerBlock::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ,CObjectX::TYPE type)
{
	FILE* pFile = nullptr;                               //ファイルポインター
	pFile = fopen("data\\TEXT\\OBJECT\\Block.txt", "a"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	m_nCreateCount++;                                                        //作られた数を増やす
	fprintf(pFile, "%s", "#=====================================\n");        //文字を書き込む
	fprintf(pFile, "%s", "#");                                               //文字を書き込む
	fprintf(pFile, "%d", m_nCreateCount);                                    //数字を書き込む
	fprintf(pFile, "%s", u8NormalBlockNumberText.data());                    //文字を書き込む(全角文字)
	fprintf(pFile, "%s", u8NormalBlockText.data());                          //文字を書き込む(全角文字)
	fprintf(pFile, "%s", "\n");                                              //改行を行う
	fprintf(pFile, "%s", "#=====================================\n");        //文字を書き込む
	fprintf(pFile, "%s", CManager::GetObjectSet()->GetStratBlockName(type)); //数字を書き込む
	fprintf(pFile, "%s", "\n");                                              //改行を行う
	fprintf(pFile, "%s", "		POS = ");                                    //「POS」の文字を書き込む
	fprintf(pFile, "%.1f ", m_fPosX);                                        //「位置」の文字を書き込む(少数点第１まで)
	fprintf(pFile, "%.1f ", m_fPosY);                                        //「位置」の文字を書き込む(少数点第１まで)
	fprintf(pFile, "%.1f ", m_fPosZ);                                        //「位置」の文字を書き込む(少数点第１まで)
	fprintf(pFile, "%s", "\n");                                              //改行を行う
	fprintf(pFile, "%s", CManager::GetObjectSet()->GetEndBlockName(type));   //文字を書き込む
	fprintf(pFile, "%s", "\n");                                              //改行を行う
	fclose(pFile);                                                           //ファイルを閉じる
}


//=================================================================================================================================
//地面用ブロックの処理の処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CFiledBlock::CFiledBlock(int nPriority) : CManagerBlock(nPriority)
{
	
}

//============================
//デストラクタ
//============================
CFiledBlock::~CFiledBlock()
{

}


//=================================================================================================================================
//上がる用の処理の処理
//=================================================================================================================================
 
//============================
//コンストラクタ
//============================
CGoUpBlock::CGoUpBlock(int nPriority) : CManagerBlock(nPriority)
{

}

//============================
//デストラクタ
//============================
CGoUpBlock::~CGoUpBlock()
{

}


//=================================================================================================================================
//道用の処理の処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CRoadBlock::CRoadBlock(int nPriority) : CManagerBlock(nPriority)
{

}
//============================
//デストラクタ
//============================
CRoadBlock::~CRoadBlock()
{

}

//=================================================================================================================================
//壁兼道用の処理の処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CWallRoadBlock::CWallRoadBlock(int nPriority) : CManagerBlock(nPriority)
{

}

//============================
//デストラクタ
//============================
CWallRoadBlock::~CWallRoadBlock()
{

}

//=================================================================================================================================
//小さいブロックの処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CSmallBlock::CSmallBlock(int nPriority) : CManagerBlock(nPriority)
{

}

//============================
//デストラクタ
//============================
CSmallBlock::~CSmallBlock()
{

}

//=================================================================================================================================
//上用の壁ブロックの処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CUpWallBlock::CUpWallBlock(int nPriority) : CManagerBlock(nPriority)
{
	
}
//============================
//デストラクタ
//============================
CUpWallBlock::~CUpWallBlock()
{

}

//=================================================================================================================================
//次のステージへ行く用objの処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CSpaceBattleShip000::CSpaceBattleShip000(int nPriority) : CManagerBlock(nPriority)
{
	SetRot(D3DXVECTOR3(INIT_ROT_X, INIT_ROT_Y, 0.0f)); //向きを調整
}

//============================
//デストラクタ
//============================
CSpaceBattleShip000::~CSpaceBattleShip000()
{

}

//=================================================================================================================================
//足場の処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CScaffold::CScaffold(int nPriority) : CManagerBlock(nPriority)
{
	
}

//============================
//デストラクタ
//============================
CScaffold::~CScaffold()
{

}

//=================================================================================================================================
//天井の処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CCeiling::CCeiling(int nPriority) : CManagerBlock(nPriority)
{

}

//============================
//デストラクタ
//============================
CCeiling::~CCeiling()
{

}


//=================================================================================================================================
//木の板群の処理
//=================================================================================================================================

//============================
//コンストラクタ
//============================
CWoodenBorad::CWoodenBorad(int nPriority) : CManagerBlock(nPriority)
{

}

//============================
//デストラクタ
//============================
CWoodenBorad::~CWoodenBorad()
{

}

//============================
//更新処理
//============================
void CWoodenBorad::Update()
{
	CObjectX::Update(); //更新処理
}