#ifndef TIME_HPP
#define TIME_HPP

class Time {
private:
  static float delta_time;
  static float last_frame;

public:
  static void update();
  static float dapatkan_delta();
};

#endif // !TIME_HPP
