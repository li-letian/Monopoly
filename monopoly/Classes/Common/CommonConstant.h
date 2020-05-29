#ifndef _COMMON_CONSTANT_H_
#define _COMMON_CONSTANT_H_

constexpr int miku = 1;		   //初音未来
constexpr int nanxiaoniao = 2; //南小鸟

//人物行走的时间
constexpr float character_walk_delay_time = 0.05f;						 //帧间隔
constexpr float character_one_step_time = 4 * character_walk_delay_time; //每走一格所花时间

//人行走动画的四个方向
constexpr int walk_down = 1;
constexpr int walk_left = 2;
constexpr int walk_right = 3;
constexpr int walk_up = 4;

//人物行走的格数
constexpr int walk_steps = 11;
constexpr int drive_steps = 23;

//格与格之间的距离
constexpr int tile_size = 64;

constexpr int msg_hide_go = 1;
constexpr int msg_make_go_apper = 2;
#endif
