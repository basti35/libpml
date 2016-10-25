#ifndef PMLMOS_HPP
#define PMLMOS_HPP value

#include<iostream>

enum pmlState { 
   NO_STATE=-1,
   STOPPED,
   STARTING,
   IDLE,
   SUSPENDING,
   SUSPENDED,
   UNSUSPENDING,
   EXECUTE,
   STOPPING,
   ABORTING,
   ABORTED,
   HOLDING,
   HELD,
   UNHOLDING,
   COMPLETING,
   COMPLETE,
   RESETTING,
   CLEARING,
   N_STATES
};

const char *pmlStateLabel[] =
{
  "STOPPED",
  "STARTING",
  "IDLE",
  "SUSPENDING",
  "SUSPENDED",
  "UNSUSPENDING",
  "EXECUTE",
  "STOPPING",
  "ABORTING",
  "ABORTED",
  "HOLDING",
  "HELD",
  "UNHOLDING",
  "COMPLETING",
  "COMPLETE",
  "RESETTING",
  "CLEARING"
};

enum pmlCommand {
  NO_COMMAND=-1,
  START,
  RESET,
  HOLD,
  UNHOLD,
  SUSPEND,
  UNSUSPEND,
  CLEAR,
  STOP,
  ABORT,
  N_COMMANDS
};

const char *pmlCommandLabel[] =
{
  "START",
  "RESET",
  "HOLD",
  "UNHOLD",
  "SUSPEND",
  "UNSUSPEND",
  "CLEAR",
  "STOP",
  "ABORT"
};

const pmlState transition[pmlState (N_STATES)][pmlCommand (N_COMMANDS)] = {
  //                  START         RESET         HOLD          UNHOLD        SUSPEND       UNSUSPEND     CLEAR         STOP          ABORT
  /*STOPPED*/        {NO_STATE,     RESETTING,    NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     ABORTING},
  /*STARTING*/       {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*IDLE*/           {STARTING,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*SUSPENDING*/     {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*SUSPENDED*/      {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     UNSUSPENDING, NO_STATE,     STOPPING,     ABORTING},
  /*UNSUSPENDING*/   {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*EXECUTE*/        {NO_STATE,     NO_STATE,     HOLDING,      NO_STATE,     SUSPENDING,   NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*STOPPING*/       {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     ABORTING},
  /*ABORTING*/       {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE},
  /*ABORTED*/        {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     CLEARING,     NO_STATE,     NO_STATE},
  /*HOLDING*/        {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*HELD*/           {NO_STATE,     NO_STATE,     NO_STATE,     UNHOLDING,    NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*UNHOLDING*/      {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*COMPLETING*/     {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*COMPLETE*/       {NO_STATE,     RESETTING,    NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*RESETTING*/      {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     STOPPING,     ABORTING},
  /*CLEARING*/       {NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     NO_STATE,     ABORTING}
};

class pmlMos
{
  protected:
    pmlState st_;
    pmlState setState(pmlState _st) {return st_ = _st;};

  public:
    pmlMos(pmlState _st=ABORTED):st_(_st){};
    pmlState state() {return st_;};
    pmlState forceState(pmlState _st) {return st_ = _st;};
    pmlState sendCommand(pmlCommand _cmd)
    {
      if(transition[st_][_cmd] >= 0)
        st_ = transition[st_][_cmd];
      return transition[st_][_cmd];
    };
    char ** print(char** floor, int nrows, int ncols) {return floor;};
};

#ifndef MAIN
#define MAIN

int main(int argc, char *argv[])
{
  pmlMos mo;

  for (mo.forceState(pmlState(0)); mo.state() < N_STATES; mo.forceState(pmlState(mo.state() + 1)))
  {
   std::cout << pmlStateLabel[mo.state()] << std::endl;
  }

  pmlState st;
  pmlCommand cmd;
  for (cmd=pmlCommand(0); cmd < N_COMMANDS; cmd=pmlCommand(cmd+1)) {
   std::cout << pmlCommandLabel[cmd] << std::endl;
  }

  for (st = pmlState (0); st < N_STATES; st=pmlState(st+1))
  {
    for (cmd = pmlCommand(0); cmd < N_COMMANDS; cmd=pmlCommand(cmd+1))
    {
      if(transition[st][cmd] >= 0)
        std::cout << "From: " << pmlStateLabel[st] << ", with a command of " << pmlCommandLabel[cmd] << " next state will be: " << pmlStateLabel[transition[st][cmd]] << std::endl;
    }
  }

  return 0;
}

#endif /* ifndef MAIN */

#endif /* ifndef PMLMOS_HPP */

