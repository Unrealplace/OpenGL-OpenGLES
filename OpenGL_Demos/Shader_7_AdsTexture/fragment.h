//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/28.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

uniform vec4      ambientColor;
uniform vec4      diffuseColor;
uniform vec4      specularColor;
uniform sampler2D colorMap;

varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;
varying vec2 vTexCoords;

void main(void)
{
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));
    
    // Multiply intensity by diffuse color, force alpha to 1.0
    vec4 vFragColor = diff * diffuseColor;
    
    // Add in ambient light
    vFragColor += ambientColor;
    
    // Modulate in the texture
    vFragColor *= texture2D(colorMap, vTexCoords);
    
    // Specular Light
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
        float fSpec = pow(spec, 128.0);
        vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
    }
    
    gl_FragColor = vFragColor;
}

