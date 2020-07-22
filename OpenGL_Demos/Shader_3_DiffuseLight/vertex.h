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

uniform vec4 diffuseColor;
uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

varying vec4 vVaryingColor;

void main(void){

    vec3 vEyeNormal = normalMatrix * vNormal;
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
    vec3 vLightDir = normalize(vLightPosition - vPosition3);

    //光照强度
    float diff = max(0.0,dot(vEyeNormal,vLightDir));

    vVaryingColor.rgb = diff * diffuseColor.rgb;
    vVaryingColor.a = diffuseColor.a;

    gl_Position = mvpMatrix * vVertex;
}
