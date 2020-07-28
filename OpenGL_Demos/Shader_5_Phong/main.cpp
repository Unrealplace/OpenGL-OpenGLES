// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include <stdarg.h>
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

GLShaderManager shaderManager;
GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLTriangleBatch     sphereBath;
GLMatrixStack       modelViewMatrix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;

GLuint    diffuseLightShader;

GLint    locMVP;
GLint  locNM;
GLint  locMV;
GLint   locAmbientColor;
GLint locDiffuseColor;
GLint locSpecularColor;
GLint  locLight;


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
    
    
    va_list attributeList;
    va_start(attributeList,szFragmentProg);
    int iArgCount = va_arg(attributeList, int);
    char *szNextArg;
    for (int i = 0; i < iArgCount; i++) {
        int index = va_arg(attributeList, int);
        szNextArg = va_arg(attributeList, char *);
        glBindAttribLocation(hReturn,index,szNextArg);
    }
    va_end(attributeList);
    
    
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
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    shaderManager.InitializeStockShaders();
    viewFrame.MoveForward(4.0f);
    gltMakeSphere(sphereBath, 1.f, 26, 13);
    diffuseLightShader = LoadShaders("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_5_Phong/vertex.h", "/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_5_Phong/fragment.h",2,GLT_ATTRIBUTE_VERTEX,"vVertex",GLT_ATTRIBUTE_NORMAL,"vNormal");
    
    //uniform vec4 ambientColor;
    //uniform vec4 diffuseColor;
    //uniform vec4 specularColor;
    //uniform vec3 vLightPosition;
    //uniform mat4 mvpMatrix;
    //uniform mat4 mvMatrix;
    //uniform mat3 normalMatrix;
    
    locMVP = glGetUniformLocation(diffuseLightShader,"mvpMatrix");
    locDiffuseColor = glGetUniformLocation(diffuseLightShader,"diffuseColor");
    locLight = glGetUniformLocation(diffuseLightShader,"vLightPosition");
    locMV = glGetUniformLocation(diffuseLightShader,"mvMatrix");
    locNM = glGetUniformLocation(diffuseLightShader,"normalMatrix");

    locAmbientColor = glGetUniformLocation(diffuseLightShader,"ambientColor");
    locDiffuseColor = glGetUniformLocation(diffuseLightShader,"specularColor");
    locMV = glGetUniformLocation(diffuseLightShader,"mvMatrix");
    locMV = glGetUniformLocation(diffuseLightShader,"mvMatrix");

}

///////////////////////////////////////////////////////////////////////////////
// Cleanup
void ShutdownRC()
{
    glDeleteProgram(diffuseLightShader);
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    static CStopWatch rotTimer;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.f, 0.f, 1.f, 0.f);
    GLfloat colorG = fmaxf(0.1, sin(rotTimer.GetElapsedSeconds()));
    GLfloat colorB = fmaxf(0.5, cos(rotTimer.GetElapsedSeconds()));
    GLfloat colorR = fmaxf(0.1, cos(rotTimer.GetElapsedSeconds()));
    
    GLfloat alpha = sin(rotTimer.GetElapsedSeconds());
    alpha = fmaxf(0.1, alpha);
    GLfloat vEyeLight[] = {-100.f,100.f,100.f};
    GLfloat vDiffuseColor[] = {colorR,colorG,colorB,0.3};
    
    GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat vSpecularColor[] = { 1.0f, 0.f, 0.f, 1.0f };
    
    glUseProgram(diffuseLightShader);
    glUniform4fv(locDiffuseColor,1,vDiffuseColor);
    glUniform4fv(locAmbientColor,1,vAmbientColor);
    glUniform4fv(locSpecularColor,1,vSpecularColor);

    glUniform3fv(locLight,1,vEyeLight);
    glUniformMatrix4fv(locMV,1,GL_FALSE,transformPipeline.GetModelViewMatrix());
    glUniformMatrix4fv(locMVP,1,GL_FALSE,transformPipeline.GetModelViewProjectionMatrix());
    glUniformMatrix3fv(locNM,1,GL_FALSE,transformPipeline.GetNormalMatrix());

    sphereBath.Draw();
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
