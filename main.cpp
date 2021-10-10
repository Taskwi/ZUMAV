#include "LinkList.h"
#include "ball.h"
#include "kdtree.h"


#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define WINDOWWITH 600
#define WINDOWHEIGHT 600
#define S 250
#define DEF_NUM_PTS 10

using namespace std;

COLORREF ballColorTable[] = {BLUE,    GREEN, RED,  YELLOW,
                             MAGENTA, BROWN, WHITE}; //��ɫ��

typedef struct {
  char name[20];
  int score;
} Person; //�û��ṹ

typedef struct direction {
  double x;
  double y;
} direction; //����ṹ

void Merge(Person *group, int p, int q, int r) {
  int length1 = q - p + 1;
  int length2 = r - q;
  Person *a1;
  Person *a2;
  int i, j, m;
  a1 = (Person *)malloc((length1 + 1) * sizeof(Person));
  a2 = (Person *)malloc((length2 + 1) * sizeof(Person));
  for (i = 0; i < length1; i++)
    a1[i] = group[p + i];
  for (j = 0; j < length2; j++)
    a2[j] = group[q + 1 + j];
  a1[length1].score = 999999;
  a2[length2].score = 999999;
  //�����ʱ����
  for (i = 0, j = 0, m = p; m <= r; m++) {
    if (a1[i].score <= a2[j].score) {
      group[m] = a1[i];
      i++;
    } else {
      group[m] = a2[j];
      j++;
    }
  }
  free(a1);
  free(a2);
}
void MergeSort(Person *group, int p, int r) {
  if (p < r) {
    int q;
    q = (p + r) / 2;
    MergeSort(group, p, q);
    MergeSort(group, q + 1, r);
    Merge(group, p, q, r);
  }
}
void Myqsort(Person *group, int size) { MergeSort(group, 0, size - 1); }
//�����㷨
/***********************************���¾�Ϊ���㷨*************************************/

//�������kdtree
static void InOrderTraverse(kdnode *T) {
  if (T) {
    InOrderTraverse(T->left);
    setcolor(ballColorTable[T->data.c]);
    setfillcolor(ballColorTable[T->data.c]);
    solidcircle(T->data.x, T->data.y, BALLRADIUS);
    InOrderTraverse(T->right);
  }
}

static float rd(void) {
  return (float)(BALLRADIUS + rand() % (WINDOWHEIGHT - 2 * BALLRADIUS));
}

