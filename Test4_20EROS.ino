
// Include libraries this sketch will use
#include  <Wire.h>
#include  <MCP342X.h>

// Instantiate objects used in this project
MCP342X myADC(0x6E);

void setup() {
  Wire.begin();  // join I2C bus

  Serial.begin(115200); // Open serial connection to send info to the host
  Serial.println("Starting up");
  Serial.println("Testing device connection...");
  Serial.println(myADC.testConnection() ? "MCP342X connection successful" : "MCP342X connection failed");

}  // End of setup()



//====mapfloat====

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  if ((in_max - in_min) + out_min != 0) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  } else {
    return 0;
  }
}



void loop() {
  static int32_t  result1;
  static int32_t  result2;

  myADC.configure( MCP342X_MODE_CONTINUOUS |
                   MCP342X_CHANNEL_1 |
                   MCP342X_SIZE_18BIT |
                   MCP342X_GAIN_1X
                 );
  myADC.startConversion();
  myADC.getResult(&result1);
  Serial.print("Ch1: ");
  Serial.print(result1);

  myADC.configure( MCP342X_MODE_CONTINUOUS |
                   MCP342X_CHANNEL_2 |
                   MCP342X_SIZE_18BIT |
                   MCP342X_GAIN_1X
                 );
  myADC.startConversion();
  myADC.getResult(&result2);
  Serial.print("\tCh2: ");
  Serial.println(result2);


  float val0 = mapfloat(result1, 25050, 91381, 4, 20);
  float val1 = mapfloat(result2, 25050, 91381, 4, 20);
  Serial.println(val0);
  Serial.println(val1);

}  // End of loop()
