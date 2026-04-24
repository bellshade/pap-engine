#include "input.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

void Input::inisialisasi(void *handle_window) { 
  window_handle = handle_window; 
  glfwSetJoystickCallback(joystick_callback);

}

// member function definition (no 'static' keyword in cpp)
void Input::joystick_callback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
    {
        std::cout << "Joystick " << jid << " connected" << std::endl;
        // The joystick was connected
    }
    else if (event == GLFW_DISCONNECTED)
    {
        std::cout << "Joystick " << jid << " disconnected" << std::endl;
        // The joystick was disconnected
    }
}

void Input::update() {
  GLFWwindow *window = (GLFWwindow *)window_handle;

  // Keyboard Binding
  state_keyboard[KEY_W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
  state_keyboard[KEY_A] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
  state_keyboard[KEY_S] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
  state_keyboard[KEY_D] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
  state_keyboard[KEY_ESC] = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;


  // Mouse Binding
  state_mouse[MOUSE_KIRI] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
  state_mouse[MOUSE_KANAN] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

  glfwGetCursorPos(window, &posisi_mouse_x, &posisi_mouse_y);

  // Gamepad Binding
  int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
  if (present == 1) {
      gamepad_connected = true;  

      int axesCount;
      const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
      xl_axis = axes[0];
      yl_axis = axes[1];
      xr_axis = axes[2];
      yr_axis = axes[3];
      l2_axis = axes[4];
      r2_axis = axes[5];
      
      int buttonsCount;
      const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);

      if (GLFW_PRESS == buttons[1]){
        std::cout << "B button pressed " << std::endl;
      }
  } else {
    gamepad_connected = false;

  }
}

bool Input::tombol_ditekan(TombolKeyboard tombol) {
  return state_keyboard[tombol];
}

bool Input::mouse_ditekan(TombolMouse mouse) { 
  return state_mouse[mouse]; 
}

bool Input::gamepad_ditekan(TombolGamepad gamepad) {
  return state_gamepad[gamepad];
}

bool Input::gamepad_terkoneksi(){
  return gamepad_connected;
}

void Input::cetak_axisgamepad(){
    std::cout << "x axes left   : " << xl_axis << "\n";
    std::cout << "y axes left   : " << yl_axis << "\n";
    std::cout << "x axes right  : " << xr_axis << "\n";
    std::cout << "y axes right  : " << yr_axis << "\n";
    std::cout << "left trigger  : " << l2_axis << "\n";
    std::cout << "right trigger : " << r2_axis << "\n";
}

void Input::ambil_posisi_mouse(double &x, double &y) {
  x = posisi_mouse_x;
  y = posisi_mouse_y;
}
