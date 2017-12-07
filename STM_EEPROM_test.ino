#include <EEPROM.h>

uint16_t data;
uint16_t Addr = 0x00;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
    String str = Serial.readString();

Serial.println(str);
    write_string_EEPROM(Addr, str);

    String echo = read_string_EEPROM(Addr);

    Serial.println(echo);
  }

}

void write_string_EEPROM (int Addr, String Str) {
    
    byte lng=Str.length();
    //EEPROM.begin (64);
    //if (lng>31 )  lng=0;
    EEPROM.write(Addr , lng);
    unsigned char* buf = new unsigned char[lng+1];
    //uint16_t buf[lng/2];

//for (byte i; i < len; )
    
    Str.getBytes(buf, lng + 1);

    
    Addr++;
    for(byte i = 0; i < lng; i+=2) {
      uint16_t buffer = ((uint16_t) buf[i+1] << 8) | buf[i];
      
      EEPROM.write(Addr+i, buffer); 
      }
    //EEPROM.end();
}

char *read_string_EEPROM (int Addr) {
    byte lng = EEPROM.read(Addr);
    char* buf = new char[lng+1];
    Addr++;
    for(byte i = 0; i < lng; i+=2) 
    { uint16_t buffer;
     EEPROM.read(i+Addr, &buffer);
     buf[i] = buffer & 0xff;
     buf[i+1] = (buffer >> 8);
     Serial.println(buf[i]);
     Serial.println(buf[i+1]);
    }
    
    
    buf[lng] = '\x0';
    return buf;
}
