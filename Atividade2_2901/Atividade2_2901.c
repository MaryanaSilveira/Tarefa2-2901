//Código para a atividade 2 da tarefa 2 (29/01)
//Aluna: Maryana Souza Silveira

#include <stdio.h> // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h" // Biblioteca padrão do pico
#include "pico/time.h" // Biblioteca de tempo do pico

#define LED_GREEN 11 // Pino do led verde
#define LED_BLUE 12 // Pino do led azul
#define LED_RED 13 // Pino do led vermelho
#define BUTTON 5 // Pino do botão

bool leds_acesos = false; // Variável para verificar se os leds estão acesos

void initial_configs (); // Função para inicializar as configurações
int64_t turn_off_greenled(alarm_id_t, void *user_data); // Função para desligar o led verde
int64_t turn_off_blueled(alarm_id_t, void *user_data); // Função para desligar o led azul
int64_t turn_off_redled(alarm_id_t, void *user_data); // Função para desligar o led vermelho


int main()
{
    initial_configs(); // Inicializa as configurações

    while(true){ // Loop infinito
        if(gpio_get(BUTTON) == 0 && !leds_acesos){ // Verifica se o botão foi pressionado e se os leds estão apagados
            sleep_ms(50); // Debounce de 50ms 

            if(gpio_get(BUTTON) == 0){ // Verifica se o botão foi pressionado
                leds_acesos = true; // Muda variável para indicar que os leds estão acesos

                gpio_put(LED_GREEN, 1); // Acende o led verde
                add_alarm_in_ms(3000, turn_off_greenled, NULL, false); // Adiciona um alarme para desligar o led verde em 3 segundos

                gpio_put(LED_BLUE, 1); // Acende o led azul
                add_alarm_in_ms(2000, turn_off_blueled, NULL, false); // Adiciona um alarme para desligar o led azul em 2 segundos

                gpio_put(LED_RED, 1); // Acende o led vermelho
                add_alarm_in_ms(1000, turn_off_redled, NULL, false); // Adiciona um alarme para desligar o led vermelho em 1 segundo
            }
        }

        sleep_ms(10); // Pausa de 10ms para evitar sobrecarga no processador
    }
    return 0;
}

void initial_configs (){ // Função para inicializar as configurações
    stdio_init_all(); // Inicializa a comunicação serial

    gpio_init(LED_GREEN); // Inicializa o pino do led verde
    gpio_set_dir(LED_GREEN, GPIO_OUT); // Define o pino do led verde como saída

    gpio_init(LED_BLUE); // Inicializa o pino do led azul
    gpio_set_dir(LED_BLUE, GPIO_OUT); // Define o pino do led azul como saída

    gpio_init(LED_RED); // Inicializa o pino do led vermelho
    gpio_set_dir(LED_RED, GPIO_OUT); // Define o pino do led vermelho como saída

    gpio_init(BUTTON); // Inicializa o pino do botão
    gpio_set_dir(BUTTON, GPIO_IN); // Define o pino do botão como entrada
    gpio_pull_up(BUTTON); // Habilita o resistor de pull-up
}

int64_t turn_off_greenled(alarm_id_t, void *user_data){ // Função para desligar o led verde
    gpio_put(LED_GREEN, 0); // Desliga o led verde
    leds_acesos = false; // Muda a variável para indicar que os leds estão apagados (permite acender os leds novamente)
    return 0;
}

int64_t turn_off_blueled(alarm_id_t, void *user_data){ // Função para desligar o led azul
    gpio_put(LED_BLUE, 0); // Desliga o led azul
    return 0;
}

int64_t turn_off_redled(alarm_id_t, void *user_data){ // Função para desligar o led vermelho
    gpio_put(LED_RED, 0); // Desliga o led vermelho
    return 0;
}