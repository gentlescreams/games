#include "sounds_manager.h"

/* ACF/ACBのマクロ定義ヘッダ */
#include "../sounds/CueSheet_0.h"
#include "../sounds/ika_acf.h"
#include "../sounds/game_sound.h"

/* 全体設定ファイルのパス */
#define ACF_FILE   "sounds/ika.acf"

/* サウンドデータファイルのパス */
#define SE_ACB_FILE   "sounds/se_game.acb"
#define AWB_FILE   "sounds/game_sound.awb"
#define ACB_FILE    "sounds/game_sound.acb"

/* 最大ボイス数を増やすための関連パラメータ */
#define MAX_VOICE           (24)
#define MAX_VIRTUAL_VOICE   (64)        /* ざっくり多め(通常ボイス＋HCA-MXボイス＋α) */
#define MAX_CRIFS_LOADER    (64)        /* ざっくり多め(通常ボイス＋HCA-MXボイス＋α) */


/*変数の実態化*/
CriAtomExPlayerHn SoundsManager::player;//プレイヤーハンドル
CriAtomExPlaybackId SoundsManager::player_id;//プレイバック
CriAtomExAcbHn SoundsManager::acb_hn;//ACBハンドル
CriAtomExVoicePoolHn SoundsManager::voice_pool;//ボイスプールハンドル
CriAtomExStandardVoicePoolConfig SoundsManager::vpconfig;
char SoundsManager::*file_name;//読み込みファイル
CriAtomDbasId SoundsManager::dbas;// D-BASハンドル 
CriAtomExCueId SoundsManager::id;//キューリスト



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



	/* サウンドデータの読み込み */
	//CriFsBinderHn awb_binder;
//	acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, AWB_FILE, NULL, NULL, 0);
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, ACB_FILE, NULL, AWB_FILE, NULL, 0);

	/* プレーヤの作成 */
	player = criAtomExPlayer_Create(NULL, NULL, 0);



	int a = 0;
	a++;
}



void SoundsManager::Load(const char *file) {

	/* 入れ替えるサウンドデータの読み込み */
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, NULL, NULL, NULL, 0);

	printf("yomikomi\n");
}


void SoundsManager::PlayBGM() {


	id = 1;

	/* キューの指定 */
	criAtomExPlayer_SetCueId(player, acb_hn, id);
	/* キューの再生開始 */


	criAtomExPlayer_Start(player);
	printf("saisei");
}



void SoundsManager::StopBGM() 
{

	/* プレーヤの停止 */
	criAtomExPlayer_Stop(player);


}

SoundsManager::~SoundsManager()
{
	/* プレーヤハンドルの破棄 */
	criAtomExPlayer_Destroy(player);

	/* ACBハンドルの解放 */
	criAtomExAcb_Release(acb_hn);

	/* ボイスプールの解放 */
	criAtomExVoicePool_Free(voice_pool);

	/* 全体設定ファイルの登録解除 */
	criAtomEx_UnregisterAcf();

	/* ライブラリの終了 */
	criAtomEx_Finalize_WASAPI();




}


