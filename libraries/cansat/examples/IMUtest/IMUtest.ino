

#define CANSAT_PRINT Serial    //define above <CansatDebug.h>
#include <CansatDebug.h>
#include <CansatSerial.h>
#include <CansatSystem.h>

#define IMU_DATA_SIZE 60
char imu_data[IMU_DATA_SIZE];

//#define OUTPUT_PROCESSING
#define OUTPUT_SERIAL_MONITOR
static CansatHwSerial PLport(Serial1);



void setup() {

  // put your setup code here, to run once:
  CansatSystemInit();  
  PLport.begin(115200);
  PLport.RxModePortSet(RxMode_IMU_PORT);
  Serial.begin(115200);

  pinMode(LED0, OUTPUT);  
}

float gyro[3]; //[roll,pirch,yaw]
void loop() {
  // put your main code here, to run repeatedly:
  float ax,ay,az;
  if( PLport.available() ) { 
      PLport.read(imu_data,IMU_DATA_SIZE);
      //Serial.write(imu_data);
      getAccelgyro(imu_data,gyro);
   #ifdef OUTPUT_SERIAL_MONITOR   
      Serial.print("gyro roll/pirch/yaw\t");      
      Serial.print(gyro[0]);
      Serial.print('\t');
      Serial.print(gyro[1]);
      Serial.print('\t');
      Serial.println(gyro[2]);
   #endif   
   #ifdef OUTPUT_PROCESSING        
      Serial.print(gyro[0]); //roll,phi
      Serial.print(" ");
      Serial.print(gyro[1]); //pitch,theta
      Serial.print(" ");
      Serial.println(gyro[2]); //yaw,psi
   #endif        
    }
    delay(20);
    
}

void getAccelgyro(char *imu_raw,float *accelgyro){
  
  char *tokenFrame = NULL;
  char *token =NULL;

  
  tokenFrame = strtok(imu_raw, "*"); 
  tokenFrame = strtok(NULL, "*"); //skip first frame data
  int i=0;
  for (token = strtok(tokenFrame, ","); token != NULL; token = strtok(NULL, ",")){
    
    char *unconverted;
     accelgyro[i]= strtod(token, &unconverted);
     i++;
  }

  
}


