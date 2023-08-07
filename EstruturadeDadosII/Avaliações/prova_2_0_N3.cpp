#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define T 5 // ordem 5 
#define N T*2


struct medicamento{
    int codigo_barra;
    char nome[30]; // Nome do medicamento
    char date[10]; // Data do cadastro
    int quant; // Quantidade
    float preco; // Preço

};

typedef struct page {
    int qnt = 0;
    bool folha = false;
    int codigos[N - 1]; // Código de barras (chave)
    struct page* pai = NULL;
    medicamento* medicamentos[N - 1];
    struct page* filhos[N];
    struct page* prox = NULL;
} pagina;

medicamento *busca(pagina *pag, int cod){
    if (NULL == pag) {
        return NULL;
    }
    if (pag->folha == true){
        for(int i = 0; i < pag->qnt; i++){

            if(pag->codigos[i] == cod){

                return pag->medicamentos[i];

            }
        }

        if( pag->codigos[pag->qnt] < cod){
            return busca(pag->prox, cod);
        }
        
    }
    else if (pag->folha == false) {
        for(int i = 0; i < pag->qnt; i++){
            if(pag->codigos[i] > cod){
                return busca(pag->filhos[i], cod);
            }
        }
        return busca(pag->filhos[pag->qnt + 1], cod);
    }
    
    return NULL;
}

pagina* criar_pagina() {
    pagina* pag = new pagina;
    for (int i = 0; i < N - 1; i++) {
        pag->codigos[i] = 0;
        pag->medicamentos[i] = NULL;
        pag->filhos[i] = NULL;
    }
    pag->filhos[N-1] = NULL;
    pag->folha = true;
    pag->qnt = 0;
    pag->prox = NULL;
    
    return pag;
}

void print(pagina *pag) {
    if (pag == NULL) return;

    print(pag->filhos[0]);

    if (pag->folha) {
        for (int i = 0; i < pag->qnt; i++) {
            printf("%d |", pag->medicamentos[i]->codigo_barra);
        }
        print(pag->prox);
    }
}

void imprimir(pagina *node, int tab = 0, int cod = 0)
{
    if (node == NULL)return;

    for(int i = node->qnt; i>0; i--){
        imprimir(node->filhos[i], tab + 1, node->codigos[0]);
    }
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    printf("|");
    for (int i = 0; i <  node->qnt; i++) {
        printf("%d-", node->codigos[i]);
    }
    printf("|\n");
    imprimir(node->filhos[0], tab + 1, node->codigos[0]);

}

pagina *brother_esq_libert(pagina* pai, int cod, int *index_pai = NULL) {
    if (pai == NULL) return NULL;

    for (int i = 0; i <= pai->qnt; i++) {
        if(pai->filhos[i] != NULL){
            for(int j = 0; j < pai->filhos[i]->qnt; j++){
                if(pai->filhos[i]->codigos[j] == cod){
                    if(i - 1 >= 0 ){
                        if(index_pai!=NULL){
                            (*index_pai) = i; // index do pai
                        }
                        return pai->filhos[i-1];

                    }else{
                        return NULL;
                    }
                }
            }
        }

    }

    return NULL;
}

void sort(pagina *pag, int cod, medicamento *med = NULL){
    if(pag == NULL){
        return;
    }

    if(pag->qnt == 0){
        pag->codigos[0] = cod;
        pag->medicamentos[0] = med;
    }
    else{
        int aux = 0;
        for(int i = pag->qnt; i >= 0; i--){
            if(pag->codigos[i-1] < cod){
                aux = i;
                break;
            }
            pag->codigos[i] = pag->codigos[i-1];
            pag->medicamentos[i] = pag->medicamentos[i-1];
        }
        pag->codigos[aux] = cod;
        pag->medicamentos[aux] = med;
    }
    
    pag->qnt+=1;
}

int index_filho(pagina *pai, int cod){
    if (pai == NULL) return -1;

    for (int i = 0; i < pai->qnt; i++) {
        if(pai->filhos[i] != NULL){
            for(int j = 0; j < pai->filhos[i]->qnt; j++){

                if(pai->filhos[i]->codigos[j] == cod){    
                    return i;
                }
            }
        }
    }
    if(pai->filhos[pai->qnt] != NULL){
        for(int j = 0; j < pai->filhos[pai->qnt]->qnt; j++){

                if(pai->filhos[pai->qnt]->codigos[j] == cod){    
                    return pai->qnt;
                }
            }
        }
    return -1;
}

