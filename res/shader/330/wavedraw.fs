#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D waveData;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec4 texelWaveColor = texture(waveData, fragTexCoord);

    //finalColor = vec4(1, 1, 1, texelColor.g);

    //if (fragTexCoord.x > .5)

    finalColor = vec4(texelColor.r, texelColor.g, texelColor.b, pow(texelWaveColor.r, 1)*2);
}