#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct {
    int moedas;
    int upgradeAtk;
    int upgradeHp;
} Inventario;

Inventario *CreateInventory();

#endif