pagina *dividir_2_0(pagina **pag_principal, pagina *pag_esq, int *comp = NULL){
    if(pag_esq == NULL) return NULL;

    int meio;
    if(comp == NULL){
        meio = ceil((N - 1) / 2.0f);
    }
    else if(*comp < pag_esq->codigos[0]){
        meio = ((N - 1) / 2.0f);
    }else{
        meio = ceil((N - 1) / 2.0f);
    }

    pagina *pag_dir = criar_pagina();
    pagina *pag_pai = criar_pagina();

    for(int i = pag_esq->qnt - meio; i > 0; i--){
        pag_dir->codigos[i-1] = pag_esq->codigos[pag_esq->qnt - 1];
        pag_esq->codigos[pag_esq->qnt - 1] = 0;

        pag_dir->medicamentos[i-1] = pag_esq->medicamentos[pag_esq->qnt - 1];
        pag_esq->medicamentos[pag_esq->qnt - 1] = NULL;

        pag_dir->filhos[i] = pag_esq->filhos[pag_esq->qnt];
        pag_esq->filhos[pag_esq->qnt] = NULL;

        if(pag_dir->filhos[i] != NULL){
            pag_dir->filhos[i]->pai = pag_dir;
        }

        pag_dir->qnt++;
        pag_esq->qnt--;
        
    }

    ///////////////////////////////////////////////
    //caso isolado, serve para quando eu voltar ele jogar o ultimo filho da esq para direita
    // só vai servir para quando tiver filhos
    pag_dir->filhos[0] = pag_esq->filhos[pag_esq->qnt];
    pag_esq->filhos[pag_esq->qnt] = NULL;
    if(pag_dir->filhos[0] != NULL){
        pag_dir->filhos[0]->pai = pag_dir;
    }
    ////////////////////////////////////////////

    pag_pai->codigos[0] = pag_esq->codigos[meio - 1];
    pag_pai->qnt++;
    pag_pai->filhos[0] = pag_esq;
    pag_pai->filhos[1] = pag_dir;

    if(pag_esq->folha == false){
        pag_esq->filhos[pag_esq->qnt] = 0;
        pag_esq->qnt--;
    }

    pag_dir->pai = pag_pai;
    pag_pai->pai = pag_esq->pai;
    pag_esq->pai = pag_pai;

    pag_dir->prox = pag_esq->prox;
    pag_esq->prox = pag_dir;
    pag_pai->folha = false;

    if(pag_pai->pai == NULL){
        *pag_principal = pag_pai;
    }else{
        int localizacao_no_filho_do_pai = -1;
        localizacao_no_filho_do_pai = index_filho(pag_pai->pai, pag_esq->codigos[0]);

        if( localizacao_no_filho_do_pai != -1){
            pag_pai->pai->filhos[localizacao_no_filho_do_pai] = pag_pai;
        }
    }
    
    return pag_pai;

}

void anexar_page(pagina *pag, pagina *pag_add){
    int index = 0;
    for(int i = pag->qnt; i >= 0; i--){

        if(pag->filhos[i] == pag_add){//achei a posicao dele
            index = i;
            break;
        }else{
            pag->codigos[i] = pag->codigos[i-1];
            pag->filhos[i+1] = pag->filhos[i];
        }
    }
    pag->codigos[index] =  pag_add->codigos[0];
    pag->filhos[index] = pag_add->filhos[0];
    pag->filhos[index+1] = pag_add->filhos[1];

    if(pag_add->filhos[0] != NULL){
        pag_add->filhos[0]->pai = pag;
    }

    if(pag_add->filhos[1] != NULL){
        pag_add->filhos[1]->pai = pag;
    }
    
    pag->qnt++;
    return;
}

void back_2_0(pagina **page_pai, pagina *pag, pagina *pag_add){
    if(pag == NULL){
        *page_pai = pag_add;
        return;
    }

    if(pag->qnt < N-1){// tem espaço para page

        anexar_page(pag, pag_add);
        
    }
    else if(pag->qnt >= (N - 1)){ // sem espaço

        pag = dividir_2_0(page_pai, pag);

        // filhos da nova pagina pai recebe false, ja q não são folhas
        for(int i = pag->qnt; i >= 0; i--){
            pag->filhos[i]->folha = false;
        }

        pagina *guardar_pag = pag_add->pai;
        guardar_pag->codigos[guardar_pag->qnt] = 0;

        anexar_page(guardar_pag, pag_add);
        back_2_0(page_pai, pag->pai, pag);
        return;
    } 
}

bool verificar_brother(pagina *pag, int cod, medicamento *med){
    if(pag == NULL) return false;

    int index_subt = -1;

    pagina *brother = brother_esq_libert(pag->pai, pag->codigos[0], &index_subt);

    if(brother != NULL){

        if(brother->qnt < (N-1)){
            int ref = cod;
            if(cod > pag->codigos[0]){
                ref = pag->codigos[0];

                sort(brother, pag->codigos[0], pag->medicamentos[0]);
                pag->qnt--;

                for(int i = 0; i < pag->qnt; i++){
                    pag->codigos[i] = pag->codigos[i+1];
                    pag->medicamentos[i] = pag->medicamentos[i+1];
                }
                sort(pag, cod, med);
                
            }else{
                sort(brother, cod, med);
            }

            if(brother->pai != NULL){
                brother->pai->codigos[index_subt-1] = ref;
            }

            return true;
        }
    }

    return false;
}

