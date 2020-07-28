//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/28.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120
uniform sampler2D colorMap;

varying vec3 vVaryingTexCoords;

void main(void){
                   
    gl_FragColor = texture2D(colorMap, vVaryingTexCoords.st);
}
