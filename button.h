#ifndef BUTTON_H
#define BUTTON_H

#include "esphome.h"

class Button {
    private:
        int pin;
        unsigned long debounceTime;
        unsigned long lastBebounceTime;
        int status;
        int lastStatus;
    
    public:
        Button(int pin) {
            this->pin = pin;
            this->debounceTime = 50;
            this->lastBebounceTime = 0;

            pinMode(pin, INPUT_PULLUP);
        }


        bool wasPressed() {
            int read = digitalRead(pin);                       //A variável read recebe a read do pino do botão: HIGH (pressionado) ou LOW (Desacionado)
            bool flag = false;

            if (read != lastStatus) {                     //Se a read atual for diferente da read anterior
                lastBebounceTime = millis();                       //Reseta a variável lastBebounceTime atribuindo o tempo atual para uma nova contagem
            }

            if ((millis() - lastBebounceTime) > debounceTime) { //Se o resultado de (tempo atual - lastBebounceTime) for maior que o tempo que determinamos (debounceTime), ou seja, já passou os 50 milissegundos que é o tempo que o botão precisa ficar pressionado para ter a certeza de que ele realmente foi pressionado? Se sim faça:
                if (read != status) {                         //Verifica se a read do botão mudou, ou seja, se é diferente do status que o botão tinha da última vez. Se sim, faça:
                    status = read;                              //status recebe o que foi lido na variável read (pressionado = 1 e não pressionado = 0)
                    if (status == HIGH) {                          //Se o status é igual a HIGH significa que o botão foi pressionado, então faça:
                        flag = true;                                       //Incrementa +1 na variável contador. (contador++ é o mesmo que: contador = contador +1)
                    }
                }
            }
            lastStatus = read;                            //Atualiza a variável lastStatus para o que foi lido na variável read
            return flag;
        }


        ~Button(){}
};

#endif //BUTTON_H
