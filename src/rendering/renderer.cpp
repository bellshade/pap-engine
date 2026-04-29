#include "renderer.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

static unsigned int VAO, VBO;
static unsigned int shader_program;

static const char *vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 posisi;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(posisi, 1.0);
}
)";

static const char *fragment_shader_src = R"(
#version 330 core
out vec4 warna;

void main() {
  warna = vec4(1.0, 0.5, 0.2, 1.0);
}
)";

unsigned int compile_shader(unsigned int type, const char *src) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  int success;
  char info[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, info);
    std::cerr << "Shader error: " << info << "\n";
  }

  return shader;
}

bool Renderer::inisialisasi() {
  if (glewInit() != GLEW_OK) {
    std::cerr << "GLEW gagal inisialisasi\n";
    return false;
  }

  float vertices[] = {
    // INFO: bagian belakang kubus
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    // INFO: bagian depan kubus
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    // INFO: bagian kiri dari si kubus
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    

    // INFO: bagian kanan dari si kubus
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

    // INFO: bagian bawah dari si kubus
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    // INFO: bagian atas dari si kubus
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader_src);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_src);

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  glAttachShader(shader_program, fs);
  glLinkProgram(shader_program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return true;
}

void Renderer::clear() {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
  glUseProgram(shader_program);

  int loc_model = glGetUniformLocation(shader_program, "model");
  int loc_view = glGetUniformLocation(shader_program, "view");
  int loc_proj = glGetUniformLocation(shader_program, "projection");

  glUniformMatrix4fv(loc_model, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(loc_view, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(loc_proj, 1, GL_FALSE, glm::value_ptr(projection));

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::shutdown() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
