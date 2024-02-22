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
uniform vec2 screenSize;
uniform float frameTime;

uniform float energyLoss;
uniform int fluidSquareSize;

#define MAX_DISTURBANCES 20

uniform vec4 disturbances[MAX_DISTURBANCES]; // x and y are coordinates, z is amount (0.5 is no energy, 0-1), w is radius of disturbance
uniform int numDisturbances;

// global variable
vec4 texelColor;

float newVelocity()
{
    float totalDist=0;
    float totalEnergy=0;

    for (int x=0; x < fluidSquareSize; ++x)
    {
        for (int y=0; y < fluidSquareSize; ++y)
        {
            vec2 coord = vec2(fragTexCoord.x + (fluidSquareSize/2 - x)/screenSize.x, fragTexCoord.y + (fluidSquareSize/2 - y)/screenSize.y);

            float dist = distance(fragTexCoord, coord);

            if (dist != 0)
            {
                if (coord.x > 0 && coord.x < 1 && coord.y > 0 && coord.y < 1)
                {
                    totalDist += 1/dist;
                    totalEnergy += (texture(texture0, coord) * fragColor * colDiffuse).r/dist;
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

    return (texelColor.g + (gravity + heightDifference)*60*frameTime)*(1 - frameTime) - 0.5;

    
}

int getDisturbanceIndex() //returns -1 if coord is not a disturbance
{
    int actualDisturbances=numDisturbances;

    if (actualDisturbances > MAX_DISTURBANCES)
        actualDisturbances = MAX_DISTURBANCES;

    for (int i=0; i < actualDisturbances; ++i)
    {
        if (distance(fragTexCoord * screenSize, vec2(disturbances[i].x, disturbances[i].y)) < disturbances[i].w)
            return i;
    }

    return -1;
}

void main()
{
    // Texel color fetching from texture sampler
    texelColor = texture(texture0, fragTexCoord) * fragColor * colDiffuse;

    // computations
    float velocity = newVelocity();
    int disturbanceIndex = getDisturbanceIndex();

    if (disturbanceIndex != -1)
        velocity += disturbances[disturbanceIndex].z * frameTime;

    float height = texelColor.r + velocity * 10 * frameTime;

    if (height > 1)
        height = 1;
    if (height < 0)
        height = 0;

    finalColor = vec4(height, velocity + 0.5, 0, 1);
}