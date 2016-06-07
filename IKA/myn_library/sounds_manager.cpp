#include "sounds_manager.h"

/* ACF/ACB�̃}�N����`�w�b�_ */
#include "../sounds/CueSheet_0.h"
#include "../sounds/ika_acf.h"
#include "../sounds/game_sound.h"

/* �S�̐ݒ�t�@�C���̃p�X */
#define ACF_FILE   "sounds/ika.acf"

/* �T�E���h�f�[�^�t�@�C���̃p�X */
#define SE_ACB_FILE   "sounds/se_game.acb"
#define AWB_FILE   "sounds/game_sound.awb"
#define ACB_FILE    "sounds/game_sound.acb"

/* �ő�{�C�X���𑝂₷���߂̊֘A�p�����[�^ */
#define MAX_VOICE           (24)
#define MAX_VIRTUAL_VOICE   (64)        /* �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��) */
#define MAX_CRIFS_LOADER    (64)        /* �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��) */


/*�ϐ��̎��ԉ�*/
CriAtomExPlayerHn SoundsManager::player;//�v���C���[�n���h��
CriAtomExPlaybackId SoundsManager::player_id;//�v���C�o�b�N
CriAtomExAcbHn SoundsManager::acb_hn;//ACB�n���h��
CriAtomExVoicePoolHn SoundsManager::voice_pool;//�{�C�X�v�[���n���h��
CriAtomExStandardVoicePoolConfig SoundsManager::vpconfig;
char SoundsManager::*file_name;//�ǂݍ��݃t�@�C��
CriAtomDbasId SoundsManager::dbas;// D-BAS�n���h�� 
CriAtomExCueId SoundsManager::id;//�L���[���X�g



/*������*/
SoundsManager::SoundsManager()
{
	/* �G���[�R�[���o�b�N�֐��̓o�^ */
	criErr_SetCallback(user_error_callback_func);

	/* �������A���P�[�^�̓o�^ */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	

	/*���C�u�����̏�����*/
	criAtomEx_Initialize_WASAPI(NULL, NULL, 0);

	/* �X�g���[�~���O�p�o�b�t�@�̍쐬 */
	dbas = criAtomDbas_Create(NULL, NULL, 0);

	/* �S�̐ݒ�t�@�C���̓o�^ */
	//criAtomEx_RegisterAcfFile(NULL, PATH ACF_FILE, NULL, 0);
	criAtomEx_RegisterAcfFile(NULL, ACF_FILE, NULL, 0);

	/* DSP�o�X�ݒ�̓o�^ */
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);


	/* �{�C�X�v�[���̍쐬�i�X�g���[���Đ��Ή��j */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
	vpconfig.player_config.streaming_flag = CRI_TRUE;
	voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, NULL, 0);
	/* MEMO: �X�g���[���Đ������Ȃ�A�{�C�X�v�[���͍\����NULL�w��ŉ� */



	/* �T�E���h�f�[�^�̓ǂݍ��� */
	//CriFsBinderHn awb_binder;
//	acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, AWB_FILE, NULL, NULL, 0);
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, ACB_FILE, NULL, AWB_FILE, NULL, 0);

	/* �v���[���̍쐬 */
	player = criAtomExPlayer_Create(NULL, NULL, 0);



	int a = 0;
	a++;
}



void SoundsManager::Load(const char *file) {

	/* ����ւ���T�E���h�f�[�^�̓ǂݍ��� */
	acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, NULL, NULL, NULL, 0);

	printf("yomikomi\n");
}


void SoundsManager::PlayBGM() {


	id = 1;

	/* �L���[�̎w�� */
	criAtomExPlayer_SetCueId(player, acb_hn, id);
	/* �L���[�̍Đ��J�n */


	criAtomExPlayer_Start(player);
	printf("saisei");
}



void SoundsManager::StopBGM() 
{

	/* �v���[���̒�~ */
	criAtomExPlayer_Stop(player);


}

SoundsManager::~SoundsManager()
{
	/* �v���[���n���h���̔j�� */
	criAtomExPlayer_Destroy(player);

	/* ACB�n���h���̉�� */
	criAtomExAcb_Release(acb_hn);

	/* �{�C�X�v�[���̉�� */
	criAtomExVoicePool_Free(voice_pool);

	/* �S�̐ݒ�t�@�C���̓o�^���� */
	criAtomEx_UnregisterAcf();

	/* ���C�u�����̏I�� */
	criAtomEx_Finalize_WASAPI();




}


