#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   
#include <windows.h>   
#include <conio.h>    
#include <string.h> 

typedef struct {
    int t_normale;
    int t_leger;
    int t_critique;
} Type_alerte;
Type_alerte ta = {0,0,0};



typedef struct {
    float min;
    float max;
    float sum;
    int nb;
} Valeurs;
Valeurs v = {1000.0, 0.0, 0.0, 0};

// hedhi lfonction fi wist prog principale while
void ValeursRapport(Valeurs *v, float temp) {
    if (temp > v->max) v->max = temp;
    if (temp < v->min) v->min = temp;
    v->sum += temp;
    v->nb += 1;
}


//sami7
#define FICHIER_CONFIG "config.txt"
#define TAILLE_BUFFER 100

typedef struct{
    char type_lieu[50];
    float seuil_min;
    float seuil_max;
    int intervalle_mesure;
} Configuration;

void creerConfiguration(Configuration *config)
{
    int valide = 0;

    printf("=== Configuration du Controleur de Temperature ===\n\n");

    while (!valide)
    {

        printf("Type de lieu (Maison, Serveur, Serre) : ");
        fgets(config->type_lieu, TAILLE_BUFFER, stdin);
        config->type_lieu[strcspn(config->type_lieu, "\n")] = '\0';

        char type_lower[TAILLE_BUFFER];
        int i;
        for (i = 0; config->type_lieu[i]; i++){
            if (config->type_lieu[i] >= 'A' && config->type_lieu[i] <= 'Z')
            {
                type_lower[i] = config->type_lieu[i] + 32;
            }
            else
            {
                type_lower[i] = config->type_lieu[i];
            }
        }
        type_lower[i] = '\0';

        if (strcmp(type_lower, "maison") != 0 && strcmp(type_lower, "serveur") != 0 && strcmp(type_lower, "serre") != 0){
            printf("\n[!] Erreur : Le type de lieu doit etre 'Maison', 'Serveur' ou 'Serre' !\n");
            printf("Veuillez reessayer...\n\n");
            continue;
        }

        printf("Seuil minimum de temperature (C) : ");
        scanf("%f", &config->seuil_min);

        printf("Seuil maximum de temperature (C) : ");
        scanf("%f", &config->seuil_max);

        printf("Intervalle de mesure (en secondes) : ");
        scanf("%d", &config->intervalle_mesure);
        getchar();

        if (config->seuil_min >= config->seuil_max){
            printf("\n[!] Erreur : Le seuil minimum (%.2fC) doit etre inferieur au seuil maximum (%.2fC) !\n",
                   config->seuil_min, config->seuil_max);
            printf("Veuillez reessayer...\n\n");
            continue;
        }

        if (config->intervalle_mesure <= 0){
            printf("\n[!] Erreur : L'intervalle de mesure (%d) doit etre positif !\n",
                   config->intervalle_mesure);
            printf("Veuillez reessayer...\n\n");
            continue;
        }

        valide = 1;
    }

    // Creer et ecrire dans le fichier
    FILE *fichier = fopen(FICHIER_CONFIG, "w");
    if (fichier == NULL){
        perror("Erreur lors de la creation du fichier de configuration");
        exit(1);
    }

    // Ecrire les parametres dans le fichier
    fprintf(fichier,"type_lieu=%s\n",config->type_lieu);
    fprintf(fichier,"seuil_min=%.2f\n",config->seuil_min);
    fprintf(fichier,"seuil_max=%.2f\n",config->seuil_max);
    fprintf(fichier,"intervalle_mesure=%d\n",config->intervalle_mesure);

    fclose(fichier);

    printf("\n[OK] Configuration enregistree avec succes dans'%s'!\n",FICHIER_CONFIG);
    printf("\nResume de la configuration :\n");
    printf("  - Type de lieu       : %s\n", config->type_lieu);
    printf("  - Seuil minimum      : %.2fC\n", config->seuil_min);
    printf("  - Seuil maximum      : %.2fC\n", config->seuil_max);
    printf("  - Intervalle mesure  : %d secondes\n\n", config->intervalle_mesure);
}

//sami7

float randombetween(float min,float max){
    float a=rand()/(float)RAND_MAX; //0.0 to 1.0

    return min+a*(max-min);
}


