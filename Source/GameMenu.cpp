
#include "GameMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "StartMenu.h"


MenuElement_t MenuElement[3] = {
	{ 100, 100, "���s" }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��100���Ay��100���Aname��"�Q�[���X�^�[�g"��
{ 100, 200, "��蒼��" },
{ 100, 300, "�Q�[���I��" },
};


//�����ŕϐ���錾�iC++���g��Ȃ��̂ŃO���[�o���ϐ��j


int Template_Init() {
	//�����ŏ�����������
	return 0;
}

int Template_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	return 0;
}

int Template_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	return 0;
}

int Template_End() {
	//�����ŏI������
	return 0;
}