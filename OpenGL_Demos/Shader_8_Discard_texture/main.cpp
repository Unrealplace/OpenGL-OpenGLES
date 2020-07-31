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

GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLTriangleBatch     sphereBatch;
GLMatrixStack       modelViewMatrix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;

GLuint    ADSTextureShader;    // The textured diffuse light shader
GLint    locAmbient;            // The location of the ambient color
GLint   locDiffuse;            // The location of the diffuse color
GLint   locSpecular;        // The location of the specular color
GLint    locLight;            // The location of the Light in eye coordinates
GLint    locMVP;                // The location of the ModelViewProjection matrix uniform
GLint    locMV;                // The location of the ModelView matrix uniform
GLint    locNM;                // The location of the Normal matrix uniform
GLint   locTexture;
GLuint  texture;
GLint   locDissolveFactor;  // The location of the dissolve factor

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

bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    GLbyte *pBits;
    int nWidth, nHeight, nComponents;
    GLenum eFormat;
    
    // Read the texture bits
    pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
    if(pBits == NULL)
        return false;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
                 eFormat, GL_UNSIGNED_BYTE, pBits);
    
    free(pBits);
    
    if(minFilter == GL_LINEAR_MIPMAP_LINEAR ||
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);
    
    return true;
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
    gltMakeSphere(sphereBatch, 1.f, 26, 13);
    ADSTextureShader = LoadShaders("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_8_Discard_texture/vertex.h", "/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_8_Discard_texture/fragment.h",3,GLT_ATTRIBUTE_VERTEX,"vVertex",GLT_ATTRIBUTE_NORMAL,"vNormal",GLT_ATTRIBUTE_TEXTURE0,"vTexture0");
    
    locAmbient = glGetUniformLocation(ADSTextureShader, "ambientColor");
    locDiffuse = glGetUniformLocation(ADSTextureShader, "diffuseColor");
    locSpecular = glGetUniformLocation(ADSTextureShader, "specularColor");
    locLight = glGetUniformLocation(ADSTextureShader, "vLightPosition");
    locMVP = glGetUniformLocation(ADSTextureShader, "mvpMatrix");
    locMV  = glGetUniformLocation(ADSTextureShader, "mvMatrix");
    locNM  = glGetUniformLocation(ADSTextureShader, "normalMatrix");
    locTexture = glGetUniformLocation(ADSTextureShader, "cloudTexture");
    locDissolveFactor = glGetUniformLocation(ADSTextureShader, "dissolveFactor");
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    LoadTGATexture("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_7_AdsTexture/CoolTexture.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup
void ShutdownRC()
{
    glDeleteProgram(ADSTextureShader);
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    static CStopWatch rotTimer;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f, 0.0f, 1.0f, 0.0f);
    
    GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
    GLfloat vAmbientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat vDiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(ADSTextureShader);
    glUniform4fv(locAmbient, 1, vAmbientColor);
    glUniform4fv(locDiffuse, 1, vDiffuseColor);
    glUniform4fv(locSpecular, 1, vSpecularColor);
    glUniform3fv(locLight, 1, vEyeLight);
    glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    glUniformMatrix4fv(locMV, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
    glUniformMatrix3fv(locNM, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
    glUniform1i(locTexture, 0);
    float fFactor = fmod(rotTimer.GetElapsedSeconds(), 10.0f);
    fFactor /= 10.0f;
    glUniform1f(locDissolveFactor, fFactor);
    sphereBatch.Draw();
    
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
