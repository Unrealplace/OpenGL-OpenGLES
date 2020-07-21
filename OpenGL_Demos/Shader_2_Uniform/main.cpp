// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include <GLTools.h>    // OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLTriangleBatch     torusBatch;
GLMatrixStack       modelViewMatrix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;

GLuint    flatShader;            // The Flat shader

GLint    locMVP;                // The location of the ModelViewProjection matrix uniform
GLint   locColor;            // The location of the color value uniform

GLint LoadShaders(const char * szVertexProg,const char *szFragmentProg,...) {
    GLuint hVertexShader;
    GLuint hFragmentShader;
    GLuint hReturn = 0;
    GLint testVal;
    // 生成顶点片断着色器
    hVertexShader = glCreateShader(GL_VERTEX_SHADER);
    hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //加载顶点着色器文件
    if (gltLoadShaderFile(szVertexProg, hVertexShader) == false) {
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
        
        return (GLint)NULL;
    }
    
    //加载片段着色器文件
    if (gltLoadShaderFile(szFragmentProg, hFragmentShader) == false) {
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
        
        return (GLint)NULL;
    }
    
    // 编译顶点和片段着色器
    glCompileShader(hFragmentShader);
    glCompileShader(hVertexShader);
    
    // 检查顶点着色器的错误
    glGetShaderiv(hVertexShader,GL_COMPILE_STATUS,&testVal);
    if (testVal == GL_FALSE) {
        char infoLog[1024];
        glGetShaderInfoLog(hVertexShader,1024,NULL,infoLog);
        printf("%s",infoLog);
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
        return (GLint)NULL;
    }
    
    // 检查片段着色器的错误
    glGetShaderiv(hFragmentShader,GL_COMPILE_STATUS,&testVal);
    if (testVal == GL_FALSE) {
        char infoLog[1024];
        glGetShaderInfoLog(hFragmentShader,1024,NULL,infoLog);
        printf("%s",infoLog);
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
        return (GLint)NULL;
    }
    
    // 创建最终的程序对象，并链接着色器
    hReturn = glCreateProgram();
    glAttachShader(hReturn,hVertexShader);
    glAttachShader(hReturn,hFragmentShader);
    
    // 绑定属性位置和属性变量
    glBindAttribLocation(hReturn,GLT_ATTRIBUTE_VERTEX,"vVertex");
    glBindAttribLocation(hReturn,GLT_ATTRIBUTE_COLOR,"vColor");

    
    // 链接程序
    glLinkProgram(hReturn);
    glDeleteShader(hVertexShader);
    glDeleteShader(hFragmentShader);
    // 检查链接是否有效
    glGetProgramiv(hReturn,GL_LINK_STATUS,&testVal);
    if (testVal == GL_FALSE) {
        char infoLog[1024];
        glGetProgramInfoLog(hReturn,1024,NULL,infoLog);
        printf("%s",infoLog);
        glDeleteProgram(hReturn);
        return (GLint)NULL;
    }
    

    return hReturn;
}


///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    
    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}


///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context.
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
    // Blue background
    glClearColor(0.7f, 0.6f, 0.0f, 1.0f );
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    viewFrame.MoveForward(4.0f);
    gltMakeTorus(torusBatch, .80f, 0.25f, 52, 26);
    flatShader = LoadShaders("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_2_Uniform/vertex.h", "/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_2_Uniform/fragment.h",2,GLT_ATTRIBUTE_VERTEX,"vVertex",GLT_ATTRIBUTE_COLOR,"vColor");
    
    locMVP = glGetUniformLocation(flatShader,"mvpMatrix");
    locColor = glGetUniformLocation(flatShader,"vColorValue");
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup
void ShutdownRC()
{
    glDeleteProgram(flatShader);
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    static CStopWatch rotTimer;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.f, 0.f, 1.f, 0.f);
    GLfloat colorG = sin(rotTimer.GetElapsedSeconds());
    GLfloat colorB = cos(rotTimer.GetElapsedSeconds());
    GLfloat colorR = cos(rotTimer.GetElapsedSeconds());
    GLfloat vColor[] = {colorR,colorG,colorB,1.0f};
    glUseProgram(flatShader);
    glUniform4fv(locColor,1,vColor);
    glUniformMatrix4fv(locMVP,1,GL_FALSE,transformPipeline.GetModelViewProjectionMatrix());
    torusBatch.Draw();
    modelViewMatrix.PopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

GLvoid PrintVersion()
{
    const GLubyte* name = glGetString(GL_VENDOR);            //返回负责当前OpenGL实现厂商的名字
    const GLubyte* biaoshifu = glGetString(GL_RENDERER);    //返回一个渲染器标识符，通常是个硬件平台
    const GLubyte* OpenGLVersion = glGetString(GL_VERSION);    //返回当前OpenGL实现的版本号
    const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);//返回着色预压编译器版本号
    const GLubyte* gluVersion = gluGetString(GLU_VERSION);    //返回当前GLU工具库版本
    printf("OpenGL实现厂商的名字：%s\n", name);
    printf("渲染器标识符：%s\n", biaoshifu);
    printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
    printf("OpenGL着色语言版本：%s\n", glsl);
    printf("GLU工具库版本：%s\n", gluVersion);
}


///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])

{
    
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Shaded Triangle");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    
    SetupRC();
    
    PrintVersion();
    
    glutMainLoop();
    
    
    ShutdownRC();
    
    return 0;
}
