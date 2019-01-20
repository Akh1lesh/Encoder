#include<avr/interrupt.h>
#include<avr/io.h>
#include<SRA16.h>
volatile long int Left_count = 0;
volatile long int Right_count =0;
int a,b,sign_a,sign_b;
float theta_r,theta,r;
  
void setup() {
 sei();
 Serial.begin(9600);
 DDRD &= ~(1<<PD2);
 PORTD |= (1<<PD2);
 DDRA  &= ~(1<<PA5);
 PORTA |= (1<<PA5);
 GICR |= 1<<INT0;
 MCUCR |= (1<<ISC01);

 DDRD &= ~(1<<PD3);
 PORTD |= (1<<PD3);
 DDRA  &= ~(1<<PA6);
 PORTA |= (1<<PA6);
 GICR |= 1<<INT1;
 MCUCR |= (1<<ISC11);


 DDRD|=(1<<PD4)|(1<<PD5);
 PORTD|=(1<<PD4)|(1<<PD5);
 DDRC |= 0b11110000;
 //PORTC |= 0b1010000;   
}

void loop() {
  float d =7.2;
  float dbw = 25.2;
  const float pi =3.14;
  float g=pi*d; 
  float x = (60*r*30.48/g); float s = (3*d);
  
 while(Serial.available()>0)
    {
      signa();
      delay(2000);
    read_a();
  delay(2000);
  signb();
  delay(2000);
    read_b();
  delay(2000);} 
 thetaf();
 rf();

  if(sign_a==15 && sign_b==15){
    float f=(dbw*theta);
     float y = (f/s);
    bot_left_forward();
    if(Right_count>=y){
      bot_brake();
   
       bot_forward();
  if(Left_count>=x ){bot_brake();}}
    
 }
 else if(sign_a==255 && sign_b==15){
  float h=(dbw*(180-theta));
  float u = (h/s);
    bot_left_forward();
  if(Right_count>=u){
    bot_brake();
      bot_forward();
  if(Left_count>=x){bot_brake();}}
   
  } 
else if(sign_a==255 && sign_b==255){
  float i =(dbw*(180+theta));
  float v = (i/s);
    bot_left_forward();
   if(Right_count>=v){bot_brake();
    bot_forward();
  if(Left_count>=x){bot_brake();}}

  }    
else if(sign_a==15 && sign_b==255){
  float j =(dbw*(360-theta));
  float w =(j/s);
    bot_left_forward();
   if(Right_count>=w){bot_brake();
    bot_forward();
  if(Left_count>=x){bot_brake();}} 
}
  }   
 
ISR(INT0_vect){
if(bit_is_set(PINA,5)){
  Left_count++;
}
else{
  Left_count--;
}  
}
ISR(INT1_vect){
  if(bit_is_set(PINA ,6)){
    Right_count--;
    }
   else{
    Right_count++;
    }
} 
  void read_a(){
  a = Serial.read();
    Serial.print("a:");
    Serial.println(a);
 }
void read_b(){
  b = Serial.read();
    Serial.print("b:");
    Serial.println(b);
} 
void signa()
{
  sign_a= Serial.read();
  Serial.print("sign_a");
  Serial.println(sign_a);
}
void signb()
{
  sign_b= Serial.read();
  Serial.print("sign_b:");
  Serial.println(sign_b);
}
void thetaf(){
   float t= ((float)b/(float)a);
  theta_r = atan(t);
  Serial.print("theta:");
  Serial.println(theta);
  Serial.println(t);
  theta = ((theta_r*180)/3.1415);
  }
void rf(){
  int p; int z; 
  p=(a*a)+(b*b);
  r= sqrt(p);
  Serial.print("r:");
  Serial.println(r);
}

  
  



