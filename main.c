#include <stdio.h>

#define VSTUPNISOUBOR "cisla.txt"
#define ODCHOZISOUBOR "prevody.txt"

void header(){
    printf("poradi          draha          cas    rychlost\n");
    printf("----------------------------------------------");
}
void headerF(FILE *prevodyS){
    fprintf(prevodyS, "poradi         draha                   cas     rychlost\n");
    fprintf(prevodyS, "-------------------------------------------------------\n");
}

int main() {
    FILE *cislaS, *prevodyS;
    int draha;
    int cas;
    int poradi = 0;
    int delkaDrahy;
    int Fporadi = 0;
    if ((cislaS = fopen(VSTUPNISOUBOR, "r")) == NULL){
        printf("Pri otevirani souboru %s vznikl error :/\n", VSTUPNISOUBOR);
    }
    else {
        if ((prevodyS = fopen(ODCHOZISOUBOR, "w")) == NULL) {
            printf("Pri otevirani souboru %s vznikl error :/\n", ODCHOZISOUBOR);
        }
        else{
          header();
          headerF(prevodyS);
          while(fscanf(cislaS, "%d%d",&draha,&cas ) != EOF){
              poradi++;
              delkaDrahy += draha;
              printf("\n%5d.|%11d m|%10d s| %.2f m/s",poradi, draha, cas, (float)draha/cas);
              if(draha/cas > 10){
                  Fporadi++;
                  fprintf(prevodyS,"\n%2d.| %2d km %5d metru| %2d minut %2d sekund| %6.2f km/h", Fporadi, draha / 1000, draha % 1000, cas / 60, cas % 60, (float)(draha/cas)* 3.6);
              }

          }
        }
    }
    printf("\n\nPrumerna delka drahy je %.2f metru", (float)delkaDrahy / poradi);
    printf("\nZe souboru bylo precteno %d dvojic cisel", poradi);
    fprintf(prevodyS,"\nDo souboru bylo zapsano %d dvojic cisel", Fporadi);
    if (fclose(cislaS) == EOF) {
        printf("There has ben an error at closing the file %s.\n", VSTUPNISOUBOR);
    }
    if (fclose(prevodyS) == EOF) {
        printf("There has ben an error at closing the file %s.\n", ODCHOZISOUBOR);
    } else {
        printf("%s file has been created.\n", ODCHOZISOUBOR);
    }
    return 0;
}
