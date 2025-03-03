# CTools

## 一、简介

本项目使用 C 语言编写，提供了多个实用函数，并配备有详细的注释说明

## 二、使用说明

### 1. Vector 库

- 函数说明：

```c
typedef struct {
  uint8_t *data;
  uint8_t size;
  uint8_t capacity;
} Vector;

Vector *CONRAD_Create_Vector(uint8_t capacity); // 创建 Vector 结构体数组
uint8_t CONRAD_Vector_Push(Vector *vector, uint8_t value); // 在数组末尾增加一个值
uint8_t CONRAD_Vector_Delete_By_Index(Vector *vector, uint8_t index); // 通过目录删除值
int16_t CONRAD_Vector_QUERY_By_Content_Common(const Vector *vector, const uint8_t content); // 通过值查询所在的数组目录（通用）
int16_t CONRAD_Vector_QUERY_By_Content_Ordered(const Vector *vector, const uint8_t content); // 通过值查询所在的数组目录（有序数组，效率更高）
Vector *CONRAD_Vector_Cut(Vector *vector, const uint8_t start, const uint8_t end); // 剪切数组
uint8_t CONRAD_Vector_Free(Vector *vector); // 释放 Vector 数组内存
```

## 三、开发计划

- [ ] 数组操作相关函数
