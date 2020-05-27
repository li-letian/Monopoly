#ifndef _COMMON_CONSTANT_H_
#define _COMMON_CONSTANT_H_

const int miku = 1;						//����δ��
const int nanxiaoniao = 2;				//��С��

//�������ߵ�ʱ��
const float character_walk_delay_time = 0.005f;						//֡���
const float character_one_step_time = 4*character_walk_delay_time;	//ÿ��һ������ʱ��

//�����߶������ĸ�����
const int walk_down = 1;
const int walk_left = 2;
const int walk_right = 3;
const int walk_up = 4;

//�������ߵĸ���
const int walk_steps = 11;
const int drive_steps = 23;

//�����֮��ľ���
const int tile_size = 64;

const int msg_hide_go = 1;
const int msg_make_go_apper = 2;
#endif
