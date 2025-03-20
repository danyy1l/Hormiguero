/**
 * @brief It defines the inventory module interface
 *
 * @file inventory.h
 * @author Álvaro Rodríguez
 * @version 0
 * @date 20-03-2025
 * @copyright GNU Public License
 */

 #ifndef INVENTORY_H
 #define INVENTORY_H
 
 #define MAX_INVENTORY_OBJS 5

 #include "object.h"
 #include "types.h"
 #include "set.h"
 
 typedef struct _Inventory Inventory;

 Inventory *inventory_create();
 Status inventory_destroy(Inventory * inventory);
 Bool inventory_is_empty(Inventory * inventory);
 Bool inventory_is_full(Inventory * inventory);
 Status inventory_add_object(Inventory* inventory, Id id);
 Status inventory_del_object(Inventory* inventory, Id id);
 Bool inventory_find_object(Inventory* inventory,Id id);
 Status inventory_set_max_objects(Inventory *inventory,int n);
 int inventory_get_max_objects(Inventory *inventory);
 Status inventory_print(Inventory* inventory);


 #endif