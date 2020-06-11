//解决VS对scanf不安全函数报警问题
#define _CRT_SECURE_NO_WARNINGS

/***************************************************
 * 文件名：Game.c
 * 描  述：实现游戏的核心方法
 * 创建人：andi
 * 日  期：2019-10-25
 * 版  本：1.0
 *
 **************************************************/
#include <stdio.h>
//#include <unistd.h>
#include "Game.h"
#include "GameLib.h"

 /* 当前的游戏状态 */
enum GameStatus CurrGameStatus = GameSplashScreen;

char Maps[8][8][10] = {
    {"天山",   "楼兰",   "白驼山",  "野猪林",   "水晶洞",  "天蚕洞",  "黑风寨",   "冰火岛"},
    {"迷宫",   "凌霄城",  "轩辕岭", "华山",     "嵩山",    "紫禁城",  "快活林",   "神龙岛"},
    {"西域",   "葫芦谷",  "唐门",   "终南山",   "石窟",    "客栈",    "玉皇顶",   "灵蛇岛"},
    {"光明顶", "摩天崖",  "聚贤庄", "后山",     "武当山",  "开封府",  "二十四桥", "蓬莱仙境"},
    {"擂鼓山", "峨眉山",  "迷踪林", "五虎岭",   "天宁寺",  "积善堂",  "镇江府",   "桃花岛"},
    {"恶人谷", "大理",    "百花谷", "孔雀山庄", "五霸岗",  "万仞堂",  "千年古刹", "六合塔"},
    {"玩偶庄", "黑木崖",  "蝴蝶谷", "铁花堡",   "霹雳堂",  "关帝庙",  "麒麟庄",   "销魂宫"},
    {"石府",   "金三角",  "忏悔崖", "通吃岛",   "通天观",  "紫霞亭",  "天弃庵",   "侠客岛"}
};
/* 江湖门派 */
Martial martials[] = {
    {1, "少林派",   "正派", .hqCoord.X = 1, .hqCoord.Y = 4, 1, "中华武学的泰斗，明末，少林众多的人才中，以悟空和箭神二人排为一等。其中，悟空出家为僧，箭神乃俗家弟子。当时江湖人称少林双绝。少林寺中众僧在两大长老的带领下参加了江浙沿海抗击倭寇的战斗，在各路应募兵马中表现得最为骁勇。但正因抗倭之事，也使江湖中的众多门派产生了矛盾，其中首推少林和日月神教。悟空、箭神曾几度带领江湖同仁攻上光明顶，但由于日月神教和血河两派结为同盟，更何况邪派中高手如云，所以几次围剿未果而终，黑白两道都损失惨重"},
    {2, "武当派",   "正派", .hqCoord.X = 3, .hqCoord.Y = 4, 1, "武当在江湖上与少林齐名，有‘北崇少林’‘南尊武当’之说。 武当新一代的首领人物，是一位谦谦君子，一张轮廓分明的脸上总是带着爽朗的笑容，就连他的仇敌都不能不承认他是条少见的男子汉。凡人从十八岁崛起江湖，身经大小三十三战，至今从未败过一次。凡人一生中最不能忍受的两件事就是失败和错误。 "},
    {3, "丐帮",     "正派", .hqCoord.X = 2, .hqCoord.Y = 6, 1, "丐帮是中原武林中人数最为众多的一个门派，也是天下第一大帮派，以遍布天下乞丐的乞丐组成，分为污衣帮和净衣帮。丐帮中人大多都是社会地位比较低的人，但他们各个铮铮硬骨，品格高尚，很少出现卑劣之人。丐帮新一代众多弟子以天葵为首，除暴安良、行侠丈义、抑强扶弱，所作所为为天下人所津津乐道。"},
    {4, "全真教",   "正派", .hqCoord.X = 2, .hqCoord.Y = 3, 1, "全真属于道教的分支之一。现今全真教中最有权威的人是一个瘦瘦小小的人，长着一双冷冷淡淡好象永远不会有什么变化的眼睛，看起来仿佛是灰色的。但他又是一个非常讲究的人，他喜欢紫色，喜欢名马佳人华衣美酒，喜欢享受。对每一件事情他都非常的挑剔，做的每一件事都经过精密计划，绝不肯多浪费一分力气，也不会有一点疏忽。这就是全真海雅。"},
    {5, "五岳剑派", "正派", .hqCoord.X = 1, .hqCoord.Y = 3, 1, "泰山派，恒山派，衡山派，华山派，嵩山派结为同气枝连的的五岳剑派，在江湖上扬名立万。五派中人一向面和心不和，所以五派的式微不是由于外敌入侵，而纯粹是内部矛盾激化走向内耗的结果，内部的勾心斗角虽然常常以抗倭为借口出现，实则是为了掌握五岳生杀大权。"},
    {6, "四川唐门", "正派", .hqCoord.X = 2, .hqCoord.Y = 2, 1, "唐门在江湖上以暗器闻名。但自从唐门的唐老太太过世后唐家堡一度家道中落，加之唐甜为称霸武林挑起纷争，又使唐门陷入了再度的浩劫，几乎一蹶不振。在这种危难的时刻唐门出现了一群新生力量：唐纾、唐斩、唐缺、唐玉。他们整顿内务，肃清奸佞，打出了匡复武林正义的旗帜，并且在江湖上行侠仗义，挽回了唐门的声誉，使唐门成为了江湖上的名门正派。"},
    {7, "大理段氏", "正派", .hqCoord.X = 5, .hqCoord.Y = 1, 1, "大理段氏人丁众多，高手如云。其中有一位名扬江湖顶尖女侠——香雪儿。香雪儿面相灵秀，肤色白皙，但微显瘦弱，看上去弱不禁风却身怀绝世武功，已深得大理武功心得。"},
    {8, "天山派",   "正派", .hqCoord.X = 0, .hqCoord.Y = 0, 1, "天山派是名门正派，也是目前江湖中最为团结的一个门派。天山派也是江湖中女弟子最为众多的一个门派，且各个武功造诣不凡，相貌清秀。"},
    {9, "古墓派",   "正派", .hqCoord.X = 3, .hqCoord.Y = 3, 1, "古墓派这一代的传人名叫暄雯，是一女子，来历不明。暄雯生性娴静，长相俊美，举止飘逸，但做事情却不似师祖小龙女，倒颇有一点杨过的风格，武功修为深不可测，同样喜穿白衣。此派轻功卓越，剑法、拳法灵动妙绝，更是全真教的克星。古墓传人的处世原则是“事不关己，高高挂起”，过着与世无争的日子，但是如果有人冒犯了古墓传人，那他一定会死得很惨。"},
    {10, "名捕门",  "正派", .hqCoord.X = 1, .hqCoord.Y = 1, 1, "名捕门历属与官府，但其中也不乏在江湖上闯出名堂的武林高手。名捕门一等一的人才中有一位绰号叫‘惊天泣鬼’的，此人从不以真面目视人，总是在幕后策划一些事情。"},
    {11, "日月神教","邪派", .hqCoord.X = 6, .hqCoord.Y = 1, 1, "由于该教高手众多，并彼此互不相服，所以教务混杂。教中弟子多为邪恶之徒，专与名门正派作对，杀人良多，罪恶昭彰，故被江湖正派之人贬为魔教。"},
    {12, "权力帮",  "邪派", .hqCoord.X = 4, .hqCoord.Y = 0, 1, "邪派之一，目前派中最高首脑为一叫阿飞的年轻人。阿飞，一个表面上异常忧悒的人。没有与其交过手的武林高手，无法想象他那弱不禁风的身躯隐藏着那么大的潜力，更不能想象他是如何用支撑起权利帮的担子的。"},
    {13, "五毒教",  "邪派", .hqCoord.X = 2, .hqCoord.Y = 0, 1, "一个以使毒为专长的门派，派中人各个都是用毒高手。此派高手人称梦魇，其人使毒已入化境，令人难以琢磨，江湖同道对其莫不绕道而行。此人品行时好时坏，但坚韧卓绝，嗜武成痴。"},
    {14, "神龙教",  "邪派", .hqCoord.X = 2, .hqCoord.Y = 7, 1, "神龙教是江湖邪派，由于教址远离中原，所以不大干预中原武林的血腥杀戮。目前神龙教有两位高手一为刀神，此人武功高深莫测，性格孤僻冷傲，不喜与人接近。二为恶龙，武功高强但脾气暴躁，做事没有耐性。"},
    {15, "青龙会",  "邪派", .hqCoord.X = 5, .hqCoord.Y = 6, 1, "江湖上绵延数百年的一个神秘组织。青龙会下分十二堂，分别以月为代号。"},
    {16, "桃花岛",  "亦正亦邪", .hqCoord.X = 4, .hqCoord.Y = 7, 1, "自从东邪黄药师扬名立万于此后，他的传人就在这里绵延不绝，竟将桃花岛建成了门派的总舵。桃花岛黄药师的关门弟子程英一生未嫁，在岛上收了几个徒弟，桃花岛的武功因此得到延续和发扬。"},
    {17, "锦衣卫",  "亦正亦邪", .hqCoord.X = 1, .hqCoord.Y = 5, 1, "大内锦衣卫中人才济济，尤其是雷神，此人野心勃勃，自幼练得一身大力金刚功，号称刀枪不入，武功实是深不可测。而且为人机智，精通兵法，行兵时能将千军万马人使得如同数十万般威力十足。"},
    {18, "血河派",  "亦正亦邪", .hqCoord.X = 5, .hqCoord.Y = 0, 1, "自从血河派的掌门一代大侠方歌吟飘然而去后，血河派日益衰落。血河派活动的范围也越来越少，基本上只限与龙门石窟。而江湖上的九大门派已经把血河派视为邪魔歪道。并已传出英雄令，只要九大门派的门人遇上血河派的人，一律格杀无论。在江湖上已经没有什么血河派的人在行走。除了无恨！没有人知道他来自何方，人们只知道他来自血河派。没有人知道他的武功有多高，因为看见他的剑的人都已经......无恨是武林中的一个谜，现隐居在天山，相传是为了一名叫若寒的女子。相传血河弟子花无缺已深得无恨真传，在无恨隐居江湖期间代理血河的一切帮中事务。花无缺为人善良真诚，在江湖上人缘甚好，并将血河派内外事务打理得井井有条。"},
    {19, "通通吃",  "亦正亦邪", .hqCoord.X = 7, .hqCoord.Y = 3, 1, "江湖上一个神秘的门派，创始人，武功不祥。总舵设在通吃岛，教中首领人物——辉翰。此人手段严酷，以威服人。平常不轻易踏足中原武林，潜心修炼武功。"},
    {20, "玩偶山庄","亦正亦邪", .hqCoord.X = 0, .hqCoord.Y = 6, 1, "江湖上一个神秘的门派，创始人，武功不祥。总舵就在玩偶山庄，教中首领人物——阳光。玩偶山庄门人众多，但大都绝迹江湖，只有阳光经常独自浪迹江湖并闯出了名堂，所以武林中人才知有这么一个门派存在。"}
};
/* 游戏中的怪物 */
Monster monsters[] = {
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 0},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 1},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 2},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 3},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 4},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 5},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {1, "鬼子", 1, 100, 5, 5, 1, 3, 10, 1, .mCoord.X = 0, .mCoord.Y = 7},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 0},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 1},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 2},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 3},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 4},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 5},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {2, "汉奸", 2, 200, 8, 12, 1, 8, 11, 1, .mCoord.X = 0, .mCoord.Y = 7},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 0},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 1},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 2},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 3},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 4},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 5},
    {3, "浪人", 3, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 5, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 6, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 7, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 8, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 9, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 9, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 9, 300, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6},
    {3, "浪人", 9, 30000, 10, 10, 3, 8, 20, 1, .mCoord.X = 0, .mCoord.Y = 6}
};
/* 游戏道具 */
Prop props[] = {
    {1, "一字长蛇剑", 1, Weapon, 50, .attack = 5, 1000, "犹如巨蟒出击，攻击凌厉！"},
    {2, "二龙汲水珠", 2, Weapon, 10, .attack = 10, 2000, "高度的灵活性，玄妙无比！"},
    {3, "三叉海神戟", 3, Weapon, 10, .attack = 15, 3000, "重达十万八千斤，威力无穷！"},
    {4, "四方苦禅杖", 4, Weapon, 10, .attack = 20, 4000, "极度彰显了少林作为中原武林第一大派和佛门贵地的崇高地位。"},
    {5, "五虎攒羊锤", 5, Weapon, 10, .attack = 25, 5000, "唯有能与元素沟通的人可以唤醒它的真正力量。"},
    {6, "六合迎风枪", 6, Weapon, 10, .attack = 30, 6000, "当年兵器谱排名第二，第一是小李他妈的飞刀！"},
    {7, "七星斩将矛", 7, Weapon, 10, .attack = 40, 7000, "矛尖有如白蛇吐信，是令敌将闻风丧胆的象征！"},
    {8, "八卦金锁鞭", 8, Weapon, 10, .attack = 50, 8000, "打在身上，仿佛是幻影涰连，遮日蔽天！"},
    {9, "九转乾坤圈", 9, Weapon, 10, .attack = 90, 10000, "金色镯子，可翻江倒海，震荡乾坤！"},
    {100, "辟邪犀", 1, Armor, 10, .defense = 5, 1000, "一块能解天下百毒的透明佩玉。"},
    {101, "乌蚕裙", 2, Armor, 10, .defense = 15, 2000, "极其坚韧，刀枪不入，水火不侵！"},
    {102, "英姿带", 3, Armor, 10, .defense = 20, 3000, "穿后精气饱满，神采飞扬，姿态英勇威风！"},
    {103, "天罡指", 4, Armor, 10, .defense = 25, 4000, "飘忽不定，防东西至，防西东至！"},
    {104, "紫鲛衫", 5, Armor, 10, .defense = 30, 5000, "海蛟皮制成，装备后可在水下呼吸！"},
    {105, "碧麟披", 6, Armor, 10, .defense = 40, 6000, "上撰：上古南火朱雀之子,曾云字！"},
    {106, "金钟罩", 7, Armor, 10, .defense = 45, 7000, "装备后有如金铸之钟覆罩全身，刀剑难损！"},
    {107, "防弹衣", 8, Armor, 10, .defense = 60, 8000, "闯荡武林、居家必备！"},
    {108, "软猬甲", 9, Armor, 10, .defense = 70, 10000, "刀枪不入还可保暖，穿在身上，妙用无穷。桃花岛的镇岛之宝！"},
    {201, "回复奶瓶(大)", 1, Consumables, 50, .power = 500, 2000, "一次性回复500点内力值。"}
};

