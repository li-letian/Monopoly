#ifndef _COMMON_CONSTANT_H_
#define _COMMON_CONSTANT_H_

constexpr int miku = 1;		   //初音未来
constexpr int nanxiaoniao = 2; //南小鸟

//各种类型位置的代号
constexpr int land_chance = 1;
constexpr int land_life = 2;
constexpr int land_hotel = 3;
constexpr int land_business = 4;
constexpr int land_park = 5;
constexpr int land_resort = 6;
constexpr int land_mall = 7;
constexpr int land_institute = 8;
constexpr int land_insurance = 9;
constexpr int land_oil = 10;
constexpr int land_technology = 11;
constexpr int land_aviation = 12;
constexpr int land_hospital = 13;
constexpr int land_jail = 14;
constexpr int land_bank = 15;
constexpr int land_lottery = 16;

//人物行走的时间
constexpr float character_walk_delay_time = 0.05f;						 //帧间隔
constexpr float character_one_step_time = 4 * character_walk_delay_time; //每走一格所花时间

//人行走动画的四个方向
constexpr int walk_down = 1;
constexpr int walk_left = 2;
constexpr int walk_right = 3;
constexpr int walk_up = 4;

//人物行走的格数
constexpr int walk_steps = 3;
constexpr int drive_steps = 23;

constexpr int msg_hide_go = 1;
constexpr int msg_make_go_apper = 2;

constexpr float grid_distance = 16.0f;

//旅店地产的售价和过路费
const int hotel_sell_value[5] = { 500,1000,2000,4000,0 };
const int hotel_rent_value[5] = { 100,400,1200,3000,7000 };

//股市常数
const int buy_number_min = 10;
//默认停止次数
constexpr int default_stop_times = 3;

//人物状态
constexpr int normal = 0;
constexpr int in_jail = 1;
constexpr int in_hospital = 2;
constexpr int on_holiday = 3;

//股市状态
constexpr int normal_market = 0;
constexpr int up_market = 1;
constexpr int down_market = 3;
constexpr int market_duration_time = 5;

//税率 = 1/tax_rate
constexpr int tax_rate = 20;

//因为地产奖励的奖金
constexpr int reward_estate_money = 20000;
constexpr int help_estate_money = 10000;

#endif
