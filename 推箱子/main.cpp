#include<iostream>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h> 
#include "box main.h"//相同目录下双引号
using namespace std;
IMAGE image[ALL];//定义全局变量,6中道具定义6种
struct _POS man;//小人的坐标
//游戏结束场景,通关后显示
//bg背景图变量的指针
void gameover(IMAGE *bg){
	putimage(0,0,bg);
	settextcolor(WHITE);
	RECT ret={0,0,SCREEN_WIDTH,SCREEN_HELGHT};
	settextstyle(20,0,_T("宋体"));//大小 宽度自适应 字体
	drawtext(_T("恭喜您~\n你成为一个出了名的推箱子大傻逼!"),&ret,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//水平居中,垂直居中,文字显示在一行(帮助文档里)
}
int map[LINE][COLUMN] = {//游戏地图
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
	{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
	{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0 },
	{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
//判断游戏结束,如果不存在箱子目的地就代表结束
//输入无, trun=继续  false=结束
bool isGameover(){
	for(int i=0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j]==BOX_DEX) return false;
		}
	}
	return true;
}
//改变游戏地图视图中对应道具并重新展示
//输入： line 道具在地图数组的行下标，column 道具在地图数组的列下标
//prop 道具的类型
//结构体指针 结构体传值 pos->x;
void changemap(_POS *pos, _PROPS prop){
	map[pos->x][pos->y]=prop;
	putimage(START_X + pos->y *RATLO,START_Y + pos->x * RATLO,&image[prop]);
}//在行line列column的位置上输出【prop】图片
//实现游戏的四个方向（上下左右）的控制
void gamecontrol (_DIRECTION direct){
	int x=man.x;
	int y=man.y;
	_POS next_pos=man;//前进下一格的坐标
	_POS next_next_pos=man;//人前两格的位置
	switch(direct){
	case UP:
		next_pos.x--;
		next_next_pos.x-=2;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x+=2;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y-=2;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y+=2;
		break;
	}
	//先处理前进方向地板的情况  x-1
	//宏展开  isValid(pos) next_pos.x>=0 && next_pos.y>=0
	//人的前方是地板
	if( isValid(next_pos)&& map[next_pos.x][next_pos.y]==FLOOR){
		changemap(&next_pos,MAN);//小人的前进一格
		changemap(&man,FLOOR);
		man=next_pos;
		//人的前方是箱子
	}else if(isValid(next_next_pos)&& map[next_pos.x][next_pos.y]==BOX ){
		//两种情况,箱子前面是地板,箱子面前是目的地
		if(map[next_next_pos.x][next_next_pos.y]==FLOOR){
			changemap(&next_next_pos,BOX);//原小人前一个前一个变成箱子
			changemap(&next_pos,MAN);//原小人前一个变成小人
			changemap(&man,FLOOR);//原小人位置变成地板
			man=next_pos;
		}else if(map[next_next_pos.x][next_next_pos.y]==BOX_DEX){
			changemap(&next_next_pos,HIT);//原小人前一个前一个变成箱子(目标点)
			changemap(&next_pos,MAN);//原小人前一个变成小人
			changemap(&man,FLOOR);//原小人位置变成地板
			man=next_pos;
		}
	}
}
int main(void){
	IMAGE bg_img;
	//搭台唱戏
	initgraph(SCREEN_WIDTH,SCREEN_HELGHT);//初始化背景大小
	loadimage(&bg_img,_T("blackground.bmp"),SCREEN_WIDTH,SCREEN_HELGHT,true);
	//加载背景(变量地址,文件(图片),大小,true)
	putimage(0,0,&bg_img);
	//加载道具图标
	loadimage(&image[WALL],_T("wall_right.bmp"),RATLO,RATLO,true);
	//加载墙(变量地址,文件(图片),大小,true)61,61是图片的像素大小
	loadimage(&image[FLOOR],_T("floor.bmp"),RATLO,RATLO,true);//地板
	loadimage(&image[BOX_DEX],_T("des.bmp"),RATLO,RATLO,true);//目的地
	loadimage(&image[MAN],_T("man.bmp"),RATLO,RATLO,true);//人
	loadimage(&image[BOX],_T("box.bmp"),RATLO,RATLO,true);//箱子
	loadimage(&image[HIT],_T("box.bmp"),RATLO,RATLO,true);//箱子命中目标(也用箱子图片表示)
	loadimage(&image[MAN_S],_T("man.bmp"),RATLO,RATLO,true);//假人
	for(int i=0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j]==3){
				man.x=i;
				man.y=j;
			}
			putimage(START_X+j*RATLO,START_Y+i*RATLO,&image[map[i][j]]);
		}
	}
	//游戏环节
	bool qiut=false;
	do{
		if(_kbhit()){//玩家按键
			char ch=_getch();
			if(ch==KEY_UP){
				gamecontrol(UP);
			}else if(ch==KEY_LEFT){
				gamecontrol(LEFT);
			}else if(ch==KEY_RIGHT){
				gamecontrol(RIGHT);
			}else if(ch==KEY_DOWN){
				gamecontrol(DOWN);
			}else if(ch==KEY_QUIT){        
				qiut=true;
			}
			if(isGameover()){
				gameover(&bg_img);
				qiut=true;
			}
		}
		Sleep(100);
	}while(qiut==false);//!quit
	system("pause");
	//游戏结束,释放资源关闭图像界面
	closegraph();
	return 0;
}