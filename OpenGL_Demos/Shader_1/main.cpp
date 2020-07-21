// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include <stdarg.h>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

GLBatch    triangleBatch;
GLShaderManager    shaderManager;

GLint    myIdentityShader;

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
    
//    int j=0;
//    va_list arg_ptr;
//    va_start(arg_ptr, i);
//    printf("&i = %p\n", &i);//打印参数i在堆栈中的地址
//    printf("arg_ptr = %p\n", arg_ptr);//打印va_start之后arg_ptr地址
//    /*这时arg_ptr应该比参数i的地址高sizeof(int)个字节,即指向下一个参数的地址*/
//    j=*((int *)arg_ptr);
//    printf("%d %d\n", i, j);
//    j=va_arg(arg_ptr, int);
//    printf("arg_ptr = %p\n", arg_ptr);//打印va_arg后arg_ptr的地址
//    /*这时arg_ptr应该比参数i的地址高sizeof(int)个字节,即指向下一个参数的地址,如果已经是最后一个参数，arg_ptr会为NULL*/
//    va_end(arg_ptr);
//    printf("%d %d\n", i, j);
//
    
    
    /*
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
     */
    
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
}


///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context.
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
    // Blue background
    glClearColor(0.7f, 0.6f, 0.0f, 1.0f );
    
    shaderManager.InitializeStockShaders();
    
    // Load up a triangle
    GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 1.f, 0.0f };
    
    GLfloat vColors [] = { 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f };
    
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.CopyColorData4f(vColors);
    triangleBatch.End();
    
    myIdentityShader = LoadShaders("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_1/vertex.h", "/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_1/fragment.h",2,GLT_ATTRIBUTE_VERTEX,"vVertex",GLT_ATTRIBUTE_COLOR,"vColor");
    
//    myIdentityShader = gltLoadShaderPairWithAttributes("/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_1/vertex.h", "/Users/mpm/OpenGL-OpenGLES/OpenGL_Demos/Shader_1/fragment.h", 2,
//
//                                                       GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_COLOR, "vColor");
    
    GLint locTime,locIndex,locColor,locFlag;
    locTime = glGetUniformLocation(myIdentityShader,"fTime");
    locIndex = glGetUniformLocation(myIdentityShader,"iIndex");
    locColor = glGetUniformLocation(myIdentityShader,"vColorValue");
    locFlag = glGetUniformLocation(myIdentityShader,"bSomeFlag");
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup
void ShutdownRC()
{
    glDeleteProgram(myIdentityShader);
    
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glUseProgram(myIdentityShader);
    triangleBatch.Draw();
    
    // Perform the buffer swap to display back buffer
    glutSwapBuffers();
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