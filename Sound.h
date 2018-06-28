#ifndef _SOUND_H_
#define _SOUND_H_


static enum {
	BGM_MAIN = 0,	//���C��BGM
	BGM_TITLE,	//�^�C�g��BGM

	SE_COUNT,	//�X�^�[�g�J�E���g
	SE_LOCK,	//���b�N������
	SE_PINTO,	//�s���g����������
	SE_JUSTPINTO,	//�W���X�g�s���g�œG��|������
	SE_EXT,		//����
	SE_RETURN,	//��͕��A
	SE_LOSS,	//��͏���
	SE_DAMAGE,	//�_���[�W
	SE_MULCH_FIRE,	//�}���`�t�H�[�J�X�g�p��
	SE_MULCH_STOCK,	//�}���`�t�H�[�J�X�����܂�����
};


void Sound_Load();
void Sound_Release();


#endif // !_SOUND_H_