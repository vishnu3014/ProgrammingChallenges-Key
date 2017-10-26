#include "stdafx.h"
#include "Graph.h"
#include "PlayingWheels.h"
#include <set>
#include <fstream>

namespace PlayingWheels
{
  void ReadWheel(std::shared_ptr<Wheel>& wheel, std::fstream& fStream)
  {
    int x3, x2, x1, x0;
    fStream >> x3;
    fStream >> x2;
    fStream >> x1;
    fStream >> x0;

    wheel->number.push_back(x0);
    wheel->number.push_back(x1);
    wheel->number.push_back(x2);
    wheel->number.push_back(x3);
  }

  void ReadData(std::shared_ptr<Wheel>& fromWheel, std::shared_ptr<Wheel>& toWheel, std::set<int>& forbidden, std::fstream& fStream)
  {
    ReadWheel(fromWheel, fStream);
    ReadWheel(toWheel, fStream);

    int numForbidden;
    fStream >> numForbidden;
   
    for (int index = 0; index < numForbidden; index++)
    {
      std::shared_ptr<Wheel> wheel = std::make_shared<Wheel>();
      ReadWheel(wheel, fStream);
      forbidden.insert(wheel->constructNumber());
    }
  }

  void PlayingWheel()
  {
    std::string filePath("E:\\data\\PlayingWheel.txt");
    std::fstream fStream(filePath, std::ios_base::in);

    int numCases;
    fStream >> numCases;

    std::shared_ptr<Wheel> fromWheel = std::make_shared<Wheel>();
    std::shared_ptr<Wheel> toWheel = std::make_shared<Wheel>();
    std::set<int> forbidden;
    ReadData(fromWheel, toWheel, forbidden, fStream);



    fStream.close();
  }
}