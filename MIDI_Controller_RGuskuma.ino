int ButtonInput[] = {5, 3, 4, 2, 9, 8, 7, 6, 10, 16, 14, 15};
boolean buttonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int pressed=0;
int i=0;

int potenciometro[] = {0,0,0,0};
int j;
int val[] = {0,0,0,0}; // Valores iniciais dos potenciometros
int lastVal[] = {0,0,0,0};



void setup() {
}

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}

// Primeiro parametro eh o canal de comunicacao MIDI
// Segundo parametro eh a nota musical
// Terceiro parametro eh a intesidade da nota musical


void controlChange(byte channel, byte control, byte value) {
  MIDIEvent event = {0x0B, 0xB0 | channel, control, value};
  MIDIUSB.write(event);
}

// Primeiro parametro eh o tipo de evento
// Segundo parametro eh o tipo de evento combinado com o canal
// Terceiro parametro eh o valor do tipo de comando CC (0-119)
// Quarto parametro eh o valor do comando de controle (0-127)


void loop() {
  
for( j=0 ; j<4 ; j++){
    potenciometro[j] = analogRead(j+A0);
    val[j] = potenciometro[j]/8;
    round(val[j]);
    if(val[j] != lastVal[j]){
    controlChange(j,16+j,val[j]);
    }
    lastVal[j] = val[j];
}
  
for(i=0; i<12; i++)
  {
          if(debounceButton(buttonState[i]) == LOW && buttonState[i] == HIGH){
              noteOn(0, i+48, 100);  // Channel 0, C3, 100 velocity
              MIDIUSB.flush(); 
              buttonState[i] = LOW;
          }
   
          else if(debounceButton(buttonState[i]) == HIGH && buttonState[i] == LOW){
                  noteOff(0, i+48, 100);   // Channel 0, C3, 100 velocity
                  MIDIUSB.flush();
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