Player players[] = {
    {9526, "gm1", "gm1", 5, 1, 1, 10000, 30000, 1000, 10000, .currCoord.X = 0, .currCoord.Y = 0},
    {9527, "华安", "an.hua", 5, 8, 1, 1000000, 300000, 99999, 1000000, .currCoord.X = 2, .currCoord.Y = 2}
};
Player* currPlayer;
//玩家所在地图坐标（X-行，Y-列），与正常坐标轴相反
int X = 1, Y = 4;

void Show()
{
    //设定颜色
    //system("cls");
    switch (CurrGameStatus)
    {
    case GameMainMenu:
        ShowMenu(); break;
    case GameSplashScreen:
        ShowSplash(); break;
    }
}
void ShowMenu()
{
    printf("显示游戏主菜单\n");
}
void ShowSplash()
{
    printf("显示游戏欢迎界面\n");
}
void InitializeGame()
{

    //初始化玩家数据
    //初始化怪物数据
    players[0].martial = martials[1];
    players[0].weapon = props[0];
    players[0].armor = props[9];
    players[1].martial = martials[3];
    players[1].weapon = props[8];
    players[1].armor = props[14];

    Bag bag = { 9527, 0, 8 };
    currPlayer = &players[1];
    currPlayer->bag = bag;
}

