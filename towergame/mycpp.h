#ifndef MYCPP_H
#define MYCPP_H

//游戏的自定义
enum {
    Game_enemy_dead = 1,

    Game_enemy_Get_to_Base ,
};


//游戏属性
enum {
    Game_base_Blood_volume = 100 ,

    Game_base_Blood_loss_speed = 10,

    Game_init_money = 300 ,

    Game_enemy_move_speed = 1,

    Game_enemy_maxHp = 40 ,

};


//关卡
enum {
    First_Level = 1,

    Second_Level ,

    Three_Level ,
};

//通过关卡的分数
enum {
    First_Count = 100,

    Second_Count = 200,

    Three_Count  = 300,
};

//敌人的速度
enum {
    Three_Speed = 10,

    Second_Speed = 15 ,

    First_Speed = 20,
};

//防御塔等级
enum {
    First_tower_rand = 1,

    Second_tower_rand = 2,

    Three_tower_rand = 3,
};

//防御塔范围
enum {
    First_tower_range = 100,

    Second_tower_range = 120,

    Three_tower_range = 140,
};
#endif // MYCPP_H
