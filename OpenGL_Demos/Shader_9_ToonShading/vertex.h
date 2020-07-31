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

uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

varying float textureCoordinate;

void main(void){
    
    vec3 vEyeNormal = normalMatrix * vNormal;
    
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
    
    vec3 vLightDir = normalize(vLightPosition - vPosition3);
    
    // 纹理坐标在 0 ~ 1 之间
    textureCoordinate = max(0.0, dot(vEyeNormal, vLightDir));
    
    gl_Position = mvpMatrix * vVertex;
}
