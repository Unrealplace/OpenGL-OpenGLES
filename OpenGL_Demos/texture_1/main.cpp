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

GLShaderManager        shaderManager;
GLMatrixStack        modelViewMatrix;
GLMatrixStack        projectionMatrix;
GLFrustum            viewFrustum;
GLGeometryTransform    transformPipeline;

GLBatch pyramidBath;
GLFrame             cameraFrame;
GLFrame  objectFrame;
GLuint textureID;

// 将TGA文件加载为2D纹理。
bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    GLbyte *pBits;
    int nWidth, nHeight, nComponents;
    GLenum eFormat;
    
    //1、读纹理位，读取像素
    /*
    参数1：纹理文件名称
    参数2：文件宽度地址
    参数3：文件高度地址
    参数4：文件组件地址
    参数5：文件格式地址
    返回值：pBits,指向图像数据的指针
    */
    pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
    if(pBits == NULL)
        return false;
    
    //2、设置纹理参数
    /*
    参数1：纹理维度
    参数2：为S/T坐标设置模式
    参数3：wrapMode,环绕模式
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    
    /*
    参数1：纹理维度
    参数2：线性过滤
    参数3：wrapMode,过滤模式
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    

    //3.载入纹理
    /*
    参数1：纹理维度
    参数2：mip贴图层次
    参数3：纹理单元存储的颜色成分（从读取像素图是获得）
    参数4：加载纹理宽
    参数5：加载纹理高
    参数6：加载纹理的深度
    参数7：像素数据的数据类型（GL_UNSIGNED_BYTE，每个颜色分量都是一个8位无符号整数）
    参数8：指向纹理图像数据的指针
    */
    glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
                 eFormat, GL_UNSIGNED_BYTE, pBits);
    
    //使用完毕释放pBits
    free(pBits);
    
    //4.加载Mip,纹理生成所有的Mip层
    //参数：GL_TEXTURE_1D、GL_TEXTURE_2D、GL_TEXTURE_3D
    glGenerateMipmap(GL_TEXTURE_2D);
 
    return true;
}

void MakePyramid(GLBatch& pyramidBath) {
    pyramidBath.Begin(GL_TRIANGLES, 18, 1);
    
    M3DVector3f vApex = {0.f,1.f,0.f};
    M3DVector3f vBackLeft = {-1.f,-1.f,-1};
    M3DVector3f vBackRight = {1.f,-1.f,-1};
    M3DVector3f vFrontLeft = {-1.f,-1.f,1.f};
    M3DVector3f vFrontRight = {1.f,-1.f,1};
    
    // 法线
    M3DVector3f n;

    // 三角形A
    m3dFindNormal(n, vBackLeft, vBackRight, vFrontRight);
    // vBackRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 0.f);
    pyramidBath.Vertex3fv(vBackLeft);
    
    // vBackRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 0.f);
    pyramidBath.Vertex3fv(vBackRight);
    
    // vFrontRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 1.f);
    pyramidBath.Vertex3fv(vFrontRight);
    
    
    //三角形B
    m3dFindNormal(n, vFrontRight, vBackLeft, vFrontLeft);
    //vFrontLeft
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 1.f);
    pyramidBath.Vertex3fv(vFrontLeft);
    
    //vBackLeft
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 0.f);
    pyramidBath.Vertex3fv(vBackLeft);
    
    //vFrontRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 1.f);
    pyramidBath.Vertex3fv(vFrontRight);
    
    // 金字塔前面
    m3dFindNormal(n, vApex, vFrontLeft, vFrontRight);
    //vApex
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.5f, 1.f);
    pyramidBath.Vertex3fv(vApex);
    
    //vFrontLeft
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 0.f);
    pyramidBath.Vertex3fv(vFrontLeft);
    
    //vFrontRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 0.f);
    pyramidBath.Vertex3fv(vFrontRight);
    
    
    // 金字塔左面
    m3dFindNormal(n, vApex, vBackLeft, vFrontLeft);
    //vApex
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.5f, 1.f);
    pyramidBath.Vertex3fv(vApex);
    
    //vFrontLeft
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 0.f);
    pyramidBath.Vertex3fv(vFrontLeft);
    
    //vBackLeft
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 0.f);
    pyramidBath.Vertex3fv(vBackLeft);
    
    
    // 金字塔右面
    m3dFindNormal(n, vApex, vBackRight, vFrontRight);
    //vApex
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.5f, 1.f);
    pyramidBath.Vertex3fv(vApex);
    
    //vBackRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 0.f);
    pyramidBath.Vertex3fv(vBackRight);
    
    //vFrontRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 0.f);
    pyramidBath.Vertex3fv(vFrontRight);
    
    // 金字塔背面
    m3dFindNormal(n, vApex, vBackRight, vBackLeft);
    //vApex
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.5f, 1.f);
    pyramidBath.Vertex3fv(vApex);
    
    //vBackRight
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 1.f, 0.f);
    pyramidBath.Vertex3fv(vBackRight);
    
    //vBackLeft
    pyramidBath.Normal3fv(n);
    pyramidBath.MultiTexCoord2f(0, 0.f, 0.f);
    pyramidBath.Vertex3fv(vBackLeft);
    
    pyramidBath.End();
}

void SetupRC()
{
    //初始化存储着色器
    shaderManager.InitializeStockShaders();
    //开启深度测试，防止图元重叠
    glEnable(GL_DEPTH_TEST);
    //设置背景颜色
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    //生成纹理
    glGenTextures(1, &textureID);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    LoadTGATexture("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/texture_1/stone.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
    
    MakePyramid(pyramidBath);
    
    cameraFrame.MoveForward(-7.0f);
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
    // 清理缓冲区和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // 保存当前矩阵到顶部这里保存到里面的是单位矩阵
    modelViewMatrix.PushMatrix();
    // 4x4矩阵
    M3DMatrix44f mCamera;
    //得到一个照相机角色帧
    cameraFrame.GetCameraMatrix(mCamera);
    //保存角色帧到堆栈顶部
    modelViewMatrix.MultMatrix(mCamera);
    
    M3DMatrix44f mObjectFrame;
    objectFrame.GetMatrix(mObjectFrame);
    modelViewMatrix.MultMatrix(mObjectFrame);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
     //1.颜色值&光源位置
        static GLfloat vLightPos [] = { 1.0f, 1.0f, 0.0f };
        static GLfloat vWhite [] = { 1.0f, 1.0f, 1.0f, 1.0f };

    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
                                    transformPipeline.GetModelViewMatrix(),
                                    transformPipeline.GetProjectionMatrix(),
                                    vLightPos, vWhite, 0);
    
    //绘制圆环
    pyramidBath.Draw();
    //清除顶部矩阵
    modelViewMatrix.PopMatrix();
    // 交换前后台缓存区数据
    glutSwapBuffers();
    
//    glutPostRedisplay();
}

// 通过键盘上下左右控制照相机的位置，已达到场景位置的改变
void SpecialKeys(int key, int x, int y)
{
   if(key == GLUT_KEY_UP)
       objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
   
   if(key == GLUT_KEY_DOWN)
       objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
   
   if(key == GLUT_KEY_LEFT)
       objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
   
   if(key == GLUT_KEY_RIGHT)
       objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
   
   glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("来看看金字塔");
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