/***********************************�����㷨*************************************/
//��ʼ��������
void initBallList(Node *head) {
  int i;
  ball b;

  for (i = 0; i < 58; ++i) {
    b.c = rand() % 6;

    ListInsert(head, 0, b);
  }
}
//�������������λ��
void updateBallPos(Node *head) {
  Node *p = head;
  //��ʼλ�ã�Ϊͷ���
  double x = X;
  double y = Y;
  int num = 0;
  //��Ĺ켣
  /*while (p->next != NULL)
  {
          p = p->next;
          dy= 2 * BALLRADIUS * rand() / (RAND_MAX + 1.0);
          dx = sqrt(400 - dy * dy);
          x += dx;
          y += dy;
          p->data.x = x;
          p->data.y = y;
  }*/

  while (p->next != NULL) {
    // Z
    if (num <= 5) {
      p = p->next;

      x = x + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 5 && num <= 13) {
      p = p->next;

      x = x - 12;
      p->data.x = x;
      y = y + 16;
      p->data.y = y;
    }
    if (num > 13 && num <= 18) {
      p = p->next;

      x = x + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    // S
    if (num == 19) {
      p = p->next;

      x = WINDOWWITH / 2.0 + 50;
      y = 100;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 19 && num <= 24) {
      p = p->next;

      x = x - BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 24 && num <= 27) {
      p = p->next;

      y = y + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 27 && num <= 32) {
      p = p->next;

      x = x + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 32 && num <= 35) {
      p = p->next;

      y = y + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 35 && num <= 40) {
      p = p->next;

      x = x - BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    // C
    if (num == 41) {
      p = p->next;

      x = WINDOWWITH - 10;
      y = 100;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 41 && num <= 46) {
      p = p->next;

      x = x - BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 46 && num <= 52) {
      p = p->next;

      y = y + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 52 && num <= 57) {
      p = p->next;

      x = x + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    if (num == 58) {
      p = p->next;

      x = 10;
      y = 300;
      p->data.x = x;
      p->data.y = y;
    }
    if (num > 58) {
      p = p->next;

      x = x + BALLRADIUS * 2;
      p->data.x = x;
      p->data.y = y;
    }
    num++;
  }
}
//����ײ��� //�޸Ĵ˺�������Ϊ�Ȳ����ڽ��м�⣬ʵ�����������
bool collisionDetection(Node *head, ball b, int *id) {
  if (!head)
    return false;
  Node *p = head->next;
  int dist = 0;
  int index = 0;
  while (p != NULL) {
    dist = 1.0 * (p->data.x - b.x) * (p->data.x - b.x) +
           1.0 * (p->data.y - b.y) * (p->data.y - b.y);
    if (dist < 400) {
      //�ڻ��б𷨣���ײ����prior�������ɵ���������ײ�����������b���ɵ������������ڻ�����0��������ײ��֮ǰ����֮֮��
      int x1, y1, x2, y2;
      int inner = 0;
      x1 = p->prior->data.x - p->data.x;
      y1 = p->prior->data.y - p->data.y;
      x2 = b.x - p->data.x;
      y2 = b.y - p->data.y;
      inner = x1 * x2 + y1 * y2;
      if (inner < 0)
        index++;
      *id = index;
      return TRUE;
    }

    p = p->next;
    index++;
  }
  return FALSE;
}
//�������
void drawBallList(Node *head) {
  Node *p;
  ball b;

  p = head;

  while (p->next != NULL) {
    p = p->next;
    b = p->data;

    setcolor(ballColorTable[b.c]);
    setfillcolor(ballColorTable[b.c]);
    solidcircle(b.x, b.y, BALLRADIUS);
  }
}
//������ײ��
void drawColBall(ball *b, double x, double y) {
  b->x = x * 1.0;
  b->y = y * 1.0;

  setcolor(ballColorTable[b->c]);
  setfillcolor(ballColorTable[b->c]);
  solidcircle(b->x, b->y, BALLRADIUS);
}
/***********************************����*************************************/
void initConsole(int width, int height) {
  char cmd[100];
  sprintf_s(cmd, 100, "mode con cols=%d lines=%d && title Zumav By Taskwi %s",
            width, height, __DATE__);
  system(cmd);
  //���ر�
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cur_info;
  GetConsoleCursorInfo(handle, &cur_info);
  cur_info.bVisible = FALSE;
  SetConsoleCursorInfo(handle, &cur_info);
}
/***********************************��Ϸ1*************************************/
void game1(int con, int &score) {
  HWND zumav = initgraph(WINDOWWITH, WINDOWHEIGHT);
  SetWindowTextA(zumav, "Zumav");
  cleardevice();
  //��ʼ������
  Node *head = NULL;
  head = CreateEmptyList();
  initBallList(head);
  updateBallPos(head);
  drawBallList(head);

  //����ײ��
  ball cball;
  cball.c = rand() % 6;
  direction direct = {-1, -1};
  float speed = 2.5;
  drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);

  //�¼�ѭ����������ꡢʱ���¼�
  MOUSEMSG m;
  bool ballMoving = FALSE;
  int time = 0;  //��ʱ��
  int count = 0; //��������������
  score = 0;
  char word[20] = {0}; // easyx������
  while (true) {

    //���飬���˾͹�
    count = listlength(head);
    if ((count - 58) * 2 * BALLRADIUS > WINDOWWITH) {
      DestroyList(head);
      closegraph();
      settextstyle(50, 0, _T("Consolas"));
      char a[100] = "Your score is ";
      strcat_s(a, word);
      MessageBoxA(GetConsoleWindow(), a, "GG !", MB_OK | MB_ICONERROR);
      return;
    }
    // ��ȡһ�������Ϣ
    if (MouseHit()) {
      m = GetMouseMsg();

      switch (m.uMsg) {
      case WM_MOUSEMOVE:
        break;

      case WM_LBUTTONDOWN:
        //��������˶�������ʼ�˶�
        if (!ballMoving) {
          double r;
          double x = (double)m.x - (double)WINDOWWITH / 2;
          double y = (double)WINDOWHEIGHT - (double)m.y;
          r = x * x + y * y;
          r = sqrt(r);
          direct.x = x * 1.0 / r;
          direct.y = y * 1.0 / r;
          ballMoving = TRUE;
        }
        break;

      case WM_RBUTTONUP:
        DestroyList(head);
        closegraph();
        settextstyle(50, 0, _T("Consolas"));
        char a[100] = "Your score is ";
        strcat_s(a, word);
        MessageBoxA(GetConsoleWindow(), a, "GG !", MB_OK | MB_ICONERROR);
        return; // ������Ҽ��˳�����
      }
    }
    // 1,2,3�����������
    BeginBatchDraw(); // 1
    //��ʱ������������ײ��
    int id;
    bool ifdelete;
    bool collision = collisionDetection(head, cball, &id);

    if (collision) {
      //�˴�Ϊ�Ľ�����㷨��ͨ��ֱ�ӽ�����룬��������Ƿ��������ͬɫ��������һֱ������ֱ��������������߲�ͬɫΪֹ
      ListInsert(head, id, cball);
      // updateBallPos(head);
      Node *temp;
      int count = 0;

      temp = get(head, id);
      count = listcount(temp, head);

      if (count >= 3) {
        ifdelete = exam1(temp, head, score);
        if (ifdelete)
          exam2(temp, head, score);
      }

      cball.c = rand() % 6;
      drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);
      ballMoving = FALSE;
      updateBallPos(head);
    }
    // drawBallList(head);

    //�����ײ���Ƿ񳬳���Χ
    if (cball.x > WINDOWWITH || cball.x < 0 || cball.y > WINDOWHEIGHT ||
        cball.y < 0) {
      cball.c = rand() % 6;
      drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);
      ballMoving = FALSE;
    }

    //�ƶ���������ײ��
    if (ballMoving == TRUE) {
      drawColBall(&cball, cball.x += (speed * direct.x),
                  cball.y -= speed * direct.y);
    } else {
      drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);
    }
    //����Ϊ������������sleep��������ͣ��t���ۼӴﵽ��ʱ���
    time++;
    if (time >= con) {
      ball new1;
      new1.c = rand() % 6;
      ListInsert(head, 0, new1);
      updateBallPos(head);
      time = 0;
    }
    //���� ��Ŀ->����->�߼�->�ַ���->ʹ�ö��ֽ��ַ���
    sprintf_s(word, "%d", score); //������ת�����ַ���
    settextcolor(YELLOW);         //����������ɫ
    settextstyle(30, 0, _T("Consolas"));
    setbkmode(TRANSPARENT);
    outtextxy(0, 0, "Your final score is:");
    outtextxy(WINDOWWITH / 2, 0, word);
    outtextxy(WINDOWWITH - 100, WINDOWHEIGHT - 50, "V4.0");
    //
    drawBallList(head);
    FlushBatchDraw(); // 2
    Sleep(1);
    EndBatchDraw(); // 3
    cleardevice();
  }
}
/***********************************��Ϸ2*************************************/
void game2(int &score) {
  //��ʼ����ͼ����
  initgraph(WINDOWWITH, WINDOWHEIGHT);
  setbkcolor(BLACK);
  cleardevice();
  //��ĸ���
  int num_pts = DEF_NUM_PTS;
  //ָ��kdtree
  struct kdnode *root = NULL;
  //��������С����
  DataType NearestBall;
  float dis;
  //������
  DataType Ball;

  srand(time(0));
  char word[20];
  //���򻭳�����kdtree��(����������ֵ�Բ�ص�)
  for (int i = 0; i < num_pts; ++i) {
    Ball.x = rd(), Ball.y = rd(), Ball.c = rand() % 6;
    int distance1;
    distance1 = (Ball.x - WINDOWWITH / 2) * (Ball.x - WINDOWWITH / 2) +
                (Ball.y - WINDOWHEIGHT) * (Ball.y - WINDOWHEIGHT);
    while (i > 0) {
      searchNearest(root, Ball, NearestBall, dis);
      if (distance1 == 0)
        break;
      if (dis >= 2 * BALLRADIUS && distance1 >= 2500 &&
          !(Ball.x < 2 / 3 * WINDOWWITH && Ball.y < 1 / 12 * WINDOWHEIGHT))
        break;
      Ball.x = rd(), Ball.y = rd();
    }
    root = kdnode_insert(root, Ball);
    setcolor(ballColorTable[Ball.c]);
    setfillcolor(ballColorTable[Ball.c]);
    solidcircle(Ball.x, Ball.y, BALLRADIUS);
  }

  //����ײ��
  DataType cball;
  cball.c = 6;
  drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);
  float ballDirctionx = -1;
  float ballDirctiony = -1;
  float speed = 8;

  //�¼�ѭ����������ꡢʱ���¼�
  MOUSEMSG m;
  bool ballMoving = FALSE;
  int time = 0;
  score = 0;
  while (root) {
    int number = 0;
    num(root, number);
    if (number >= 30) {
      kdtree_destroy(root);
      closegraph();
      settextstyle(50, 0, _T("Consolas"));
      char a[100] = "Your score is ";
      strcat_s(a, word);
      MessageBoxA(GetConsoleWindow(), a, "GG !", MB_OK | MB_ICONERROR);
      return;
    }
    BeginBatchDraw();
    // ��ȡһ�������Ϣ
    if (MouseHit()) {
      m = GetMouseMsg();
      switch (m.uMsg) {
      case WM_MOUSEMOVE:
        break;

      case WM_LBUTTONDOWN:
        //��������˶�������ʼ�˶�
        if (!ballMoving) {
          float x, y, r;
          x = m.x - WINDOWWITH / 2;
          y = WINDOWHEIGHT - m.y;
          r = x * x + y * y;
          r = sqrt(r);
          ballDirctionx = x / r;
          ballDirctiony = y / r;
          ballMoving = TRUE;
        }
        break;

      case WM_RBUTTONUP:
        closegraph();
        kdtree_destroy(root);
        settextstyle(50, 0, _T("Consolas"));
        char a[100] = "Your score is ";
        strcat_s(a, word);
        MessageBoxA(GetConsoleWindow(), a, "GG !", MB_OK | MB_ICONERROR);

        return;
      }
    }

    //�����ײ���Ƿ񳬳���Χ
    if (cball.x > WINDOWWITH + BALLRADIUS || cball.x < -BALLRADIUS ||
        cball.y > WINDOWHEIGHT + BALLRADIUS || cball.y < -BALLRADIUS) {
      cball.c = 6;
      drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);
      ballMoving = FALSE;
      continue;
    }

    //	//�ƶ���������ײ��
    if (ballMoving == TRUE) {
      cleardevice();
      drawColBall(&cball, cball.x + speed * ballDirctionx,
                  cball.y - speed * ballDirctiony);

      //�����������̾���
      searchNearest(root, cball, NearestBall, dis);
      if (dis <= 2 * BALLRADIUS) {

        if (cball.c == NearestBall.c) {
          root = kdnode_delete(root, NearestBall);
          printf("\a");
          score++;
          ballMoving = false;
          cball.c = rand() % 6;
        } else {
          if (cball.c != 6)
            root = kdnode_insert(root, cball);
          ball a;
          a.c = NearestBall.c;
          a.x = NearestBall.x;
          a.y = NearestBall.y;
          root = kdnode_delete(root, NearestBall);
          float x1, y1, r1;
          x1 = a.x - cball.x;
          y1 = cball.y - a.y;
          r1 = x1 * x1 + y1 * y1;
          r1 = sqrt(r1);
          ballDirctionx = x1 / r1;
          ballDirctiony = y1 / r1;
          cball = a;
        }

        continue;
      }
      InOrderTraverse(root);
    } else {
      cleardevice();
      InOrderTraverse(root);
      cball.c = 6;
      drawColBall(&cball, WINDOWWITH / 2, WINDOWHEIGHT);
    }
    Sleep(10);
    time++;
    if (time >= 200) {
      time = 0;
      ball a;
      a.c = rand() % 6;
      a.x = rd();
      a.y = rd();
      while (1) {
        searchNearest(root, a, NearestBall, dis);
        if (dis >= 2 * BALLRADIUS)
          break;
        a.x = rd(), a.y = rd();
      }
      root = kdnode_insert(root, a);
      InOrderTraverse(root);
    }
    //���� ��Ŀ->����->�߼�->�ַ���->ʹ�ö��ֽ��ַ���
    sprintf_s(word, "%d", score); //������ת�����ַ���
    settextcolor(YELLOW);         //����������ɫ
    settextstyle(30, 0, _T("Consolas"));
    setbkmode(TRANSPARENT);
    outtextxy(0, 0, "Your final score is:");
    outtextxy(WINDOWWITH / 2, 0, word);
    outtextxy(WINDOWWITH - 100, WINDOWHEIGHT - 50, "V4.0");
    //
    EndBatchDraw();
  }
  closegraph();
  kdtree_destroy(root);

  system("PAUSE");
}
/***********************************ѡ������*************************************/
void start(int &score) {
  initConsole(40, 10);
  printf("please choose the mode,1 or 2?\n");
  printf("1:the balls are in a line");
  printf("\n2.the ball appears randomly");
  int m = 1;
  int e = 0;
  while (m)
    switch (_getch()) {
    case '1':
      e = 1;
      m = 0;
      break;
    case '2':
      e = 2;
      m = 0;
      break;
    default:
      break;
    }
  system("cls");
  if (e == 1) {
    printf("**************Normal Zumav**************\n");
    printf("1.Easy\n2.Normal\n3.Hard\n4.Hell\n5.�����ˣ������ܵ�\n");
    printf("\n          Please choose          \n");
    int t = 1;
    int con;
    while (t)
      switch (_getch()) {
      case '1':
        con = 4 * S;
        t = 0;
        break;
      case '2':
        con = 3 * S;
        t = 0;
        break;
      case '3':
        con = 2 * S;
        t = 0;
        break;
      case '4':
        con = 1 * S;
        t = 0;
        break;
      case '5':
        con = S / 2;
        t = 0;
        break;
      default:
        break;
      }
    system("cls");
    game1(con, score);
  } else {
    game2(score);
  }
}
//���outtextxy�������� ��Ŀ->����->�߼�->�ַ���->ʹ�ö��ֽ��ַ���

