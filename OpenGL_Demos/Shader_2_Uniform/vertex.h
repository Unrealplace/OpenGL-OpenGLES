//
//  vertex.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/21.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120
uniform mat4 mvpMatrix;

attribute vec4 vVertex;

void main(void) {
    gl_Position = mvpMatrix * vVertex;
}
