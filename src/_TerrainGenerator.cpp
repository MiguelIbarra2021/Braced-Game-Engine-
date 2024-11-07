#include "_TerrainGenerator.h"

_TerrainGenerator::_TerrainGenerator()
{
    //ctor
}

_TerrainGenerator::~_TerrainGenerator()
{
    //dtor
}

GLvoid _TerrainGenerator::initTerrain(char* file)
{
    // Load Terrain Textures
    tex->loadTexture(file);

    // Initalize Variables
    t_max.x = t_max.y = 1.0;
    t_min.x = t_min.y = 0.0;
}

GLvoid _TerrainGenerator::drawTerrain()
{
    // Apply Transforms
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1,0,0);
    glRotatef(rotation.y, 0,1,0);
    glRotatef(rotation.z,0,0,1);

    glDisable(GL_LIGHTING);

    // Initalize Floor Plane
    tex->bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(t_max.x, t_max.y);
            glVertex3f(-1.0,-1.0,1.0);
        glTexCoord2f(t_min.x, t_max.y);
            glVertex3f(1.0,-1.0,1.0);
        glTexCoord2f(t_min.x, t_min.y);
            glVertex3f(1.0,-1.0,-1.0);
        glTexCoord2f(t_max.x, t_min.y);
            glVertex3f(-1.0,-1.0,-1.0);
    glEnd();

    glEnable(GL_LIGHTING);
}
