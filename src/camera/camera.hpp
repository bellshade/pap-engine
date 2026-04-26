#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "../sistem/input.hpp"

class Camera {
  private:
    glm::vec3 posisi;
    glm::vec3 depan;
    glm::vec3 atas;

    float yaw;
    float pitch;
    
    float kecepatan;
    float sensitivitas;

public:
    Camera();
    void set_posisi(const glm::vec3& pos);
    glm::mat4 dapatkan_view_matrix() const;
    void update_keyboard(Input& input, float dt);
    void update_mouse(double xoffset, double yoffset);
};

#endif // !CAMERA_HPP