bool insertion(pagina **page_pai, pagina *pag, int cod, medicamento *med){ 
    // não tem o caso de ser o primeiro
    pagina *aux = pag;
    if(pag == NULL) return false;

    if (aux->folha){
        if(aux->qnt <(N-1)){
            sort(aux, cod, med);
            return false;
        }
        else{
            // dois casos

            if(verificar_brother(pag, cod, med)){ // irmao tem vaga
                return false;
            }
            else { // divide 

                pagina *pai_q = aux->pai;
                aux = dividir_2_0(page_pai, aux, &cod);

                insertion(page_pai, aux, cod, med);

                back_2_0(page_pai, pai_q, aux);
                return false;
            }
        }
    }
    else{
        for(int i = 0; i < (aux)->qnt; i++){
            if((aux)->codigos[i] > cod){
                if(insertion(page_pai, (aux)->filhos[i], cod, med) == false){
                    return false;
                }
            }
        }

        if(aux->codigos[aux->qnt-1] < cod){
            insertion(page_pai, (aux)->filhos[(aux)->qnt], cod, med);
        }
    }
    return true;
}

void insercao(pagina **page_pai, int cod, medicamento *med){
    if(*page_pai == NULL){
        pagina *pag = criar_pagina();
        pag->codigos[0] = cod;
        pag->medicamentos[0] = med;
        pag->qnt++;
        *page_pai = pag;
        return;
    }else{
        insertion(page_pai, *page_pai, cod, med);
    }
    return;
}
////
pagina *brother_dir_libert(pagina* pai, int cod) {
    if (pai == NULL) return NULL;

    for (int i = 0; i <= pai->qnt; i++) {
        if(pai->filhos[i] != NULL){

            for(int j = 0; j < pai->filhos[i]->qnt; j++){
                if(pai->filhos[i]->codigos[j] == cod){
                    if(i - 1 >= 0 ){
                        return pai->filhos[i+1];
                    }else{
                        return NULL;
                    }
                }
            }
        }

    }

    return NULL;
}

///////////////////////////////////////////REMOCAO//////////////////////////////////////////

///////////////////////////////////////////REMOCAO//////////////////////////////////////////

bool remove_cod(pagina *pag, int cod){
    if(pag == NULL) return false;
    bool ativador = false;

    
    for(int i = 0; i < pag->qnt; i++){
        if(pag->codigos[i] == cod){
            ativador = true;
        }
        if(ativador == true){
            pag->codigos[i] = pag->codigos[i+1];
            pag->medicamentos[i] = pag->medicamentos[i+1];

        }
    }
  

    if(ativador == true){
        // limpando 
        if(pag->qnt-1 == 1){
            pag->codigos[pag->qnt] = 0;
            pag->medicamentos[pag->qnt] = NULL;
           

        }else{
        

            pag->codigos[pag->qnt - 1] = 0;
            pag->medicamentos[pag->qnt - 1] = NULL;
            
        }

        pag->qnt--;

    }else if(pag->codigos[pag->qnt-1] == cod){
        
        pag->codigos[pag->qnt - 1] = 0;
        pag->medicamentos[pag->qnt - 1] = NULL;
           
        pag->qnt--;
    }

    return ativador;
}

bool pelo_menos_um_filho_que_menor_minimo(pagina *pag){
    if(pag == NULL){
        return false;
    }

    for(int i = 0; i <= pag->qnt; i++){
        if(pag->filhos[i] != NULL){
            if(pag->filhos[i]->qnt < T-1){
                return true;
            }
        }
    }

    return false;
}

