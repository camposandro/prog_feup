#pragma once

#include <iostream>
#include <vector>

#include "Bus.h"
#include "Shift.h"
#include "Company.h"

using namespace std;

class Bus
{
 private:
  unsigned int orderInLine;
  unsigned int driverId;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
  Bus(unsigned int id, unsigned int driver, unsigned int line);
  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getDriverId() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
  // set methods
  void setOrderInLine(unsigned int orderInLine);
  void setDriverId(unsigned int driverId);
  void setLineId(unsigned int lineId);
  void setSchedule(vector<Shift> vectorShifts);
  // other methods
};
