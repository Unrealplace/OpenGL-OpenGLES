#include "GLShaderManager.h"
#include "GLTools.h"
#include "GLFrame.h"
#include "GLFrustum.h"
#include "GLMatrixStack.h"
#include "GLGeometryTransform.h"
#include <glut/glut.h>

// 点
GLBatch batch_points;
// 点线
GLBatch batch_line;
// 线段依次连接
GLBatch batch_lineStrip;
// 线段依次连接并且首位相连
GLBatch batch_lineClose;
// 三角
GLBatch batch_trangle;
// 三角依次连接
GLBatch batch_trangleStrip;
// 三角环
GLBatch batch_trangleFan;
 
GLMatrixStack modelViewStack;
GLMatrixStack projectionStack;
GLFrame cameraFrame;
// 世界坐标系
GLFrame objectFrame;
GLFrustum viewFrustum;
GLShaderManager shaderManager;
GLGeometryTransform transformPipeLine;
 
GLfloat vGreen[] = {0.0, 1.0, 0.0, 1.0};
GLfloat vBlack[] = {0.0, 0.0, 0.0, 1.0};
GLint g_step = 0;
 
void SetupRC()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    // 创建存储着色器
    shaderManager.InitializeStockShaders();
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);
    transformPipeLine.SetMatrixStacks(modelViewStack, projectionStack);
    //移动相机原点，否则看不到后续绘制的图案
    cameraFrame.MoveForward(-15.0f);
    
    // 24个顶点
    GLfloat vCoast[24][3] =
    {{2.80, 1.20, 0.0 }, {2.0,  1.20, 0.0 },
    {2.0,  1.08, 0.0 },  {2.0,  1.08, 0.0 },
    {0.0,  0.80, 0.0 },  {-.32, 0.40, 0.0 },
    {-.48, 0.2, 0.0 },   {-.40, 0.0, 0.0 },
    {-.60, -.40, 0.0 },  {-.80, -.80, 0.0 },
    {-.80, -1.4, 0.0 },  {-.40, -1.60, 0.0 },
    {0.0, -1.20, 0.0 },  { .2, -.80, 0.0 },
    {.48, -.40, 0.0 },   {.52, -.20, 0.0 },
    {.48,  .20, 0.0 },   {.80,  .40, 0.0 },
    {1.20, .80, 0.0 },   {1.60, .60, 0.0 },
    {2.0, .60, 0.0 },    {2.2, .80, 0.0 },
    {2.40, 1.0, 0.0 },   {2.80, 1.0, 0.0 }};
 
    batch_points.Begin(GL_POINTS, 24);
    batch_points.CopyVertexData3f(vCoast);
    batch_points.End();
 
    batch_line.Begin(GL_LINES, 24);
    batch_line.CopyVertexData3f(vCoast);
    batch_line.End();
 
    batch_lineStrip.Begin(GL_LINE_STRIP, 24);
    batch_lineStrip.CopyVertexData3f(vCoast);
    batch_lineStrip.End();
 
    batch_lineClose.Begin(GL_LINE_LOOP, 24);
    batch_lineClose.CopyVertexData3f(vCoast);
    batch_lineClose.End();
 
    //==============金字塔==============//
    GLfloat vPyramid[12][3] =
    {
      -2.0f, 0.0f, -2.0f,    2.0f, 0.0f, -2.0f,     0.0f, 4.0f, 0.0f,
       2.0f, 0.0f, -2.0f,    2.0f, 0.0f, 2.0f,      0.0f, 4.0f, 0.0f,
       2.0f, 0.0f, 2.0f,    -2.0f, 0.0f, 2.0f,      0.0f, 4.0f, 0.0f,
     -2.0f, 0.0f, 2.0f,    -2.0f, 0.0f, -2.0f,     0.0f, 4.0f, 0.0f
    };
 
    batch_trangle.Begin(GL_TRIANGLES, 12);
    batch_trangle.CopyVertexData3f(vPyramid);
    batch_trangle.End();
    //=================================//
 
    //=============trangleFun=============//
    GLfloat vFan[8][3];
    vFan[0][0] = 0.0;
    vFan[0][1] = 0.0;
    vFan[0][2] = 0.0;
    GLfloat r1 = 3.0;
    GLint index1 = 1;
    for (GLfloat angle=0.0; angle<M3D_2PI; angle+=(M3D_2PI/6.0f),index1++)
    {
        vFan[index1][0] = GLfloat(cos(angle)*r1);
        vFan[index1][1] = GLfloat(sin(angle)*r1);
        vFan[index1][2] = -0.5;
    }
    //封闭图像轮廓
    index1++;
    vFan[index1][0] = r1;
    vFan[index1][1] = 0.0;
    vFan[index1][2] = 0.0;
    batch_trangleFan.Begin(GL_TRIANGLE_FAN, 8);
    batch_trangleFan.CopyVertexData3f(vFan);
    batch_trangleFan.End();
    //=================================//
 
    //=============trangleStrip============//
    GLfloat vStrip[100][3];
    GLfloat r2 = 3.0;
    GLint index2 = 0;
    for (GLfloat angle=0.0; angle<M3D_2PI; angle+=(M3D_2PI/20))
    {
        GLfloat tempX = GLfloat(cos(angle)*r2);
        GLfloat tempY = GLfloat(sin(angle)*r2);
 
        vStrip[index2][0] = tempX;
        vStrip[index2][1] = tempY;
        vStrip[index2][2] = 0.5;
        index2++;
 
        vStrip[index2][0] = tempX;
        vStrip[index2][1] = tempY;
        vStrip[index2][2] = -0.5;
        index2++;
    }
    //封闭图像轮廓
    vStrip[index2][0] = r2;
    vStrip[index2][1] = 0.0;
    vStrip[index2][2] = 0.5;
    index2++;
 
    vStrip[index2][0] = r2;
    vStrip[index2][1] = 0.0;
    vStrip[index2][2] = -0.5;
    index2++;
 
    batch_trangleStrip.Begin(GL_TRIANGLE_STRIP, index2);
    batch_trangleStrip.CopyVertexData3f(vStrip);
    batch_trangleStrip.End();
    //=================================//
}
 
