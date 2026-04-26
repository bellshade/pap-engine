#include "mesin_engine.hpp"
#include "../core/time.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <ostream>

double last_x = 400, last_y = 300;
bool first_mouse = true;

bool MesinGame::inisialisasi() {
  window.lebar = 800;
  window.tinggi = 600;
  window.judul = "Pap Game";

  if (!window.inisialisasi()) {
    return false;
  }

  input.inisialisasi(window.handle);

  if (!renderer.inisialisasi()) {
    return false;
  }

  berjalan = true;
  return true;
}

void MesinGame::jalankan() {
  while (berjalan && !window.harus_tutup()) {

    Time::update();

    float dt = Time::dapatkan_delta();
    float kecepatan = 1.0f;
    
    input.update();
    

    if (input.tombol_ditekan(KEY_ESC)) {
      std::cout << "\nkeluar dari program\n";
      berjalan = false;
    }

    if (input.tombol_ditekan(KEY_W)) {
      transform.posisi.y += kecepatan * dt;
    }

    if (input.tombol_ditekan(KEY_A)) {
      transform.posisi.x -= kecepatan * dt;
    }

    if (input.tombol_ditekan(KEY_S)) {
      transform.posisi.y -= kecepatan * dt;
    }

    if (input.tombol_ditekan(KEY_D)) {
      transform.posisi.x += kecepatan * dt;
    }

    // if (input.mouse_ditekan(MOUSE_KIRI)) {
    //   std::cout << "klik mouse kiri\n";
    // }

    // if (input.mouse_ditekan(MOUSE_KANAN)) {
    //   std::cout << "klik mouse kanan\n";
    // }

    if (input.gamepad_ditekan(BUTTON_A)) {
      std::cout << "tombol A di gamepad ditekan";
    }

    double x, y;
    input.ambil_posisi_mouse(x, y);

    if (first_mouse) {
      last_x = x;
      last_y = y;
      first_mouse = false;
    }

    double xoffset = x - last_x;
    double yoffset = last_y - y;

    last_x = x;
    last_y = y;

    camera.update_mouse(xoffset, yoffset);
    camera.update_keyboard(input, dt);

    glm::mat4 model = transform.dapatkan_matrix();
    glm::mat4 view = camera.dapatkan_view_matrix();
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    renderer.clear();
    renderer.render(model, view, projection);

    MesinGame::status();

    window.update();
  }
}

void MesinGame::status() {

  std::cout << "\033[0;1H";
  std::cout << "\033[J";

  std::cout << std::boolalpha;
  std::cout << "tombol dari W ditekan : " << (input.tombol_ditekan(KEY_W) == 1)
            << "\n";
  std::cout << "tombol dari A ditekan : " << (input.tombol_ditekan(KEY_A) == 1)
            << "\n";
  std::cout << "tombol dari S ditekan : " << (input.tombol_ditekan(KEY_S) == 1)
            << "\n";
  std::cout << "tombol dari D ditekan : " << (input.tombol_ditekan(KEY_D) == 1)
            << "\n";

  if (input.mouse_ditekan(MOUSE_KIRI)) {
    std::cout << "klik mouse kiri ditekan\n";
  } else {
    std::cout << "\033[34mklik mouse kiri tidak ditekan\n\033[0m";
  }

  if (input.mouse_ditekan(MOUSE_KANAN)) {
    std::cout << "klik mouse kanan ditekan\n";
  } else {
    std::cout << "\033[34mklik mouse kana tidak ditekan\n\033[0m";
  }

  double x, y;
  input.ambil_posisi_mouse(x, y);
  std::cout << "posisi mouse x: " << x << " y: " << y << "\n\n";

  if (input.gamepad_terkoneksi()) {
    std::cout << "Gamepad terkoneksi \n";
    input.cetak_axisgamepad();

  } else {
    std::cout << "\033[34mGamepad tidak terkoneksi\n\033[0m";
  }
}

void MesinGame::shutdown() {
  renderer.shutdown();
  window.shutdown();
}
