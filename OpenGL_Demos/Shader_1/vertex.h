// The ShadedIdentity Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

attribute vec4 vColor;
attribute vec4 vVertex;

varying vec4 vVaryingColor;

void main(void)
{
    vVaryingColor = vColor;
    gl_Position = vVertex;
}



/**
 在编译ShadedTriangle 程序的时候，出现着色器部分报错。

 错误如下。

 ERROR: 0:5: '' :  version '330' is not supported


 在网上搜了一下解决方案，解决方法是让修改为

 #version 120


 但之后会出现

 ERROR: 0:7: Invalid storage qualifiers 'in' in global variable context

 ERROR: 0:8: Invalid storage qualifiers 'in' in global variable context

 ERROR: 0:10: Invalid storage qualifiers 'out' in global variable context

 ERROR: 0:14: Use of undeclared identifier 'vVaryingColor'

 ERROR: 0:14: Use of undeclared identifier 'vColor'

 ERROR: 0:15: Use of undeclared identifier 'vVertex'

 后来百度发现是因为 version 120 版本还没有使用 in out ， 需要将in out 改为对应 attribute varying。

 修改后代码如下 ：

 // The ShadedIdentity Shader

 // Vertex Shader

 // Richard S. Wright Jr.

 // OpenGL SuperBible

 #version 120


 attribute vec4 vColor;

 attribute vec4 vVertex;


 varying vec4 vVaryingColor;


 void main(void)

 {

     vVaryingColor = vColor;

     gl_Position = vVertex;

 }

 // The ShadedIdentity Shader

 // Fragment Shader

 // Richard S. Wright Jr.

 // OpenGL SuperBible

 #version 120


 varying vec4 vVaryingColor;


 void main(void)

 {

    gl_FragColor = vVaryingColor;

 }
 
 ————————————————
 版权声明：本文为CSDN博主「IkeShy_Zz」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
 原文链接：https://blog.csdn.net/u013993254/java/article/details/62047417
 */
