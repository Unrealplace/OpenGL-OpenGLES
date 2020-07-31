//
//  vertex.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/31.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

attribute vec4 vVertex;
attribute vec3 vNormal;
attribute vec2 vTexture0;

uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;
varying vec2 vTexCoords;

void main(void){
    
    vVaryingNormal = normalMatrix * vNormal;
    // 获取顶点位置的视觉坐标
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
    // 获取到光源的向量
    vVaryingLightDir = normalize(vLightPosition - vPosition3);
    vTexCoords = vTexture0;

    gl_Position = mvpMatrix * vVertex;
}
