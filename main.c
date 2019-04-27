#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    struct elemento * prox;
    double dado_int;
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
        return 0;
}

void InserirNoInicio(t_lista * l, t_elemento * new){ //ponteiro para o elemento como parâmetro.
    new->prox = l->inicio;  
    if (!EstaVazia(l)){
        l->inicio = new;
    }
    else{
        l->inicio = new;
        l->fim = new;
    }
}

t_elemento * RetirarDoInicio (t_lista * l){ //retorna um ponteiro pra uma struct elemento.
    t_elemento * dado; 
    if (!EstaVazia(l)){
        dado = l->inicio;
        l->inicio = l->inicio->prox; //muda o início para o próximo elemento da lista
        if (l->inicio == NULL){ //só havia 1 elemento na lista
            l->fim = NULL;      //após retirado, não tem mais nenhum
        }
        return dado;            //retorna a struct toda do elemento inicial
    }
    else{
        printf("Lista já está vazia\n");
        return NULL; //retorna uma struct nula.
    }
}

void InserirNoFim(t_lista * l, t_elemento * new){
    new->prox = NULL;
    if(!EstaVazia(l)){
        l->fim->prox = new; //o último elemento passa a appontar para o novo.
    }
    else{
        l->inicio = new; //nesse caso, estamos inserindo o primeiro elemento da lista.
    }
    l->fim = new; //em ambas as situações, new é o novo último.
}    