int main() {
  Person A;
  FILE *fp;
  int t = 1;
  while (t) {
    A.score = 0;
    initConsole(25, 10);
    printf("\n\tZumav\n\n    1. Start\n    2. Rule\n    3. Ranking\n    q. "
           "quit\n");
    int count = 0;
    switch (_getch()) {
    case 'q':
      return 0;
    case '2':
      MessageBoxA(
          GetConsoleWindow(),
          "1.�������Ҳ���Ļʱ����Ϸ����\n2.1ģʽ�£�3����ɫ��ͬ���������\n3."
          "2ģʽ�£������������������ð���Ļ���ʹ������ȥ���÷�",
          "Rule", MB_OK | MB_ICONASTERISK);
      ;
      break;
    case '3':
      initConsole(25, 10);
      Person *data;
      FILE *fp1;
      if (fopen_s(&fp1, "D:\\GameRanking.txt", "r") != 0) {
        initConsole(25, 10);
        printf("No data!");
      } else {
        int count;
        fscanf_s(fp1, "%d\n", &count);
        printf("the num of players:%d\n", count);
        data = (Person *)malloc(count * sizeof(Person));
        for (int p = 0; p < count; p++) {
          fscanf_s(fp1, "%s\n", &data[p].name, 20);
          fscanf_s(fp1, "%d\n", &data[p].score);
        }
        fclose(fp1);
        for (int p = 0; p < count; p++) {
          printf("%d:", p + 1);
          printf("%s:", data[p].name);
          printf("%d\n", data[p].score);
        }
        free(data);
      }
      printf("\nplease tap to continue");
      _getch();
      break;
    case '1': {
      InputBox(A.name, 20, "please input your name", "Zumav 4", "player");
      system("cls");
      start(A.score);
      int N = 0;
      Person *group;
      int i = 0;
      if ((fopen_s(&fp, "D:\\GameRanking.txt", "r")) == 0) {
        fscanf_s(fp, "%d\n", &N);
        group = (Person *)malloc((N + 1) * sizeof(Person));
        for (i = 0; i < N; i++) {
          fscanf_s(fp, "%s\n", &group[i].name, 20);
          fscanf_s(fp, "%d\n", &group[i].score);
        }
        fclose(fp);
        group[N] = A;
      } else {
        group = (Person *)malloc(sizeof(Person));
        group[N] = A;
      }
      N++;
      Myqsort(group, N);
      FILE *fpwrite;
      if ((fopen_s(&fpwrite, "D:\\GameRanking.txt", "w")) == 0) {

        fprintf_s(fpwrite, "%d\n", N);
        for (i = 0; i < N; i++) {
          fprintf_s(fpwrite, "%s\n", group[i].name);
          fprintf_s(fpwrite, "%d\n", group[i].score);
        }
        fclose(fpwrite);
      }
    }
    }
  }
}