bool merger_bread_2_0(pagina *pai_pag, pagina *pag){
    if(pag == NULL or pai_pag == NULL) return false;

    bool vai = false;
    bool maior = false;
    bool lado_dir = false;
    bool lado_esq = false;

    if(pelo_menos_um_filho_que_menor_minimo(pai_pag)){
        

        for(int i = 0; i<=pai_pag->qnt; i++){
            if(pai_pag->filhos[i]!= NULL){
                int tam = pai_pag->filhos[i]->qnt;

                if(tam < T-1){ // o menor achei
                    vai = true;
                }
                if(tam > T-1){ // maior achei
                    maior = true;
                }

                if(vai == true and maior == false){ // achou o menor e o maior ainda não achou, então o maior deve ta dir
                    
                    lado_dir = true;
                } 
                else if(vai == false and maior == true){ // achou o maior e o não achou o menor ainda, então o maior ta na esq
                    
                    lado_esq = true; // garatia de que existe o maior e o menor
                }
                
                if(vai == true and maior == true){
                    

                    break;
                }
            }
        }


        if(vai == true and maior == true){
            bool parar = false;
            
            if(lado_esq){ // maior ta na esq, então temos que ir da esq para direita
                
                for(int i = 0; i < pai_pag->qnt; i++){
                    printf(" B ");

                    pagina *fh_0 = pai_pag->filhos[i];
                    pagina *fh_1 = pai_pag->filhos[i+1];
                    
                    if(fh_1 != NULL and fh_1->qnt < T-1){
                        parar = true;
                    }
                    int tam = pai_pag->filhos[i]->qnt;

                    
                    if(fh_0 != NULL and fh_0->qnt > T-1 ){ // maior achei
                        
                        
                        sort(fh_1, fh_0->codigos[tam-1], fh_0->medicamentos[tam-1]);
                        pai_pag->codigos[i] = fh_0->codigos[fh_0->qnt-1];
                        remove_cod(fh_0, fh_0->codigos[tam-1]);
                        //atualizando as chaves
                        pai_pag->codigos[i] = fh_0->codigos[fh_0->qnt-1]; 
                        
                    }
                    
                    if(parar == true){
                        
                        break;
                    }
                
                    
                }
                return true;

            }
            else if(lado_dir){ // maior ta na dir, então temos que ir da dir para esq
                
                
                for(int i = pai_pag->qnt; i > 0 ; i--){

                    
                    pagina *fh_dir = pai_pag->filhos[i];
                    pagina *fh_esq = pai_pag->filhos[i-1];
                    
                        if(fh_esq != NULL and fh_esq->qnt < T-1){
                            parar = true;
                        }
                        
                        if(fh_dir != NULL and fh_dir->qnt > T-1){ // maior achei
                            
                            sort(fh_esq, fh_dir->codigos[0], fh_dir->medicamentos[0]);
                            pai_pag->codigos[i-1] = fh_esq->codigos[fh_esq->qnt-1];
                            remove_cod(fh_dir, fh_dir->codigos[0]);
                            //atualizando a chave
                            pai_pag->codigos[i-1] = fh_esq->codigos[fh_esq->qnt-1];
                        }
                        if(parar == true){
                            
                            
                            break;
                        }
                    
                }
                return true;

            }
        }
    }
    return false;
}

bool todos_T_2_0(pagina **page_principal, pagina *pai_pag, pagina *pag){
    if(pai_pag == NULL) return false;

    int contagem = 0;
    bool vai = false;

    if((pag->qnt < T-1 and *page_principal != pag) or (pai_pag->qnt - 1 < T-1 and *page_principal != pai_pag)){
        
        return false;
    }

    for(int i = 0; i <= pai_pag->qnt; i++){
        if(pai_pag->filhos[i]!= NULL){
            if(pai_pag->filhos[i]->qnt == T-1){
                contagem++;
            }else{
                contagem = 0;
            }
            if(contagem == 3){
                

                vai = true;
                break;
            }
        }
    }

    if(vai == true){
        
        
        int pos[3];
        contagem = 0;

        for(int i = 0; i<=pai_pag->qnt; i++){
            if(contagem == 3){
                vai = true;
                
                break;
            }
            if(pai_pag->filhos[i] != NULL && pai_pag->filhos[i]->qnt == T-1){
                pos[contagem] = i;
                contagem++;
            }else{
                contagem = 0;
                pos[0] = 0;
                pos[1] = 0;
                pos[2] = 0;
            }
        }
 
        int i = pos[0];
        
            
        int meio = (pai_pag->filhos[i+1]->qnt)/2;

        for(int j = 0; j < meio ; j++){
            sort(pai_pag->filhos[i], pai_pag->filhos[i+1]->codigos[0], pai_pag->filhos[i+1]->medicamentos[0]);
            remove_cod(pai_pag->filhos[i+1], pai_pag->filhos[i+1]->codigos[0]);

            //atualizando a referência
        }
        pai_pag->codigos[i] = pai_pag->filhos[i]->codigos[pai_pag->filhos[i]->qnt-1];

        i=pos[2];
        
        int arm=pai_pag->filhos[i]->qnt;

        for(int k = 0; k < arm; k++){
            sort(pai_pag->filhos[pos[1]], pai_pag->filhos[i]->codigos[0], pai_pag->filhos[i]->medicamentos[0]);
            remove_cod(pai_pag->filhos[i], pai_pag->filhos[i]->codigos[0]);

            //atualizando a referência        
        }
        pai_pag->codigos[pos[1]] = pai_pag->filhos[pos[1]]->codigos[pai_pag->filhos[pos[1]]->qnt-1];
        
        pai_pag->filhos[pos[1]]->prox = pai_pag->filhos[pos[2]]->prox;

        /// formatando pra ficar ordenando
        for(int a = pos[2]; a < pai_pag->qnt; a++){
            
            pai_pag->codigos[a-1] = pai_pag->codigos[a];
            pai_pag->filhos[a] = pai_pag->filhos[a+1];

        }
        pai_pag->codigos[pai_pag->qnt-1] = 0;
        pai_pag->filhos[pai_pag->qnt] = NULL;
        pai_pag->qnt--;
        return true;
    }

    return false;

}

