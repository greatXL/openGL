#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
int m_PointNumber = 0; //����ʱ���Ƶ����Ŀ
int m_DrawMode;   
//����������
void DrawCordinateLine(void)
{
	int i = 0 ;
	//������Ϊ��ɫ
	glColor3f(0.0f, 0.0f ,0.0f);
	glBegin(GL_LINES);
        for (i=10;i<=250;i=i+10)
		{
			glVertex2f((float)(i), 0.0f);
			glVertex2f((float)(i), 250.0f);
			glVertex2f(0.0f, (float)(i));
			glVertex2f(250.0f, (float)(i));
		}
	glEnd();
}
//����һ���㣬������һ�������α�ʾһ���㡣
//����һ���㣬������һ�������α�ʾһ���㡣
void putpixel(GLsizei x, GLsizei y)
{
	glRectf(10*x,10*y,10*x+10,10*y+10);
}
///////////////////////////////////////////////////////////////////
//DDA�����㷨                                                   //
//����˵����x0,y0  �������                                     //  
//          x1,y1  �յ�����                                     // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ��� //
/////////////////////////////////////////////////////////////////// 
void DDACreateLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	//������ɫ
	glColor3f(1.0f,0.0f,0.0f);
	
	//�Ի��߶������п���
	if(num == 1)
		printf("DDA�����㷨����������\n");
	else if(num==0)
		return;
	//�����㷨��ʵ��
	GLsizei dx,dy,epsl,k;
	GLfloat x,y,xIncre,yIncre;
	dx = x1-x0;
	dy = y1-y0;
	x = x0;
	y = y0;
	if(abs(dx) > abs(dy)) epsl = abs(dx);
	else epsl = abs(dy);
	xIncre = (float)dx / epsl ;
	yIncre = (float)dy / epsl ;
	for(k = 0; k<=epsl; k++){
		putpixel((int)(x+0.5), (int)(y+0.5));
		if (k>=num-1) {
			printf("x=%f,y=%f,ȡ����x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
			break;
		}
		x += xIncre;
		y += yIncre;
		if(x >= 25 || y >= 25) break;
	}
}
///////////////////////////////////////////////////////////////////
//�е�Bresenham�㷨��ֱ��(0<=k<=1)                               //
//����˵����x0,y0  �������                                     //  
//          x1,y1  �յ�����                                     // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ��� //
/////////////////////////////////////////////////////////////////// 
void BresenhamLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);
	if(num == 1)
	{
		printf("�е�Bresenham�㷨��ֱ�ߣ��������꼰�б�ʽ��ֵ\n");
	}
	else if(num==0)
		return;
	//�е�Bresenham�����㷨��ʵ��
	GLsizei dx , dy, d, UpIncre, DownIncre, x, y;
	if (x0 > x1){
		x = x1; x1 = x0; x0 = x;
		y = y1; y1 = y0; y0 = y;
	}
	x = x0; y = y0;
	dx = x1 - x0; dy = y1 - y0;
	d = dx - 2 * dy;
	UpIncre=2*dx-2*dy;DownIncre=-2*dy;
	while(x<=x1)
	{
		putpixel(x,y);
		printf("x = %d , y = %d \n",x,y);
		x++;
		if(d<0)
		{
			y++;
			d+=UpIncre;
		}
		else
			d+=DownIncre;
	}
}
///////////////////////////////////////////////////////////////////
//�Ľ���Bresenham�㷨��ֱ��(0<=k<=1)                             //
//����˵����x0,y0  �������                                     //  
//          x1,y1  �յ�����                                     // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ��� //
/////////////////////////////////////////////////////////////////// 
void Bresenham2Line(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);
	if(num == 1)
		printf("�Ľ���Bresenham�㷨��ֱ�ߣ��������꼰�б�ʽ��ֵ\n");
	else if(num==0)
		return;
	//�����㷨��ʵ��
	GLsizei x,y,dx,dy,e;
	dx = x1-x0;
	dy = y1-y0;
	e = -dx;x=x0;y=y0;
	while(x<=x1)
	{
		putpixel(x,y);
		printf("x = %d , y = %d \n",x,y);
		x++;
		e = e+2*dy;
		if(e>0)
		{
			y++;
			e = e-2*dx;
		}
	}

}
///////////////////////////////////////////////////////////////////
//Bresenham�㷨��Բ                                             //
//����˵����x,y    Բ������                                     //  
//          R      Բ�뾶                                       // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ��� //
/////////////////////////////////////////////////////////////////// 
void BresenhamCircle(GLsizei x, GLsizei y, GLsizei R, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("Bresenham�㷨��Բ���������꼰�б�ʽ��ֵ\n");
	int d,k=0,xa,ya;
	xa=0;ya=R;d=1-R;
	while(xa<=ya){
		putpixel(xa+x,ya+y);
		putpixel(ya+x,xa+y);
		putpixel(-ya+x,xa+y);
		putpixel(-xa+x,ya+y);
		putpixel(-xa+x,-ya+y);
		putpixel(-ya+x,-xa+y);
		putpixel(ya+x,-xa+y);
		putpixel(xa+x,-ya+y);
		if (k>=num-1) {
			printf("x=%d , y=%d\n" , xa+x,ya+y);
			break;
		}
		k++;
		if(d<0) d+=2*xa+3;
		else{
			d+=2*(xa-ya)+5;
			ya--;
		}
		xa++;
	}	
}

//��ʼ������
void Initial(void)
{
    // ���ô�����ɫΪ��ɫ
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{

	if(h == 0)		h = 1;
	// ���������ߴ�
   	glViewport(0, 0, w, h);
	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// �����޼��ռ�ķ�Χ
   	if (w <= h) 
		glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    else 
		glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

}
// �ڴ����л���ͼ��
void ReDraw(void)
{
	//�õ�ǰ����ɫ��䴰��
	glClear(GL_COLOR_BUFFER_BIT);

	//����������
	DrawCordinateLine();
	switch(m_DrawMode)
	{
	case 1:
		DDACreateLine(1,1.5,6,4,m_PointNumber);
		break;
	case 2:
		BresenhamLine(0,0,20,15,m_PointNumber);
		break;
	case 3:
		Bresenham2Line(1,1,8,6,m_PointNumber);
		break;
	case 4:
		BresenhamCircle(12,12,10,m_PointNumber);
		break;
	default:
		break;
	}

    glFlush();
}

//����ʱ��ص�����
void TimerFunc(int value)
{
	if(m_PointNumber == 0)
		value = 1;

	m_PointNumber = value;

	glutPostRedisplay();
	glutTimerFunc(500, TimerFunc, value+1);
}

int main(int argc, char* argv[])
{
	char a[4][30]={{"DDA�㷨��ֱ��"},{"�е�Bresenham�㷨��ֱ��"},{"�Ľ�Bresenham�㷨��ֱ��"},{"�˷ַ�����Բ"}};
	glutInit(&argc, argv);
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	printf("����ģʽ\n");
	printf("1    DDA�㷨��ֱ��\n");
	printf("2    �е�Bresenham�㷨��ֱ��\n");
	printf("3    �Ľ�Bresenham�㷨��ֱ��\n");
	printf("4    �˷ַ�����Բ\n���������ģʽ:");
	scanf("%d",&m_DrawMode);
	glutCreateWindow(a[m_DrawMode-1]); 
	glutDisplayFunc(ReDraw); 
    glutReshapeFunc(ChangeSize); 
	glutTimerFunc(500, TimerFunc, 1);
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
	return 0;
}

