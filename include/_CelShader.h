#ifndef _CELLSHADER_H
#define _CELLSHADER_H

#include "_Common.h"

class _CelShader {
private:
    GLuint shaderProgram;

    GLuint compileShader(const char* source, GLenum type);
    GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);

public:
    _CelShader();
    ~_CelShader();

    void initialize();
    void use();
    void setModelMatrix(GLfloat* model);
    void setViewProjectionMatrices(GLfloat* view, GLfloat* projection);
    void setLightDirection(GLfloat x, GLfloat y, GLfloat z);
};

#endif // !_CELLSHADER_H
