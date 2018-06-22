#ifndef _SOUND_H_
#define _SOUND_H_


enum {
	BGM_MAIN,	//���C��BGM
	BGM_TITLE,	//�^�C�g��BGM

	SE_PINTO,	//�s���g����������
	SE_JUSTPINTO,	//�W���X�g�s���g�̎�
	SE_EXT,		//����
	SE_RETURN,	//��͕��A
	SE_LOSS,	//��͏���
	SE_DAMAGE,	//�_���[�W
	SE_MULCH_FIRE,	//�}���`�t�H�[�J�X�g�p��
	SE_MULCH_STOCK,	//�}���`�t�H�[�J�X�����܂�����
	SE_LOCK //LOCK
};


void Sound_Load();
void Sound_Release();


#endif // !_SOUND_H_