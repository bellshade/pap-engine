#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

bool Window::inisialisasi() {
  if (!glfwInit()) {
    std::cerr << "gagal inisialisasi GLFW\n";
    return false;
  }

  handle = glfwCreateWindow(lebar, tinggi, judul, nullptr, nullptr);

  if (!handle) {
    std::cerr << "gagal buat windownya\n";
    glfwTerminate();
    return false;
  }

  glfwSetInputMode((GLFWwindow*)handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwMakeContextCurrent((GLFWwindow *)handle);

  return true;
}

void Window::update() {
  glfwSwapBuffers((GLFWwindow *)handle);
  glfwPollEvents();
}

bool Window::harus_tutup() {
  return glfwWindowShouldClose((GLFWwindow *)handle);
}

void Window::shutdown() {
  glfwDestroyWindow((GLFWwindow *)handle);
  glfwTerminate();
}
