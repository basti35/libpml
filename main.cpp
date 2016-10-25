#define MAIN
#include "pml_mo.hpp"
#include "conv_in.hpp"
#include <unistd.h>

/*
#include<palletizer>
#include<conv_out>
*/

int main(int argc, char *argv[])
{
  srand(0);
/*pmlMos *MOs[5];
  MOs[0] = (pmlMos *) new convIn;
  MOs[1] = (pmlMos *) new convIn;
  MOs[2] = (pmlMos *) new palletizer;
  MOs[3] = (pmlMos *) new convOut;
  MOs[4] = (pmlMos *) new unitController;
*/
  char buff[30];
  char *floor = buff;
  conv_in conv_in_1(ABORTED, 30);

  std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;
  conv_in_1.sendCommand(CLEAR);
  std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;
  conv_in_1.spin();
  std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;
  conv_in_1.sendCommand(RESET);
  std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;
  conv_in_1.spin();
  std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;
  conv_in_1.sendCommand(START);
  std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;
  for (int i = 0; i < 100; ++i)
  {
    conv_in_1.spin();
    conv_in_1.print(&floor, 1, 30);
    std::cout << "Floor : " << floor  << " out_box = " << conv_in_1.out_box() << std::endl;
    std::cout << "Line: " << __LINE__ <<  ": STATE: " << pmlStateLabel[conv_in_1.state()] << std::endl;

    sleep(1); 
  }

  return 0;
}
