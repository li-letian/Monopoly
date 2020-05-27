#ifndef _COMMON_CONSTANT_H_
#define _COMMON_CONSTANT_H_

const int miku = 1;						//初音未来
const int nanxiaoniao = 2;				//南小鸟

//人物行走的时间
const float character_walk_delay_time = 0.005f;						//帧间隔
const float character_one_step_time = 4*character_walk_delay_time;	//每走一格所花时间

//人行走动画的四个方向
const int walk_down = 1;
const int walk_left = 2;
const int walk_right = 3;
const int walk_up = 4;

//人物行走的格数
const int walk_steps = 11;
const int drive_steps = 23;

//格与格之间的距离
const int tile_size = 64;

const int msg_hide_go = 1;
const int msg_make_go_apper = 2;
#endif
