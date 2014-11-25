/**
 * A serial controller to manage a steering servo and
 * a drive motor
 */

#define RESET 255

#define UP_DOWN_CAMERA_SERVO_PIN 9 
#define LEFT_RIGHT_CAMERA_SERVO_PIN 10

#define STEERING_SERVO_PIN 3

#define MOTOR_FWD_PIN 5
#define MOTOR_REV_PIN 6

int incomingCommand;
int incomingValue;

/**
 * Setup the pins for input/output
 */
void setup()
{
   pinMode(UP_DOWN_CAMERA_SERVO_PIN, OUTPUT);
   pinMode(LEFT_RIGHT_CAMERA_SERVO_PIN, OUTPUT);
   pinMode(STEERING_SERVO_PIN, OUTPUT);
   pinMode(MOTOR_FWD_PIN, OUTPUT);
   pinMode(MOTOR_REV_PIN, OUTPUT);
}

/**
 * Loops the serial monitor and passes the commands off onto the 
 * appropriate control
 */
void loop()
{
    if (Serial.available() > 0) 
    {
        incomingCommand = Serial.read();
        if(incomingCommand != RESET)
        {
          incomingValue = Serial.read();
          handleCommand(incomingCommand, incomingValue);
        }
    }
}

/**
 * Handles the command to the various IO devices
 * @param command The command
 * @param value The value to pass to the command
 */
void handleCommand(int command, int value)
{
  switch(command)
  {
    case STEERING_SERVO_PIN:
    case UP_DOWN_CAMERA_SERVO_PIN:
    case LEFT_RIGHT_CAMERA_SERVO_PIN:
      analogWrite(command, value);
      break;  
    case MOTOR_FWD_PIN:
      analogWrite(MOTOR_REV_PIN, 0);
      analogWrite(MOTOR_FWD_PIN, value);
      break;  
    case MOTOR_REV_PIN:
      analogWrite(MOTOR_FWD_PIN, 0);
      analogWrite(MOTOR_REV_PIN, value);
      break;  
    default:
      Serial.println("Invalid Command "); 
      Serial.print(command);
      Serial.print(" ");
      Serial.print(value);
      break;    
  }
}