void ShowMap()
{
    Clear(MARGIN_X, 3);
    //地图的起始位置固定为MARGIN_X, 3
    int i = 0, j = 0;
    char* martialIntro = NULL;//门派介绍
    for (; i < 8; i++)
    {
        SetPosition(MARGIN_X, 3 + i);
        printf("|  ");
        for (j = 0; j < 8; j++)
        {
            if (i == X && j == Y) {
                SetColor(13, 15);
            }
            else {
                SetColor(10, 0);
            }
            printf("%-9s", Maps[i][j]);
            SetColor(10, 0);
        }
        printf(" |\n");
    }
    SetPosition(MARGIN_X, 11);
    printf("-----------------------------------------------------------------------------\n");
    //显示门派信息-根据当前地图坐标，对应门派
    Martial* currMartial = NULL;
    for (i = 0; i < 20; i++)
    {
        if (X == martials[i].hqCoord.X && Y == martials[i].hqCoord.Y)//门派总部坐标与当前玩家坐标相等时
        {
            currMartial = &martials[i];
            martialIntro = martials[i].description;
            break;
        }
    }
    if (martialIntro == NULL)
    {
        SetPosition(MARGIN_X, 12);
        printf("\t\t\t\t<%s>", Maps[X][Y]);
        SetPosition(MARGIN_X, 13);
        printf("\t\t\t此地光秃秃的，有待建设！");
        return;
    }
    j = 0;
    SetPosition(MARGIN_X, 12);
    if (currMartial != NULL)
        printf("\t\t\t\t<%s>  总舵", currMartial->name);
    else
    {
        SetPosition(MARGIN_X, 18);
        return;
    }
    int length = strlen(martialIntro);
    if (length > 500) length = 500;
    for (i = 0; i < length; i++)
    {
        if (i % 72 == 0)
        {
            SetPosition(MARGIN_X + 2, 13 + i / 72);
        }
        printf("%c", *(martialIntro + i));

    }

}
void ShowPlayer()
{
    //printf("名称\t级别\t门派\t武器\t防具\n");
    //printf("%s\t%d\t%s\t%s\t%s\n", players[0].name, players[0].level, players[0].martial.name, players[0].weapon.name, players[0].armor.name);
    ClearMessage();
    //将光标定位到信息显示区的开始
    SetPosition(MARGIN_X, 12);
    int SEP = 10;
    //printf("信息显示区");
    SetPosition(MARGIN_X + SEP, 12);
    //Player test = currPlayer;
    printf("您的个人资料如下：");
    SetPosition(MARGIN_X + SEP, 13);
    printf("编号：%d\t姓名：%s\t级别：%d\t\t经验值：%d", currPlayer->id, currPlayer->name, currPlayer->level, currPlayer->exp);
    SetPosition(MARGIN_X + SEP, 14);
    printf("门派：%s\tH  P：%d\t内力：%d\t金币：%d", currPlayer->martial.name, currPlayer->hp, currPlayer->mp, currPlayer->gold);
    SetPosition(MARGIN_X + SEP, 15);
    printf("武器：%s(%d级/攻击%d)\t", currPlayer->weapon.name, currPlayer->weapon.level, currPlayer->weapon.attack);
    printf("防具：%s(%d级/防御%d)\t", currPlayer->armor.name, currPlayer->armor.level, currPlayer->armor.defense);
    SetPosition(MARGIN_X + SEP, 16);
    printf("背包信息：");
    SetPosition(MARGIN_X + SEP, 17);
    if (currPlayer->bag.propCount == 0)
    {
        printf("当前背包空荡荡的，行走江湖要小心哦0^0");
        return;
    }
    int i;
    for (i = 0; i < currPlayer->bag.propCount; i++)
    {
        if (i != 0 && i % 4 == 0)
        {
            SetPosition(MARGIN_X + SEP, 17 + i / 4);
        }
        printf("%-12s(%-2d)", currPlayer->bag.props[i].name, currPlayer->bag.props[i].stock);
    }

}
void ShowMonster()
{
    int SEP = 10;
    int i;
    //对应9级怪物的级别别称
    char* levelNames[9] = { "乳臭未干", "初出茅庐", "粗通皮毛", "青年才俊", "略有小成", "心领神会", "出类拔萃", "所向无敌", "天人合一" };
    ClearMessage();
    //将光标定位到信息显示区的开始
    SetPosition(MARGIN_X, 12);
    printf("当前地图的怪物：");
    SetPosition(MARGIN_X, 14);
    //遍历怪物数组，找到所有跟玩家坐标相同的怪物
    int monsterCount = sizeof(monsters) / sizeof(Monster);
    int monsterIndex[9];//最多9个怪物
    int currCount = 0;//当前地图的怪物总数
    for (i = 0; i < monsterCount; i++)
    {
        if (X == monsters[i].mCoord.X && Y == monsters[i].mCoord.Y && monsters[i].state != 0)
        {
            //显示怪物
            printf("%d.%s(%s)\t\t", currCount + 1, monsters[i].name, levelNames[monsters[i].level - 1]);
            monsterIndex[currCount] = i;
            currCount++;
            if (currCount == 9) break;
            if (currCount % 3 == 0)
            {
                SetPosition(MARGIN_X, 14 + currCount / 3);
            }
        }
    }
    if (currCount == 0)
    {
        SetPosition(MARGIN_X + SEP, 14);
        printf("真是鸡不生蛋鸟不拉屎的地方，这里没有其他人，到下个地图去吧。");
        return;
    }

    int choice;
    do {
        SetPosition(MARGIN_X, 18);
        printf("请选择要攻击的对象(按0返回):");
        scanf("%d", &choice);
        if (choice < 0 || choice > currCount) {//用户输入错误时清空本行
            SetPosition(MARGIN_X, 18);
            printf("                                          ");
        }
    } while (choice < 0 || choice > currCount);
    if (choice == 0)
        return;
    SetPosition(MARGIN_X, 18);
    ShowFight(NULL, &monsters[monsterIndex[choice - 1]]); //调用攻击函数，显示战斗结果

}
void ShowFight(Player* player, Monster* monster)
{
    SetPosition(MARGIN_X, 18);
    printf("                                          ");
    SetPosition(MARGIN_X, 18);
    int count = 0;
    do
    {
        //玩家每次攻击需要耗费10*攻击力点内力值
        monster->hp -= currPlayer->weapon.attack;
        currPlayer->hp -= monster->att;

        currPlayer->mp -= 10 * currPlayer->weapon.attack;
        if (currPlayer->mp <= 0)
        {
            SetPosition(MARGIN_X, 18);
            printf("                                                           ");
            SetPosition(MARGIN_X, 18);
            printf("当前内力已透支，还是逃命要紧！");
            return;
        }
        SetPosition(MARGIN_X, 18);
        printf("                                          ");
        SetPosition(MARGIN_X, 18);
        printf("战斗第%d轮：%sHP-%d\t%sHP-%d", count + 1, currPlayer->name, currPlayer->hp, monster->name, monster->hp);
        count++;
        Sleep(1000 * 50);//50毫秒
    } while (currPlayer->hp > 0 && monster->hp > 0 && currPlayer->mp > 0);
    SetPosition(MARGIN_X, 18);
    printf("                                          ");
    SetPosition(MARGIN_X, 18);
    if (currPlayer->hp <= 0)
    {
        printf("江湖快讯：大侠《%s》在与《%s》的战斗中壮烈牺牲！(按任意键继续)", currPlayer->name, monster->name);
        return;
    }
    currPlayer->exp += monster->exp;
    currPlayer->gold += monster->maxMoney;
    monster->state = 0;
    printf("经过艰苦的战斗，%s被您杀死，获得%d经验，%d金币！", monster->name, monster->exp, monster->maxMoney);
    system("pause");
    ShowMonster();
}
void ShowHQ()
{
    X = currPlayer->martial.hqCoord.X;
    Y = currPlayer->martial.hqCoord.Y;
    ShowMap();
}
void ShowTrade()
{
    ClearMessage();
    //在信息区打印商店的商品
    int propCount = sizeof(props) / sizeof(Prop) >= 15 ? 15 : sizeof(props) / sizeof(Prop);
    int i;
    SetPosition(MARGIN_X, 12);
    printf("欢迎进入《%s》道具店：", Maps[X][Y]);
    SetPosition(MARGIN_X + 4, 13);
    for (i = 0; i < propCount; i++)
    {
        if (i % 3 == 0)
        {
            SetPosition(MARGIN_X + 4, 13 + i / 3);
        }
        printf("%-3d.%-10s(%-2d)%-4c", props[i].id, props[i].name, props[i].stock, ' ');
    }
    //用户选择进行交易
    SetPosition(MARGIN_X, 18);
    printf("请输入购买的道具编号：(按0退出)");
    int tradeId;
    scanf("%d", &tradeId);
    if (tradeId == 0)
    {
        ShowMap();
        return;
    }
    //根据判断，扣除库存及玩家金钱
    //更新玩家背包
    SetPosition(MARGIN_X, 18);
    Trade(currPlayer, tradeId);
    ShowTrade();
}
void StartNewGame() {}    //开启新游戏
void EndGame() {}        //结束游戏

