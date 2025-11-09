#include "save.h"
#include <stdio.h>

void Progesso_salvo(Inventario *inv) {
    FILE *f = fopen("assets/save.txt", "w");//falta colocar
    if (f) {
        fprintf(f, "%d %d %d\n", inv->moedas, inv->upgradeAtk, inv->upgradeHp);
        fclose(f);
    }
}

void Load_Progress(Inventario*inv) {
    FILE *f = fopen("assets/save.txt", "r"); //falta colocar
    if (f) {
        fscanf(f, "%d %d %d", &inv->moedas, &inv->upgradeAtk, &inv->upgradeHp);
        fclose(f);
    }
}
