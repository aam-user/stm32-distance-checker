#include "mbed.h"
#include <cstdio>
//cat /dev/ttyACM0


DigitalOut led_red(D2);    // LED Rosso (Pericolo)
DigitalOut led_yell(D4);   // LED Giallo (Attenzione)
DigitalOut buzzer(D7);     // Buzzer su D7
DigitalOut trig(D12);
DigitalIn  echo(D11);
Timer      tempo_volo;

int main() {
    while (true) {
        // --- Trigger Sensore ---
        trig = 0; wait_us(2);
        trig = 1; wait_us(10);
        trig = 0;

        // --- Lettura Echo ---
        while (echo == 0);
        tempo_volo.reset();
        tempo_volo.start();
        while (echo == 1);
        tempo_volo.stop();

        float distanza = (tempo_volo.elapsed_time().count() * 0.0343f) / 2.0f;


        // --- LOGICA A CASCATA ---
        
        if (distanza < 10.0f) {
            // MOLTO VICINO: LED Rosso e Beep veloce
            printf("PERICOLO! Distanza: %.2f cm\n", distanza);
            led_red = 1;
            ThisThread::sleep_for(50ms); // Beep più lungo
            led_red = 0;
            led_yell = 0;
            
            buzzer = 1;
            ThisThread::sleep_for(50ms); // Beep brevissimo
            buzzer = 0;
        } 
        else if (distanza < 20.0f) {
            // ATTENZIONE: LED Giallo e Beep più lento
            printf("Attento, Distanza: %.2f cm\n", distanza);
            led_red = 0;
            led_yell = 1;
            ThisThread::sleep_for(150ms); // Beep più lungo
            led_yell = 0;
            
            buzzer = 1;
            ThisThread::sleep_for(150ms); // Beep più lungo
            buzzer = 0;
        } 
        else {
            printf("Distanza: %.2f cm\n", distanza);
            // SICURO: Tutto spento
            led_red = 0;
            led_yell = 0;
            buzzer = 0;
        }

        // Tempo di attesa tra una scansione e l'altra
        ThisThread::sleep_for(100ms);
    }
}