void Process(char key)
{
    switch (key)
    {
    case '1'://1、自我欣赏
        ShowPlayer();
        break;
    case '2'://2、探查(打怪)
        ShowMonster();
        break;
    case '3'://3、回总部
        ShowHQ();
        break;
    case '4'://4、购买装备
        ShowTrade();
        break;
    case '5'://5、举目四望(待完成)
        break;
    case '6'://6、到此一游(待完成)
        break;
    }
}
int Trade(Player* player, int propId)
{
    int i;
    //需要判断：商品的库存，玩家余额够不够，玩家背包空间够不够
    Prop* tradeProp = NULL;//要购买的商品指针
    int propCount = sizeof(props) / sizeof(Prop);
    for (i = 0; i < propCount; i++)
    {
        if (propId == props[i].id) {
            tradeProp = &props[i];//tradeProp = props + i;
            break;
        }
    }

    if (i == propCount)
    {
        printf("商品编号输入错误，请重新输入！");
        system("pause");
        return 0;
    }
    if (tradeProp->stock <= 0)
    {
        printf("地主家都没有余粮！商店都被买空啦！");
        system("pause");
        return 0;
    }
    if (player->gold < tradeProp->price)
    {
        printf("钱包都是瘪的，这里可是看钱的社会！！");
        system("pause");
        return 0;
    }
    if (player->bag.propCount >= player->bag.propMax && player->bag.propCount != 0)
    {
        printf("背包已满，交易失败！");
        system("pause");
        return 0;
    }
    //满足交易条件，执行交易的业务操作
    //1、商品库存-1
    tradeProp->stock--;
    //2、玩家金币-商品单价
    player->gold -= tradeProp->price;
    //*3、玩家背包道具增加
    //判断玩家背包中是否已有该商品

    //如果有该商品，背包中的该商品总数+1
    for (i = 0; i < player->bag.propCount; i++)
    {
        //如果要购买的商品id 跟 背包中的某个商品id相同
        if (propId == player->bag.props[i].id)
        {
            player->bag.props[i].stock++;
            break;
        }
    }
    if (i == player->bag.propCount)//如果没有该商品，该商品添加到背包中即可
    {
        //向背包中创建一个商品-复制一份要交易的商品信息到背包中
        int newIndex = player->bag.propCount;
        player->bag.props[newIndex].id = tradeProp->id;
        player->bag.props[newIndex].price = tradeProp->price;
        player->bag.props[newIndex].stock = 1;
        strcpy(player->bag.props[newIndex].name, tradeProp->name);
        strcpy(player->bag.props[newIndex].desc, tradeProp->desc);
        player->bag.propCount++;
    }
    return 1;
}
void ProcessMenu() {}
void ProcessSplash() {}
void ProcessGame() {}
void ProcessExit() {}

void ShowGame() {}
void ShowExit() {}
