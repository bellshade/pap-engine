#ifndef MESIN_ENGINE_HPP
#define MESIN_ENGINE_HPP

#include "../sistem/window.hpp"
#include "../sistem/input.hpp"

class MesinGame {
  private:
    Window window;
    Input input;
    bool berjalan;

  public:
    bool inisialisasi();
    void jalankan();
    void shutdown();
    void status();
};

#endif // !MESIN_ENGINE_HPP
