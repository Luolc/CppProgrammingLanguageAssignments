#include <iostream>
#include <string>

#include "dos_gis.h"
#include "gis_shape/gis_point.h"
#include "gis_shape/gis_polyline.h"
#include "gis_shape/gis_shape_set.h"
#include "util/io_util.hpp"
#include "util/string_util.hpp"

int main() {
  freopen("input.txt", "r", stdin);

  luolc::dosgis::DosGisManager manager;

  std::string cmd;
  while (std::getline(std::cin, cmd)) {
    manager.Execute(cmd);
  }
//  manager.Execute("add point a1 5,6");
//  manager.Execute("add point a2 10,20");
//  manager.Execute("add point a3 5,6");
//  manager.Execute("judge point a1 equal a3");
//  manager.Execute("judge point a1 equal a2");
//  manager.Execute("del point a1");
//  manager.Execute("set point a2 set 5,6");
//  manager.Execute("judge point a3 equal a2");
//  manager.Execute("set point a3 move -5,-6");
//  manager.Execute("set point a2 set 0,0");
//  manager.Execute("judge point a2 equal a3");

  manager.PrintAllShapes();

  return 0;
}