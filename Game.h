#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <windows.h>
/***************************************************
 * 文件名：Game.h
 * 描  述：定义游戏的核心方法及相关结构
 * 创建人：andi
 * 日  期：2019-10-25
 * 版  本：1.0
 *
 **************************************************/
#define MARGIN_X 15  //左边距
enum GameStatus {
    GameMainMenu = 1, GameRunning = 2, GameFighting = 3, GameSplashScreen = 4, GameExit = 5
};
/* 门派 */
typedef struct _martial {
    int id;         //门派编号
    char name[21];  //门派名称
    char type[11];  //门派类型：正派、邪派、亦正亦邪
    COORD hqCoord;  //总部坐标（X-行，Y-列），与正常坐标轴相反
    int isOpen;     //是否开放
    char description[1000];//门派描述
}Martial;
//游戏道具类型枚举，对应 武器、防具、心法、消耗品、碎片
typedef enum _propType {
    Weapon, Armor, Book, Consumables, Fragment
} PropType;
/* 游戏道具 */
typedef struct _prop {
    int id;
    char name[50];
    int level;
    PropType type;
    int stock;          //当前道具的数量
    union {
        int attack;     //如果是武器，就对应攻击力
        int defense;    //如果是防具，就对应防御力
        int power;      //如果是血瓶等消耗品，对应增加的能量值
    };

    double price;
    char desc[200];     //游戏道具描述
}Prop;
/* 玩家背包 */
typedef struct _bag {
    int playerId;       //所属玩家编号
    int propCount;      //当前道具的总数
    int propMax;        //背包中最大道具数
    Prop props[8];      //背包中的道具数组，默认8个道具插槽(8可以设置成常量)
}Bag;
/* 玩家结构 */
typedef struct _player {
    int id;
    char name[50];  //玩家名称
    char pass[50];  //玩家登陆密码
    int life;       //玩家生命数，默认100条命，死亡一次减当前级别点生命值
    int level;      //玩家级别-侠客等级=LOG2(玩家经验)的取整+1（举例：经验是65，那么侠客等级=LOG2 65的取整+1=6+1=7）
    int exp;        //玩家经验值
    int hp;         //玩家当前血量
    int mp;         //玩家内力值-内力值为0，玩家死亡
    int mpMax;      //玩家当前级别内力上限-内力上限=30万＋15万*级别
    int gold;       //玩家金币数
    Martial martial;//所属门派
    Prop weapon;    //所装备的武器
    Prop armor;     //所装备的防具
    COORD currCoord;//玩家当前坐标（X-行，Y-列），与正常坐标轴相反
    Bag bag;
}Player;
/* 怪物 */
typedef struct _monster {
    int id;
    char name[50];  //怪物名称
    int level;      //怪物级别
    int hp;         //怪物生命值
    int att;        //怪物攻击力
    int deff;       //怪物防御力
    int minMoney;   //掉落金币最小值
    int maxMoney;   //掉落金币最大值
    int exp;        //杀死后玩家所得经验值
    int state;      //怪物状态，1-生存，0-死亡
    COORD mCoord;   //怪物坐在地图坐标（X-行，Y-列），与正常坐标轴相反
}Monster;
void InitializeGame();  //初始化游戏数据
void StartNewGame();    //开启新游戏
void EndGame();         //结束游戏

void ProcessMenu();
void ProcessSplash();
void ProcessGame();
void ProcessExit();
/* 游戏业务的入口 */
void Process(char key);

void ShowInfo();
void ShowPlayer();
void ShowMap();
void ShowMonster(); //显示怪物
void ShowFight(Player* player, Monster* monster);
void ShowSplash();
void ShowMenu();
void ShowGame();
void ShowExit();
void show();
void ShowHQ();//回总部
void ShowTrade();//购买装备
/* 返回交易是否成功 */
int Trade(Player* player, int propId);


#endif // GAME_H_INCLUDED
#pragma once
