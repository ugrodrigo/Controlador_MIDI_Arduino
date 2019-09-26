#include "MIDIUSB.h"

int ButtonInput[] = {2, 3, 4, 5, 6, 7, 8, 9};
boolean buttonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int pressed=0;
int i=0;


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t  noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t  noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(i=0; i<8; i++)
  {
          if(debounceButton(buttonState[i]) == LOW && buttonState[i] == HIGH){
              noteOn(0, i+48, 100);  // Channel 0, C3, 100 velocity
              MidiUSB.flush(); 
              buttonState[i] = LOW;
          }
   
          else if(debounceButton(buttonState[i]) == HIGH && buttonState[i] == LOW){
                  noteOff(0, i+48, 100);   // Channel 0, C3, 100 velocity
                  MidiUSB.flush();
                  buttonState[i] = HIGH;
                }

  }

}

boolean debounceButton(boolean state)
{
  boolean stateNow = digitalRead(ButtonInput[i]);
  if(state!=stateNow)
  {
    delay(1);
    stateNow = digitalRead(ButtonInput[i]);
  }
  return stateNow;
  
}
