#include <iostream>
/*
#include <HX711.h>
#include <SoftwareSerial.h>

#define calibration_factor -21010
#define DOUT  7 //MOSI pin
#define CLK  8 //MISO pin
#define TxD 1
#define RxD 0


SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth
HX711 scale;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    scale.begin(DOUT, CLK);
    yield();

    scale.set_scale(calibration_factor);
    tare();
}

void tare()
{
    //Serial.println("Tare");

    scale.tare(); //reset the weight
    yield();
    delay(1000);
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

    float value = scale.get_units();
    mySerial.println(value);
    Serial.println(value);
    delay(500);

}

*/


#include<math.h>
using namespace std;
// find gcd
int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0) {
          return b;
      }
      a = b;
      b= t;
   }
}
int main() {
   //2 random prime numbers
  // double p = 69697;
   //double q = 420691;
    double p = 7;
    double q = 2;

   double n=p*q;//calculate n
   double track = 0;
    double track1 = 0;

    double phi= (p-1)*(q-1);//calculate phi

    double d=0;
    double d1=0;
   //e stands for encrypt
   double e=3;

    //for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
   while(1<e<phi) {                 //Nøkkel må være mellom 1 og phi
      track = gcd(e,phi);           //Kjører gcd funksjon
      if(track==1){                 // track==1 betyr at det er coprime
              track1 = gcd(e,n);    //Sjekker om e er coprime med n (med premiss om at den er coprime med phi)
              track = gcd(e,phi);
              if (track1==1 && track==1){       //Må værecoprime med både phi og n
                  d=e+1;                        //dekryptering skal være større enn e
                  for (int i = 0; i < phi; ++i) {
                      d1 = fmod(e*d, phi);          //Formel som må være oppfylt for at d skal fungere
                      if (d1==1){
                          cout<<"\n"<<"e is:"<<e;
                          cout<<"\n"<<"d is:"<<d;
                          break;
                      }else{
                          d++;
                      }
                  }
                  break;
              } else
                  e++;
          break;
      }
      else
         e++;
   }
   //private key
   //d stands for decrypt
   //choosing d such that it satisfies d*e = 1 mod phi
    //double d1=1/e;
    //double d=fmod(d1,phi);          //The number that needs to be stored in the application (together with p and q)

    //double d;
    //d=(1+(2*phi))/e;
    //cout<<"\n"<<"Decryption1 key = "<<d1;
    //cout<<"\n"<<"Decryption key = "<<d;

    //Manuell input for testing (Her skal måledataen inn når koden skal over på arduino
    double message;
    printf("\n Write your message here\n");
    scanf("%lf",&message);

    //Creating the cipher text (m^e)%n
    double c = pow(message, e);
    c= fmod(c, n);

    //Decrypting the cipher text (c^d)%n. Dette fungerer ikke som det skal.
    double m = pow(c,d);        //Decrypting message
    m = fmod(m, n);

    //m=fmod(m,n);                //Decryption part two


    //Control the code and the compilation
    cout<<"\n"<<"1 Decrypted message = "<<m;
    cout<<"\n"<<"1 Encrypted message = "<<c;
    cout<<"\n Original Message = "<<message;
    cout<<"\n"<<"Encrypted message = "<<c;
    cout<<"\n"<<"Decrypted message = "<<m;
    cout<<"\n"<<"e is:"<<e;
    cout<<"\n"<<"d is:"<<d;
    cout<<"\n"<<"Track = "<<track;
    cout<<"\n"<<"n = "<<n;
    return 0;
}


/*

 * C++ Program to Implement the RSA Algorithm
 * Kopiert fra annen kilde



#include<iostream>

#include<math.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    cout << "\nENTER FIRST PRIME NUMBER\n";
    cin >> p;
    //p=69697;

    flag = prime(p);

    if (flag == 0)
    {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }

    cout << "\nENTER ANOTHER PRIME NUMBER\n";
    cin >> q;
    //q=420691;


    flag = prime(q);

    if (flag == 0 || p == q)

    {

        cout << "\nWRONG INPUT\n";

        exit(1);

    }

    cout << "\nENTER MESSAGE\n";

    fflush(stdin);

    cin >> msg;

    for (i = 0; msg[i] != '\0'; i++)

        m[i] = msg[i];

    n = p * q;

    t = (p - 1) * (q - 1);

    ce();

    cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";

    for (i = 0; i < j - 1; i++)

        cout << e[i] << "\t" << d[i] << "\n";

    encrypt();

    decrypt();

    return 0;

}

void ce()

{

    int k;

    k = 0;

    for (i = 2; i < t; i++)

    {

        if (t % i == 0)

            continue;

        flag = prime(i);

        if (flag == 1 && i != p && i != q)

        {

            e[k] = i;

            flag = cd(e[k]);

            if (flag > 0)

            {

                d[k] = flag;

                k++;

            }

            if (k == 99)

                break;

        }

    }

}

long int cd(long int x)

{

    long int k = 1;

    while (1)

    {

        k = k + t;

        if (k % x == 0)

            return (k / x);

    }

}

void encrypt()

{

    long int pt, ct, key = e[0], k, len;

    i = 0;

    len = strlen(msg);

    while (i != len)

    {

        pt = m[i];

        pt = pt - 96;

        k = 1;

        for (j = 0; j < key; j++)

        {

            k = k * pt;

            k = k % n;

        }

        temp[i] = k;

        ct = k + 96;

        en[i] = ct;

        i++;

    }

    en[i] = -1;

    cout << "\nTHE ENCRYPTED MESSAGE IS\n";

    for (i = 0; en[i] != -1; i++)

        printf("%c", en[i]);

}

void decrypt()

{

    long int pt, ct, key = d[0], k;

    i = 0;

    while (en[i] != -1)

    {

        ct = temp[i];

        k = 1;

        for (j = 0; j < key; j++)

        {

            k = k * ct;

            k = k % n;

        }

        pt = k + 96;

        m[i] = pt;

        i++;

    }

    m[i] = -1;

    cout << "\nTHE DECRYPTED MESSAGE IS\n";

    for (i = 0; m[i] != -1; i++)

        printf("%c", m[i]);

}
 */