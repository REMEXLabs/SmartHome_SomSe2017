/*
Author: Andreas Fliehr
Update: June 2, 2017
//--------------------------------------------------------------------------
*/

#ifndef __FINGER_H__
#define __FINGER_H__

#include "FPS_GT511C3.h"
#include "Singleton.h"

// Provides a class for the fingerprint scanner
//
class FingerprintScanner : public Singleton <FingerprintScanner>
{
  friend class Singleton <FingerprintScanner>;

  public:
    ~FingerprintScanner () {}

    void registerScanner(uint8_t rxPin, uint8_t txPin);
    uint8_t actionHandler(uint8_t setupState, uint8_t personID);
    bool checkFinger();
    bool update();
    int16_t getSensorValue();

  protected:
      FingerprintScanner() : scanner(0, 0) {}

  private:
    FPS_GT511C3 scanner;

    uint8_t fingerID = 200;

    void scanFingerID();
    bool finishedScan();
    void createID(uint8_t personID);
    void removeID(uint8_t personID);
    void removeAllIDs();
};

#endif // __FINGER_H__
