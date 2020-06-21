#include "GLShaderManager.h"
#include "GLTools.h"
#include "GLFrame.h"
#include "GLFrustum.h"
#include "GLMatrixStack.h"
#include "GLGeometryTransform.h"
#include <glut/glut.h>

// 存储着色器管理工具类
GLShaderManager     shaderManager;
// 投影矩阵堆栈
GLMatrixStack       modelViewMatrix;
// 模型视图矩阵堆栈
GLMatrixStack       projectionMatrix;
// 设置观察者坐标
GLFrame             cameraFrame;
// 设置图形环绕时，视图坐标
GLFrame             objectFrame;
//设置图片绘制时的投影方式
GLFrustum           viewFrustum;
//容器类
GLBatch             triangleBatch;
//几何变换的管道
GLGeometryTransform transformPipeLine;

//一个黑色 一个绿色
GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
 
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
    //把相机往后移，要不然可能会看不到图，感兴趣的可以改改数值就懂了是啥意思了。
    cameraFrame.MoveForward(-15);
    //通过三角形创建金字塔
    GLfloat vPyramid[12][3] = {
        //背面的三角形的三个点坐标
        -2.0f, 0.0f, -2.0f,
        2.0f, 0.0f, -2.0f,
        0.0f, 4.0f, 0.0f,
        //右边的三角形的三个点坐标
        2.0f, 0.0f, -2.0f,
        2.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,
        //正面的三角形的三个点坐标
        2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,
        //左边的三角形的三个点坐标
        -2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, -2.0f,
        0.0f, 4.0f, 0.0f,
    };
    triangleBatch.Begin(GL_TRIANGLES, 12);
    triangleBatch.CopyVertexData3f(vPyramid);
    triangleBatch.End();
    
}

// 召唤场景
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix();
    
    M3DMatrix44f camera;
    cameraFrame.GetCameraMatrix(camera);
    modelViewMatrix.MultMatrix(camera);
    
    
    M3DMatrix44f obj;
    objectFrame.GetMatrix(obj);
    modelViewMatrix.MultMatrix(obj);
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT,transformPipeLine.GetModelViewProjectionMatrix(),vGreen);
    triangleBatch.Draw();
    
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
    glLineWidth(2.5f);
    
    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
     --transformPipeline.GetModelViewProjectionMatrix() 获取的
     GetMatrix函数就可以获得矩阵堆栈顶部的值
     参数3：颜色值（黑色）
     */
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeLine.GetModelViewProjectionMatrix(), vBlack);
    triangleBatch.Draw();
    
    // 复原原本的设置
    ////通过调用glPolygonMode将多边形正面或者背面设为全部填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    
    
    modelViewMatrix.PopMatrix();
    glutSwapBuffers();
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
 
// 窗口已更改大小，或刚刚创建。无论哪种情况，我们都需要
// 使用窗口维度设置视口和投影矩阵.
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    //设置投影矩阵
    viewFrustum.SetPerspective(35, float(w)/float(h), 1, 500);
    //加载投影矩阵
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    //加载单元矩阵
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
