//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/31.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

varying float textureCoordinate;
uniform sampler1D colorTable;

void main(void)
{
    // 第一个参数代表图片纹理，第二个参数代表纹理坐标点，通过GLSL的内建函数texture2D来获取对应位置纹理的颜色RGBA值
    gl_FragColor = texture1D(colorTable, textureCoordinate);
}
