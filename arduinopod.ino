// POD 2.0 MIDI-Controller
// 4 Buttons that send CC-Signals to the POD and Switch to
// a different Program (1A - 1D)
// TODO: Maybe use interrupts instead of looping over the state of each button
// TODO: Add little delay after sending commands to the pod, since pushing two or more buttons
//       simultaneuously seems to restart the pod and is probably not the best idea...

int PinButton1 = 12;
int PinButton2 = 11;
int PinButton3 = 10;
int PinButton4 = 9;

int PinLED1 = 5;
int PinLED2 = 4;
int PinLED3 = 3;
int PinLED4 = 2;

int currentProg = 0; // So we can see if we even need to change the Program

void resetLEDs() {
    digitalWrite(PinLED1, LOW);
    digitalWrite(PinLED2, LOW);
    digitalWrite(PinLED3, LOW);
    digitalWrite(PinLED4, LOW);
    }

void sendMIDI(int program) {
    // Sysex to change to program 1A:
    // f0 00 01 0c 00 00 c0 01 f7
    Serial.write(0xf0);
    Serial.write(0x00);
    Serial.write(0x01);
    Serial.write(0x0c);
    Serial.write(0x00);
    Serial.write(0x00);
    Serial.write(0xc0);
    Serial.write(program);
    Serial.write(0xf7);
    }

void setup() {
    Serial.begin(31250); // Baud-Rate for MIDI
    pinMode(PinButton1, INPUT);
    pinMode(PinButton2, INPUT);
    pinMode(PinButton3, INPUT);
    pinMode(PinButton4, INPUT);
    pinMode(PinLED1, OUTPUT);
    pinMode(PinLED2, OUTPUT);
    pinMode(PinLED3, OUTPUT);
    pinMode(PinLED4, OUTPUT);
    resetLEDs();
}

void loop() {

    // Buttons are HIGH by default and LOW when pressed
    // Button 1 -> Change to Program 1A
    if (digitalRead(PinButton1) == LOW && currentProg != 1) {
        currentProg = 1;
        resetLEDs();
        digitalWrite(PinLED1, HIGH);
        sendMIDI(1);
        }

    // Button 2 -> Change to Program 1B
    if (digitalRead(PinButton2) == LOW && currentProg != 2) {
        currentProg = 2;
        resetLEDs();
        digitalWrite(PinLED2, HIGH);
        sendMIDI(2);
        }

    // Button 3 -> Change to Program 1C
    if (digitalRead(PinButton3) == LOW && currentProg != 3) {
        currentProg = 3;
        resetLEDs();
        digitalWrite(PinLED3, HIGH);
        sendMIDI(3);
        }

    // Button 4 -> Change to Program 1D
    if (digitalRead(PinButton4) == LOW && currentProg != 4) {
        currentProg = 4;
        resetLEDs();
        digitalWrite(PinLED4, HIGH);
        sendMIDI(4);
        }
    }
