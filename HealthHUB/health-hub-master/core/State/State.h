/*
Author: Nina Schaaf
Update: 14. Mai 2017
//--------------------------------------------------------------------------
*/

#ifndef __STATE_H__
#define __STATE_H__

#include <stdint.h>
#include "Singleton.h"
#include "Timer.h"

namespace ScanStates
{
  const uint8_t IDLE = 0;
  const uint8_t START = 1;
  const uint8_t FINISHED = 2;
  const uint8_t TIMEOUT = 3;
}

namespace SetupStates
{
  const uint8_t SETUP_IDLE          = 0; // be ready for scanning
  const uint8_t SETUP_START         = 1; // enroll a specific person ID
  const uint8_t DELETE              = 2; // remove a specific person ID
  const uint8_t RESET               = 3; // remove all IDs from the scanner's storage
  const uint8_t FIRST_SCAN_1        = 11;
  const uint8_t FIRST_SCAN_2        = 12;
  const uint8_t FIRST_SCAN_3        = 13;
  const uint8_t ERROR_FIRST_SCAN    = 14;
  const uint8_t ERROR_FINGER_1      = 15;
  const uint8_t FIRST_SCAN_SUCCESS  = 16;
  const uint8_t SECOND_SCAN_1       = 21;
  const uint8_t SECOND_SCAN_2       = 22;
  const uint8_t SECOND_SCAN_3       = 23;
  const uint8_t ERROR_SECOND_SCAN   = 24;
  const uint8_t ERROR_FINGER_2      = 25;
  const uint8_t SECOND_SCAN_SUCCESS = 26;
  const uint8_t THIRD_SCAN_1        = 31;
  const uint8_t THIRD_SCAN_2        = 32;
  const uint8_t THIRD_SCAN_3        = 33;
  const uint8_t ERROR_THIRD_SCAN    = 34;
  const uint8_t ERROR_FINGER_3      = 35;
  const uint8_t THIRD_SCAN_SUCCESS  = 36;
  const uint8_t REMOVE_FINGER       = 4;
  const uint8_t SETUP_TIMEOUT       = 5;
  const uint8_t SETUP_DONE          = 6;
  const uint8_t NOT_CONNECTED       = 7;
}

// The class is Singleton and provides globally accessible states.
// Use: State::getInstance().functionCall
//
class State : public Singleton <State>
{
  friend class Singleton <State>;

  public:
    ~State () {}

    void setScanState(uint8_t state);
    uint8_t getScanState();

    void setSetupState(uint8_t state);
    uint8_t getSetupState();

  protected:
    State() {}

  private:
    volatile uint8_t scanState = ScanStates::IDLE;
    volatile uint8_t setupState = SetupStates::SETUP_IDLE;
};

#endif // __STATE_H__
