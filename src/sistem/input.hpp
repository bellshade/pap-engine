#ifndef INPUT_HPP
#define INPUT_HPP

#include <unordered_map>
enum TombolKeyboard {
  KEY_W,
  KEY_A,
  KEY_S,
  KEY_D,
  KEY_ESC,
};

enum TombolMouse {
  MOUSE_KIRI,
  MOUSE_KANAN,
};

enum TombolGamepad{
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  BUTTON_SELECT = 6,
  BUTTON_START = 7,
};

class Input {
private:
  void *window_handle;

  std::unordered_map<int, bool> state_keyboard;
  std::unordered_map<int, bool> state_mouse;
  std::unordered_map<int, bool> state_gamepad; 
  double posisi_mouse_x;
  double posisi_mouse_y;

  bool gamepad_connected;
  float xr_axis;
  float yr_axis;
  float xl_axis;
  float yl_axis;
  float l2_axis;
  float r2_axis;

  static void joystick_callback(int jid, int event);

public:
  void inisialisasi(void *handle_window);
  
  void update();

  bool tombol_ditekan(TombolKeyboard tombol);
  bool mouse_ditekan(TombolMouse tombol);
  bool gamepad_ditekan(TombolGamepad tombol);
  bool gamepad_terkoneksi();
  void cetak_axisgamepad();

  void ambil_posisi_mouse(double &x, double &y);

};

#endif // !INPUT_HPP
