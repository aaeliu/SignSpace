#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "scene.h"

struct printer {
  std::ofstream file;
  scene* context;

  printer (std::string filename, scene* c);

  void print_sdf_functions ();
  void print_map();
  void print_raymarch (int steps);
  void print_render ();
  void print_main ();
  void print ();
};