void bubler_menor(int i, pagina *pag){
    if(pag == NULL) return;

    for(int pos = i + 1; pos < pag->qnt; pos++){
        pag->codigos[pos] = pag->codigos[pos+1];
        pag->medicamentos[pos] = pag->medicamentos[pos+1];
        pag->filhos[pos] = pag->filhos[pos+1];
    }
    pag->filhos[pag->qnt] = NULL; // ultimo filho
    pag->codigos[pag->qnt-1] = 0;

    pag->qnt--;

}

void caso_especif_juntar_irmao_com_pai(pagina **page_principal, pagina *pai, int index_pai){
    if(pai == NULL) return;
    
    if(pai->filhos[index_pai] != NULL){
        if(pai->filhos[index_pai]->folha == true){
            pagina *irmao_esq = brother_esq_libert(pai, pai->filhos[index_pai]->codigos[0]);
            pagina *irmao_dir = brother_dir_libert(pai, pai->filhos[index_pai]->codigos[0]);
            bool dir = false, esq = false;

            if(irmao_esq != NULL){
                if(irmao_esq->folha == false){
                    esq = true;
                }
            }

            if(irmao_dir != NULL){
                if(irmao_dir->folha == false){
                    dir = true;
                }
            }

            if(dir){
               

                for(int i = irmao_dir->qnt; i>0; i--){
                    irmao_dir->codigos[i] = irmao_dir->codigos[i-1];
                    irmao_dir->medicamentos[i] = irmao_dir->medicamentos[i-1]; // possivelmente não tem
                    irmao_dir->filhos[i+1] = irmao_dir->filhos[i];

                }
                irmao_dir->filhos[1] = irmao_dir->filhos[0]; // vai sobrar um filho da esq, precisa ir para direita tbm


                irmao_dir->codigos[0] = pai->codigos[0];
                irmao_dir->medicamentos[0] = pai->medicamentos[0]; // possivelmente nao tem
                
                irmao_dir->qnt++;

                irmao_dir->filhos[0] = pai->filhos[0]; // atualizando filho q antes era do isolado
                if(pai->filhos[0]!= NULL){
                    pai->filhos[0]->pai = irmao_dir;
                }

                if(*page_principal == pai){
                    
                    irmao_dir->pai = NULL;
                    *page_principal = irmao_dir;
                }else{
                    

                    irmao_dir->pai = pai->pai;
                    // nome das vai ficar assim pra eu não esquecer o q ta fazendo, é muita coisa 
                    int atualizar_novo_filho_do_pai_do_pai = index_filho(pai->pai, pai->codigos[0]);
                    pai->pai->filhos[atualizar_novo_filho_do_pai_do_pai] = irmao_dir;
                }
                delete pai;
                
                
            }
            else if(esq){
               
                irmao_esq->codigos[irmao_esq->qnt] = pai->codigos[0];
                irmao_esq->qnt++;
                irmao_esq->filhos[irmao_esq->qnt] = pai->filhos[1];
                
                if(pai->filhos[1]!= NULL){
                    pai->filhos[1]->pai = irmao_esq;
                }

                if(*page_principal == pai){
                    
                    irmao_esq->pai = NULL;
                    *page_principal = irmao_esq;
                }else{
                    

                    irmao_esq->pai = pai->pai;
                    // nome das vai ficar assim pra eu não esquecer o q ta fazendo, é muita coisa 
                    int atualizar_novo_filho_do_pai_do_pai = index_filho(pai->pai, pai->codigos[0]);
                    pai->pai->filhos[atualizar_novo_filho_do_pai_do_pai] = irmao_esq;
                }
                delete pai;
                

            }
        }
    }

}

