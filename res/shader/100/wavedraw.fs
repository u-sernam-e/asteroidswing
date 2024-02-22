#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D waveData;
uniform vec4 colDiffuse;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord);
    vec4 texelWaveColor = texture2D(waveData, fragTexCoord);

    //finalColor = vec4(1, 1, 1, texelColor.g);

    //if (fragTexCoord.x > .5)

    gl_FragColor = vec4(texelColor.r, texelColor.g, texelColor.b, texelWaveColor.r*2.0);
}