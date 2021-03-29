// POD 2.0 MIDI-Controller
// 4 Buttons that send CC-Signals to the POD and Switch to
// a different Program (1A - 1D)
// Added functionality: Switch between banks 1 and 2

int PinButton1 = 12;
int PinButton2 = 11;
int PinButton3 = 10;
int PinButton4 = 9;

int PinLED1 = 5;
int PinLED2 = 4;
int PinLED3 = 3;
int PinLED4 = 2;

int currentBank = 0;
int currentProg = 0; // So we can see if we even need to change the Program

void resetLEDs() {
    digitalWrite(PinLED1, LOW);
    digitalWrite(PinLED2, LOW);
    digitalWrite(PinLED3, LOW);
    digitalWrite(PinLED4, LOW);
    }

void setLEDs() {
    digitalWrite(PinLED1, HIGH);
    digitalWrite(PinLED2, HIGH);
    digitalWrite(PinLED3, HIGH);
    digitalWrite(PinLED4, HIGH);
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

void buttonAction(int button, int led, int prog) {
    // Buttons are HIGH by default and LOW when pressed
    if (digitalRead(button) == LOW) {
        if (currentProg != prog) {
            currentProg = prog;
            if (currentBank == 1) {
                // if we are in bank 2 we "invert" the LEDs
                setLEDs();
                digitalWrite(led, LOW);
                }
            else {
                resetLEDs();
                digitalWrite(led, HIGH);
            }
            sendMIDI(currentBank*4+prog);
            delay(250);
            }
        else if (currentProg == prog) {
            currentBank = currentBank ^ 1;
            if (currentBank == 1) {
                // if we are in bank 2 we "invert" the LEDs
                setLEDs();
                digitalWrite(led, LOW);
            }
            else {
                resetLEDs();
                digitalWrite(led, HIGH);
                }
            sendMIDI(currentBank*4+prog);
            delay(250);
            }
        }
    }

void loop() {

    // check if buttons were pressed:
    buttonAction(PinButton1, PinLED1, 1);
    buttonAction(PinButton2, PinLED2, 2);
    buttonAction(PinButton3, PinLED3, 3);
    buttonAction(PinButton4, PinLED4, 4);
    }