//esta3melt pointeur bech valeur matetresatech
void write_log(FILE *f,const char *location,int intervalle_mesure,int i,float seuilmin,float seuilmax,Type_alerte *ta,int *c1,int *c2,int *c3){

    float valeur;
    int c;

    Sleep(intervalle_mesure*1000);
    if(strcmp(location,"maison")==0){
        valeur=randombetween(15.0,50.0);
        printf("Températue mesure %.2f: ",valeur);
        c=1;
        ValeursRapport(&v,valeur);
    }else if(strcmp(location,"serre")==0){
        valeur=randombetween(20.0,60.0);
        printf("Températue mesure %.2f: ",valeur);
        c=3;
        ValeursRapport(&v,valeur);
    }else if(strcmp(location,"serveur")==0){
        valeur=randombetween(20.0,60.0);
        printf("Températue mesure %.2f: ",valeur);
        c=2;
        ValeursRapport(&v,valeur);
    }
    int marge = 0; 
    int crit=0;
    
    switch (c) {
        case 1:
            marge = 2;
            crit=5;
            break; 
        case 2:
            marge = 3;
            crit=5;
            break;
        case 3:
            marge = 5;
            crit=6;
            break;
    }
    if (valeur >= seuilmin && valeur <= seuilmax) {
        //printf("valeur capteur: %.2f\n",valeur);
        printf("Normal\n");
        (*c1)=0;
        (*c2)=0;
        (*c3)=0;
    }
    else if ((valeur < seuilmin && valeur >= (seuilmin - marge)) || (valeur > seuilmax && valeur <= (seuilmax + marge))) {
        //printf("valeur capteur: %.2f\n",valeur);
        printf("Depassement leger: niveau 1\n"); 
        (*c1)++;
        (*c2)=0;
        (*c3)=0;
    }
    else if((valeur>seuilmax+marge && valeur<=seuilmax+crit) ||(valeur<seuilmin-marge && valeur>=seuilmin-crit)){
        printf("depassement important: niveau 2\n");
        (*c2)++;
        (*c1)=0;
        (*c3)=0;
    }
    else {
        //printf("valeur capteur: %.2f\n",valeur);
        printf("Depassement critique: niveau 3\n");
        (*c3)++;
        (*c1)=0;
        (*c2)=0;
    }
    if(*c1>=3){
        ta->t_normale++;
        (*c1)=0;
    }else if(*c2>=3){
        ta->t_leger++;
        *c2=0;
    }
    else if(*c3>=3){
        ta->t_critique++;
        *c3=0;
    }

    //printf("valeur capteur: %.2f\n",valeur);
    time_t now=time(NULL);//taedh wa9t bel secont men 1970
    struct tm *t=localtime(&now);
    fprintf(f,"mesure %d: %.2f   %02d-%02d-%04d %02d:%02d:%02d\n",i,valeur,t->tm_mday,t->tm_mon+1,t->tm_year+1900,t->tm_hour,t->tm_min,t->tm_sec);
    
}

int main() {


    srand(time(NULL));//donne des nb aleatoires diff
    Configuration config;
    creerConfiguration(&config);
    FILE *f1=fopen("config.txt","r");



    char etablissement[50];
    float seuilmax,seuilmin;
    int intervalle_mesure;
    fscanf(f1,"type_lieu=%49s\n",&etablissement);
    fscanf(f1,"seuil_min=%f\n",&seuilmin);
    fscanf(f1,"seuil_max=%f\n",&seuilmax);
    fscanf(f1,"intervalle_mesure=%d\n",&intervalle_mesure);
    
    fclose(f1);

    
    FILE *f=fopen("journal.txt","w");
    int i=1;
    int c1=0;
    int c2=0;
    int c3=0;
    
    while(1){

        write_log(f,etablissement,intervalle_mesure,i,seuilmin,seuilmax,&ta,&c1,&c2,&c3);
        i++;

        if(_kbhit()){ //tcapti chnaw nzelt 
            char c=_getch(); //tchouf chnaw nzelt 3al clavier
            if(c=='q'){
                printf("Arrêt demandé par l'utilisateur.\n");
                printf("####################################\n");
                printf("Rapport:\n");
                break;
            }
        }
    }
    fclose(f);

    FILE *f2=fopen("rapport_journalier.txt","w");
    fprintf(f2,"Température MAX : %.2f°C\n", v.max);
    fprintf(f2,"Température MIN : %.2f°C\n", v.min);
    fprintf(f2,"Température MOYENNE : %.2f°C\n",v.sum/v.nb);
    fprintf(f2,"Ona %d d'alert de niveau 1: depassement leger.\n",ta.t_normale);
    fprintf(f2,"Ona %d d'alert de niveau 2: depassement important.\n",ta.t_leger);
    fprintf(f2,"Ona %d d'alert de niveau 3: depassement critique.\n",ta.t_critique);

    fprintf(f2,"La Durée totale en état d'alerte est:%d seconde.\n",(ta.t_normale+ta.t_leger+ta.t_critique)*intervalle_mesure);
    fclose(f2);



    FILE *f3=fopen("rapport_journalier.txt","r");

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f3)) {
        printf("%s", ligne);   // afficher chaque ligne
    }

    fclose(f3); 
    return 0;
}