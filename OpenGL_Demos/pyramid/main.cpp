//
//  main.cpp
//  pyramid
//
//  Created by mpm on 2020/6/24.
//  Copyright © 2020 mpm. All rights reserved.
//

#include "GLShaderManager.h"
#include "GLTools.h"
#include "GLFrame.h"
#include "GLFrustum.h"
#include "GLMatrixStack.h"
#include "GLGeometryTransform.h"
#include <glut/glut.h>

// 存储着色器管理工具类
GLShaderManager     shaderManager;
// 模型视图矩阵堆栈
GLMatrixStack       modelViewMatrix;
// 投影矩阵堆栈
GLMatrixStack       projectionMatrix;
// 设置观察者坐标
GLFrame             cameraFrame;
// 设置图形环绕时，视图坐标
GLFrame             objectFrame;
// 设置图片绘制时的投影方式,视景体
GLFrustum           viewFrustum;
//椎体容器类
GLBatch             pyramidBatch;
//立方体容器类
GLBatch             cubeBatch;

//transformPipeline:它是变换管道，类型是 GLGeometryTransform，专门用来管理投影和模型矩阵的 。
//其实就是把两个矩阵堆栈都存到他这个管道里，方便我们用的时候拿出来。
//如果不使用这个管道，在RenderScene里这段代码
// shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
// 修改为从各自的堆栈里获取矩阵也能实现相同效果
// shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, modelViewMatix.GetMatrix(), projectionMatrix.GetMatrix(), vRed);
// 几何变换的管道
GLGeometryTransform transformPipeLine;

