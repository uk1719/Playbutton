#include <Arduino.h>

int Button_pin1=12;//〇12
int Button_pin2=14;//〇13
int Button_pin3=27;//〇27
int Button_pin4=26;//〇23

int Button_input1=0;
int Button_input2=0;
int Button_input3=0;
int Button_input4=0;

int Button_flag1=0;
int Button_flag2=0;
int Button_flag3=0;

int LED_pin1=4;
int LED_pin2=16;
int LED_pin3=17;
int ButtonLED_pin=5;

int Button_status=0;
/*
0:何もスイッチが押されず1桁目も押されていない状態(初期状態)
1:スイッチが1桁だけ認識された状態
2:スイッチが2桁認識された状態
3:スイッチが3桁押されてすべて正解の状態
4:スイッチが3桁押されて1つだけ正解の状態
5:スイッチが3桁押されて2つ正解の状態
*/
int Button_error=0;
/*
10:リセットスイッチが押されている状態(待機状態)
11:リセットスイッチとキースイッチが押されている状態(リセット確定)
20:2つ以上のスイッチが押されている状態
*/

int Button_num=0;

int Button_correct_num=0;
int Button_correct1=0;
int Button_correct2=0;
int Button_correct3=0;

int correct_cnt=0;

int LED_controle=0;

int Serial_num=0;

int reset_flag=0;


int Button_status_check(int num)
{
  
   
    if(num>100)
    {
      return 3;
    }
    else if(num>10)
    {
      return 2;
    }
    else if(num>0)
    {
      return 1;
    }
  else 
  {
    return 0;
  }
}
  

  int Button_correct_random()
  {


    int x=0;
    x=random(1,6);
    if(x==1)
    {
      return 123;
    }
    else if(x==2)
    {
      return 132;
    }
    else if(x==3)
    {
      return 231;
    }
    else if(x==4)
    {
      return 213;
    }
    else if(x==5)
    {
      return 312;
    }
    else 
    {
      return 321;
    }
  }


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // 初期化が完了したらメッセージを出す
  Serial.println("ESP32 Serial Monitor Ready!");

  Button_correct_num=Button_correct_random();

  pinMode(Button_pin1,INPUT_PULLDOWN);
  pinMode(Button_pin2,INPUT_PULLDOWN);
  pinMode(Button_pin3,INPUT_PULLDOWN);
  pinMode(Button_pin4,INPUT_PULLDOWN);

  pinMode(LED_pin1,OUTPUT);
  pinMode(LED_pin2,OUTPUT);
  pinMode(LED_pin3,OUTPUT);
  pinMode(ButtonLED_pin,OUTPUT);

  digitalWrite(LED_pin1,LOW);
  digitalWrite(LED_pin2,LOW);
  digitalWrite(LED_pin3,LOW);
  digitalWrite(ButtonLED_pin,LOW);

  }

