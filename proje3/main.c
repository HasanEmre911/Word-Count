#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct bagliListe{
    int adet;
    char kelime[30];
    struct bagliListe *next;
};

struct bagliListe *ilk=NULL, *son=NULL, *temp=NULL;

void yazdir(struct bagliListe *yaz){
	while(yaz){
		printf("%s : %d\n",yaz->kelime,yaz->adet);
		yaz=yaz->next;
	}
	return;
}

int zatenVarMi(struct bagliListe *varMi, char word[30]){ //Yollanan kelime bagli liste icerisinde varsa 0 degeri dondurur ve bu kelime tekrardan bagli listeye eklenmez.
    int sayac=0;
    while(varMi){
        if(strcmp(varMi->kelime,word)==0){
            sayac++;

        }
    varMi=varMi->next;
	}
    if(sayac>0)
        return 0;
    else
        return 1;
}

void basaEkle(struct bagliListe *yeniKelime){
    yeniKelime->next = ilk;
    ilk = yeniKelime;
}

void sonaEkle(struct bagliListe *yeniKelime){
    son->next = yeniKelime;
    son = yeniKelime;
    son->next = NULL;
}

void arayaEkle(struct bagliListe *yeniKelime){
    temp = ilk;
    while(temp->next->adet > yeniKelime->adet){
        temp = temp->next;
    }
    struct bagliListe *onune = (struct bagliListe*) malloc(sizeof(struct bagliListe));
    onune = temp->next;
    temp->next = yeniKelime;
    yeniKelime->next = onune;
}

int main()
{

    FILE *dosya,*dosya2;
    if(!(dosya = fopen("metin.txt","r"))){
        printf("Dosya acilamadi.\n");
        return 0;
    }

    char word[30],ayniMi[30];
    int kelimeAdedi=0,varMi;

    while(!feof(dosya))
    {
        fscanf(dosya,"%s",word);
        dosya2 = fopen("metin.txt","r");
        while(!feof(dosya2)){
            fscanf(dosya2,"%s",ayniMi);
            if(strcmp(word,ayniMi)==0){
                kelimeAdedi++;
            }
        }
        fclose(dosya2);

        varMi = zatenVarMi(ilk,word);
        if(varMi==0){
            kelimeAdedi=0;
            continue;
        }

        struct bagliListe *yeniKelime = (struct bagliListe*) malloc(sizeof(struct bagliListe));
        strcpy(yeniKelime->kelime,word);
        yeniKelime->adet = kelimeAdedi;

        if(ilk==NULL){
            ilk = yeniKelime;
            son = yeniKelime;
            ilk -> next = NULL;
        }
        else{
            if(yeniKelime->adet >= ilk->adet){
                basaEkle(yeniKelime);
            }
            else if(yeniKelime->adet <= son->adet){
                sonaEkle(yeniKelime);
            }
            else{
                arayaEkle(yeniKelime);
            }
        }
        kelimeAdedi=0;
    }
    fclose(dosya);
    yazdir(ilk);
}
