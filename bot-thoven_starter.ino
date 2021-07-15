/////////////////////////////////////////////////////////////////////////////////////////////////
// BOT-THOVEN - STARTER CODE
// Starter Code to play a tune on a xylophone-playing robot
// By JASON PAK, 2020
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// global variable to present the PCA9685 Servo Driver
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

/////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE CLASS
// Each "Note" represents one key on the xylophone and its respective servo motor
//////////////////////////////////////////////////////////////////////////////////////////////////

class Note {
  private:
    int servoNum; // unique ID for the servo motor
    int dynamic; // larger number = larger volume/dynamic
    int minVal;  //servo rotation value at which mallet touches key
    int maxVal; //servo rotation value that mallet comes up to after touching key

  // Constructor
  public:
    Note(int servoN, int dyn, int minV) {
      this -> servoNum = servoN;
      this->dynamic = dyn;
      this->minVal = minV;
      this->maxVal = minV + (60 / dyn); //adjusts maxValue depending on dynamic level
    }

    // Method to play the note for a given duration (ms)
    void Note::playNote(int dur)
    {
      // rotate motor downwards to strike xylophone key
      for (uint16_t pulselen = this->maxVal; pulselen > curval; pulselen--) {
        pwm1.setPWM(this->servoNum, 0, pulselen);
        delay(this->dynamic);
      }

      // rotate motor back up to starting position
      for (uint16_t pulselen = curval; pulselen < this->maxVal; pulselen++) {
        pwm1.setPWM(this->servoNum, 0, pulselen);
        delay(this->dynamic);
      }

      delay(dur); // wait for the given duration
      return;
    }

    // Getter Methods
    int Note::getMin()
    {
      return minVal;
    }

    int Note::getMax()
    {
      return maxVal;
    }

    int Note::getServo()
    {
      return servoNum;
    }

    int Note::getDynamic()
    {
      return dynamic;
    }

    int Note::getDriver()
    {
      return driverVal;
    }

    // Setter Method to update the dynamic (volume)
    void Note::setDynamic(int x)
    {
      this->dynamic = x;
      //when updating the dynamic, the maxVal adjusts accordingly as well
      this->maxVal = minVal + (60 / x);
    }

};

/////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN CODE
// User must modify the code based on their set-up and the tune they wish to perform
// Sample code is provided below
/////////////////////////////////////////////////////////////////////////////////////////////////

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//Instantiate Notes -> params: (servo id, dynamic, min)
Note g1 = Note(0, 2, 109);
Note a1 = Note(1, 2, 134);
Note b1 = Note(2, 2, 132);
Note c1 = Note(3, 2, 151);
Note d1 = Note(4, 2, 150);
Note e1 = Note(5, 2, 120);
Note f1 = Note(6, 2, 140);
Note g2 = Note(7, 2, 124);

void setup() {
  Serial.begin(9600);
  pwm1.begin();
  pwm1.setPWMFreq(SERVO_FREQ);
  delay(10);
}

void loop() {
  //modify the code depending on the tune you wish to play!
  // code sample below plays an upwards scale, 50ms per note:
  g1.playNote(50);
  a1.playNote(50);
  b1.playNote(50);
  c1.playNote(50);
  d1.playNote(50);
  e1.playNote(50);
  f1.playNote(50);
  g2.playNote(50);
}
