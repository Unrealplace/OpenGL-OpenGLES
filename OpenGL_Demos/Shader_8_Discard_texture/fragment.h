//
//  fragment.h
//  OpenGL_Demos
//
//  Created by mpm on 2020/7/31.
//  Copyright © 2020 mpm. All rights reserved.
//

#version 120

uniform vec4      ambientColor;
uniform vec4      diffuseColor;
uniform vec4      specularColor;
uniform sampler2D cloudTexture;
uniform float dissolveFactor;

varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;
varying vec2 vTexCoords;

void main(void)
{
    vec4 vCloudSample = texture2D(cloudTexture,vTexCoords);
    
    if(vCloudSample.r < dissolveFactor)
        discard;
    
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));
    
    // Multiply intensity by diffuse color, force alpha to 1.0
    vec4 vFragColor = diff * diffuseColor;
    
    // Add in ambient light
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

