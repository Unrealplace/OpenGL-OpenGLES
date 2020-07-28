//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/28.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;

void main(void){
    
    float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));
    
    vec4 vFragColor = diff * diffuseColor;
    
    vFragColor += ambientColor;
    
    // Specular Light
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
        float fSpec = pow(spec, 128.0);
        vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
    }
    
    gl_FragColor = vFragColor;
}
