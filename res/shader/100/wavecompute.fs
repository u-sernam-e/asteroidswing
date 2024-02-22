#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Custom variables
uniform vec2 screenSize;
uniform float frameTime;

uniform float energyLoss;
uniform int fluidSquareSize;

#define MAX_SQUARE_SIZE 51
#define MAX_DISTURBANCES 20

uniform vec4 disturbances[MAX_DISTURBANCES]; // x and y are coordinates, z is amount (0.5 is no energy, 0-1), w is radius of disturbance
uniform int numDisturbances;

// global variable
vec4 texelColor;

int min(const int a, const int b)
{
    if (a < b)
        return a;
    return b;
}

float newVelocity()
{
    float totalDist=0.0;
    float totalEnergy=0.0;

    int actualSquareSize=min(fluidSquareSize, MAX_SQUARE_SIZE);

    for (int x=0; x < MAX_SQUARE_SIZE; ++x)
    {
        if (x == actualSquareSize)
            break;

        for (int y=0; y < MAX_SQUARE_SIZE; ++y)
        {
            if (y == actualSquareSize)
                break;

            vec2 coord = vec2(fragTexCoord.x + float(fluidSquareSize/2 - x)/screenSize.x, fragTexCoord.y + float(fluidSquareSize/2 - y)/screenSize.y);

            float dist = distance(fragTexCoord, coord);

            if (dist != 0.0)
            {
                if (coord.x > 0.0 && coord.x < 1.0 && coord.y > 0.0 && coord.y < 1.0)
                {
                    totalDist += 1.0/dist;
                    totalEnergy += (texture2D(texture0, coord) * fragColor * colDiffuse).r/dist;
                }
                else
                {
                    //totalDist += 1/dist;
                    //totalEnergy += (0.5f)/dist;
                }
            }
        }
    }

    float heightDifference = (totalEnergy/totalDist) - texelColor.r;

    float gravity = energyLoss * 0.01;
    if (texelColor.r > 0.5)
        gravity = -gravity;

    return (texelColor.g + (gravity + heightDifference)*60.0*frameTime)*(1.0 - frameTime) - 0.5;

    
}

int getDisturbanceIndex() //returns -1 if coord is not a disturbance
{
    int actualDisturbances=min(numDisturbances, MAX_DISTURBANCES);

    for (int i=0; i < MAX_DISTURBANCES; ++i)
    {
        if (i == actualDisturbances)
            break;
        if (distance(fragTexCoord * screenSize, vec2(disturbances[i].x, disturbances[i].y)) < disturbances[i].w)
            return i;
    }

    return -1;
}

float getDisturbanceAmount()
{
    int actualDisturbances=min(numDisturbances, MAX_DISTURBANCES);

    for (int i=0; i < MAX_DISTURBANCES; ++i)
    {
        if (i == actualDisturbances)
            break;
        if (distance(fragTexCoord * screenSize, vec2(disturbances[i].x, disturbances[i].y)) < disturbances[i].w)
            return disturbances[i].z * frameTime;
    }

    return 0.0;
}

void main()
{
    // Texel color fetching from texture sampler
    texelColor = texture2D(texture0, fragTexCoord) * fragColor * colDiffuse;

    // computations
    float velocity = newVelocity();
    int disturbanceIndex = getDisturbanceIndex();

    if (disturbanceIndex != -1)
        velocity += getDisturbanceAmount();

    float height = texelColor.r + velocity * 10.0 * frameTime;

    if (height > 1.0)
        height = 1.0;
    if (height < 0.0)
        height = 0.0;

    gl_FragColor = vec4(height, velocity + 0.5, 0, 1);
}