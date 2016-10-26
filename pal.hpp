#ifndef PAL_HPP
#define PAL_HPP

#include "pml_mo.hpp"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

class pal_mo:
  public pmlMos
{
  char * pallet;
  bool out_pal_;
  int pal_rows_, pal_cols_, str_cols_;
  int curr_pos_;

  public:


    pal_mo(pmlState _st=ABORTED, int _pal_rows=5, int _pal_cols=5)
    {
      pal_rows_ = _pal_rows;
      pal_cols_ = _pal_cols;
      str_cols_ = pal_cols_+1;
      curr_pos_ = 0;
      pallet = (char *) malloc(str_cols_ * pal_rows_);

      for(int i=0; i<pal_rows_; ++i)
      {
        strncpy( &pallet[i*(str_cols_)], "_____", str_cols_);
      }
      st_ = _st;
      out_pal_ = false;
    };

    char ** print(char** floor, int nrows, int ncols)
    {
      std::cout << "nrow: " << nrows << ", pal_rows_: " << pal_rows_ << std::endl;
      assert(pal_rows_ <= nrows);
      for(int i=0; i<std::min(nrows, pal_rows_); ++i)
      {
        strncpy((*floor+ncols*i), &pallet[i*(str_cols_)], str_cols_);
        std::cout << __FILE__ << __LINE__ << " " << i << " " << &pallet[i*(str_cols_)] << "  " << (*floor+ncols*i) << std::endl;
      }

      return floor;
    };
    bool out_pal() {return out_pal_;};
    void add_box(char next_box='_')
    {
      if(next_box == '_')
        return;
      int curr_row = curr_pos_ / pal_cols_;
      pallet[curr_row*(pal_cols_+1) + curr_pos_ % pal_cols_] = next_box;
      ++curr_pos_;
      if(curr_pos_ >= pal_cols_*pal_rows_)
      {
        out_pal_ = true;
        for(int i=0; i<pal_rows_; ++i)
        {
          strncpy( &pallet[i*(str_cols_)], "_____", str_cols_);
        }
        curr_pos_ = 0;
      }
    };

    void spin( char next_box[] = "__")
    {
      out_pal_ = false;
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
        case UNSUSPENDING:
          add_box(next_box[0]);
          add_box(next_box[1]);
          st_ = EXECUTE;
          break;
        case SUSPENDED:
          if(next_box[0] == 'x' || next_box[1] == 'x')
          {
            add_box(next_box[0]);
            add_box(next_box[1]);
            this->sendCommand(UNSUSPEND);
          }
          break;
        case EXECUTE:
          add_box(next_box[0]);
          add_box(next_box[1]);
          if(next_box[0] != 'x' && next_box[1] != 'x')
            this->sendCommand(SUSPEND);            
          break;
      }
    };

};


#endif /* ifndef PAL_HPP */
