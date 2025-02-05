//Código para a atividade 1 da tarefa 2 (29/01)
//Aluna: Maryana Souza Silveira

#include <stdio.h> // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h" // Biblioteca de funções padrão do Pico
#include "hardware/timer.h" // Biblioteca de funções de timer

#define LED_GREEN 11 // Pino do LED verde
#define LED_YELLOW 12 // Pino do LED amarelo (obs: corresponde ao led azul na BitDogLab)
#define LED_RED 13 // Pino do LED vermelho

int controle_led = 0; // Variável de controle do LED (0 - vermelho, 1 - amarelo, 2 - verde)

bool repeating_timer_callback(struct repeating_timer *t);  // Função de callback do timer

int main(){
    stdio_init_all(); // Inicializa a comunicação serial

    gpio_init(LED_GREEN); // Inicializa o pino do LED verde
    gpio_set_dir(LED_GREEN, GPIO_OUT); // Define o pino do LED verde como saída

    gpio_init(LED_YELLOW); // Inicializa o pino do LED amarelo
    gpio_set_dir(LED_YELLOW, GPIO_OUT); // Define o pino do LED amarelo como saída

    gpio_init(LED_RED); // Inicializa o pino do LED vermelho
    gpio_set_dir(LED_RED, GPIO_OUT); // Define o pino do LED vermelho como saída

    struct repeating_timer timer; // Cria uma estrutura de timer
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); // Adiciona um timer de 3 segundos

    while(true){
        printf("\nBem-vindo ao semáforo! \nVermelho - pare \nAmarelo - preste atenção \nVerde - siga\n "); // Imprime a mensagem do semáforo
        sleep_ms(1000); // Aguarda 1 segundo
    }

    return 0; 
}

bool repeating_timer_callback(struct repeating_timer *t){ // Função de callback do timer
    // Desliga todos os LEDs
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_YELLOW, 0);

    switch (controle_led){// Acende o LED de acordo com o controle
    case 0:
        gpio_put(LED_RED, 1);  // Acende o LED vermelho
        break;
    case 1:
        gpio_put(LED_YELLOW, 1); // Acende o LED amarelo
        break;
    case 2:
        gpio_put(LED_GREEN, 1); // Acende o LED verde
        break;
    }

    controle_led = (controle_led + 1) % 3; // Alterna o controle do LED
    return true;
}