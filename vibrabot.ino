#include <JeeLib.h> 

byte recvCount;

// set PINs
int gotMsg = 4;   // set the digital for LED showing incomming signals
int vibrator = 5; // set the analog pin where the vibrator is connected

// set node id and group id 
int nodeId = 4; // the ID of this node
int groupId = 4; // the ID of the group this node is addded to

// initialize variables 
byte remoteVal; // each byte sent from the server is parsed as an incomming value of type char
int valInt; // remote val as integer. 

int remoteValMap = 0; // a value in the range 0 - 255 to be sent as an analog write: either to the vibrator and/or other sensors...
int testTimer = 0;
String s = "";

char ASCIIchar = '0';

void setup () 
{ 
    Serial.begin(57600); 
    Serial.println("\n[vibrabot1]"); 
    rf12_initialize(nodeId, RF12_915MHZ, groupId); 
    pinMode(gotMsg, OUTPUT); 
    pinMode(vibrator, OUTPUT); 
} 


void loop () 
{ 
  testTimer++;

//  ASCIIchar++;
  
  // log 
  //Serial.println(testTimer); 
  //Serial.println(ASCIIchar); 
  
//  analogWrite(vibrator, testTimer);


/*  
  if(testTimer>254)
  {
    testTimer = 0;
    analogWrite(vibrator, testTimer);
//    delay(100);
  } 
 */ 
  // check when the node gets a package
  if (rf12_recvDone() && rf12_crc == 0) { 

    // confirm packet received
    digitalWrite(4,HIGH); 
    delay(100); 
    digitalWrite(4,LOW); 

    for (byte i = 0; i < rf12_len; ++i) { 
      Serial.println(""); 

      // stored incoming data
      remoteVal =  rf12_data[i];
    
      // transform byte into an integer
//      valInt = remoteVal - '0';
      valInt = (int)remoteVal;

      /* Transform value 0-5 to 0-255
      Note that this assumes that only values between 0 and 5
      are sent to the node
      */
      remoteValMap = map(valInt, 0, 5, 0, 255);
      
      analogWrite(vibrator, remoteValMap);
      
      // print data in incoming byte
      Serial.print(remoteValMap); 
    } // end for each package 
    
    recvCount = (recvCount + 1) % 20; 
       //*/ 
  } // end if this node gets a package

//  delay(30);
} // end loop function
