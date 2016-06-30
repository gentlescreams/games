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

	static CriAtomExPlayerHn player;//�v���C���[�n���h��
	static CriAtomExPlayerHn se_player;//se�v���C���[�n���h��
	static CriAtomExPlaybackId player_id;//�v���C�o�b�N
	static CriAtomExAcbHn acb_hn;//ACB�n���h��
	static CriAtomExAcbHn se_acb_hn;//SE ACB�n���h��
	static CriAtomExVoicePoolHn voice_pool;//�{�C�X�v�[���n���h��
	static 	CriAtomExStandardVoicePoolConfig vpconfig;
	static CriAtomDbasId dbas;// D-BAS�n���h�� 
	static CriAtomExCueId id;//�L���[���X�g

	/*�G���[�R�[���o�b�N�֐�*/
	static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
	{
		const CriChar8 *errmsg;
		/* �G���[�R�[�h����G���[������ɕϊ����ăR���\�[���o�͂��� */
		errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
		//printf("%s\n", &errmsg);
		return;
	}

	/* �������m�ۊ֐��̃��[�U���� */
	static void *user_alloc_func(void *obj, CriUint32 size)
	{
		void *ptr;
		ptr = malloc(size);
		return ptr;
	}

	/* ����������֐��̃��[�U���� */
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
