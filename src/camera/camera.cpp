#include "camera.hpp"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera()
    : posisi(0.0f, 0.0f, 5.0f), depan(0.0f, 0.0f, -1.0f),
      atas(0.0f, 1.0f, 0.0f), yaw(-90.0f), pitch(0.0f), kecepatan(3.0f),
      sensitivitas(0.01f) {}

void Camera::set_posisi(const glm::vec3 &pos) { posisi = pos; }

glm::mat4 Camera::dapatkan_view_matrix() const {
  return glm::lookAt(posisi, posisi + depan, atas);
}

void Camera::update_keyboard(Input &input, float dt) {
  float velocity = kecepatan * dt;

  if (input.tombol_ditekan(KEY_W)) {
    posisi += depan * velocity;
  }

  if (input.tombol_ditekan(KEY_S)) {
    posisi -= depan * velocity;
  }

  if (input.tombol_ditekan(KEY_A)) {
    posisi -= glm::normalize(glm::cross(depan, atas)) * velocity;
  }

  if (input.tombol_ditekan(KEY_D)) {
    posisi += glm::normalize(glm::cross(depan, atas)) * velocity;
  }
}

void Camera::update_mouse(double xoffset, double yoffset) {
  xoffset *= sensitivitas;
  yoffset *= sensitivitas;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f) {
    pitch = 89.0f;
  }

  if (pitch < -89.0f) {
    pitch = -89.0f;
  }

  glm::vec3 arah;

  arah.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  arah.y = sin(glm::radians(pitch));
  arah.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  depan = glm::normalize(arah);
}
