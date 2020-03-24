#include <iostream>
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
    //2 random prime numbers, the ones written are for testing
    // double p = 69697;
    //double q = 420691;
    double p = 107;
    double q = 113;

    double n=p*q;//calculate n
    double track = 0;
    double track1 = 0;

    double phi= (p-1)*(q-1);//calculate phi

    double d=0;
    double d1=0;
    //public key
    //e stands for encrypt
    double e=3;
    //for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
    while(1<e<phi) {
        track = gcd(e,phi);
        if(track==1){
            track1 = gcd(e,n);
            track = gcd(e,phi);
            if (track1==1 && track==1){
                d=e+1;
                for (int i = 0; i < phi; ++i) {
                    d1 = fmod(e*d, phi);
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
            //break;
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

    double message;
    printf("\n Write your message here\n");
    scanf("%lf",&message);

    //double enc;                 //Ensure that the encryption is not manipulated
    //double c = pow(message,e);  //encrypt the message
    //c = fmod(c,n);
    //enc=fmod(c,n);            //Encryption part two

    double c = pow(message, e);
    cout<<"\n"<<"1 Encrypted message = "<<c;
    c= fmod(c, n);
    double m = pow(c,d);        //Decrypting message
    cout<<"\n"<<"1 Decrypted message = "<<m;
    m = fmod(m, n);
    //m=fmod(m,n);                //Decryption part two


    //Control the code and the compilation
    cout<<"\n Original Message = "<<message;
    cout<<"\n"<<"Encrypted message = "<<c;
    cout<<"\n"<<"Decrypted message = "<<m;
    cout<<"\n"<<"e is:"<<e;
    cout<<"\n"<<"d is:"<<d;
    cout<<"\n"<<"Track = "<<track;
    cout<<"\n"<<"n = "<<n;
    return 0;
}