bool pelos_menos_um_T(pagina **page_principal, pagina *pag, bool sem_restricao = false){
    if(pag == NULL) return true;

    
    for(int i = 0; i < pag->qnt; i = i + 2){

        
        if((pag->filhos[i] != NULL and pag->filhos[i+1] != NULL and (pag->qnt > T-1 or *page_principal == pag) and sem_restricao == false) or (pag->filhos[i] != NULL and pag->filhos[i+1] != NULL and sem_restricao == true)){
            
            
            if((pag->filhos[i]->qnt < T - 1 and pag->filhos[i+1]->qnt >= T-1) or (pag->filhos[i]->qnt >= T-1 and pag->filhos[i+1]->qnt < T - 1) or ((pag->filhos[i]->qnt < T-1 or pag->filhos[i+1]->qnt < T-1) and sem_restricao == true)){
            
                ///////////junção 
                for(int j = pag->filhos[i+1]->qnt - 1; j>=0; j--){
                    sort(pag->filhos[i], pag->filhos[i+1]->codigos[j],pag->filhos[i+1]->medicamentos[j]);
                    remove_cod(pag->filhos[i+1], pag->filhos[i+1]->codigos[j]);
                }

                pag->filhos[i]->prox = pag->filhos[i+1]->prox;
        

                //limpando
                delete pag->filhos[i+1];
                

                if(pag->qnt == T-1 and pag->pai == NULL){
                    

                    *page_principal = pag->filhos[i];
                    (*page_principal)->pai = NULL;
                    return true;
                }
                else if(pag->qnt == T-1){
                    


                    if(pag->pai == NULL and pag->qnt<T-1){
                        *page_principal = pag;
                        (*page_principal)->pai = NULL;
                    }else{

                        
                        bubler_menor(i, pag);

                        int index_pai_page = index_filho(pag->pai, pag->codigos[0]);
                        pag->filhos[index_pai_page] = pag->filhos[i];
                        pag->filhos[i]->pai = pag;

                        caso_especif_juntar_irmao_com_pai(page_principal, pag->pai, index_pai_page);
                    }
                    
                    
                    return true;
                }
                else{
                    // pode diminuir
                    

                    if(pag->pai == NULL and pag->qnt<T-1){
                        

                        *page_principal = pag->filhos[i];
                        (*page_principal)->pai = NULL;

                    }else{
                        
                        imprimir(pag->filhos[i]);
                        bubler_menor(i, pag);
                        int index_pai_page = index_filho(pag, pag->filhos[i]->codigos[0]);
                        pag->filhos[index_pai_page] = pag->filhos[i];
                        // atualizando a chave
                        pag->codigos[i] = pag->filhos[index_pai_page]->codigos[pag->filhos[index_pai_page]->qnt - 1]; 
                        }
                    

                    return true;
                }
            }
        }
    }
    return false;
}

pagina * funcao_2_0_brother_dir(pagina *pai, int cod){
    if(pai == NULL) return NULL;

    for (int i = 0; i < pai->qnt; i++) {
        if(pai->filhos[i] != NULL){

            for(int j = 0; j < pai->filhos[i]->qnt; j++){
                if(pai->filhos[i]->codigos[j] == cod){
                    
                    return pai->filhos[i+1];
                    
                }
            }
        }

    }

    if(pai->filhos[pai->qnt]->codigos[0] == cod){
        // printf("XXX");
        return pai->filhos[pai->qnt];
    }

    return NULL;
}

