//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/22.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

varying vec4 vVaryingColor;

void main(void){

    gl_FragColor = vVaryingColor;
}
