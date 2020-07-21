//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/21.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120
uniform vec4 vColorValue;

void main(void) {
    gl_FragColor = vColorValue;
}
