#include<SRA16.h>
volatile long int Left_count = 0;
volatile long int Right_count =0;
int a,b,sign_a,sign_b;
float theta_r,theta,r;
void setup(){
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
}
void loop() {
  Serial.println("Left Count:");
  Serial.println(Left_count);
  Serial.println("Right Count:");
  Serial.println(Right_count);
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


