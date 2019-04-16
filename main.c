#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    struct elemento * prox;
    int dado_int;
    char dado_char;
    int flag;     //1 para int, 0 para char
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

void InserirNoInicio(t_lista * l, t_elemento * new){
    new->prox = l->inicio;  
    if (!EstaVazia(l)){
        l->inicio = new;
    }
    else{
        l->inicio = new;
        l->fim = new;
    }
}

t_elemento * RetirarDoInicioChar(t_lista * l){
    t_elemento * dado;
    if (!EstaVazia(l)){
        dado = l->inicio;
        l->inicio = l->inicio->prox;
        if (l->inicio == NULL){
            l->fim = NULL;
        }
        return dado;
    }
    else{
        printf("Lista já está vazia\n");
        return NULL;
    }
}

void InserirNoFim(t_lista * l, t_elemento * new){
    new->prox = NULL;
    if(!EstaVazia(l)){
        l->fim->prox = new;
    }
    else{
        l->inicio = new;
    }
    l->fim = new;
}    

t_elemento * RetirarDoFim(t_lista * l){
    if(!EstaVazia(l)){
        t_elemento * dado;
        if(l->inicio == l->fim){ //Apenas 1 elemento
            dado = l->inicio;
            l->inicio = NULL;
            l->fim = NULL;
            return dado;
        }
        else{
            t_elemento * penultimo = l->inicio;
            while(penultimo->prox != l->fim){
                penultimo = penultimo->prox;
            }
            dado = l->fim;
            l->fim = penultimo;     //Novo fim
            l->fim->prox = NULL;
            return dado;
        }
    }
    else{
        printf("Lista já está vazia\n");
        return NULL;
    }
}

void Inserir(t_lista * l, int pos, t_elemento * new){
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
            new->prox = atual->prox;
            atual->prox = new;
        }
    }
}

t_elemento * remover(int pos, t_lista * l){
    int i;
    if(!EstaVazia(l)){
        t_elemento * dado_ret;
        if(l->inicio == l->fim){ //Apenas 1 elemento
            dado_ret = l->inicio;
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
                dado_ret = l->fim;
                l->fim = ant_removido;
                return dado_ret;
            }
            else{
                dado_ret = ant_removido->prox;
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

void empilhar(t_lista * p, t_elemento * new){
    InserirNoFim(p , new);
}

t_elemento * desempilhar(t_lista * p){
    return RetirarDoFim(p);
}

void na_pilha(t_lista * p){
    t_elemento * pont_aux = p->inicio;
    while(pont_aux != NULL){
        if(pont_aux->flag == 0){
            printf("%c ", pont_aux->dado_char);
            pont_aux = pont_aux->prox;
        }
        else{
            printf("%d ", pont_aux->dado_int);
            pont_aux = pont_aux->prox;
        }
    }
    printf("\n");
}

int validar_express(t_elemento * entrada){
    t_lista * pilha_validar = (t_lista *)malloc(sizeof(t_lista));
    int i = 0;
    while(entrada[i]->dado_char != '\0'){
        if (entrada[i]->dado_char == '('){
            empilhar(pilha_validar, '(');
        }
        else
            if(entrada[i]->dado_char == ')'){
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

t_elemento * infix_to_posfix(t_elemento * entrada){
    t_lista * pilha_posf = (t_lista *)malloc(sizeof(t_lista));
    t_elemento * entrada_pos = (t_elemento *)malloc(sizeof(sizeof(t_elemento)*1000));
    t_elemento * aux;
    int i = 0, j = 0;
    while(entrada[i]->dado_char != '\0'){
        if(entrada[i]->flag == 0){
            printf("Entrada: %c\n", entrada[i]);
            if(entrada[i]->dado_char == '+' || entrada[i]->dado_char == '-'){
                while(!EstaVazia(pilha_posf) && (pilha_posf->fim->dado_char != '(' && pilha_posf->fim->dado_char != ')')){ //Enquanto tiver coisa na pilha e houver um operador não parentesis
                    entrada_pos[j] = desempilhar(pilha_posf);
                    j++;
                }
                printf("Empilhou %c\n", entrada[i]->dado_char);
                empilhar(pilha_posf, entrada[i]);
            }
            else if(entrada[i]->dado_char == '*' || entrada[i]->dado_char == '/'){
                while(!EstaVazia(pilha_posf) && (pilha_posf->fim->dado_char == '*' || pilha_posf->fim->dado_char == '/')){ //Desempilha todos * /
                    entrada_pos[j] = desempilhar(pilha_posf);
                    j++;
                }
                printf("Empilhou %c\n", entrada[i]->dado_char);
                empilhar(pilha_posf, entrada[i]);
            }
            else if(entrada[i]->dado_char == '('){
                printf("Empilhou %c\n", entrada[i]->dado_char);
                empilhar(pilha_posf, entrada[i]);
            }
            else if(entrada[i]->dado_char == ')'){
                aux = pilha_posf->fim;
                while(aux->dado_char != '('){
                    aux = desempilhar(pilha_posf);
                    printf("Desempilhou: %c\n", aux->dado_char);
                    entrada_pos[j] = aux;
                    j++;
                }
                j--;
                entrada_pos[j]->dado_char = '\0';
                entrada_pos[j]->flag = 0;
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
        else{
            entrada_pos[j] = entrada[i];
            j++;
            i++;
            printf("O que tem na pilha:");
            na_pilha(pilha_posf);
            printf("\n");
        }
    }
    while(!EstaVazia(pilha_posf)){
        entrada_pos[j] = desempilhar(pilha_posf);
        j++;
    }
    entrada_pos[j]->dado_char = '\0';
    entrada_pos[j]->flag = 0;
    free(pilha_posf);
    return entrada_pos;
}

int avaliar_express(t_elemento * saida){
    t_lista * pilha_avaliar = (t_lista *)malloc(sizeof(t_lista));
    int i = 0;
    t_elemento * valor1, valor2,
    float resultado;
    int aux;

    i = 0;
    while(saida[i]->dado_char != '\0'){
        if(saida[i]->flag == 0){
            valor1 = desempilhar(pilha_avaliar);
            valor2 = desempilhar(pilha_avaliar);
            if(saida[i]->dado_char == '+'){
                resultado = valor1->dado_int + valor2->dado_int;
                printf("%d\n", resultado);
            }
            else if(saida[i]->dado_char == '-'){
                resultado = valor2->dado_int - valor1->dado_int;
                printf("%d\n", resultado);
            }
            else if(saida[i]->dado_char == '*'){
                resultado = valor1->dado_int * valor2->dado_int;
                printf("%d\n", resultado);
            }
            else{
                resultado = (float)valor2/valor1;
                printf("%d\n", resultado);
            }
            empilhar(pilha_avaliar, resultado);
        }
        i++;
        else{
                empilhar(pilha_avaliar, saida[i]);
        }
    }
    valor1 = desempilhar(pilha_avaliar);
    resultado = valor1->dado_int;
    free(pilha_avaliar);
    return resultado;
}

t_elemento * tratar_entrada(char * entrada){
    return entrada_nova;
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