//Code by Reichenstein7 (thejamerson.com)

//Keyboard Controls:
//
// q -Motor 1 Left
// w -Motor 1 Stop
// e -Motor 1 Right
//
// a -Motor 2 Left
// s -Motor 2 Stop
// d -Motor 2 Right

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motor 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 5;
int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed

void setup() {  // Setup runs once per reset
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);

  //Define L298N Dual H-Bridge Motor Controller Pins

  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);

  // initial state
  analogWrite(speedPinA, 255);//Sets speed variable via PWM
  analogWrite(speedPinB, 255);//Sets speed variable via PWM
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
}

void loop() {
  char sdata[256];
  int nl = 10; // end of line character

  // Initialize the Serial interface:

  if (Serial.available() > 0) {
    int bytes = Serial.readBytesUntil(nl, sdata, 80); // read until end line
    int speed; // Local variable

    //Serial.println(bytes);
    //    for (int i = 0; i < bytes; i++) {
    //      Serial.print(sdata[i]);
    //    }

    sdata[bytes] = '\0';   // make it a proper string
    Serial.print("Received: ");
    Serial.println(sdata);


    switch (sdata[0]) {

      //______________Motor 1______________

      case 'q': // Motor 1 Forward
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
        Serial.println("   "); // Creates a blank line printed on the serial monitor
        break;

      case 'w': // Motor 1 Stop (Freespin)
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, LOW);
        Serial.println("Motor 1 Stop");
        Serial.println("   ");
        break;

      case 'e': // Motor 1 Reverse
        digitalWrite(dir1PinA, HIGH);
        digitalWrite(dir2PinA, LOW);
        Serial.println("Motor 1 Reverse");
        Serial.println("   ");
        break;

      //______________Motor 2______________

      case 'a': // Motor 2 Forward
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, HIGH);
        Serial.println("Motor 2 Forward");
        Serial.println("   ");
        break;

      case 's': // Motor 1 Stop (Freespin)
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, LOW);
        Serial.println("Motor 2 Stop");
        Serial.println("   ");
        break;

      case 'd': // Motor 2 Reverse
        digitalWrite(dir1PinB, HIGH);
        digitalWrite(dir2PinB, LOW);
        Serial.println("Motor 2 Reverse");
        Serial.println("   ");
        break;

      case '8':  // Move forward
        {
          int speed1 = 0, speed2 = 0;
          sscanf(sdata, "8 %d %d", &speed1, &speed2);
          if (speed1 > 0 && speed2 > 0) {
            sprintf(sdata, "Set speed %d %d", speed1, speed2);
            Serial.println(sdata);
            analogWrite(speedPinA, speed1);//Sets speed variable via PWM
            analogWrite(speedPinB, speed2);//Sets speed variable via PWM
          }
          digitalWrite(dir1PinA, LOW);
          digitalWrite(dir2PinA, HIGH);
          digitalWrite(dir1PinB, LOW);
          digitalWrite(dir2PinB, HIGH);
          Serial.println("Forward");
          
        }

        break;

      case '2':  // move backward
        {
          int speed1 = 0, speed2 = 0;
          sscanf(sdata, "2 %d %d", &speed1, &speed2);
          if (speed1 > 0 && speed2 > 0) {
            sprintf(sdata, "Set speed %d %d", speed1, speed2);
            Serial.println(sdata);
            analogWrite(speedPinA, speed1);//Sets speed variable via PWM
            analogWrite(speedPinB, speed2);//Sets speed variable via PWM
          }
          digitalWrite(dir1PinA, HIGH);
          digitalWrite(dir2PinA, LOW);
          digitalWrite(dir1PinB, HIGH);
          digitalWrite(dir2PinB, LOW);
          Serial.println("Reverse");
          
        }
        break;
      case 'S': // set speed of two motors
        {
          int speed1, speed2;
          sscanf(sdata, "S %d %d", &speed1, &speed2);
          analogWrite(speedPinA, speed1);//Sets speed variable via PWM
          analogWrite(speedPinB, speed2);//Sets speed variable via PWM
          sprintf(sdata, "Set speed %d %d", speed1, speed2);
          Serial.println(sdata);
          
        }
        break;

      default:
        // stop
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, LOW);
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, LOW);
        Serial.println("STOP");

    }
  }
}
