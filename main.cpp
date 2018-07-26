#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
int m_PointNumber = 0; //动画时绘制点的数目
int m_DrawMode;   
//绘制坐标线
void DrawCordinateLine(void)
{
	int i = 0 ;
	//坐标线为黑色
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
//绘制一个点，这里用一个正方形表示一个点。
//绘制一个点，这里用一个正方形表示一个点。
void putpixel(GLsizei x, GLsizei y)
{
	glRectf(10*x,10*y,10*x+10,10*y+10);
}
///////////////////////////////////////////////////////////////////
//DDA画线算法                                                   //
//参数说明：x0,y0  起点坐标                                     //  
//          x1,y1  终点坐标                                     // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画 //
/////////////////////////////////////////////////////////////////// 
void DDACreateLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	//设置颜色
	glColor3f(1.0f,0.0f,0.0f);
	
	//对画线动画进行控制
	if(num == 1)
		printf("DDA画线算法：各点坐标\n");
	else if(num==0)
		return;
	//画线算法的实现
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
			printf("x=%f,y=%f,取整后x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
			break;
		}
		x += xIncre;
		y += yIncre;
		if(x >= 25 || y >= 25) break;
	}
}
///////////////////////////////////////////////////////////////////
//中点Bresenham算法画直线(0<=k<=1)                               //
//参数说明：x0,y0  起点坐标                                     //  
//          x1,y1  终点坐标                                     // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画 //
/////////////////////////////////////////////////////////////////// 
void BresenhamLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);
	if(num == 1)
	{
		printf("中点Bresenham算法画直线：各点坐标及判别式的值\n");
	}
	else if(num==0)
		return;
	//中点Bresenham划线算法的实现
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
//改进的Bresenham算法画直线(0<=k<=1)                             //
//参数说明：x0,y0  起点坐标                                     //  
//          x1,y1  终点坐标                                     // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画 //
/////////////////////////////////////////////////////////////////// 
void Bresenham2Line(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);
	if(num == 1)
		printf("改进的Bresenham算法画直线：各点坐标及判别式的值\n");
	else if(num==0)
		return;
	//画线算法的实现
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
//Bresenham算法画圆                                             //
//参数说明：x,y    圆心坐标                                     //  
//          R      圆半径                                       // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画 //
/////////////////////////////////////////////////////////////////// 
void BresenhamCircle(GLsizei x, GLsizei y, GLsizei R, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("Bresenham算法画圆：各点坐标及判别式的值\n");
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

//初始化窗口
void Initial(void)
{
    // 设置窗口颜色为蓝色
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{

	if(h == 0)		h = 1;
	// 设置视区尺寸
   	glViewport(0, 0, w, h);
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 建立修剪空间的范围
   	if (w <= h) 
		glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    else 
		glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

}
// 在窗口中绘制图形
void ReDraw(void)
{
	//用当前背景色填充窗口
	glClear(GL_COLOR_BUFFER_BIT);

	//画出坐标线
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

//设置时间回调函数
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
	char a[4][30]={{"DDA算法画直线"},{"中点Bresenham算法画直线"},{"改进Bresenham算法画直线"},{"八分法绘制圆"}};
	glutInit(&argc, argv);
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	printf("绘制模式\n");
	printf("1    DDA算法画直线\n");
	printf("2    中点Bresenham算法画直线\n");
	printf("3    改进Bresenham算法画直线\n");
	printf("4    八分法绘制圆\n请输入你的模式:");
	scanf("%d",&m_DrawMode);
	glutCreateWindow(a[m_DrawMode-1]); 
	glutDisplayFunc(ReDraw); 
    glutReshapeFunc(ChangeSize); 
	glutTimerFunc(500, TimerFunc, 1);
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环
	return 0;
}

