#include "vector.h"

#include <stdint.h>
#include <stdlib.h>

#define SUCCESS 0
#define MEMORY_ERROR 1
#define INDEX_OUT_OF_BOUNDS 2
#define NOT_FIND (-1)

Vector *CONRAD_Create_Vector(const uint8_t capacity) {
  Vector *vector = malloc(sizeof(Vector));
  if (vector == NULL)
    return NULL;

  vector->data = malloc(capacity * sizeof(uint8_t));
  if (vector->data == NULL) {
    free(vector);
    return NULL;
  }

  vector->size = 0;
  vector->capacity = capacity;

  return vector;
}

uint8_t CONRAD_Vector_Push(Vector *vector, const uint8_t value) {
  if (vector == NULL || vector->data == NULL)
    return MEMORY_ERROR;

  if (vector->size == vector->capacity) {
    uint8_t new_capacity = vector->capacity * 2;
    if (vector->capacity == 0)
      new_capacity = 1;

    uint8_t *new_data = realloc(vector->data, new_capacity * sizeof(uint8_t));
    if (new_data == NULL)
      return MEMORY_ERROR;

    vector->data = new_data;
    vector->capacity = new_capacity;
  }

  vector->data[vector->size] = value;
  vector->size++;
  return SUCCESS;
}

uint8_t CONRAD_Vector_Delete_By_Index(Vector *vector, const uint8_t index) {
  if (vector == NULL || vector->data == NULL)
    return MEMORY_ERROR;
  if (index >= vector->size)
    return INDEX_OUT_OF_BOUNDS;

  for (uint8_t i = index; i < vector->size - 1; i++) {
    vector->data[i] = vector->data[i + 1];
  }

  if (vector->capacity / 2 >= vector->size) {
    const uint8_t new_capacity = vector->capacity / 2;
    uint8_t *new_data = realloc(vector->data, new_capacity * sizeof(uint8_t));

    vector->data = new_data;
    vector->capacity = new_capacity;
  }

  vector->size--;
  return SUCCESS;
}

int16_t CONRAD_Vector_QUERY_By_Content_Common(const Vector *vector,
                                              const uint8_t content) {
  for (uint8_t index = 0; index < vector->size; index++) {
    if (vector->data[index] == content)
      return index;
  }

  return NOT_FIND;
}

int16_t CONRAD_Vector_QUERY_By_Content_Ordered(const Vector *vector,
                                               const uint8_t content) {
  uint8_t left = 0, right = vector->size - 1;
  uint8_t result = -1;
  while (left <= right) {
    uint8_t mid = left + (right - left) / 2;
    if (vector->data[mid] == content) {
      result = mid;
      right = mid - 1;
    } else if (vector->data[mid] < content) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return result;
}

uint8_t CONRAD_Vector_Free(Vector *vector) {
  free(vector->data);
  free(vector);
  return SUCCESS;
}