//一个黑色 一个绿色
GLfloat vGreen[] = { 0.3f, .4f, 0.3f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLint bathType = 0;
 
void SetupRC()
{
    //设置背景颜色
    glClearColor(0.9, 0.9, 0.9, 1);
    //初始化shaderManager
    shaderManager.InitializeStockShaders();
    //开启深度测试(后面再说是干啥的)
    glEnable(GL_DEPTH_TEST);
    //设置变换管线以使用两个矩阵堆栈
    transformPipeLine.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    
    // 把相机往后移，要不然可能会看不到图，感兴趣的可以改改数值就懂了是啥意思了。
    // 为了让效果明显，将观察者坐标位置Z移动往屏幕里移动15个单位位置
    // 参数：表示离屏幕之间的距离。 负数，是往屏幕后面移动；正数，往屏幕前面移动
    // GLFrame类型，表示camera
    cameraFrame.MoveForward(-15);
    //通过三角形创建金字塔,坐标是相对于物体坐标系来确定的，然后再通过一系列矩阵变换到窗口坐标
    GLfloat vPyramid[18][3] = {
        //背面的三角形的三个点坐标
        1.0f,0.f,-1.f,
        0.f,3.f,0.f,
        -1.f,0.f,-1.f,
        
        //右边的三角形的三个点坐标
        1.f,0.f,-1.f,
        0.f,3.f,0.f,
        1.f,0.f,1.f,
        
        //正面的三角形的三个点坐标
        1.f,0.f,1.f,
        0.f,3.f,0.f,
        -1.f,0.f,-1.f,
        
        //左边的三角形的三个点坐标
        -1.f,0.f,1.f,
        -1.f,0.f,-1.f,
        0.f,3.f,0.f,
        
        //底部三角形的三个点坐标
        -1.f,0.f,-1.f,
        1.f,0.f,-1.f,
        1.f,0.f,1.f,

        //底部的三角形的三个点坐标
        -1.f,0.f,-1.f,
        -1.f,0.f,1.f,
        1.f,0.f,1.f,
    };
    pyramidBatch.Begin(GL_TRIANGLES, 18);
    pyramidBatch.CopyVertexData3f(vPyramid);
    pyramidBatch.End();
    
    GLfloat cubeVert[36][3] = {
        // 底部
        0.f,0.f,0.f,
        0.f,0.f,2.f,
        2.f,0.f,0.f,
        
        2.f,0.f,2.f,
        0.f,0.f,2.f,
        2.f,0.f,0.f,
        
        //左
        0.f,0.f,0.f,
        0.f,0.f,2.f,
        0.f,2.f,2.f,
        
        0.f,0.f,0.f,
        0.f,2.f,2.f,
        0.f,2.f,0.f,
        
        //右
        2.f,0.f,2.f,
        2.f,2.f,2.f,
        2.f,0.f,0.f,
        
        2.f,2.f,2.f,
        2.f,0.f,0.f,
        2.f,2.f,0.f,
        
        //前
        2.f,0.f,2.f,
        2.f,2.f,2.f,
        0.f,0.f,2.f,
        
        2.f,2.f,2.f,
        0.f,0.f,2.f,
        0.f,2.f,2.f,
        
        //后
        0.f,0.f,0.f,
        0.f,2.f,0.f,
        2.f,2.f,0.f,
        
        0.f,0.f,0.f,
        2.f,0.f,0.f,
        2.f,2.f,0.f,
        
        //上
        0.f,2.f,2.f,
        0.f,2.f,0.f,
        2.f,2.f,0.f,
        
        0.f,2.f,2.f,
        2.f,2.f,2.f,
        2.f,2.f,0.f,
        
    };
    
    cubeBatch.Begin(GL_TRIANGLES, 36);
    cubeBatch.Color4f(1.f, 0.f, 0.f, 0.1);
    cubeBatch.CopyVertexData3f(cubeVert);
    cubeBatch.End();
}

// 召唤场景
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // 坐标转换过程
    // 压栈
    //    modelViewMatrix.PushMatrix();
    //    这句代码的意思是压栈，如果 PushMatix() 括号里是空的，就代表是把栈顶的矩阵复制一份，再压栈到它的顶部。
    //    如果不是空的，比如是括号里是单元矩阵，那么就代表压入一个单元矩阵到栈顶了。
    //
    modelViewMatrix.PushMatrix();
    
    // 摄像机矩阵
    M3DMatrix44f camera;
    cameraFrame.GetCameraMatrix(camera);
    
    //    将modelViewMatrix 的堆栈中的矩阵 与 mOjbectFrame 矩阵相乘，
    //    存储到modelViewMatrix矩阵堆栈中modelViewMatrix.MultMatrix(mObjectFrame);
    //    这句代码的意思是把 模型视图矩阵堆栈 的 栈顶 的矩阵copy出一份来和新矩阵进行矩阵相乘，然后再将相乘的结果赋值给栈顶的矩阵。

    modelViewMatrix.MultMatrix(camera);
    
    // 只要使用 GetMatrix 函数就可以获取矩阵堆栈顶部的值，这个函数可以进行2次重载。
    // 用来使用GLShaderManager 的使用。或者是获取顶部矩阵的顶点副本数据
    M3DMatrix44f obj;
    objectFrame.GetMatrix(obj);
    modelViewMatrix.MultMatrix(obj);
    
    //使用默认光源着色器
    //通过光源、阴影效果跟提现立体效果
    //参数1：GLT_SHADER_FLAT 着色器类型
    //参数2：模型视图矩阵
    //参数3：投影矩阵
    //参数4：基本颜色值
    shaderManager.UseStockShader(GLT_SHADER_FLAT,transformPipeLine.GetModelViewProjectionMatrix(),vGreen);
    switch (bathType) {
        case 0:
            pyramidBatch.Draw();

            break;
        case 1:
            cubeBatch.Draw();
            break;
            
        default:
            break;
    }
    
    
    //画黑色边框
    glPolygonOffset(-1.0f, -1.0f);// 偏移深度，在同一位置要绘制填充和边线，会产生z冲突，所以要偏移
    glEnable(GL_POLYGON_OFFSET_LINE);
    
    // 画反锯齿，让黑边好看些
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //绘制线框几何黑色版 三种模式，实心，边框，点，可以作用在正面，背面，或者两面
    //通过调用glPolygonMode将多边形正面或者背面设为线框模式，实现线框渲染
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //设置线条宽度
    glLineWidth(1.f);
    
    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
     --transformPipeline.GetModelViewProjectionMatrix() 获取的
     GetMatrix函数就可以获得矩阵堆栈顶部的值
     参数3：颜色值（黑色）
     */
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeLine.GetModelViewProjectionMatrix(), vBlack);
    
    switch (bathType) {
        case 0:
            pyramidBatch.Draw();
            break;
        case 1:
            cubeBatch.Draw();
            break;
            
        default:
            break;
    }
    
    // 复原原本的设置
    ////通过调用glPolygonMode将多边形正面或者背面设为全部填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    
    //把栈顶的矩阵出栈，恢复为原始的矩阵堆栈，这样就不会影响后续的操作了。
    modelViewMatrix.PopMatrix();
    glutSwapBuffers();
}

