#include <location.h>


float homepos[2]={37.287413, 127.062302};
float currpos[2]={37.359498, 127.105321};
float result[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  get_ditance_bearing(currpos,homepos,result);
  Serial.print("dist(km)=");
  Serial.println(result[0]/1000.);
  Serial.print("bearing=");
  Serial.println(result[1]);
}


void loop() {
  // put your main code here, to run repeatedly:

}
