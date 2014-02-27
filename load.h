#ifndef LOAD_H
#define LOAD_H

#include "common.h"

typedef void (APIENTRY * glGenFramebuffers_Func)(GLsizei n, GLuint *ids);
extern glGenFramebuffers_Func glGenFramebuffers;

typedef void (APIENTRY * glBindFramebuffer_Func)(GLenum target, GLuint framebuffer);
extern glBindFramebuffer_Func glBindFramebuffer;

typedef void (APIENTRY * glGenRenderbuffers_Func)(GLsizei n, GLuint *renderbuffers);
extern glGenRenderbuffers_Func glGenRenderbuffers;

typedef void (APIENTRY * glBindRenderbuffer_Func)(GLenum target, GLuint renderbuffer);
extern glBindRenderbuffer_Func glBindRenderbuffer;

typedef void (APIENTRY * glRenderbufferStorage_Func)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
extern glRenderbufferStorage_Func glRenderbufferStorage;

typedef void (APIENTRY * glFramebufferRenderbuffer_Func)(GLenum target,	GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
extern glFramebufferRenderbuffer_Func glFramebufferRenderbuffer;

typedef void (APIENTRY * glFramebufferTexture2D_Func)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern glFramebufferTexture2D_Func glFramebufferTexture2D;

typedef void (APIENTRY * glDeleteFramebuffers_Func)(GLsizei n, GLuint *framebuffers);
extern glDeleteFramebuffers_Func glDeleteFramebuffers;

void loadfuncs();

#endif
