
#define KEY_UP     'w'//�궨����������
#define KEY_LEFT   'a'
#define KEY_RIGHT  'd'
#define KEY_DOWN   's'
#define KEY_QUIT   'q'
#define LINE 9//��
#define COLUMN 12//��
#define RATLO 61//���ش�С
#define START_X 100//���ϽǵĴ������ӡλ�õ�����
#define START_Y 150
#define SCREEN_HELGHT 768//��
#define SCREEN_WIDTH 960//��
#define isValid(pos) next_pos.x>=0 && next_pos.y>=0//С��ǰ����if�����궨��
typedef enum _PROPS _PROPS;//���Ͷ������Ʊ���enum _PROPS -�� _PROPS
typedef enum _DIRECTION  _DIRECTION;//ͬ��
typedef struct _POS  _POS ;
enum _PROPS{//���� ö��
	WALL,//ǽ
	FLOOR,//�ذ�
	BOX_DEX,//Ŀ��
	MAN,//��
	BOX,//����
	HIT,//��������
	MAN_S,//����
	ALL//һ�����ٸ�Ԫ��
};
enum _DIRECTION//��Ϸ���Ʒ���  ö��
{   
	UP,
	DOWN,
	LEFT,
	RIGHT
};
struct _POS{//������ṹ��
	int x;//С���ڵĶ�ά�������
	int y;//С����
};	