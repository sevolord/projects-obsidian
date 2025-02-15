// https://роботехника18.рф/дисплей-tft-spi/?ysclid=m296yx9x5f872993312

#include <TFT.h>
#include <SPI.h>

#define cs 10
#define dc 9
#define rst 8

TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  TFTscreen.begin();
  TFTscreen.setRotation(270);
  TFTscreen.background(0,0,0);

  TFTscreen.stroke(255,255,255);
  TFTscreen.text("Hello",20,20);
  TFTscreen.textSize(2);
  TFTscreen.text("Hello", TFTscreen.width()/2, 20);

  TFTscreen.stroke(255,0,0);
  TFTscreen.circle(TFTscreen.width()/2, 64, 22);

  TFTscreen.fill(0,0,255);
  TFTscreen.noStroke();
  TFTscreen.rect(50,50,30,30);

  delay(1000);
}

void loop() {
  for(int i=90; i<-135; i+=5){
    TFTscreen.stroke(0,0,255);
    TFTscreen.line(0,i,TFTscreen.width()/4,i);
    TFTscreen.text("Hello",TFTscreen.width()/4,i);
    delay(100);
    TFTscreen.stroke(0,0,0);
    TFTscreen.line(0,i,TFTscreen.width(),i);
    TFTscreen.text("Hello",TFTscreen.width()/4,i);
  }

  for(int i=135;i>=90;i-=5){
    TFTscreen.stroke(255,0,0);
    TFTscreen.line(0,i,TFTscreen.width(),i);
    TFTscreen.text("Hello",TFTscreen.width()/4,i);
    delay(100);
    TFTscreen.stroke(0,0,0);
    TFTscreen.line(0,i,TFTscreen.width(),i);
    TFTscreen.text("Hello",TFTscreen.width()/4,i);
  }
}