void KeyBoardEnter(unsigned char key,int a,int b) {
    if (key == 'n') {
        bathType++;
        if (bathType > 1) {
            bathType = 0;
        }
    }
    glutPostRedisplay();
}

// 键盘方向键操作回调
// 控制Object的移动，从而改变视口，这里是对物体坐标系进行旋转
void SpecialKey(int key, int x, int y)
{
    //上下方向键绕X轴旋转，左右方向键绕Y轴旋转
    switch(key)
    {
        case GLUT_KEY_UP:
            objectFrame.RotateWorld(m3dDegToRad(-5.0), 1.0, 0.0, 0.0);
            objectFrame.TranslateWorld(0.f, 0.05f, 0.f);
            break;
        case GLUT_KEY_DOWN:
            objectFrame.RotateWorld(m3dDegToRad(5.0), 1.0, 0.0, 0.0);
            objectFrame.TranslateWorld(0.f, -0.05f, 0.f);
            break;
        case GLUT_KEY_LEFT:
            objectFrame.RotateWorld(m3dDegToRad(-5.0), 0.0, 1.0, 0.0);
            objectFrame.TranslateWorld(-0.1, 0.f, 0.f);
            break;
        case GLUT_KEY_RIGHT:
            objectFrame.RotateWorld(m3dDegToRad(5.0), 0.0, 1.0, 0.0);
            objectFrame.TranslateWorld(0.1, 0.f, 0.f);
            break;
        default:
        break;
    }
    // 重新刷新window
    glutPostRedisplay();
}
 
// 窗口已更改大小，或刚刚创建。无论哪种情况，我们都需要
// 使用窗口维度设置视口和投影矩阵.
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    
   //3.setPerspective函数的参数是一个从顶点方向看去的视场角度（用角度值表示）
   // 设置透视模式(这里是透视投影，还有一个方法是设置正投影)，初始化其透视矩阵
   viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
   
   //4.把透视矩阵加载到透视矩阵堆栈中
   projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
   
    //modelViewMatrix 矩阵堆栈 加载单元矩阵,这一步可以省略，因为堆栈底部默认就是一个单元矩阵
   modelViewMatrix.LoadIdentity();
}

 
int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    //申请一个颜色缓存区、深度缓存区、双缓存区、模板缓存区
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    //设置window 的尺寸
    glutInitWindowSize(800, 600);
    //创建window的名称
    glutCreateWindow("GL_TRIANGLES");
    //注册回调函数（改变尺寸）
    glutReshapeFunc(ChangeSize);
    //特殊键位函数（上下左右）控制旋转
    glutSpecialFunc(SpecialKey);
    
    glutKeyboardFunc(KeyBoardEnter);
    //显示函数
    glutDisplayFunc(RenderScene);
    
    //判断一下是否能初始化glew库，确保项目能正常使用OpenGL 框架
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    //绘制
    SetupRC();
    
    //runloop运行循环
    glutMainLoop();
    return 0;
}
