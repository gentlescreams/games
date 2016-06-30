#include "sounds_manager.h"
#include <stdio.h>

/* ACF/ACB�̃}�N����`�w�b�_ */
#include "../sounds/game_sounds.h"
#include "../sounds/game_sound_acf.h"

/* �S�̐ݒ�t�@�C���̃p�X */
#define ACF_FILE   "sounds/game_sound.acf"

/* �T�E���h�f�[�^�t�@�C���̃p�X */
#define AWB_FILE   "sounds/game_sounds.awb"
#define ACB_FILE    "sounds/game_sounds.acb"

/* �ő�{�C�X���𑝂₷���߂̊֘A�p�����[�^ */
#define MAX_VOICE           (24)
#define MAX_VIRTUAL_VOICE   (64)        /* �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��) */
#define MAX_CRIFS_LOADER    (64)        /* �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��) */


/*�ϐ��̎��ԉ�*/
CriAtomExPlayerHn SoundsManager::player;//�v���C���[�n���h��
CriAtomExPlayerHn SoundsManager::se_player;//se�v���C���[�n���h��
CriAtomExPlaybackId SoundsManager::player_id;//�v���C�o�b�N
CriAtomExAcbHn SoundsManager::acb_hn;//ACB�n���h��
CriAtomExAcbHn SoundsManager::se_acb_hn;//se_ACB�n���h��
CriAtomExVoicePoolHn SoundsManager::voice_pool;//�{�C�X�v�[���n���h��
CriAtomExStandardVoicePoolConfig SoundsManager::vpconfig;
CriAtomDbasId SoundsManager::dbas;// D-BAS�n���h�� 
CriAtomExCueId SoundsManager::id;//�L���[���X�g
SoundsManager* SoundsManager::instance = nullptr;

 SoundsManager*  SoundsManager::GetInstance() {

	 //�C���X�^���X���Ȃ���΃��������m��
	 if (instance == nullptr)
	 {
		 instance = new SoundsManager();
	 }

	 return instance;
}


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

	acb_hn = criAtomExAcb_LoadAcbFile(NULL, ACB_FILE, NULL, AWB_FILE, NULL, 0);
//	se_acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, NULL, NULL, NULL, 0);
	/* �v���[���̍쐬 */
	player = criAtomExPlayer_Create(NULL, NULL, 0);
	se_player = criAtomExPlayer_Create(NULL, NULL, 0);

}



void SoundsManager::Load() {

	/* ����ւ���T�E���h�f�[�^�̓ǂݍ��� */
//	acb_hn = criAtomExAcb_LoadAcbFile(NULL, SE_ACB_FILE, NULL, NULL, NULL, 0);

	printf("acb�t�@�C����ǂݑւ����܂�\n");
}


void SoundsManager::PlayBGM(CriAtomExCueId cue_id) {


	///* �v���[���Ƀt�F�[�_���A�^�b�`*/
	//criAtomExPlayer_AttachFader(player, NULL, NULL, 0);

	///* �t�F�[�h�C���^�A�E�g���Ԃ̎w��
	// 5�b�ŃN���X�t�F�[�h���s���悤�w��B*/
	//criAtomExPlayer_SetFadeInTime(player, 5000);    // �t�F�[�h�C�����Ԃ̎w��
	//criAtomExPlayer_SetFadeOutTime(player, 5000);   // �t�F�[�h�A�E�g���Ԃ̎w��

	/* �L���[�̎w�� */
	criAtomExPlayer_SetCueId(player, acb_hn, cue_id);
	/* �L���[�̍Đ��J�n */

	/*�v���[���Đ�*/
	criAtomExPlayer_Start(player);
	printf("bgm�Đ�\n");
}


void SoundsManager::PlaySE(CriAtomExCueId id) {
	/* �L���[�̎w�� */
	criAtomExPlayer_SetCueId(se_player, acb_hn, id);
	/* �L���[�̍Đ��J�n */
	criAtomExPlayer_Start(se_player);
	printf("se�Đ�\n");

}


void SoundsManager::StopBGM()
{

	/* �v���[���̒�~ */
	criAtomExPlayer_Stop(player);
	printf("���y��~\n");

}

void SoundsManager::StopSE() {
	/* �v���[���̒�~ */
	criAtomExPlayer_Stop(se_player);
	printf("���y��~\n");

	
}

SoundsManager::~SoundsManager()
{
	/* �v���[���n���h���̔j�� */
	criAtomExPlayer_Destroy(player);
	criAtomExPlayer_Destroy(se_player);

	/* ACB�n���h���̉�� */
	criAtomExAcb_Release(acb_hn);

	/* �{�C�X�v�[���̉�� */
	criAtomExVoicePool_Free(voice_pool);

	/* �S�̐ݒ�t�@�C���̓o�^���� */
	criAtomEx_UnregisterAcf();

	/* ���C�u�����̏I�� */
	criAtomEx_Finalize_WASAPI();




}


