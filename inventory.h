#ifndef INVENTORY_H
#define INVENTORY_H

int AddToInventory(const char* itemName, int quantity, int effect);
void RemoveFromInventory(const char* itemName, int quantity);
int GetInventoryItemCount(const char* itemName);

#endif // INVENTORY_H
