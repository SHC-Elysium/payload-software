const int STEP=23;
#include <AccelStepper.h>
const int DIR=24;
const long targetApogee=10000;
const long minposition=0;
const long maxposition=X; //idk what that is
//AccelStepper with pins listed on driver
AccelStepper airbrakemotor(AccelStepper::DRIVER, STEP, DIR);
void setup() {
  //set motor speed and acceleration
 airbrakemotor.setMaxSpeed(X); //max speed
 airbrakemotor.setAcceleration(X); //acceleration
 airbrakemotor.setCurrentPosition(0); //assume motor is in retracted position when starts

}

void loop() {
  //reacts to the predicted apogee from runge-kutta method and moves in or out.
  //example method for constnatly adjusting motor using controller
  long currentPos = airbrakemotor.currentPosition(); //current motor position
  long predictedApogee = calcApogee(); //calculated apogee
  long Error=predictedApogee-targetApogee; //error based on difference between predicted apogee and target apogee
  long stepperCorrection=K*Error; //some k constant that adjusts the motor a certain amount based on the relative error
  long targetPos = currentPos+stepperCorrection;
  targetPos = constrain(targetPos,minposition,maxposition); //ensures the motor doesnt extend past its min/max position
  airbrakemotor.moveTo(targetPos); //tell motor to move to new position
  airbrakemotor.run(); 
}  