bool caso_juncao(pagina **page_principal, pagina *pai_pag, pagina *pag){
    if(pag == NULL){
        return true;
    }
    if(pai_pag->qnt == T-1){

        pagina *irmao_esq = brother_esq_libert(pai_pag->pai, pai_pag->codigos[0]);
        pagina *irmao_dir =funcao_2_0_brother_dir(pai_pag->pai, pai_pag->codigos[0]);
        int index_pai_page = index_filho(pai_pag->pai, pai_pag->codigos[0]);

        if(irmao_dir == pai_pag){ // serve pra dir e esquerd
            irmao_dir = NULL;
        }
        if(irmao_esq == pai_pag){
            irmao_esq = NULL;
        }

        if(irmao_dir != NULL){
            int gd = pai_pag->qnt;
            int x = irmao_dir->qnt;
            
            for(int aux = 0; aux < x; aux++){

                sort(pai_pag, irmao_dir->codigos[aux], irmao_dir->medicamentos[aux]);

                pai_pag->filhos[pai_pag->qnt] = irmao_dir->filhos[aux+1];

                if(irmao_dir->filhos[aux+1] != NULL){
                    irmao_dir->filhos[aux+1]->pai = pai_pag;
                }
            }
            

            pai_pag->filhos[pai_pag->qnt] = irmao_dir->filhos[irmao_dir->qnt];
            if(irmao_dir->filhos[irmao_dir->qnt] != NULL){
                irmao_dir->filhos[irmao_dir->qnt]->pai = pai_pag;
            }
            

            if(irmao_dir->filhos[0] != NULL){
                for(int i = 0; i < irmao_dir->qnt; i++){
                    if(pai_pag->filhos[gd] != NULL){
                        sort(pai_pag->filhos[gd], irmao_dir->filhos[0]->codigos[i], irmao_dir->filhos[0]->medicamentos[i]);
                    }
                }
            }

            
            if(*page_principal == pai_pag->pai){
                
                pai_pag->pai = NULL;
                *page_principal = pai_pag;
                imprimir(*page_principal);

            }
            else{
                

                int index_pai_pai = index_filho(pai_pag->pai->pai, pai_pag->pai->codigos[0]);
                pai_pag->pai->pai->filhos[index_pai_pai] = pai_pag;
                pai_pag->pai = pai_pag->pai->pai;
            }
            return true;

        }else if(irmao_esq != NULL){
            
            int gd = pai_pag->qnt;
            int x = irmao_esq->qnt;
            
            for(int aux = 0; aux < gd; aux++){
                sort(irmao_esq, pai_pag->codigos[aux], pai_pag->medicamentos[aux]);
                irmao_esq->filhos[irmao_esq->qnt] = pai_pag->filhos[aux+1];

                if(pai_pag->filhos[aux+1] != NULL){
                    
                    pai_pag->filhos[aux+1]->pai = irmao_esq;
                }
            }
            
            irmao_esq->filhos[irmao_esq->qnt] = pai_pag->filhos[pai_pag->qnt];
            if(pai_pag->filhos[pai_pag->qnt] != NULL){
                pai_pag->filhos[pai_pag->qnt]->pai = irmao_esq;
            }

            if(pai_pag->filhos[0] != NULL){
                

                for(int i = 0; i < pai_pag->qnt; i++){
                    if(irmao_esq->filhos[x] != NULL){
                        sort(irmao_esq->filhos[x], pai_pag->filhos[0]->codigos[i], pai_pag->filhos[0]->medicamentos[i]);
                    }
                }
            }
            
            
            if(*page_principal == pai_pag->pai){
                irmao_esq->pai = NULL;
                *page_principal = irmao_esq;
                

            }
            else{
                int index_pai_pai = index_filho(pai_pag->pai->pai, pai_pag->pai->codigos[0]);
                pai_pag->pai->pai->filhos[index_pai_pai] = irmao_esq;
                irmao_esq->pai = pai_pag->pai->pai;
            }
            
            return true;

        }
    }
    return false;

}

bool redistribuir(pagina **page_principal, pagina *pag){
    if(pag == NULL) return false;

    pagina *pai_pag = pag->pai;
    if(pai_pag == NULL){
        return false;
    }
    

    if(merger_bread_2_0(pai_pag, pag)){
        
    }
    else if(todos_T_2_0(page_principal, pai_pag, pag)){
        
    }
    else if(pelos_menos_um_T(page_principal, pag->pai)){
        
    }
    else{
        
        if(pag->qnt < T-1){
            pagina *guarde = pag; 
            if(caso_juncao(page_principal, pag->pai, pag)){   
                pelos_menos_um_T(page_principal, guarde->pai, true);

            }
            
        }
        
        return true;
    }

    return false;
}

bool remocao_init(pagina **page_pai, pagina *pag, int cod){


    if(pag == NULL) return false;

    if(pag->folha == true){

        for(int i = 0; i < pag->qnt; i++){
            if(pag->codigos[i] == cod){
                
                remove_cod(pag, cod);

                redistribuir(page_pai, pag);    
                return false;
            }
        }
    }


    for(int i = 0; i < (pag)->qnt; i++){
        if(pag->codigos[i] >= cod){
            if(remocao_init(page_pai, pag->filhos[i], cod) == false){
                return false;
            }
        }
    }

    if(pag->codigos[pag->qnt-1] < cod){
        if(remocao_init(page_pai, pag->filhos[pag->qnt], cod) == false){
            return false;
        }
    }
    
    return true;
}


///////////////Sistema\\\\\\\\\\/
void print_data(medicamento *med){
    if (med == NULL) return;
    printf("\n\t\t************************");
    printf("\n\t\t|**Codigo de Barras: %d", med->codigo_barra);
    printf("\n\t\t|**Nome: %s", med->nome);
    printf("\n\t\t|**Data: %s", med->date);
    printf("\n\t\t|**Quantidade: %d", med->quant);
    printf("\n\t\t|**Preco: %.3f", med->preco);
    printf("\n\t\t************************");

}

medicamento *criar_medicamento(){
    medicamento *med = new medicamento;

    printf("\n\t\tCódigo de Barra: ");
    scanf("%d", &med->codigo_barra);
    printf("\t\tNome do Medicamento: ");
    scanf(" %[^\n]s", med->nome);
    printf("\t\tData do Cadastro: ");
    scanf(" %[^\n]s", med->date);
    printf("\t\tQuantidade: ");
    scanf("%d", &med->quant);
    printf("\t\tPreço: ");
    scanf("%f", &med->preco);

    return med;
}