void loop() {




  Button_input1=digitalRead(Button_pin1);
  Button_input2=digitalRead(Button_pin2);
  Button_input3=digitalRead(Button_pin3);
  Button_input4=digitalRead(Button_pin4);

  Serial_num=Button_input1+Button_input2*10+Button_input3*100+Button_input4*1000;

  Serial.print("Serial_num:");
  Serial.println(Serial_num);
  delay(500);
  Serial.print("correctnum:");
  Serial.println(Button_correct_num);
  Serial.print("Button_num:");
  Serial.println(Button_num);
/*
  digitalWrite(LED_pin1,HIGH);
  digitalWrite(LED_pin2,HIGH);
  digitalWrite(LED_pin3,HIGH);
  
  Serial.println("HIGH");
  delay(2000);
  
  digitalWrite(LED_pin1,LOW);

  digitalWrite(LED_pin2,LOW);
  digitalWrite(LED_pin3,LOW);

  Serial.println("LOW");
  delay(2000);
*/

  if(Button_input4==0)
  {
    reset_flag=0;
  }

if(Button_input1+Button_input2+Button_input3==1)
{

  if(Button_input1)
  {
    digitalWrite(LED_pin1,HIGH);
    
    if(Button_flag1==0)
   {
    Button_status=Button_status_check(Button_num);
    Button_flag1=1;
    if(Button_status==0)
    {
      Button_num=Button_num+1;
    }
    else if(Button_status==1)
    {
      Button_num=Button_num+10;
    }
    else if(Button_status==2)
    {
      Button_num=Button_num+100;
      Button_status=3;
    }
  }

  }

  if(Button_input2)
  {
    digitalWrite(LED_pin2,HIGH);
    if(Button_flag2==0)
    {
      Button_status=Button_status_check(Button_num);
      Button_flag2=1;
     if(Button_status==0)
    {
      Button_num=Button_num+2;
    }
    else if(Button_status==1)
    {
      Button_num=Button_num+20;
    }
    else if(Button_status==2)
    {
      Button_num=Button_num+200;
      Button_status=3;
    }
  }
  }
  if(Button_input3)
  {
    digitalWrite(LED_pin3,HIGH);
    digitalWrite(ButtonLED_pin,HIGH);
    if(Button_flag3==0)
    {
      Button_status=Button_status_check(Button_num);
      Button_flag3=1;
     if(Button_status==0)
    {
      Button_num=Button_num+3;
    }
    else if(Button_status==1)
    {
      Button_num=Button_num+30;
    }
    else if(Button_status==2)
    {
      Button_num=Button_num+300;
      Button_status==3;
    }
  }
  }
}

  if(Button_input4)
  {
    digitalWrite(LED_pin1,LOW);
    digitalWrite(LED_pin2,LOW);
    digitalWrite(LED_pin3,LOW);

    if(reset_flag==0)
    {
      Button_correct_num=Button_correct_random();
      Button_num=0;
      Button_status=0;
      Button_flag1=0;
      Button_flag2=0;
      Button_flag3=0;
      reset_flag=1;
    }
  }
  if(Button_input3==0)
  {
    digitalWrite(ButtonLED_pin,LOW);
  }

  if(Button_status==3)
  {
     digitalWrite(LED_pin1,LOW);
        digitalWrite(LED_pin2,LOW);
        digitalWrite(LED_pin3,LOW);

    if(Button_correct_num%100==Button_num%100)
    {
      correct_cnt++;  
    }
    Button_correct_num=Button_correct_num-Button_correct_num%100;
    Button_num=Button_num-Button_num%100;
    if(Button_correct_num%10==Button_num%10)
    {
      correct_cnt++;
    }
    Button_correct_num=Button_correct_num-Button_correct_num%10;
    Button_num=Button_num-Button_num%10;
    if(Button_correct_num%10==Button_num%10)
    {
      correct_cnt++;
    }
    if(correct_cnt==0)
    {

    }
    else if(correct_cnt==1)
    {
      for(int i=0;i<5;i++)
      {
        digitalWrite(LED_pin1,HIGH);
        delay(200);
        digitalWrite(LED_pin1,LOW);
        delay(200);
      }
      Button_status=0;
      Button_flag1=0;
      Button_flag2=0;
      Button_flag3=0;
    digitalWrite(LED_pin1,LOW);
    digitalWrite(LED_pin2,LOW);
    digitalWrite(LED_pin3,LOW);
    }
    else if(correct_cnt==2)
    {
      for(int i=0;i<5;i++)
      {
        digitalWrite(LED_pin1,HIGH);
        delay(200);
        digitalWrite(LED_pin1,LOW);
        delay(200);
        digitalWrite(LED_pin2,HIGH);
        delay(200);
        digitalWrite(LED_pin2,LOW);
        delay(200);
      }
      Button_status=0;
      Button_flag1=0;
      Button_flag2=0;
      Button_flag3=0;
    digitalWrite(LED_pin1,LOW);
    digitalWrite(LED_pin2,LOW);
    digitalWrite(LED_pin3,LOW);
    }
    else if(correct_cnt==3)
    {
      Button_status=0;
      Button_flag1=0;
      Button_flag2=0;
      Button_flag3=0;
      for(int i=0;i<5;i++)
      {
        digitalWrite(LED_pin1,HIGH);
        delay(200);
        digitalWrite(LED_pin1,LOW);
        delay(200);
        digitalWrite(LED_pin2,HIGH);
        delay(200);
        digitalWrite(LED_pin2,LOW);
        delay(200);
        digitalWrite(LED_pin3,HIGH);
        delay(200);
        digitalWrite(LED_pin3,LOW);
        delay(200);
      }
      for(int i=0;i<5;i++)
      {
        digitalWrite(LED_pin1,HIGH);
        digitalWrite(LED_pin2,HIGH);
        digitalWrite(LED_pin3,HIGH);
        delay(200);
        digitalWrite(LED_pin1,LOW);
        digitalWrite(LED_pin2,LOW);
        digitalWrite(LED_pin3,LOW);
        delay(200);
      }
    }
  }

}