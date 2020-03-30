#include<math.h>
#include <cstdio>
#include <iostream>

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

// Kjører en egen funksjon for valg av nøkler
long decision (long e, long d, long d1, long phi, long track, long track1, long n){
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
                    if (d1==1 && d!=0){
                        cout<<"\n"<<"e is:"<<e;
                        cout<<"\n"<<"d is:"<<d;
                        return d,e;
                    }else{
                        d++;
                    }
                }
            } else
                e++;
        }
        else
            e++;
    }
}

int main() {
    //2 random prime numbers
    // double p = 69697;
    //double q = 420691;
    long p = 7;
    long q = 11;

    long n=p*q;//calculate n
    long track = 0;
    long track1 = 0;

    long phi= (p-1)*(q-1);//calculate phi

    long d=0;
    long d1=0;
    //e stands for encrypt
    long e=3;
    int breaak = 1;
    long temp_e = 13;       //Hardkodet versjon av d og e. Funksjonen som velger nøkler vil ikke returnere dem som de skal.
    long temp_d = 37;

    decision(e,d,d1,phi, track, track1, n);

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
    long message;
    printf("\n Write your message here\n");
    scanf("%li",&message);


    //Denne delen fungerer ikke som den skal uavhengig av om jeg bruker float eller long
    //Creating the cipher text (m^e)%n
    long c = pow(message, temp_e);
    c= fmod(c, n);

    //Decrypting the cipher text (c^d)%n. Dette fungerer ikke som det skal.
    long m = pow(c,temp_d);        //Decrypting message
    m = fmod(m, n);

    //m=fmod(m,n);                //Decryption part two


    //Control the code and the compilation
    cout<<"\n Original Message = "<<message;
    cout<<"\n"<<"Encrypted message = "<<c;
    cout<<"\n"<<"Decrypted message = "<<m;
    cout<<"\n"<<"e is:"<<e;                     //E og d oppdateres ikke av funksjonen "decision"
    cout<<"\n"<<"d is:"<<d;
    cout<<"\n"<<"Track = "<<track;
    cout<<"\n"<<"n = "<<n;
    return 0;
}