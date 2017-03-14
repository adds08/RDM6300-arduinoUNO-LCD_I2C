#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>

int rx=5;
int tx=1;
int id = 0;
char char_id[11];
int count=0;
boolean isAuthorized = false;
char* aTag[4];

SoftwareSerial rfID(rx,tx);
LiquidCrystal_I2C lcd_display(0x3F, 16, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("initiated");
  lcd_display.init();
  rfID.begin(9600);
  lcd_display.setBacklight(true);
  lcd_display.print("RF-ID");
  available_tags();
}

void available_tags() {
  aTag[0] = "36001E42CB";//key-tag
  aTag[1] = "3C002F8179"; 
  aTag[2] = "3C002E7A89"; 
}

void loop() {
  // put your main code here, to run repeatedly:
  check_id();
}

void display_id(){
  if(sizeof(char_id)>0){
    for(int i=0;i<3;i++){
      if(strcmp(aTag[i],char_id) == 0 ){
        isAuthorized = true;
        Serial.println(aTag[i]);
        Serial.println(char_id); 
        break;
      }
        Serial.println(aTag[i]);
        Serial.println(char_id); 
    }
    if(isAuthorized){
      lcd_display.print("Available");
      lcd_display.setCursor(0,1);
      lcd_display.print(char_id); 
      isAuthorized = false;
    }
    else{
      lcd_display.print("Unavailable!");
      lcd_display.setCursor(0,1);
      lcd_display.print(char_id);
    }
  }
  else{
    lcd_display.print("Some err");
  }
}

void check_id(){
   if(rfID.available()){
    id = rfID.read();
      if(id==2){
        count = 0;
      }
      else if(id==3){
        char_id[10] = 0;
        count = -1;
        clear_id();
        lcd_display.clear();  
        display_id();
      }
      else{      
        char_id[count] = id;
        count++;
      }
    }
}

void clear_id(){
  while (rfID.read() >= 0) {
    ;
  }
}

