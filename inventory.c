#include <string.h>
#include "inventory.h"
#include "globals.h"

int AddToInventory(const char* itemName, int quantity, int effect) {
    if (!itemName) return 0;
    
    // Check if item already exists
    for (int i = 0; i < inventoryCount; i++) {
        if (strcmp(inventory[i].name, itemName) == 0) {
            inventory[i].quantity += quantity;
            return 1;
        }
    }
    
    // Add new item
    if (inventoryCount < MAX_INVENTORY) {
        strncpy(inventory[inventoryCount].name, itemName, 31);
        inventory[inventoryCount].name[31] = '\0';  // Ensure null termination
        inventory[inventoryCount].quantity = quantity;
        inventory[inventoryCount].effect = effect;
        inventoryCount++;
        return 1;
    }
    return 0;
}

void RemoveFromInventory(const char* itemName, int quantity) {
    for (int i = 0; i < inventoryCount; i++) {
        if (strcmp(inventory[i].name, itemName) == 0) {
            inventory[i].quantity -= quantity;
            if (inventory[i].quantity <= 0) {
                for (int j = i; j < inventoryCount - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                inventoryCount--;
            }
            return;
        }
    }
}

int GetInventoryItemCount(const char* itemName) {
    for (int i = 0; i < inventoryCount; i++) {
        if (strcmp(inventory[i].name, itemName) == 0) {
            return inventory[i].quantity;
        }
    }
    return 0;
}
