#ifndef _SOUNDS_MANAGER_H_
#define _SOUNDS_MANAGER_H_
#include "pc\cri_adx2le.h"
#include <vector>

class SoundsManager
{
public:
	static SoundsManager*  GetInstance();
	~SoundsManager();

	
	static void Load();
	static void PlayBGM(CriAtomExCueId cue_id);	
	static void PlaySE(CriAtomExCueId id);
	static void StopBGM();
	static void StopSE();

private:
	SoundsManager();
	static SoundsManager* instance;

	static CriAtomExPlayerHn player;//プレイヤーハンドル
	static CriAtomExPlayerHn se_player;//seプレイヤーハンドル
	static CriAtomExPlaybackId player_id;//プレイバック
	static CriAtomExAcbHn acb_hn;//ACBハンドル
	static CriAtomExAcbHn se_acb_hn;//SE ACBハンドル
	static CriAtomExVoicePoolHn voice_pool;//ボイスプールハンドル
	static 	CriAtomExStandardVoicePoolConfig vpconfig;
	static CriAtomDbasId dbas;// D-BASハンドル 
	static CriAtomExCueId id;//キューリスト

	/*エラーコールバック関数*/
	static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
	{
		const CriChar8 *errmsg;
		/* エラーコードからエラー文字列に変換してコンソール出力する */
		errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
		//printf("%s\n", &errmsg);
		return;
	}

	/* メモリ確保関数のユーザ実装 */
	static void *user_alloc_func(void *obj, CriUint32 size)
	{
		void *ptr;
		ptr = malloc(size);
		return ptr;
	}

	/* メモリ解放関数のユーザ実装 */
	static void user_free_func(void *obj, void *ptr)
	{
		free(ptr);
	}


};

/* Cue List (Cue ID) */
#define CRI_GAME_SOUNDS_BGM_TITLE   ( 0) /*   */
#define CRI_GAME_SOUNDS_BGM_GAME    ( 1) /*   */
#define CRI_GAME_SOUNDS_BGM_RESURT  ( 2) /*   */
#define CRI_GAME_SOUNDS_SE_BULLET   ( 3) /*   */
#define CRI_GAME_SOUNDS_SE_BUTTON   ( 4) /*   */

#endif // !_SOUNDS_MANAGER_H_
