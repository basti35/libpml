#define MAIN
#include "pml_mo.hpp"
#include "conv_in.hpp"
#include "pal.hpp"
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
  char buff1[30], buff2[30], buff_out[30];
  char empty[31];
  memset(&empty[0], ' ', 30);
  std::string floor[5];
  empty[31] = '\0';
  char *buff_conv_1=buff1;
  char *buff_conv_2=buff2;
  char *buff_conv_out=buff_out;
  char buff3[5*6];
  char *buff_pal;
  buff_pal = &buff3[0];
  conv_in conv_in_1(ABORTED, 30);
  conv_in conv_in_2(ABORTED, 30);
  conv_in conv_out_1(ABORTED, 30);
  pal_mo pal(ABORTED, 5, 5);

  conv_in_1.sendCommand(CLEAR);
  conv_in_2.sendCommand(CLEAR);
  pal.sendCommand(CLEAR);
  conv_out_1.sendCommand(CLEAR);
  conv_in_1.spin();
  conv_in_2.spin();
  pal.spin();
  conv_out_1.spin();
  conv_in_1.sendCommand(RESET);
  conv_in_2.sendCommand(RESET);
  pal.sendCommand(RESET);
  conv_out_1.sendCommand(RESET);
  conv_in_1.spin();
  conv_in_2.spin();
  pal.spin();
  conv_out_1.spin();
  conv_in_1.sendCommand(START);
  conv_in_2.sendCommand(START);
  pal.sendCommand(START);
  conv_out_1.sendCommand(START);
  for (int i = 0; i < 10000; ++i)
  {
    char next_box = (rand() < (RAND_MAX / 4 ))?'x':'_';
    conv_in_1.spin(next_box);
    next_box = (rand() < (RAND_MAX / 8 ))?'x':'_';
    conv_in_2.spin(next_box);
    conv_in_1.print(&buff_conv_1, 1, 30);
    conv_in_2.print(&buff_conv_2, 1, 30);
    char in_box[3];
    in_box[0] = conv_in_1.out_box()?'x':'_';
    in_box[1] = conv_in_2.out_box()?'x':'_';
    pal.spin(in_box);
    pal.print(&buff_pal, 5, 6);
    conv_out_1.spin(pal.out_pal()?'x':'_');
    conv_out_1.print(&buff_conv_out, 1, 30);
    std::cout << "Floor : " << buff_conv_1  << " out_box = " << conv_in_1.out_box() << std::endl;
    std::cout << "Floor : " << buff_conv_2  << " out_box = " << conv_in_2.out_box() <<  " STATE: " << pmlStateLabel[conv_in_2.state()] << std::endl;
    for(int j; j< 5; ++j)
      std::cout << (buff_pal+6*j) << std::endl;
    std::cout <<  " out_pal = " << pal.out_pal() <<  " STATE: " << pmlStateLabel[pal.state()] << std::endl;

    floor[0] = std::string("") + buff_conv_1 + (buff_pal+6*0) + buff_conv_out;
    floor[1] = std::string("") + empty + (buff_pal+6*1);
    floor[2] = std::string("") + empty + (buff_pal+6*2);
    floor[3] = std::string("") + buff_conv_2 + (buff_pal+6*3);
    floor[4] = std::string("") + empty + (buff_pal+6*4);
    std::cout << floor[0] << std::endl <<
                 floor[1] << std::endl <<
                 floor[2] << std::endl <<
                 floor[3] << std::endl <<
                 floor[4] << std::endl ;

    usleep(50000); 
  }

  return 0;
}
