#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    struct elemento * prox;
    char dado;
}t_elemento;

typedef struct lista{
    t_elemento * inicio;
    t_elemento * fim;
}t_lista;

int EstaVazia(t_lista * l){
    if (l->inicio == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void InserirNoInicio(t_lista * l, char new){
    t_elemento * novo = (t_elemento *)malloc(sizeof(t_elemento));
    novo->dado = new;
    novo->prox = l->inicio;  
    if (!EstaVazia(l)){
        l->inicio = novo;
    }
    else{
        l->inicio = novo;
        l->fim = novo;
    }
}

char RetirarDoInicio(t_lista * l){
    char dado_ret;
    if (!EstaVazia(l)){
        dado_ret = l->inicio->dado;
        l->inicio = l->inicio->prox;
        if (l->inicio == NULL){
            l->fim = NULL;
        }
        return dado_ret;
    }
    else{
        printf("Lista já está vazia\n");
        return 'e';
    }
}

void InserirNoFim(t_lista * l, char new){
    t_elemento * novo = (t_elemento *)malloc(sizeof(t_elemento));
    novo->dado = new;
    novo->prox = NULL;
    if(!EstaVazia(l)){
        l->fim->prox = novo;
    }
    else{
        l->inicio = novo;
    }
    l->fim = novo;
}    

char RetirarDoFim(t_lista * l){
    if(!EstaVazia(l)){
        char dado_ret;
        if(l->inicio == l->fim){ //Apenas 1 elemento
            dado_ret = l->inicio->dado;
            l->inicio = NULL;
            l->fim = NULL;
            return dado_ret;
        }
        else{
            t_elemento * penultimo = l->inicio;
            while(penultimo->prox != l->fim){
                penultimo = penultimo->prox;
            }
            dado_ret = l->fim->dado;
            l->fim = penultimo;     //Novo fim
            l->fim->prox = NULL;
            return dado_ret;
        }
    }
    else{
        printf("Lista já está vazia\n");
        return 'e';
    }
}

void Inserir(t_lista * l, int pos, char new){
    if (pos <= 0){
        InserirNoInicio(l, new);
    }
    else{
        t_elemento * atual = l->inicio;
        int i;
        for(i = 0; i < (pos-1) && atual != NULL; i++){
            atual = atual->prox;
        }
        if(atual == NULL || atual == l->fim){
            InserirNoFim(l, new);
        }
        else{
            t_elemento * novo = (t_elemento *)malloc(sizeof(t_elemento));
            novo->dado = new;
            novo->prox = atual->prox;
            atual->prox = novo;
        }
    }
    
}

int remover(int pos, t_lista * l){
    int i;
    if(!EstaVazia(l)){
        char dado_ret;
        if(l->inicio == l->fim){ //Apenas 1 elemento
            dado_ret = l->inicio->dado;
            l->inicio = NULL;
            l->fim = NULL;
            return dado_ret;
        }
        if(pos <= 0){
            dado_ret = RetirarDoInicio(l);
            return dado_ret;
        }
        else{
            t_elemento * ant_removido = l->inicio;
            for(i = 0; i < (pos-1) && ant_removido->prox != NULL; i++){
                ant_removido = ant_removido->prox;
            }
            if(ant_removido->prox == NULL){
                dado_ret = l->fim->dado;
                l->fim = ant_removido;
                return dado_ret;
            }
            else{
                dado_ret = ant_removido->prox->dado;
                ant_removido->prox = ant_removido->prox->prox;
                return dado_ret;
            }
        }
    }
    else{
        printf("Lisa já está vazia\n");
        return 'e';
    }
}

void empilhar(t_lista * p, char new){
    InserirNoFim(p , new);
}

char desempilhar(t_lista * p){
    return RetirarDoFim(p);
}

void na_pilha(t_lista * p){
    t_elemento * pont_aux = p->inicio;
    while(pont_aux != NULL){
        printf("%c ", pont_aux->dado);
        pont_aux = pont_aux->prox;
    }
    printf("\n");
}

int validar_express(char * entrada){
    t_lista * pilha_validar = (t_lista *)malloc(sizeof(t_lista));
    int i = 0;
    while(entrada[i] != '\0'){
        if (entrada[i] == '('){
            empilhar(pilha_validar, '(');
        }
        else
            if(entrada[i] == ')'){
                if(!EstaVazia(pilha_validar)){
                    desempilhar(pilha_validar);
                }
                else{
                    free(pilha_validar);
                    return 0;
                }
            }
        i++;
    }
    if(EstaVazia(pilha_validar)){
        free(pilha_validar);
        return 1;
    }
    else{
        free(pilha_validar);
        return 0;
    }
}

char * infix_to_posfix(char * entrada){
    t_lista * pilha_posf = (t_lista *)malloc(sizeof(t_lista));
    char * entrada_pos = (char *)malloc(sizeof(1000));
    char aux;
    int i = 0, j = 0;
    while(entrada[i] != '\0'){
        printf("Entrada: %c\n", entrada[i]);
        if(entrada[i] == '+' || entrada[i] == '-'){
            if(!EstaVazia(pilha_posf)){
                if(pilha_posf->fim->dado == '(' || pilha_posf->fim->dado == ')'){
                    printf("Empilhou %c\n", entrada[i]);
                    empilhar(pilha_posf, entrada[i]);
                }
                else{
                    entrada_pos[j] = desempilhar(pilha_posf);
                    j++;
                    printf("Empilhou %c\n", entrada[i]);
                    empilhar(pilha_posf, entrada[i]);
                }
            }
            else{
                printf("Empilhou %c\n", entrada[i]);
                empilhar(pilha_posf, entrada[i]);
            }
        }
        else if(entrada[i] == '*' || entrada[i] == '/'){
            if(!EstaVazia(pilha_posf)){
                if(pilha_posf->fim->dado == '*' || pilha_posf->fim->dado == '/'){
                    entrada_pos[j] = desempilhar(pilha_posf);
                    j++;
                    printf("Empilhou %c\n", entrada[i]);
                    empilhar(pilha_posf, entrada[i]);
                }
                else{
                    printf("Empilhou %c\n", entrada[i]);
                    empilhar(pilha_posf, entrada[i]);
                }
            }
            else{
                printf("Empilhou %c\n", entrada[i]);
                empilhar(pilha_posf, entrada[i]);
            }
        }
        else if(entrada[i] == '('){
            printf("Empilhou %c\n", entrada[i]);
            empilhar(pilha_posf, entrada[i]);
        }
        else if(entrada[i] == ')'){
            aux = pilha_posf->fim->dado;
            while(aux != '('){
                aux = desempilhar(pilha_posf);
                printf("Desempilhou: %c\n", aux);
                entrada_pos[j] = aux;
                j++;
            }
            j--;
            entrada_pos[j] = '\0';
        }
        else{
            entrada_pos[j] = entrada[i];
            j++;
        }
        i++;
        printf("O que tem na pilha:");
        na_pilha(pilha_posf);
        printf("\n");
        
    }
    while(!EstaVazia(pilha_posf)){
        entrada_pos[j] = desempilhar(pilha_posf);
        j++;
    }
    entrada_pos[j] = '\0';
    free(pilha_posf);
    return entrada_pos;
}

int avaliar_express(char * saida){
    t_lista * pilha_avaliar = (t_lista *)malloc(sizeof(t_lista));
    int i = 0;
    int valor1, valor2, resultado;

    while(saida[i] != '\0'){
        if(saida[i] == '+' || saida[i] == '-' || saida[i] == '*' || saida[i] == '/'){
            valor1 = (int)desempilhar(pilha_avaliar);
            valor2 = (int)desempilhar(pilha_avaliar);
            printf("Desempilhou: %d %d\n", valor1, valor2);
            if(saida[i] == '+'){
                resultado = valor1 + valor2;
                printf("%d\n", resultado);
            }
            else if(saida[i] == '-'){
                resultado = valor2 - valor1;
                printf("%d\n", resultado);
            }
            else if(saida[i] == '*'){
                resultado = valor1 * valor2;
                printf("%d\n", resultado);
            }
            else{
                resultado = valor2/valor1;
                printf("%d\n", resultado);
            }
            printf("Empilhou: %d\n", resultado);
            empilhar(pilha_avaliar, resultado);
        }
        else{
            printf("Empilhou: %c\n", saida[i]);
            empilhar(pilha_avaliar, saida[i]);
        }   
        i++;
    }
    resultado = desempilhar(pilha_avaliar);
    free(pilha_avaliar);
    return resultado;
}

int main(void){
    char entrada[1000];
    char * saida;
    int resultado;
    scanf("%s", entrada);

    if(validar_express(entrada)){
        saida = infix_to_posfix(entrada);
        printf("%s\n", saida);
        resultado = avaliar_express(saida);
        printf("Resultado da expressão: %d\n", resultado);
    }
    else{
        printf("Expressão inválida\n");
    }
    return 0;
}