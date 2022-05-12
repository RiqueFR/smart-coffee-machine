#include "button.h"

Button::Button(int pin) {

    this->pin = pin;

    pinMode(pin, INPUT_PULLUP);
}

bool Button::changed() {
    bool now = digitalRead(pin); // Lê o estado atual do botão;
    if (unstable != now) { // Checa se houve mudança;
        bouncerTime = millis(); // Atualiza timer;
        unstable = now; // Atualiza estado instável;
    }else if (millis() - bouncerTime > 10) { // Checa o tempo de trepidação acabou;
        if (stable != now) { // Checa se a mudança ainda persiste;
            stable = now; // Atualiza estado estável;
            return 1;
        }
    }
    return 0;
}

bool Button::wasPressed() {
    if(changed() && pressed == 0){
        pressed = 1;
        return 1;
    }else if(changed() && pressed == 1){
        pressed = 0;
    }
    
    return 0;
}

Button::~Button(){}