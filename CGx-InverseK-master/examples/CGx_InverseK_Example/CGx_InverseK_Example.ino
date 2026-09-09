


// Arduino/Teensy example for Arduino Braccio

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

float a0, a1, a2, a3;
float b0, b1, b2, b3;
float c0, c1, c2, c3;
float d0, d1, d2, d3;


void setup() {
  Serial.begin(9600);
  Braccio.begin();

  // Setup the lengths and rotation limits for each link
  Link base, upperarm, forearm, hand;

  base.init(0, b2a(0.0), b2a(180.0));
  upperarm.init(200, b2a(15.0), b2a(165.0));
  forearm.init(200, b2a(0.0), b2a(180.0));
  hand.init(270, b2a(0.0), b2a(180.0));

  // Attach the    to the inverse kinematic model
  InverseK.attach(base, upperarm, forearm, hand);



  // InverseK.solve() return true if it could find a solution and false if not.

  // Calculates the angles without considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3)
  if(InverseK.solve(400, -325, -90, a0, a1, a2, a3)) {
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
    Serial.println("No solution found!");
  }

    if(InverseK.solve(220, 325, 300, b0, b1, b2, b3)) {
    Serial.print(a2b(b0)); Serial.print(',');
    Serial.print(a2b(b1)); Serial.print(',');
    Serial.print(a2b(b2)); Serial.print(',');
    Serial.println(a2b(b3));
  } else {
    Serial.println("No solution found!");
  }

    if(InverseK.solve(220, 325, -90, c0, c1, c2, c3)) {
    Serial.print(a2b(c0)); Serial.print(',');
    Serial.print(a2b(c1)); Serial.print(',');
    Serial.print(a2b(c2)); Serial.print(',');
    Serial.println(a2b(c3));
  } else {
    Serial.println("No solution found!");
  }
    if(InverseK.solve(300, 0, 200, d0, d1, d2, d3)) {
    Serial.print(a2b(d0)); Serial.print(',');
    Serial.print(a2b(d1)); Serial.print(',');
    Serial.print(a2b(d2)); Serial.print(',');
    Serial.println(a2b(d3));
  } else {
    Serial.println("No solution found!");
  }
}

void loop() {


  Braccio.ServoMovement(20,     a2b(a0), a2b(a1), a2b(a2), a2b(a3), 180, 10);
  delay (1000);
  Braccio.ServoMovement(20,     a2b(a0), a2b(a1), a2b(a2), a2b(a3), 180, 73);
  delay (1000);
  Braccio.ServoMovement(20,     a2b(b0), a2b(b1), a2b(b2), a2b(b3), 180, 73);
  delay (1000);
  Braccio.ServoMovement(20,     a2b(c0), a2b(c1), a2b(c2), a2b(c3), 180, 73);
  delay (1000);
  Braccio.ServoMovement(20,     a2b(c0), a2b(c1), a2b(c2), a2b(c3), 180, 10);
  delay (1000);
  Braccio.ServoMovement(20,     a2b(d0), a2b(d1), a2b(d2), a2b(d3), 180, 10);
  delay (1000);


}

// Quick conversion from the Braccio angle system to radians
float b2a(float b){
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
  return (a + HALF_PI) * 180 / PI;
}
