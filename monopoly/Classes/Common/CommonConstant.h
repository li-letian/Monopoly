#ifndef _COMMON_CONSTANT_H_
#define _COMMON_CONSTANT_H_

constexpr int miku = 1;		   //初音未来
constexpr int nanxiaoniao = 2; //南小鸟

constexpr int initial_money = 150000;
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

//人物的朝向
constexpr int forward_dir = 1;
constexpr int backward_dir = -1;

//人物行走的格数
constexpr int total_position = 452;
constexpr int start_position = 0;

constexpr int turtle_steps = 1;
constexpr int init_turtle_times = 3;
constexpr int walk_steps = 10;
constexpr int speed_steps = 2 * walk_steps;
constexpr int flying_steps = 3 * walk_steps;

constexpr int msg_start_go = 1;
constexpr int msg_make_go_apper = 2;
constexpr int msg_hide_go_only = 3;

constexpr float grid_distance = 16.0f;

//旅店地产的售价和过路费
constexpr int hotel_land_value = 300;
constexpr int hotel_sell_value[5] = { 500,1000,2000,4000,0 };
constexpr int hotel_rent_value[5] = { 100,400,1200,3000,7000 };

constexpr int business_land_value = 2000;
constexpr int business_rent_value = 300;

constexpr int insurance_value = 2000;
constexpr int aviation_value = 800;
constexpr int oil_value = 500;

constexpr int loan_value = 150000;
//股市常数
constexpr int buy_number_min = 10;
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
//房价、租价上涨或下降率
constexpr float land_price_rate = 0.3f;

//政府奖励或补助的资金
constexpr int reward_estate_money = 20000;
constexpr int help_estate_money = 10000;
constexpr int reward_stock_money = 20000;

//记录神灵附身状态
constexpr int no_god = 0;
constexpr int unluck = 1;
constexpr int poor = 2;
constexpr int luck = 3;
constexpr int rich = 4;
constexpr int angel = 5;
constexpr int devil = 6;
constexpr int earth = 7;	//土地公
constexpr int mine_position = 8;//地雷

constexpr int earth_duration_time = 3;
constexpr int weak_god_duration_time = 5;

//交通罚款
constexpr int traffic_fine = 5000;

constexpr float dice_stay_time = 0.5f;

constexpr int AI_save_money = 0;
constexpr int AI_withdraw_money = 1;

constexpr int AI_yes = 0;
constexpr int AI_no = 1;
#endif