medicamento *busca_cod_barra(pagina *pag, int cod){
    if(pag == NULL) return NULL;

    if(pag->folha == true){
        for(int i = 0; i<pag->qnt; i++){
            if(pag->codigos[i] == cod){
                return pag->medicamentos[i];
            }
        }
    }

    for (int i = 0; i < pag->qnt; i++) {
        if(pag->codigos[i] >= cod){
            return busca_cod_barra(pag->filhos[i], cod);
        }
    }
    
    if(pag->codigos[pag->qnt] < cod){
        return busca_cod_barra(pag->filhos[pag->qnt], cod);
    }
    return NULL;
}

void buscar_med(pagina *pag){
    int cod = 0;
    printf("\n\t\tDigite o Codigo de Barras do Medicamento: ");
    scanf("%d", &cod);

    medicamento *medic_busc = busca_cod_barra(pag, cod);
    if(medic_busc == NULL){
        printf("\n\t\tMedicamento Inexistente !");
    }else{
        print_data(medic_busc);
    }
}

void inserir_medi(pagina **pagina_principal){
    printf("\n\n\t\t1 - Inserir Novo Medicamento");
    printf("\n\t\t2 - Adicionar Medicamento\n\t\t>");
    int op = 999;
    scanf("%d", &op);

    switch (op)
    {
    case 1:{
        medicamento *med_novo = criar_medicamento();
        if(busca_cod_barra(*pagina_principal, med_novo->codigo_barra) !=  NULL){
            printf("\n\t\tMedicamento já existente !");
        }else{
            insercao(pagina_principal, med_novo->codigo_barra, med_novo);
            printf("\n\t\tAdicionado !");
        }
        return;
    }
    case 2:{
        printf("\n\t\tCodigo do Medicamento: \n\t\t>>>>>");
        int cod = 999;
        scanf("%d", &cod);
        
        medicamento *produto = busca_cod_barra(*pagina_principal, cod);
        
        if(produto ==  NULL){
            printf("\n\t\tEsse medicamento precisa ser inserido !");
        }else{

            int quantid = 0;
            printf("\n\t\tQuantidade de medicamentos que deseja adicionar: ");
            scanf("%d", &quantid);

            if(quantid >= 0){
                produto->quant = produto->quant + quantid;
                printf("\n\t\tAdicionado !");
            }else{
                printf("\n\t\tQuantidade Invalida !");
            }
        }
        return;
    }
    default:
        return;
    }

}

void remover_medi(pagina **pagina_principal){
    if(*pagina_principal == NULL){
        printf("\n\t\tAdicione Medicamentos");
        return;
    }

    printf("\n\t\tCodigo do Medicamento: \n\t\t>>>>>");

    int cod = 999;
    scanf("%d", &cod);
    
    medicamento *produto = busca_cod_barra(*pagina_principal, cod);
    
    if(produto ==  NULL){
        printf("\n\t\tEsse medicamento precisa ser inserido no estoque!");
    }else{

        int quantid = 0;
        printf("\n\t\tQuantidade de medicamentos que deseja remover: ");
        scanf("%d", &quantid);

        if(quantid > produto->quant){
            printf("\n\t\tQuantidade de medicamentos maior que o estoque disponivel na farmacia !");
        }
        else if(quantid <= produto->quant){
            int total = produto->quant - quantid;

            if(total == 0){
                remocao_init(pagina_principal, *pagina_principal, produto->codigo_barra);
                printf("\n\t\tMedicamento Removido do Estoque !");
            }else{
                produto->quant = total;
                printf("\n\t\tRetirado %d do estoque de medicamentos %s.", quantid, produto->nome);
            }
        }
    }

}

bool menu(pagina **pag_principal){

    printf("\n\t\t1 - Buscar Medicamento");
    printf("\n\t\t2 - Inserir Medicamento");
    printf("\n\t\t3 - Retirar Medicamento");
    printf("\n\t\t4 - Imprimir Medicamentos\n\t\t>");
    int op = 999;
    scanf("%d", &op);

    switch (op)
    {
    case 0:{
        return false;
    }
    case 1:{
        buscar_med(*pag_principal);    
        return true;
    }case 2:{
        inserir_medi(pag_principal);
        return true;
    }case 3:{
        remover_medi(pag_principal);
        return true;
    }case 4:{
        if(*pag_principal == NULL){
            printf("\n\t\tSem Medicamentos Inseridos !");
        }else{
            printf("\n\t\t*****Codigos de Barras*****\n");
            print(*pag_principal);
        }
        return true;
    case 5:{
        imprimir(*pag_principal);
    }
    }default:
        printf("\n\t\tOpcao Invalida");
        return true;
    }

    return true;
}

int main(){ 

    pagina *pag = NULL;  
    bool logic = true;  
    while (logic == true){
        logic = menu(&pag);
    }

    return 0;

}

