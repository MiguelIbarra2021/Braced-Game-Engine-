#include "_Particles.h"

_Particles::_Particles()
{
    //ctor
}

_Particles::~_Particles()
{
    //dtor
}

void _Particles::init(vec3 position, char* textureFile) {
    // Load the texture
    textureLoader.loadTexture(textureFile);

    srand(static_cast<unsigned>(time(0))); // Seed for randomness
    activeParticleCount = MAX_PARTICLES;
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        particles[i].position = position;

        // Assign velocity component-wise
        particles[i].velocity.x = (rand() % 200 - 100) / 100.0f;
        particles[i].velocity.y = (rand() % 200 - 100) / 100.0f;
        particles[i].velocity.z = (rand() % 200 - 100) / 100.0f;

        particles[i].lifespan = 1.0f + (rand() % 100) / 100.0f;
        particles[i].size = 0.2f + (rand() % 50) / 100.0f;

        // Assign color component-wise
        particles[i].color.x = 1.0f; // Red
        particles[i].color.y = 0.5f; // Green
        particles[i].color.z = 0.0f; // Blue
    }

}

    // Update the particle system (reduce lifespan, move particles)
void _Particles::update(float deltaTime)  {
    for (int i = 0; i < activeParticleCount; ++i) {
        if (particles[i].lifespan > 0) {
            particles[i].lifespan -= deltaTime;

            // Update position component-wise
            particles[i].position.x += particles[i].velocity.x * deltaTime;
            particles[i].position.y += particles[i].velocity.y * deltaTime;
            particles[i].position.z += particles[i].velocity.z * deltaTime;
        } else {
            particles[i].lifespan = 0; // Ensure lifespan doesn't go negative
        }
    }
}

// Render the particles
void _Particles::draw() {
    // Enable texture and blending for particles
    glEnable(GL_TEXTURE_2D);
    textureLoader.bindTexture(); // Bind the loaded texture

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    for (int i = 0; i < activeParticleCount; ++i) {
        if (particles[i].lifespan > 0) {
            float alpha = particles[i].lifespan; // Fade out over time
            //glColor4f(1.0f, 1.0f, 1.0f, alpha);  // White with transparency

            float size = particles[i].size;

            // Draw a textured quad for each particle
            glTexCoord2f(0.0f, 0.0f); glVertex3f(particles[i].position.x - size, particles[i].position.y - size, particles[i].position.z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(particles[i].position.x + size, particles[i].position.y - size, particles[i].position.z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(particles[i].position.x + size, particles[i].position.y + size, particles[i].position.z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(particles[i].position.x - size, particles[i].position.y + size, particles[i].position.z);
        }
    }
    glEnd();

    // Restore OpenGL state
    glDisable(GL_BLEND);
    //glDisable(GL_TEXTURE_2D);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Reset color to white (opaque)
}
