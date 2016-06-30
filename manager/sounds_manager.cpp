#include "sounds_manager.h"
#include <stdio.h>

/* ACF/ACBのマクロ定義ヘッダ */
#include "../sounds/game_sounds.h"
#include "../sounds/game_sound_acf.h"

/* 全体設定ファイルのパス */
#define ACF_FILE   "sounds/game_sound.acf"

/* サウンドデータファイルのパス */
#define AWB_FILE   "sounds/game_sounds.awb"
#define ACB_FILE    "sounds/game_sounds.acb"

/* 最大ボイス数を増やすための関連パラメータ */
#define MAX_VOICE           (24)
#define MAX_VIRTUAL_VOICE   (64)        /* ざっくり多め(通常ボイス＋HCA-MXボイス＋α) */
#define MAX_CRIFS_LOADER    (64)        /* ざっくり多め(通常ボイス＋HCA-MXボイス＋α) */


/*変数の実態化*/
CriAtomExPlayerHn SoundsManager::player;//プレイヤーハンドル
CriAtomExPlayerHn SoundsManager::se_player;//seプレイヤーハンドル
CriAtomExPlaybackId SoundsManager::player_id;//プレイバック
CriAtomExAcbHn SoundsManager::acb_hn;//ACBハンドル
CriAtomExAcbHn SoundsManager::se_acb_hn;//se_ACBハンドル
CriAtomExVoicePoolHn SoundsManager::voice_pool;//ボイスプールハンドル
CriAtomExStandardVoicePoolConfig SoundsManager::vpconfig;
CriAtomDbasId SoundsManager::dbas;// D-BASハンドル 
CriAtomExCueId SoundsManager::id;//キューリスト
SoundsManager* SoundsManager::instance = nullptr;

 SoundsManager*  SoundsManager::GetInstance() {

	 //インスタンスがなければメモリを確保
	 if (instance == nullptr)
	 {
		 instance = new SoundsManager();
	 }

	 return instance;
}


/*初期化*/
SoundsManager::SoundsManager()
{
	/* エラーコールバック関数の登録 */
	criErr_SetCallback(user_error_callback_func);

	/* メモリアロケータの登録 */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	

	/*ライブラリの初期化*/
	criAtomEx_Initialize_WASAPI(NULL, NULL, 0);

	/* ストリーミング用バッファの作成 */
	dbas = criAtomDbas_Create(NULL, NULL, 0);

	/* 全体設定ファイルの登録 */
	//criAtomEx_RegisterAcfFile(NULL, PATH ACF_FILE, NULL, 0);
	criAtomEx_RegisterAcfFile(NULL, ACF_FILE, NULL, 0);

	/* DSPバス設定の登録 */
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);

	/* ボイスプールの作成（ストリーム再生対応） */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
	vpconfig.player_config.streaming_flag = CRI_TRUE;
	voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, NULL, 0);
	/* MEMO: ストリーム再生無しなら、ボイスプールは構造体NULL指定で可 */

	acb_hn = criAtomExAcb_LoadAcbFile(NULL, ACB_FILE, NULL, AWB_FILE, NULL, 0);
//	se_acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, NULL, NULL, NULL, 0);
	/* プレーヤの作成 */
	player = criAtomExPlayer_Create(NULL, NULL, 0);
	se_player = criAtomExPlayer_Create(NULL, NULL, 0);

}



void SoundsManager::Load() {

	/* 入れ替えるサウンドデータの読み込み */
//	acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, NULL, NULL, NULL, 0);

	printf("acbファイルを読み替えします\n");
}


void SoundsManager::PlayBGM(CriAtomExCueId cue_id) {


	///* プレーヤにフェーダをアタッチ*/
	//criAtomExPlayer_AttachFader(player, NULL, NULL, 0);

	///* フェードイン／アウト時間の指定
	// 5秒でクロスフェードを行うよう指定。*/
	//criAtomExPlayer_SetFadeInTime(player, 5000);    // フェードイン時間の指定
	//criAtomExPlayer_SetFadeOutTime(player, 5000);   // フェードアウト時間の指定

	/* キューの指定 */
	criAtomExPlayer_SetCueId(player, acb_hn, cue_id);
	/* キューの再生開始 */

	/*プレーヤ再生*/
	criAtomExPlayer_Start(player);
	printf("bgm再生\n");
}


void SoundsManager::PlaySE(CriAtomExCueId id) {
	/* キューの指定 */
	criAtomExPlayer_SetCueId(se_player, acb_hn, id);
	/* キューの再生開始 */
	criAtomExPlayer_Start(se_player);
	printf("se再生\n");

}


void SoundsManager::StopBGM()
{

	/* プレーヤの停止 */
	criAtomExPlayer_Stop(player);
	printf("音楽停止\n");

}

void SoundsManager::StopSE() {
	/* プレーヤの停止 */
	criAtomExPlayer_Stop(se_player);
	printf("音楽停止\n");

	
}

SoundsManager::~SoundsManager()
{
	/* プレーヤハンドルの破棄 */
	criAtomExPlayer_Destroy(player);
	criAtomExPlayer_Destroy(se_player);

	/* ACBハンドルの解放 */
	criAtomExAcb_Release(acb_hn);

	/* ボイスプールの解放 */
	criAtomExVoicePool_Free(voice_pool);

	/* 全体設定ファイルの登録解除 */
	criAtomEx_UnregisterAcf();

	/* ライブラリの終了 */
	criAtomEx_Finalize_WASAPI();




}


