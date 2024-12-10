#ifndef _PARTICLES_H
#define _PARTICLES_H
#include "_Common.h"
#include "_TextureLoader.h"

#define MAX_PARTICLES 100

struct Particle {
    vec3 position;
    vec3 velocity;
    float lifespan;
    float size;
    vec3 color;
};

class _Particles {
public:
    _Particles();
    virtual ~_Particles();

    Particle particles[MAX_PARTICLES];
    int activeParticleCount;
    _TextureLoader textureLoader;

    // Initialize the particle system at a given position
    void init(vec3 position, char* textureFile);
    // Update the particle system (reduce lifespan, move particles)
    void update(float deltaTime);
    // Render the particles
    void draw();
};


#endif // _PARTICLES_H
