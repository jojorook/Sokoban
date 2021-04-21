#include<iostream>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h> 
#include "box main.h"//��ͬĿ¼��˫����
using namespace std;
IMAGE image[ALL];//����ȫ�ֱ���,6�е��߶���6��
struct _POS man;//С�˵�����
//��Ϸ��������,ͨ�غ���ʾ
//bg����ͼ������ָ��
void gameover(IMAGE *bg){
	putimage(0,0,bg);
	settextcolor(WHITE);
	RECT ret={0,0,SCREEN_WIDTH,SCREEN_HELGHT};
	settextstyle(20,0,_T("����"));//��С �������Ӧ ����
	drawtext(_T("��ϲ��~\n���Ϊһ���������������Ӵ�ɵ��!"),&ret,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//ˮƽ����,��ֱ����,������ʾ��һ��(�����ĵ���)
}
int map[LINE][COLUMN] = {//��Ϸ��ͼ
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
//�ж���Ϸ����,�������������Ŀ�ĵؾʹ������
//������, trun=����  false=����
bool isGameover(){
	for(int i=0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j]==BOX_DEX) return false;
		}
	}
	return true;
}
//�ı���Ϸ��ͼ��ͼ�ж�Ӧ���߲�����չʾ
//���룺 line �����ڵ�ͼ��������±꣬column �����ڵ�ͼ��������±�
//prop ���ߵ�����
//�ṹ��ָ�� �ṹ�崫ֵ pos->x;
void changemap(_POS *pos, _PROPS prop){
	map[pos->x][pos->y]=prop;
	putimage(START_X + pos->y *RATLO,START_Y + pos->x * RATLO,&image[prop]);
}//����line��column��λ���������prop��ͼƬ
//ʵ����Ϸ���ĸ������������ң��Ŀ���
void gamecontrol (_DIRECTION direct){
	int x=man.x;
	int y=man.y;
	_POS next_pos=man;//ǰ����һ�������
	_POS next_next_pos=man;//��ǰ�����λ��
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
	//�ȴ���ǰ������ذ�����  x-1
	//��չ��  isValid(pos) next_pos.x>=0 && next_pos.y>=0
	//�˵�ǰ���ǵذ�
	if( isValid(next_pos)&& map[next_pos.x][next_pos.y]==FLOOR){
		changemap(&next_pos,MAN);//С�˵�ǰ��һ��
		changemap(&man,FLOOR);
		man=next_pos;
		//�˵�ǰ��������
	}else if(isValid(next_next_pos)&& map[next_pos.x][next_pos.y]==BOX ){
		//�������,����ǰ���ǵذ�,������ǰ��Ŀ�ĵ�
		if(map[next_next_pos.x][next_next_pos.y]==FLOOR){
			changemap(&next_next_pos,BOX);//ԭС��ǰһ��ǰһ���������
			changemap(&next_pos,MAN);//ԭС��ǰһ�����С��
			changemap(&man,FLOOR);//ԭС��λ�ñ�ɵذ�
			man=next_pos;
		}else if(map[next_next_pos.x][next_next_pos.y]==BOX_DEX){
			changemap(&next_next_pos,HIT);//ԭС��ǰһ��ǰһ���������(Ŀ���)
			changemap(&next_pos,MAN);//ԭС��ǰһ�����С��
			changemap(&man,FLOOR);//ԭС��λ�ñ�ɵذ�
			man=next_pos;
		}
	}
}
int main(void){
	IMAGE bg_img;
	//��̨��Ϸ
	initgraph(SCREEN_WIDTH,SCREEN_HELGHT);//��ʼ��������С
	loadimage(&bg_img,_T("blackground.bmp"),SCREEN_WIDTH,SCREEN_HELGHT,true);
	//���ر���(������ַ,�ļ�(ͼƬ),��С,true)
	putimage(0,0,&bg_img);
	//���ص���ͼ��
	loadimage(&image[WALL],_T("wall_right.bmp"),RATLO,RATLO,true);
	//����ǽ(������ַ,�ļ�(ͼƬ),��С,true)61,61��ͼƬ�����ش�С
	loadimage(&image[FLOOR],_T("floor.bmp"),RATLO,RATLO,true);//�ذ�
	loadimage(&image[BOX_DEX],_T("des.bmp"),RATLO,RATLO,true);//Ŀ�ĵ�
	loadimage(&image[MAN],_T("man.bmp"),RATLO,RATLO,true);//��
	loadimage(&image[BOX],_T("box.bmp"),RATLO,RATLO,true);//����
	loadimage(&image[HIT],_T("box.bmp"),RATLO,RATLO,true);//��������Ŀ��(Ҳ������ͼƬ��ʾ)
	loadimage(&image[MAN_S],_T("man.bmp"),RATLO,RATLO,true);//����
	for(int i=0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j]==3){
				man.x=i;
				man.y=j;
			}
			putimage(START_X+j*RATLO,START_Y+i*RATLO,&image[map[i][j]]);
		}
	}
	//��Ϸ����
	bool qiut=false;
	do{
		if(_kbhit()){//��Ұ���
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
	//��Ϸ����,�ͷ���Դ�ر�ͼ�����
	closegraph();
	return 0;
}