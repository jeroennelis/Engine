#pragma once

#include "Platform/OpenGl/GL.h"

class ZedShader{
public:
    ZedShader(GLchar* vs, GLchar* fs);
    ~ZedShader();

    GLuint getProgramId();

    static const GLint ATTRIB_VERTICES_POS = 0;
private:
    bool compile(GLuint &shaderId, GLenum type, GLchar* src);
    GLuint verterxId_;
    GLuint fragmentId_;
    GLuint programId_;
};