t_elemento * RetirarDoFim(t_lista * l){
    if(!EstaVazia(l)){
        t_elemento * dado;
        if(l->inicio == l->fim){ //Apenas 1 elemento
            dado = l->inicio;
            l->inicio = NULL;
            l->fim = NULL;
            return dado; //retorna o único elemento e torna a lista vazia
        }
        else{ //mais de 1 elemento
            t_elemento * penultimo = l->inicio; //struct para percorrer a lista
            while(penultimo->prox != l->fim){ //enquanto a struct de referência não for de fato a penúltima.
                penultimo = penultimo->prox;  //percorre-se a lista.
            }
            dado = l->fim;
            l->fim = penultimo;  //O fim agora pertence ao penúltimo
            l->fim->prox = NULL; //o último se refere ao NULL
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
        t_elemento * atual = l->inicio; //ponteiro usado para percorrer a lista
        int i;
        for(i = 0; i < (pos-1) && atual != NULL; i++){ //até chegar na posição solicitada ou no fim da lista
            atual = atual->prox;
        }
        if(atual == NULL || atual == l->fim){ 
            //se atual é o último elemento ou até tentou ultrapassar o tamnho da lista
            InserirNoFim(l, new);
        }
        else{
            new->prox = atual->prox; //o novo elemento se refere ao próximo
            atual->prox = new; //e o de referência se refere ao novo.
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
            for(i = 0; i < (pos-1) && ant_removido->prox->prox != NULL; i++){
                ant_removido = ant_removido->prox;
            } //mesma estrutura de Inserir, porém nesse caso, o limite na lista
              //é o penúltimo elemento
            if(ant_removido->prox->prox == NULL){ //se o removido é o último elemento
                dado_ret = l->fim; 
                l->fim = ant_removido;
                return dado_ret;
            }
            else{
                dado_ret = ant_removido->prox;
                ant_removido->prox = ant_removido->prox->prox;
                return dado_ret; //retira o valor em questão da lista
            }
        }
    }
    else{
        printf("Lista já está vazia\n");
        return NULL;
    }
}

void empilhar(t_lista * p, t_elemento * new){
    InserirNoFim(p , new); 
}

t_elemento * desempilhar(t_lista * p){
    return RetirarDoFim(p);
} //as duas última funções explicitam que a extremidade de 
  //acesso para a pilha é o final da lista encadeada
  //Complexidade O(n) !

void na_pilha(t_lista * p){
    t_elemento * pont_aux = p->inicio; //percorre a lista
    while(pont_aux != NULL){ //enquanto não chegar no final
        if(pont_aux->flag == 0){ //o elemento é um char
            printf("%c ", pont_aux->dado_char); // imprime o char carregado
        }
        else{ //é um int
            printf("%.1lf ", pont_aux->dado_int); //imprime o int carregado
        }
        pont_aux = pont_aux->prox; //próximo ponteiro
    }
    printf("\n"); //ou seja, imprime todos os elementos da lista
}

int validar_express(t_elemento ** entrada){ //recebe como entrada um ponteiro que aponta para um ponteiro de uma struct
                                            //entrada -> ponteiro da struct -> struct
    t_lista * pilha_validar = (t_lista *)malloc(sizeof(t_lista)); //ponteiro para lista
    t_elemento * parent = (t_elemento *)malloc(sizeof(t_elemento)); //ponteiro para elemento
    parent->dado_char = '('; 
    parent->dado_int = -1;
    parent->flag = 0; 
    int i = 0;
    while(entrada[i]->dado_char != '\0'){ //enquanto o vetor de entradas não acabar
        if (entrada[i]->dado_char == '('){ //se for encontrada uma prioridade
            empilhar(pilha_validar, parent); //esta é empilhada
        }
        else
            if(entrada[i]->dado_char == ')'){ //para cada '('encontrado, deve ter um ')' para desempilhar
                if(!EstaVazia(pilha_validar)){
                    desempilhar(pilha_validar);
                }
                else{ //se a pilha esti1ver vazia, significa que existe um '(' sem ')' correspondente
                    free(pilha_validar); 
                    return 0; //mostra que a entrada é inválida
                }
            }
        i++; //percorrendo toda a entrada
    }
    if(EstaVazia(pilha_validar)){ //se após percorrer toda a entrada e não sobrarem parênteses
        free(pilha_validar);
        return 1; //é uma expressão válida para prioridade.
    }
    else{
        free(pilha_validar);
        return 0;
    }
}

t_elemento ** infix_to_posfix(t_elemento ** entrada, t_elemento ** entrada_pos){ //essa função também retorna um ponteiro para um ponteiro de um elemento
    t_lista * pilha_posf = (t_lista *)malloc(sizeof(t_lista));
    t_elemento * aux;
    int i = 0, j = 0;
    while(entrada[i]->dado_char != '\0'){ //enquanto a entrada não terminar
        if(entrada[i]->flag == 0){ //se for um char
            if(entrada[i]->dado_char == '+' || entrada[i]->dado_char == '-'){ //se foi encontrado um dos operadores de menor prioridade
                while(!EstaVazia(pilha_posf) && (pilha_posf->fim->dado_char != '(' && pilha_posf->fim->dado_char != ')')){ 
                    //Enquanto a pilha que guarda os operadores para execução não estiver vazia e o elemento mais externo não for parênteses
                    entrada_pos[j] = desempilhar(pilha_posf); //retira o último operando e o coloca na versão pós-fixa da entrada
                    j++;
                }
                empilhar(pilha_posf, entrada[i]); //desempilhou todas as proridades antes de acrescentar o operando na pilha
            }
            else if(entrada[i]->dado_char == '*' || entrada[i]->dado_char == '/'){ //operadores de maior prioridade
                while(!EstaVazia(pilha_posf) && (pilha_posf->fim->dado_char == '*' || pilha_posf->fim->dado_char == '/')){ //Desempilha todos * /
                    entrada_pos[j] = desempilhar(pilha_posf);
                    j++;
                } //desempilha todas as operações de mesma prioridade que já estão na pilha
                empilhar(pilha_posf, entrada[i]);
            }
            else if(entrada[i]->dado_char == '('){
                empilhar(pilha_posf, entrada[i]);
            }
            else if(entrada[i]->dado_char == ')'){ 
                aux = pilha_posf->fim; //aponta para o primeiro elemento da pilha
                if (aux->dado_char == '('){
                    aux = desempilhar(pilha_posf);
                    j++;
                }
                while(aux->dado_char != '('){ //a pilha vai sendo esvaziada e passando o conteúdo para o aux
                    aux = desempilhar(pilha_posf); //como '(' vai ser obtido pelo desempilhar, este será acrescentado na estrada_pos antes de sair do while
                    entrada_pos[j] = aux;
                    j++; 
                }
                j--; //como o '(' foi colocado indevidamente, a pos em entrada_pos é descrementado
                entrada_pos[j]->dado_char = '\0'; //'(' é sobrescrito por '\0'
                entrada_pos[j]->flag = 0; 
            }
            else{
                entrada_pos[j] = entrada[i];
                j++;
            }
            i++;
        }
        else{
            entrada_pos[j] = entrada[i]; //se for operando, coloca direto na versão pós fixa.
            j++; 
            i++;
        }
    }
    while(!EstaVazia(pilha_posf)){
        entrada_pos[j] = desempilhar(pilha_posf);
        j++; 
    } //depois de ler toda a entrada, esvazia a pilha colocando todos os operandos na entrada_pos

    t_elemento * last = (t_elemento *)malloc(sizeof(t_elemento));
    last->dado_char = '\0';
    last->dado_int = -1;
    last->flag = 0;
    entrada_pos[j] = last; //encerrando a entrada pós-fixa com o \0.
    free(pilha_posf); 
    return entrada_pos;
}

double avaliar_express(t_elemento ** saida){
    t_lista * pilha_avaliar = (t_lista *)malloc(sizeof(t_lista)); //pilha de avaliação
    t_elemento * resultado = (t_elemento *)malloc(sizeof(t_elemento)); //ponteiro para struct
    int i = 0;
    t_elemento * valor1;
    t_elemento * valor2;
    resultado->dado_char = 'x'; //o char carregado é o 'x', para mostrar que é um número
    resultado->flag = 1; //sinaliza que é um int

    while(saida[i]->dado_char != '\0'){ //enquanto a saída não terminar
        if(saida[i]->flag == 0){ //se for um operador
            t_elemento * resultado = (t_elemento *)malloc(sizeof(t_elemento));
            resultado->dado_char = 'x';
            resultado->flag = 1; //cria novamente a estrutura anterior
            valor1 = desempilhar(pilha_avaliar);
            valor2 = desempilhar(pilha_avaliar); //pega os dois últimos valores da pilha destinados para a operação
            if(saida[i]->dado_char == '+'){ //avaliação individual para cada operador
                resultado->dado_int = valor1->dado_int + valor2->dado_int;
            }
            else if(saida[i]->dado_char == '-'){
                resultado->dado_int = valor2->dado_int - valor1->dado_int;
            }
            else if(saida[i]->dado_char == '*'){
                resultado->dado_int = valor1->dado_int * valor2->dado_int;
            }
            else{
                resultado->dado_int = (float)valor2->dado_int/valor1->dado_int;
            }
            empilhar(pilha_avaliar, resultado); //o resultado da operação entra na pilha de operações
        }
        else{
            empilhar(pilha_avaliar, saida[i]); //se for número, só é destinado para pilha
        }
        i++;

    }
    resultado = desempilhar(pilha_avaliar); //só terá apenas um valor
    free(pilha_avaliar);
    return resultado->dado_int;
}

void tratar_entrada(char * entry, t_elemento ** entrada_nova){
    t_elemento * novo = (t_elemento *)malloc(sizeof(t_elemento));
    int i = 0;
    int j = 0;
    if ('0' <= entry[i] && entry[i] <= '9'){ //tratar números
        novo->dado_char = 'x';
        novo->dado_int = entry[i] - '0'; //operação com chars, mas retorna um inteiro, já que as distâncias na tabela asc são correspondentes com a subtração
        novo->flag = 1; 
    }
    else{
        novo->dado_char = entry[i];
        novo->dado_int = -1;
        novo->flag = 0; 
    }
    entrada_nova[i] = novo; //realizada apenas para o primeiro elemento
    i++;  
    j++;
    while(entry[i] != '\0'){ //trata os demais elementos até o fim da entrada
        t_elemento * novo = (t_elemento *)malloc(sizeof(t_elemento));
        if ('0' <= entry[i] && entry[i] <= '9'){
            novo->dado_char = 'x';
            novo->flag = 1;
            if (entrada_nova[j-1]->flag == 1){ //se o elemento da posição anterior da ent_nova for um inteiro, ou seja, trata-se de um número de mais de um algarismo
                novo->dado_int = (entrada_nova[j-1]->dado_int)*10 + (entry[i] - '0');
                //multiplica o int já existente em ent_nova por 10 (sendo 1 algarismo ou mais)
                //adiciona com a entry atual
                j--; //como no fim do escopo j é incrementado, o decremento serve para que o mesmo 
                     //número de mais algarismos fique posicionado corretamente na ent_nova 
            }
            else {
                novo->dado_int = entry[i] - '0';
            }
        }
        else{
            novo->dado_char = entry[i];
            novo->dado_int = -1;
            novo->flag = 0; 
        }
        entrada_nova[j] = novo; //acrescenta o elemento tratado
        i++;
        j++;
    }
    t_elemento * last = (t_elemento *)malloc(sizeof(t_elemento));
    last->dado_char = '\0';
    last->dado_int = -1;
    last->flag = 0;
    entrada_nova[j] = last;
    return;
}

int main(void){
    char entrada[100];
    t_elemento * entrada_nova[100]; //um vetor que guarda 100 ponteiros para 
    t_elemento * saida[100]; //a operação está limitada à 100 caracteres
    int i = 0;
    double resultado;
    scanf("%s", entrada);
    tratar_entrada(entrada, entrada_nova); //compacta números de mais algarismos, transforma números de char para inteiros
    
    if(validar_express(entrada_nova)){ //condiciona a validade da expressão
        printf("\n");
        while(entrada_nova[i]->dado_char != '\0'){
            printf("%c %.0lf %d\n", entrada_nova[i]->dado_char, entrada_nova[i]->dado_int, entrada_nova[i]->flag); 
            i++; 
        }
        infix_to_posfix(entrada_nova, saida); //saída recebe a versão pós-fixa da entrada
        printf("\n");
        i = 0;
        while(saida[i]->dado_char != '\0'){
            printf("%c %.0lf %d\n", saida[i]->dado_char, saida[i]->dado_int, saida[i]->flag); 
            i++;
        }
        resultado = avaliar_express(saida);
        printf("\n");
        printf("Resultado da expressão: %lf\n", resultado);
    }
    else{
        printf("Expressão inválida\n");
    }
    return 0;
}