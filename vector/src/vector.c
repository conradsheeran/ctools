#include "vector.h"

#include <stdint.h>
#include <stdlib.h>

#define SUCCESS 0
#define MEMORY_ERROR 1
#define INDEX_OUT_OF_BOUNDS 2
#define PARAMETER_ERROR 3
#define NOT_FOUND (-1)

/**
 * @author Yang He
 * @brief 创建并初始化一个动态数组
 * @param capacity 初始容量，必须大于 0
 * @return 成功返回初始化后的 Vector 指针；内存分配失败返回 NULL
 * @note 若 capacity 为 0，初始容量会自动设置为 1
 */
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

/**
 * @author Yang He
 * @brief 向 Vector 尾部追加元素，自动处理扩容
 * @param vector 目标 Vector 指针，必须非空且已初始化
 * @param value 待追加的元素值
 * @return SUCCESS(0) 成功；MEMORY_ERROR(1) 内存分配失败
 * @note 容量不足时自动扩容为原容量的 2 倍（初始为 0 时扩容为 1）
 */
uint8_t CONRAD_Vector_Push(Vector *vector, const uint8_t value) {
  if (vector == NULL || vector->data == NULL)
    return MEMORY_ERROR;

  if (vector->size == vector->capacity) {
    uint8_t new_capacity = vector->capacity * 2;
    if (vector->capacity == 0)
      new_capacity = 1;

    int16_t *new_data = realloc(vector->data, new_capacity * sizeof(int16_t));
    if (new_data == NULL)
      return MEMORY_ERROR;

    vector->data = new_data;
    vector->capacity = new_capacity;
  }

  vector->data[vector->size] = value;
  vector->size++;
  return SUCCESS;
}

/**
 * @author Yang He
 * @brief 删除指定索引位置的元素，自动处理缩容
 * @param vector 目标 Vector 指针，必须非空且已初始化
 * @param index 待删除元素的索引，必须小于当前size
 * @return SUCCESS(0) 成功；MEMORY_ERROR(1) 内存错误；INDEX_OUT_OF_BOUNDS(2)
 * 索引越界
 * @note 删除后若容量大于等于当前size的两倍，自动缩容为原容量的一半
 */
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
    int16_t *new_data = realloc(vector->data, new_capacity * sizeof(int16_t));

    vector->data = new_data;
    vector->capacity = new_capacity;
  }

  vector->size--;
  return SUCCESS;
}

/**
 * @author Yang He
 * @brief 线性查找指定内容的元素（无序数组适用）
 * @param vector 目标 Vector 指针，必须非空且已初始化
 * @param content 待查找的元素值
 * @return 找到返回元素索引(0~255)，未找到返回 NOT_FOUND(-1)
 * @warning 函数不检查 vector 指针有效性，需调用者确保
 */
int16_t CONRAD_Vector_QUERY_By_Content_Common(const Vector *vector,
                                              const uint8_t content) {
  for (uint8_t index = 0; index < vector->size; index++) {
    if (vector->data[index] == content)
      return index;
  }

  return NOT_FOUND;
}

/**
 * @author Yang He
 * @brief 二分查找指定内容的元素（有序数组适用）
 * @param vector 目标 Vector 指针，必须非空且已初始化，且元素按升序排列
 * @param content 待查找的元素值
 * @return 找到返回首次出现的索引(0~255)，未找到返回 NOT_FOUND(-1)
 * @note 若存在重复元素，返回第一个匹配项的索引
 */
int16_t CONRAD_Vector_QUERY_By_Content_Ordered(const Vector *vector,
                                               const uint8_t content) {
  uint8_t left = 0, right = vector->size - 1;
  uint8_t result = -1;
  while (left <= right) {
    uint8_t mid = left + (right - left) / 2;
    if (vector->data[mid] == content) {
      result = mid;
      right = mid - 1; // 继续向左查找更早出现的位置
    } else if (vector->data[mid] < content) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return result;
}

/**
 * @author Yang He
 * @brief 截取原 Vector 的子数组（从 start 到 end，不包含尾端）
 * @param vector 源 Vector 指针，必须非空且已初始化
 * @param start 起始索引，必须小于等于 end 且不越界
 * @param end 结束索引，必须小于 vector->size
 * @return 成功返回包含子数组的新 Vector 指针；参数错误或内存失败返回 NULL
 * @warning 返回的新 Vector 需调用 CONRAD_Vector_Free 释放
 */
Vector *CONRAD_Vector_Cut(Vector *vector, const uint8_t start,
                          const uint8_t end) {
  if (vector == NULL || vector->data == NULL)
    return NULL;
  if (start >= vector->size || end >= vector->size || start > end)
    return NULL;

  Vector *cut_vector = CONRAD_Create_Vector(end - start + 1);

  for (uint8_t i = start; i < end; i++) {
    CONRAD_Vector_Push(cut_vector, vector->data[i]);
  }

  return cut_vector;
}

/**
 * @author Yang He
 * @brief 释放 Vector 及其内部数据的内存
 * @param vector 待释放的 Vector 指针
 * @return 始终返回 SUCCESS(0)
 * @warning 传入指针后，原指针会失效，不可再次使用
 */
uint8_t CONRAD_Vector_Free(Vector *vector) {
  free(vector->data);
  free(vector);
  return SUCCESS;
}
