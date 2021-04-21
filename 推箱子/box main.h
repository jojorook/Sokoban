
#define KEY_UP     'w'//宏定义上下左右
#define KEY_LEFT   'a'
#define KEY_RIGHT  'd'
#define KEY_DOWN   's'
#define KEY_QUIT   'q'
#define LINE 9//行
#define COLUMN 12//列
#define RATLO 61//像素大小
#define START_X 100//左上角的从哪里打印位置的坐标
#define START_Y 150
#define SCREEN_HELGHT 768//高
#define SCREEN_WIDTH 960//宽
#define isValid(pos) next_pos.x>=0 && next_pos.y>=0//小人前进的if条件宏定义
typedef enum _PROPS _PROPS;//类型定义类似别名enum _PROPS -》 _PROPS
typedef enum _DIRECTION  _DIRECTION;//同上
typedef struct _POS  _POS ;
enum _PROPS{//道具 枚举
	WALL,//墙
	FLOOR,//地板
	BOX_DEX,//目的
	MAN,//人
	BOX,//箱子
	HIT,//命中箱子
	MAN_S,//假人
	ALL//一共多少个元素
};
enum _DIRECTION//游戏控制方向  枚举
{   
	UP,
	DOWN,
	LEFT,
	RIGHT
};
struct _POS{//定义个结构体
	int x;//小人在的二维数组的行
	int y;//小人列
};	