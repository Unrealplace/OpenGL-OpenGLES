//
//  vertex.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/28.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

attribute vec4 vVertex;
attribute vec3 vTexCoords;

varying vec3 vVaryingTexCoords;

void main(void){
    
    vVaryingTexCoords = vTexCoords;
    gl_Position = vVertex;
}

