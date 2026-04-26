#include "time.hpp"
#include <GLFW/glfw3.h>

float Time::delta_time = 0.0f;
float Time::last_frame = 0.0f;

void Time::update() {
  float current = glfwGetTime();
  delta_time = current - last_frame;
  last_frame = current;
}

float Time::dapatkan_delta() { return delta_time; }
