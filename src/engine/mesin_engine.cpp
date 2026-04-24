#include "mesin_engine.hpp"
#include <iostream>
#include <ostream>

bool MesinGame::inisialisasi() {
  window.lebar = 800;
  window.tinggi = 600;
  window.judul = "Pap Game";

  if (!window.inisialisasi()) {
    return false;
  }

  input.inisialisasi(window.handle);

  berjalan = true;
  return true;
}

void MesinGame::jalankan() {
  while (berjalan && !window.harus_tutup()) {

    input.update();
    MesinGame::status();
    
    if (input.tombol_ditekan(KEY_ESC)) {
      std::cout << "\nkeluar dari program\n";
      berjalan = false;
    }

    // if (input.tombol_ditekan(KEY_W)) {
    //   std::cout << "tombol dari w ditekan\n";
    // }

    // if (input.tombol_ditekan(KEY_A)) {
    //   std::cout << "tombol dari a ditekan\n";
    // }

    // if (input.tombol_ditekan(KEY_S)) {
    //   std::cout << "tombol dari s ditekan\n";
    // }

    // if (input.tombol_ditekan(KEY_D)) {
    //   std::cout << "tombol dari d ditekan\n";
    // }

    // if (input.mouse_ditekan(MOUSE_KIRI)) {
    //   std::cout << "klik mouse kiri\n";
    // }

    // if (input.mouse_ditekan(MOUSE_KANAN)) {
    //   std::cout << "klik mouse kanan\n";
    // }

    double x, y;
    input.ambil_posisi_mouse(x, y);
    // std::cout << "posisi mouse x: " << x << " y: " << y << "\n";

    if (input.gamepad_ditekan(BUTTON_A)){
      std::cout << "tombol A di gamepad ditekan";
    }

    // TODO: untuk update dan render
    window.update();
  }
}

void MesinGame::status(){

  std::cout << "\033[0;1H";
  std::cout << "\033[J";       
  
  std::cout << std::boolalpha;
  std::cout << "tombol dari W ditekan : " << (input.tombol_ditekan(KEY_W) == 1) << "\n";
  std::cout << "tombol dari A ditekan : " << (input.tombol_ditekan(KEY_A) == 1)<< "\n";
  std::cout << "tombol dari S ditekan : " << (input.tombol_ditekan(KEY_S) == 1)<< "\n";
  std::cout << "tombol dari D ditekan : " << (input.tombol_ditekan(KEY_D) == 1)<< "\n";

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

  if (input.gamepad_terkoneksi()){
      std::cout << "Gamepad terkoneksi \n";
      input.cetak_axisgamepad();

  } else {
      std::cout << "\033[34mGamepad tidak terkoneksi\n\033[0m";
  }

}

void MesinGame::shutdown() { window.shutdown(); }