void DrawBatch(GLBatch *pBatch)
{
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeLine.GetModelViewProjectionMatrix() ,vGreen);
    pBatch->Draw();
 
    //绘制轮廓曲线
    glPolygonOffset(-1.0, -1.0);
    glEnable(GL_POLYGON_OFFSET_LINE);
    //打开抗锯齿
    glEnable(GL_LINE_SMOOTH);
    //开启混合模式
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //将GLBatch类的Draw函数的绘制模式改成线条模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.5);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeLine.GetModelViewProjectionMatrix(), vBlack);
    pBatch->Draw();
    //将GLBatch类的Draw函数的绘制模式改成填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0);
    glDisable(GL_BLEND);
}
 
// 执行渲染场景
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //默认模型视图矩阵入栈
    modelViewStack.PushMatrix();
    //当前模型视图矩阵乘视图
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewStack.MultMatrix(mCamera);
    
    
    //当前模型视图矩阵乘模型矩阵
    M3DMatrix44f mObject;
    objectFrame.GetCameraMatrix(mObject);
    modelViewStack.MultMatrix(mObject);
    
    
    //GetModelViewProjectionMatrix()函数会把模型视图矩阵左乘透视矩阵构成 模型视图透视矩阵
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeLine.GetModelViewProjectionMatrix(), vBlack);
 
    switch(g_step)
    {
    case 0:
        glPointSize(4.0f);
        batch_points.Draw();
        glPointSize(1.0f);
        break;
    case 1:
        glLineWidth(2.0f);
        batch_line.Draw();
        glLineWidth(1.0f);
        break;
    case 2:
        glLineWidth(2.0f);
        batch_lineStrip.Draw();
        glLineWidth(1.0f);
        break;
    case 3:
        glLineWidth(2.0f);
        batch_lineClose.Draw();
        glLineWidth(1.0f);
        break;
    case 4:
        DrawBatch(&batch_trangle);
        break;
    case 5:
        DrawBatch(&batch_trangleStrip);
        break;
    case 6:
        DrawBatch(&batch_trangleFan);
        break;
    default:
        break;
    }
    //当前模型视图矩阵出栈，恢复成默认矩阵
    modelViewStack.PopMatrix();
    glutSwapBuffers();
}

// 键盘其他按键操作，切换渲染方式
void KeyBoardCallBack(unsigned char key, int x, int y)
{
    if ('a' == key)
    {
        g_step++;
        if (g_step > 6)
        {
            g_step = 0;
        }
        switch(g_step)
        {
        case 0:
            glutSetWindowTitle("GL_points");
            break;
        case 1:
            glutSetWindowTitle("GL_lines");
            break;
        case 2:
            glutSetWindowTitle("GL_lineStrip");
            break;
        case 3:
            glutSetWindowTitle("GL_lineClose");
            break;
        case 4:
            glutSetWindowTitle("GL_trangle");
            break;
        case 5:
            glutSetWindowTitle("GL_trangleStrip");
            break;
        case 6:
            glutSetWindowTitle("GL_trangleFun");
            break;
        }
        glutPostRedisplay();
    }
}

// 键盘方向键操作回调
void SpecialKey(int key, int x, int y)
{
    //上下方向键绕X轴旋转，左右方向键绕Y轴旋转
    switch(key)
    {
    case GLUT_KEY_UP:
        objectFrame.RotateWorld(m3dDegToRad(-5.0), 1.0, 0.0, 0.0);
        break;
    case GLUT_KEY_DOWN:
        objectFrame.RotateWorld(m3dDegToRad(5.0), 1.0, 0.0, 0.0);
        break;
    case GLUT_KEY_LEFT:
        objectFrame.RotateWorld(m3dDegToRad(-5.0), 0.0, 1.0, 0.0);
        break;
    case GLUT_KEY_RIGHT:
        objectFrame.RotateWorld(m3dDegToRad(5.0), 0.0, 1.0, 0.0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
 
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    //创建透视矩阵
    viewFrustum.SetPerspective(35.0, float(w)/h, 1.0, 50);
    projectionStack.LoadMatrix(viewFrustum.GetProjectionMatrix());
    //创建模型视图矩阵（单位矩阵）
    modelViewStack.LoadIdentity();
}
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GL_points");
    
    // 注册监听回调函数
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyBoardCallBack);
    glutSpecialFunc(SpecialKey);
    glutDisplayFunc(RenderScene);
 
    GLenum ret = glewInit();
    if (GLEW_OK != ret)
    {
        fprintf(stderr, "glew error %s", glewGetErrorString(ret));
        return 1;
    }
    
    SetupRC();
    glutMainLoop();
 
    return 0;
}
