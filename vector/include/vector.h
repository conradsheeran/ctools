#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

typedef struct {
  uint8_t *data;
  uint8_t size;
  uint8_t capacity;
} Vector;

Vector *CONRAD_Create_Vector(uint8_t capacity);
uint8_t CONRAD_Vector_Push(Vector *vector, uint8_t value);
uint8_t CONRAD_Vector_Delete_By_Index(Vector *vector, uint8_t index);
int16_t CONRAD_Vector_QUERY_By_Content_Common(const Vector *vector,
                                              const uint8_t content);
int16_t CONRAD_Vector_QUERY_By_Content_Ordered(const Vector *vector,
                                               const uint8_t content);
Vector *CONRAD_Vector_Cut(Vector *vector, const uint8_t start,
                          const uint8_t end);
uint8_t CONRAD_Vector_Free(Vector *vector);

#endif //VECTOR_H
