#ifndef CONV_IN_HPP
#define CONV_IN_HPP

#include "pml_mo.hpp"
#include <string.h>
#include <stdlib.h>

class conv_in:
  public pmlMos
{
  std::string conveyor;
  bool out_box_;
  int conv_size_;

  public:


    conv_in(pmlState _st=ABORTED, int _conv_size=20)
    {
      conv_size_ = _conv_size;
      conveyor.resize(conv_size_);
      memset(&conveyor[0], '_', conv_size_-1);
      conveyor[conv_size_] = '\0';
      st_ = _st;
      out_box_ = false;
    };
    char ** print(char** floor, int nrows, int ncols)
    {
      if(nrows > 0)
        strncpy(*floor, conveyor.c_str(), ncols);
      return floor;
    };
    bool out_box() {return out_box_;};

    void spin( char next_box = '_')
    {
      switch(st_)
      {
        case ABORTING:
          st_ = ABORTED; 
          break;
        case CLEARING:
        case STOPPING:
          st_ = STOPPED;
          break;
        case RESETTING:
          st_ = IDLE;
          break;
        case STARTING:
        case UNSUSPENDING:
        case UNHOLDING:
          st_ = EXECUTE;
          break;
        case SUSPENDING:
          st_ = SUSPENDED;
          break;
        case HOLDING:
          st_ = HELD;
          break;
        case COMPLETING:
          st_ = COMPLETE;
          break;
        case SUSPENDED:
          if(next_box == 'x')
          {
            conveyor.insert(0, "x");
            conveyor.resize(conv_size_);
            this->sendCommand(UNSUSPEND);
          }
          break;
        case EXECUTE:
          if(conveyor[conveyor.length()-1] == 'x')
            out_box_ = true;
          else
            out_box_ = false;
          conveyor.insert(0, "_");
          conveyor[0] = next_box;
          conveyor.resize(conv_size_);
          bool theres_something = false;
          for( int pos=0; pos < conveyor.length(); ++pos)
          {
            if(conveyor[pos]=='x')
            {
              theres_something = true;
              break;
            }
          }
          if(!theres_something)
            this->sendCommand(SUSPEND);            
          break;
      }
    };

};


#endif /* ifndef CONV_IN_HPP */
