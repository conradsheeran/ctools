#include "vector.h"

#include <stdio.h>

int main(void) {
  Vector *vector = CONRAD_Create_Vector(5);
  CONRAD_Vector_Push(vector, 20);
  CONRAD_Vector_Push(vector, 30);
  CONRAD_Vector_Push(vector, 40);
  CONRAD_Vector_Push(vector, 50);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);
  CONRAD_Vector_Push(vector, 60);

  CONRAD_Vector_Delete_By_Index(vector, 1);

  const uint8_t Index_40 = CONRAD_Vector_QUERY_By_Content_Common(vector, 40);

  printf("40: %u\n", Index_40);

  for (uint8_t i = 0; i < vector->size; i++) {
    printf("%d\n", vector->data[i]);
  }
  CONRAD_Vector_Free(vector);
}