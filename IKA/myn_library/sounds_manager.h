#ifndef _SOUNDS_MANAGER_H_
#define _SOUNDS_MANAGER_H_
#include "pc\cri_adx2le.h"
#include <vector>

class SoundsManager
{
public:
	SoundsManager();
	~SoundsManager();

	static CriAtomExPlayerHn player;//プレイヤーハンドル
	static CriAtomExPlaybackId player_id;//プレイバック
	static CriAtomExAcbHn acb_hn;//ACBハンドル
	static CriAtomExVoicePoolHn voice_pool;//ボイスプールハンドル
	static 	CriAtomExStandardVoicePoolConfig vpconfig;
	static char *file_name;//読み込みファイル
	static CriAtomDbasId dbas;// D-BASハンドル 
	static CriAtomExCueId id;//キューリスト

	static void Load(const char *file);
	static void PlayBGM();
	static void StopBGM();

private:
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


enum MyEnum
{

};
#endif // !_SOUNDS_MANAGER_H_
