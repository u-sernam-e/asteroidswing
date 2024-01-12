#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// Custom variables

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord) * fragColor * colDiffuse;

    vec2 center = vec2(0.5, 0.5);
    float distanceFromCenter = sqrt((center.x - fragTexCoord.x)*(center.x - fragTexCoord.x) + (center.y - fragTexCoord.y)*(center.y - fragTexCoord.y));
    float circleRad = 0.3333;

    // Calculate final fragment color
    float colorMultiplier;

    if (distanceFromCenter < circleRad) // DESMOS!
        colorMultiplier = -distanceFromCenter + 1;
    else
        colorMultiplier = -3*distanceFromCenter + 1.5;

    if (colorMultiplier < 0)
        colorMultiplier = 0;
    
    finalColor = vec4(255, 255, 255, texelColor.a*colorMultiplier);
}