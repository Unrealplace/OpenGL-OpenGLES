//
//  vertex.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/22.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

attribute vec4 vVertex;
attribute vec3 vNormal;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

varying vec4 vVaryingColor;

void main(void){

    // 获取表面法线的视觉坐标
    vec3 vEyeNormal = normalMatrix * vNormal;
    // 获取顶点位置的视觉坐标
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
    // 获取到光源的向量
    vec3 vLightDir = normalize(vLightPosition - vPosition3);
    // 向量点乘得到漫反射光照强度 0-1
    float diff = max(0.0,dot(vEyeNormal,vLightDir));

    // 用强度乘以漫反射光
    vVaryingColor = diff * diffuseColor;
    // 添加环境光
    vVaryingColor += ambientColor;
    // 镜面光
    vec3 vReflection = normalize(reflect(-vLightDir,vEyeNormal));
    float spec = max(0.0,dot(vEyeNormal,vReflection));
    if(diff != 0) {
        float fspec = pow(spec,128.0);
        vVaryingColor.rgb += vec3(fspec,fspec,fspec);
    }

    gl_Position = mvpMatrix * vVertex;

}
