#ifndef _COMMON_CONSTANT_H_
#define _COMMON_CONSTANT_H_

constexpr int miku = 1;		   //����δ��
constexpr int nanxiaoniao = 2; //��С��

//�������ߵ�ʱ��
constexpr float character_walk_delay_time = 0.05f;						 //֡���
constexpr float character_one_step_time = 4 * character_walk_delay_time; //ÿ��һ������ʱ��

//�����߶������ĸ�����
constexpr int walk_down = 1;
constexpr int walk_left = 2;
constexpr int walk_right = 3;
constexpr int walk_up = 4;

//�������ߵĸ���
constexpr int walk_steps = 11;
constexpr int drive_steps = 23;

//�����֮��ľ���
constexpr int tile_size = 64;

constexpr int msg_hide_go = 1;
constexpr int msg_make_go_apper = 2;
#endif
