//
// Created by André Mathlener on 07/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHESIZER_H
#define XVA1USERINTERFACE_SYNTHESIZER_H

#include <string>
#include <Arduino.h>
#include "Envelope.h"

using namespace std;

class Synthesizer {
private:
    int currentPatchNumber = 1;
    string currentPatchName = "";
    string currentPatchNameU = "";
    string currentPatchNameL = "";
    byte currentPatchDataU[512] = {};
    byte currentPatchDataL[512] = {};

public:

    void begin();

    void selectPatchU(int number);

    void selectPatchL(int number);

    void changePatchU(int number);

    void changePatchL(int number);

    void loadPatchDataU();

    void loadPatchDataL();

    void savePatchDataU(int number);

    void savePatchDataL(int number);

    int getPatchNumberU() const;

    int getPatchNumberL() const;

    const string &getPatchNameU() const;

    const string &getPatchNameL() const;

    byte getParameter(int number) const;

    byte getParameterU(int number) const;

    byte getParameterL(int number) const;

    void setParameter(int number, int value);

    void setParameterU(int number, int value);

    void setParameterL(int number, int value);

    void setCurrentPatchNameU();

    void setCurrentPatchNameL();

    Envelope getEnvelopeValues(Envelope &envelope);
};


#endif //XVA1USERINTERFACE_SYNTHESIZER_H
