//
//  main.cpp
//  rotate_object
//
//  Created by mpm on 2020/7/1.
//  Copyright © 2020 mpm. All rights reserved.
//

#include <iostream>
#include <GLTools.h>    // OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#define NUM_SPHERES 50
GLFrame spheres[NUM_SPHERES];

GLShaderManager        shaderManager;
GLMatrixStack        modelViewMatrix;
GLMatrixStack        projectionMatrix;
GLFrustum            viewFrustum;
GLGeometryTransform    transformPipeline;

GLTriangleBatch        torusBatch;
GLBatch                floorBatch;
GLTriangleBatch     sphereBatch;
GLFrame             cameraFrame;

void SetupRC()
{
    //初始化存储着色器
    shaderManager.InitializeStockShaders();
    //开启深度测试，防止图元重叠
    glEnable(GL_DEPTH_TEST);
    //设置背景颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //创建一个花环将顶点存在torusBatch中
    gltMakeTorus(torusBatch, 0.4f, 0.15f, 30, 30);
    //创建一个球体将顶点存在sphereBatch中
    gltMakeSphere(sphereBatch, 0.1f, 26, 13);
    //创建一个以线段的网状的地面，共324个顶点
    floorBatch.Begin(GL_LINES, 324);
    //存储顶点
    for(GLfloat x = -20.0; x <= 20.0f; x+= 0.5) {
        floorBatch.Vertex3f(x, -0.55f, 20.0f);
        floorBatch.Vertex3f(x, -0.55f, -20.0f);
        
        floorBatch.Vertex3f(20.0f, -0.55f, x);
        floorBatch.Vertex3f(-20.0f, -0.55f, x);
    }
    floorBatch.End();
    // 球体的变换位置
    for(int i = 0; i < NUM_SPHERES; i++) {
        GLfloat x = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        GLfloat z = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        spheres[i].SetOrigin(x, 0.0f, z);
    }
}

void ChangeSize(int nWidth, int nHeight)
{
    //视口变换，转换成设备坐标
    glViewport(0, 0, nWidth, nHeight);
    //进行透视投影变换
    viewFrustum.SetPerspective(35.0f, float(nWidth)/float(nHeight), 1.0f, 100.0f);
    //堆栈矩阵，将投影变换后的投影矩阵与projectionMatrix堆栈的顶部矩阵相乘得到新的矩阵放入projectionMatrix堆栈顶部
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    //管理管线，通过modelViewMatrix和projectionMatrix指针指向堆栈矩阵的顶部
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene(void)
{
    // 颜色顶点
    static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};
    static GLfloat vTorusColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    static GLfloat vSphereColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    
//    static CStopWatch    rotTimer;
//    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    float yRot = 0.f;

    // 清理缓冲区和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // 保存当前矩阵到顶部这里保存到里面的是单位矩阵
    modelViewMatrix.PushMatrix();
    // 4x4矩阵
    M3DMatrix44f mCamera;
    //得到一个照相机角色帧
    cameraFrame.GetCameraMatrix(mCamera);
    //保存角色帧到堆栈顶部
    modelViewMatrix.PushMatrix(mCamera);
    
    // 点光源的顶点
    M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
    M3DVector4f vLightEyePos;
    // 将点光源的顶点和照相机的位置相乘转换成视觉坐标系
    m3dTransformVector4(vLightEyePos, vLightPos, mCamera);
    
    //通过平面存储着色器将空间坐标转换为平面坐标
    //transformPipeline.GetModelViewProjectionMatrix() 管理管线通过transformPipeline得到projectionMatrix堆栈顶部的矩阵
    shaderManager.UseStockShader(GLT_SHADER_FLAT,
                                 transformPipeline.GetModelViewProjectionMatrix(),
                                 vFloorColor);
     //绘制地面
    floorBatch.Draw();
    //遍历之前在spheres中地面的顶点坐标
    for(int i = 0; i < NUM_SPHERES; i++) {
        //保存当前矩阵到堆栈
        modelViewMatrix.PushMatrix();
        //将顶点坐标转换为矩阵并存在modelViewMatrix堆栈顶部
        modelViewMatrix.MultMatrix(spheres[i]);
        //通过点光源存储着色器将空间坐标转换为平面坐标,这里存储着色器好做了将管理管线中的模型视图矩阵和投影矩阵变换成模型视图投影矩阵的操作
        shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                     transformPipeline.GetProjectionMatrix(), vLightEyePos, vSphereColor);
        //绘制球体
        sphereBatch.Draw();
        //清除顶部矩阵
        modelViewMatrix.PopMatrix();
    }
    
    // 模型视图变换缩放变换
    modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
    
    // 保存当前变换后的模型视图矩阵到堆栈矩阵顶部
    modelViewMatrix.PushMatrix();
    
    // 模型视图变换旋转变换
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    //通过点光源存储着色器将空间坐标转换为平面坐标,这里存储着色器好做了将管理管线中的模型视图矩阵和投影矩阵变换成模型视图投影矩阵的操作
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vTorusColor);
    //绘制圆环
    torusBatch.Draw();
    //清除顶部矩阵
    modelViewMatrix.PopMatrix();
    
    // 模型试图变换旋转变换
    modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    // 模型视图变换平移变换
    modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
    //通过点光源存储着色器将空间坐标转换为平面坐标,这里存储着色器好做了将管理管线中的模型视图矩阵和投影矩阵变换成模型视图投影矩阵的操作
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vSphereColor);
    //绘制球体
    sphereBatch.Draw();
    
    // 清除顶部矩阵
    modelViewMatrix.PopMatrix();
    //清除顶部矩阵
    modelViewMatrix.PopMatrix();
    // 交换前后台缓存区数据
    glutSwapBuffers();
    
    glutPostRedisplay();
}

// 通过键盘上下左右控制照相机的位置，已达到场景位置的改变
void SpecialKeys(int key, int x, int y)
{
    float linear = 0.1f;
    float angular = float(m3dDegToRad(5.0f));
    if(key == GLUT_KEY_UP)
        cameraFrame.MoveForward(linear);
    if(key == GLUT_KEY_DOWN)
        cameraFrame.MoveForward(-linear);
    if(key == GLUT_KEY_LEFT)
        cameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
    if(key == GLUT_KEY_RIGHT)
        cameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGL SphereWorld");
    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    SetupRC();
    glutMainLoop();
    return 0;
}
