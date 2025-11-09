#include "inventario.h"
#include <stdlib.h>

Inventario *CreateInventory() {
    Inventario *inv = malloc(sizeof(Inventario));
    inv -> moedas = 0;
    inv -> upgradeAtk = 0;
    inv -> upgradeHp = 0;
    return inv;
}

void Liberar_Inventario(Inventario *inv) {
    // Se houver texturas:
    // UnloadTexture(inv->algumaTextura);
    free(inv);
}

