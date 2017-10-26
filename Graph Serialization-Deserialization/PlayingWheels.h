#pragma once
#include <vector>

namespace PlayingWheels
{
  typedef struct Wheel
  {
    std::vector<int> number;

    int constructNumber()
    {
      return number[0] + number[1] * 10 + number[2] * 100 + number[3] * 1000;
    }

    void left(int pos)
    {
      if (pos > 3)
        return;

      number[pos] = number[pos] - 1;
      if (number[pos] < 0)
        number[pos] = 9; 
    }

    void right(int pos)
    {
      if (pos > 3)
        return;

      number[pos] = (number[pos] + 1) % 10;
    }
  }Wheel;
  
  void PlayingWheel();
}