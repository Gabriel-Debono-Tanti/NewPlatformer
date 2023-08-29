#version 330 core

uniform sampler2D texture;
uniform vec2 resolution;
uniform float pixelSize;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;
    uv *= vec2(textureSize(texture, 0)) / resolution;
    uv = floor(uv * pixelSize) / pixelSize;

    gl_FragColor = texture2D(texture, uv);
}
