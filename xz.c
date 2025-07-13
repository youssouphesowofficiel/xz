#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1000
#define MAX_WORDS 100

void remplacer_mot(char *phrase, const char *motA, const char *motB) {
    char buffer[MAX_LEN];
    char *pos, *debut = phrase;
    int lenA = strlen(motA);
    buffer[0] = '\0';

    while ((pos = strstr(debut, motA)) != NULL) {
    
        int avant = (pos == phrase || !isalnum(*(pos - 1)));
        int apres = !isalnum(*(pos + lenA));
        if (avant && apres) {
            strncat(buffer, debut, pos - debut);
            strcat(buffer, motB);
            debut = pos + lenA;
        } else {
            strncat(buffer, debut, pos - debut + 1);
            debut = pos + 1;
        }
    }

    strcat(buffer, debut);
    strcpy(phrase, buffer);
}


int comparer(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    char phrase[MAX_LEN];
    char motA[100], motB[100];
    char *mots[MAX_WORDS];
    char *token;
    int i = 0;

    // Entrée utilisateur
    printf("Entrez une phrase : ");
    fgets(phrase, MAX_LEN, stdin);
    phrase[strcspn(phrase, "\n")] = 0; // Supprime le \n

    printf("Entrez le mot A à remplacer : ");
    scanf("%s", motA);

    printf("Entrez le mot B de remplacement : ");
    scanf("%s", motB);

    // Remplacement
    remplacer_mot(phrase, motA, motB);

    // Séparation des mots
    token = strtok(phrase, " ");
    while (token != NULL && i < MAX_WORDS) {
        mots[i] = strdup(token); // Allocation dynamique
        i++;
        token = strtok(NULL, " ");
    }

    // Tri alphabétique
    qsort(mots, i, sizeof(char *), comparer);

    // Affichage des mots triés
    printf("\nMots en ordre alphabétique :\n");
    for (int j = 0; j < i; j++) {
        printf("%s\n", mots[j]);
        free(mots[j]); // Libération mémoire
    }

    return 0;
}
