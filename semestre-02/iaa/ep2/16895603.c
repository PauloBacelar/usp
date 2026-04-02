#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    int gravidade;  // 4 = vermelho, 3 = laranja, 2 = amarelo,1 = verde, 0 = azul
    char prioridadeStr[16];
    int prioridade; // 0 = N/A, 1 = prioridade
    int tempoEspera;
} Paciente;


int mapeia_gravidade(char* s) {
    if (strcmp(s, "Vermelho") == 0) {
        return 4;
    } else if (strcmp(s, "Laranja") == 0) {
        return 3;
    } else if (strcmp(s, "Amarelo") == 0) {
        return 2;
    } else if (strcmp(s, "Verde") == 0) {
        return 1;
    }

    return 0;
}


char* desmapeia_gravidade(int gravidade) {
    switch (gravidade) {
        case 4:
            return "Vermelho";
        case 3:
            return "Laranja";
        case 2:
            return "Amarelo";
        case 1:
            return "Verde";
        default:
            return "Azul";
    }
}


int mapeia_prioridade(char* s) {
    return strcmp(s, "N/A") == 0 ? 0 : 1;
}


Paciente* carregar_pacientes_csv(char* caminho) {
    FILE* f = fopen(caminho, "r");

    int maxPacientes = 8;
    Paciente* pacientes = malloc(maxPacientes * sizeof(Paciente));

    char linha[64];
    int indicePaciente = 0;
    while (fgets(linha, sizeof(linha), f)) {
        char *paciente = strchr(linha, '\n');
        if (paciente)  {
            *paciente = '\0';
        }

        char* gravidade = strtok(linha, ",");
        char* prioridade = strtok(NULL, ",");
        char* tempoEspera = strtok(NULL, ",");

        if (indicePaciente == maxPacientes) {
            maxPacientes *= 2;
            Paciente *novoArrPacientes = realloc(pacientes, maxPacientes * sizeof(Paciente));
            pacientes = novoArrPacientes;
        }

        pacientes[indicePaciente].gravidade = mapeia_gravidade(gravidade);
        pacientes[indicePaciente].prioridade = mapeia_prioridade(prioridade);
        strcpy(pacientes[indicePaciente].prioridadeStr, prioridade);
        pacientes[indicePaciente].tempoEspera = atoi(tempoEspera);
        indicePaciente++;
    }

    fclose(f);

    // Sentinela pra saber onde termina (gravidade = prioridade = tempoEspera = -1)
    if (indicePaciente == maxPacientes) {
        Paciente *novoArrPacientes = realloc(pacientes, (maxPacientes + 1) * sizeof(Paciente));
        pacientes = novoArrPacientes;
    }
    pacientes[indicePaciente].gravidade = -1;
    pacientes[indicePaciente].prioridade = -1;
    pacientes[indicePaciente].tempoEspera = -1;

    return pacientes;
}


void escalonar_pacientes(Paciente* pacientes) {
    int i = 0;

    do {
        Paciente* paciente = &pacientes[i];

        if (paciente->gravidade == 3 && paciente->tempoEspera > 10) {
            paciente->gravidade = 4;
        } else if (paciente->gravidade == 2 && paciente->tempoEspera > 60) {
            paciente->gravidade = 3;
        } else if (paciente->gravidade == 1 && paciente->tempoEspera > 120) {
            paciente->gravidade = 2;
        } else if (paciente->gravidade == 0 && paciente->tempoEspera > 240) {
            paciente->gravidade = 1;
        }

        i++;
    } while (pacientes[i].gravidade != -1);
}


void ordernar_pacientes(Paciente* pacientes) {
    int i = 1;
    while (pacientes[i].gravidade != -1) {
        Paciente key = pacientes[i];
        int j = i - 1;

        while (j >= 0) {
            if (pacientes[j].gravidade == -1) {
                break;
            }

            int troca = 0;
            if (pacientes[j].gravidade < key.gravidade) {
                troca = 1;
            } else if (pacientes[j].gravidade == key.gravidade) {
                if (key.gravidade != 4 && key.gravidade != 3) {
                    if (key.prioridade == 1 && pacientes[j].prioridade == 0) {
                        troca = 1;
                    } else if (pacientes[j].prioridade == key.prioridade && pacientes[j].tempoEspera < key.tempoEspera) {
                        troca = 1;
                    }
                } else if (pacientes[j].tempoEspera < key.tempoEspera) {
                    troca = 1;
                }
            }

            if (!troca) {
                break;
            }
            
            pacientes[j + 1] = pacientes[j];
            j--;
        }
        pacientes[j + 1] = key;
        i++;
    }
}


void exportar_csv(Paciente* pacientes) {
    FILE *arquivo = fopen("OrdemDeAtendimentos.csv", "w");

    int i = 0;
    int primeiroPaciente = 1;

    while (pacientes[i].gravidade != -1) {
        if (!primeiroPaciente) {
            fprintf(arquivo, "\n");
        }

        fprintf(arquivo, "%s,%s,%d", desmapeia_gravidade(pacientes[i].gravidade), pacientes[i].prioridadeStr, pacientes[i].tempoEspera);
        
        i++;
        primeiroPaciente = 0;
    }

    fclose(arquivo);
}


int main() {
    Paciente *pacientes = carregar_pacientes_csv("pacientes.csv");

    escalonar_pacientes(pacientes);
    ordernar_pacientes(pacientes);
    exportar_csv(pacientes);

    free(pacientes);

    return 0;
}
