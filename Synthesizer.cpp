//
// Created by André Mathlener on 07/04/2021.
//

#include "Synthesizer.h"
int read_status;

#define HWSERIAL5 Serial5
#define HWSERIAL4 Serial4


void Synthesizer::selectPatchU(int number) {
  int synthPatchNumber = number - 1;

  Serial.print("Selecting patch #");
  Serial.print(synthPatchNumber);
  Serial.print(" on Synth...");

  HWSERIAL5.write('r');  // 'r' = Read program
  HWSERIAL5.write(synthPatchNumber);



  int bytesRead = 0;
  int retry = 0;
  while (bytesRead == 0 && retry != 100) {
    if (HWSERIAL5.available()) {
      read_status = HWSERIAL5.read();
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }

  Serial.print("Status=");
  Serial.println(read_status, DEC);

  loadPatchDataU();
  currentPatchNumber = number;
}

void Synthesizer::selectPatchL(int number) {
  int synthPatchNumber = number - 1;

  Serial.print("Selecting patch #");
  Serial.print(synthPatchNumber);
  Serial.print(" on Synth...");

  HWSERIAL4.write('r');  // 'r' = Read program
  HWSERIAL4.write(synthPatchNumber);



  int bytesRead = 0;
  int retry = 0;
  while (bytesRead == 0 && retry != 100) {
    if (HWSERIAL4.available()) {
      read_status = HWSERIAL4.read();
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }

  Serial.print("Status=");
  Serial.println(read_status, DEC);

  loadPatchDataL();
  currentPatchNumber = number;
}

void Synthesizer::changePatchU(int number) {
  currentPatchNumber = number;
}

void Synthesizer::changePatchL(int number) {
  currentPatchNumber = number;
}

void Synthesizer::loadPatchDataU() {
  HWSERIAL5.write('d');  // 'd' = Display program

  Serial.println("Reading patch data from Synth...");

  byte rxBuffer[512];
  int bytesRead = 0;
  int retry = 0;
  while (bytesRead != 512 && retry != 100) {
    if (HWSERIAL5.available()) {
      byte b = HWSERIAL5.read();
      rxBuffer[bytesRead] = b;
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }
  HWSERIAL5.flush();
  memcpy(currentPatchDataU, rxBuffer, 512);
  setCurrentPatchNameU();
}

void Synthesizer::loadPatchDataL() {
  HWSERIAL4.write('d');  // 'd' = Display program

  Serial.println("Reading patch data from Synth...");

  byte rxBuffer[512];
  int bytesRead = 0;
  int retry = 0;
  while (bytesRead != 512 && retry != 100) {
    if (HWSERIAL4.available()) {
      byte b = HWSERIAL4.read();
      rxBuffer[bytesRead] = b;
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }
  HWSERIAL4.flush();
  memcpy(currentPatchDataL, rxBuffer, 512);
  setCurrentPatchNameL();
}

void Synthesizer::savePatchDataU(int number) {
  int synthPatchNumber = number - 1;

  Serial.println("Writing patch data from Synth...");
  Serial.println(number);
  HWSERIAL5.write('w');  // 'w' = Write program
  HWSERIAL5.write(synthPatchNumber);
}

void Synthesizer::savePatchDataL(int number) {
  int synthPatchNumber = number - 1;

  Serial.println("Writing patch data from Synth...");
  Serial.println(number);
  HWSERIAL4.write('w');  // 'w' = Write program
  HWSERIAL4.write(synthPatchNumber);
}


void Synthesizer::setCurrentPatchNameU() {
  string patchName = "";

  for (int i = 480; i <= 504; i++) {
    patchName += (char)currentPatchDataU[i];
  }
  currentPatchNameU = patchName;

  Serial.print("Patch name: ");
  Serial.println(patchName.c_str());
}

void Synthesizer::setCurrentPatchNameL() {
  string patchName = "";

  for (int i = 480; i <= 504; i++) {
    patchName += (char)currentPatchDataL[i];
  }
  currentPatchNameL = patchName;

  Serial.print("Patch name: ");
  Serial.println(patchName.c_str());
}

int Synthesizer::getPatchNumberU() const {
  return currentPatchNumber;
}

int Synthesizer::getPatchNumberL() const {
  return currentPatchNumber;
}

const string &Synthesizer::getPatchNameU() const {
  return currentPatchNameU;
}

const string &Synthesizer::getPatchNameL() const {
  return currentPatchNameL;
}

byte Synthesizer::getParameter(int number) const {
  return currentPatchDataU[number];
}

byte Synthesizer::getParameterU(int number) const {
  return currentPatchDataU[number];
}

byte Synthesizer::getParameterL(int number) const {
  return currentPatchDataL[number];
}

void Synthesizer::setParameter(int number, int value) {
    HWSERIAL5.write('s');  // 's' = Set Parameter

    if (number > 255) {
      // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
      HWSERIAL5.write(255);
      HWSERIAL5.write(number - 256);
      HWSERIAL5.write(value);
    } else {
      HWSERIAL5.write(number);
      HWSERIAL5.write(value);
    }

    currentPatchDataU[number] = value;

    if (number >= 480 && number <= 504) {
      setCurrentPatchNameU();
    }
}

void Synthesizer::setParameterU(int number, int value) {
  HWSERIAL5.write('s');  // 's' = Set Parameter

  if (number > 255) {
    // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
    HWSERIAL5.write(255);
    HWSERIAL5.write(number - 256);
    HWSERIAL5.write(value);
  } else {
    HWSERIAL5.write(number);
    HWSERIAL5.write(value);
  }

  currentPatchDataU[number] = value;

  if (number >= 480 && number <= 504) {
    setCurrentPatchNameU();
  }
}
void Synthesizer::setParameterL(int number, int value) {
  HWSERIAL4.write('s');  // 's' = Set Parameter

  if (number > 255) {
    // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
    HWSERIAL4.write(255);
    HWSERIAL4.write(number - 256);
    HWSERIAL4.write(value);
  } else {
    HWSERIAL4.write(number);
    HWSERIAL4.write(value);
  }

  currentPatchDataL[number] = value;

  if (number >= 480 && number <= 504) {
    setCurrentPatchNameL();
  }
}

void Synthesizer::begin() {
  HWSERIAL5.begin(500000, SERIAL_8N1);  // XVA1 Serial
  HWSERIAL4.begin(500000, SERIAL_8N1);  // XVA1 Serial
}

Envelope Synthesizer::getEnvelopeValues(Envelope &envelope) {
  Envelope returnEnvelope = Envelope();

  for (int i = 0; i < 6; ++i) {
    returnEnvelope.level[i] = getParameterU(envelope.level[i]);
    returnEnvelope.rate[i] = getParameterU(envelope.rate[i]);
  }

  return returnEnvelope;
}
