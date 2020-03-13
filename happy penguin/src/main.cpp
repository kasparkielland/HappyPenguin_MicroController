//#include <iostream>
#include <HX711.h>
#include <SoftwareSerial.h>

#define calibration_factor -21010
#define DOUT  7 //MOSI pin
#define CLK  8 //MISO pin
#define TxD 1
#define RxD 0


SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth
HX711 scale;

#include<math.h>
using namespace std;
// find gcd
int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}

double encrypt(double message) {
   //2 random prime numbers
   double p = 69697;
   double q = 420691;
   double n=p*q;//calculate n
   double track;
   double phi= (p-1)*(q-1);//calculate phi
   //public key
   //e stands for encrypt
   double e=7;
   //for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
   while(e<phi) {
      track = gcd(e,phi);
      if(track==1)
         break;
      else
         e++;
   }
   //private key
   //d stands for decrypt
   //choosing d such that it satisfies d*e = 1 mod phi
    double d1=1/e;
    double d=fmod(d1,phi);          //The number that needs to be stored in the application (together with p and q)
    //double message;
    //printf("Write your message here\n");
    //scanf("%lf",&message);

    double enc;                 //Ensure that the encryption is not manipulated
    double c = pow(message,e);  //encrypt the message
    enc=fmod(c,n);                //Encryption part two
    double m = pow(c,d);        //Decrypting message
    m=fmod(m,n);                //Decryption part two


    //Control the code and the compilation
    //cout<<"Original Message = "<<message;
    //cout<<"\n"<<"1 Encrypted message = "<<enc;
    //cout<<"\n"<<"Decrypted message = "<<m;
    //cout<<"\n"<<"Track = "<<track;
    //cout<<"\n"<<"n = "<<n;
    return enc;
}


void tare()
{
    //Serial.println("Tare");

    scale.tare(); //reset the weight
    yield();
    delay(1000);
}







void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    scale.begin(DOUT, CLK);
    yield();

    scale.set_scale(calibration_factor);
    tare();
}

void loop()
{
    byte c;

    if(mySerial.available())
    {
        c = mySerial.read();
        //Serial.println(c);
        if(c == 97)
        {
            tare();
        }
    }

    double value = scale.get_units();
    double encrypted = encrypt(value);
    mySerial.println(encrypted);
    Serial.println(encrypted);
    delay(1000);

}
