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
#define MAX_POINTS 10

uniform vec2 points[MAX_POINTS];
uniform int numPoints;

uniform float brightness;
uniform float aspectRatio; // 1 means square, larger number means wider

float distanceToLine(vec2 a, vec2 b, vec2 c) // c is the point
{
    float lineDistance;

    float lengthAB = sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y)); // length of AB line
    float angleAB = acos((b.x - a.x)/lengthAB); // angle of AB line

    float lengthAC = sqrt((c.x - a.x)*(c.x - a.x) + (c.y - a.y)*(c.y - a.y)); // length of AC line
    float angleAC = acos((c.x - a.x)/lengthAC); // angle of AC line
    if (b.y > a.y == c.y < a.y)
        angleAC = -angleAC; // this is because it was broken for some reason

    vec2 cRotated = vec2(a.x + cos(angleAC - angleAB) * lengthAC, a.y + sin(angleAC - angleAB) * lengthAC); // c rotated so that AB would be parallel the x axis

    if (cRotated.x < a.x)
        lineDistance = lengthAC;
    else if (cRotated.x > a.x + lengthAB)
        lineDistance = sqrt((c.x - b.x)*(c.x - b.x) + (c.y - b.y)*(c.y - b.y)); // length of BC line
    else
        lineDistance = a.y - cRotated.y;

    if (lineDistance < 0) lineDistance = -lineDistance;

    return lineDistance;
}

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord) * fragColor * colDiffuse;

    // Calculate final fragment color
    int numPointsREAL=numPoints;
    if (numPoints > MAX_POINTS) numPointsREAL = MAX_POINTS;

    vec2 usedPoints[MAX_POINTS];
    float alphaBrightness=0;
    float colorBrightness=0;

    for (int i=0; i < numPointsREAL; i++)
    {
        float distance=distanceToLine(vec2(points[i].x*aspectRatio, points[i].y), vec2(points[(i+1)%numPointsREAL].x*aspectRatio, points[(i+1)%numPointsREAL].y), vec2(fragTexCoord.x*aspectRatio, fragTexCoord.y));// mess with aspect ratio

        alphaBrightness += (brightness*0.0015)/distance - 0.005;
        colorBrightness += (brightness*0.0015)/distance;
    }

    finalColor = vec4(colorBrightness + texelColor.r, colorBrightness + texelColor.g, colorBrightness + texelColor.b, alphaBrightness);
}