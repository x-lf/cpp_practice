#include <stdio.h>
#include <string.h>

#define MAX_COL 100
#define MAX_ROW 100

typedef struct
{
    int col_num;
    int row_num;
    double data[MAX_COL * MAX_ROW + 5];
    void (*const print)(struct matrix *);
    void (*const transpose)(struct matrix *);
} matrix;

void print_matrix(matrix *M)
{
    for (int i = 0; i < M->row_num; ++i)
    {
        for (int j = 0; j < M->col_num; ++j)
        {
            printf("%6.2f ", M->data[i * M->col_num + j]);
        }
        printf("\n");
    }
}

void transpose(matrix *M)
{
    double temp[MAX_COL * MAX_ROW + 5];

    // 复制数据到临时数组
    for (int i = 0; i < M->row_num; ++i)
    {
        for (int j = 0; j < M->col_num; ++j)
        {
            temp[j * M->row_num + i] = M->data[i * M->col_num + j];
        }
    }

    // 交换行数和列数
    int temp_num = M->row_num;
    M->row_num = M->col_num;
    M->col_num = temp_num;

    // 将临时数组的数据复制回原来的数据数组
    memcpy(M->data, temp, sizeof(double) * (MAX_COL * MAX_ROW + 5));
}

matrix matrix_init(int col_num, int row_num)
{
    if (col_num > MAX_COL)
    {
        fprintf(stderr, "Error: col_num exceeds MAX_COL\n");
        col_num = MAX_COL;
    }
    if (row_num > MAX_ROW)
    {
        fprintf(stderr, "Error: row_num exceeds MAX_ROW\n");
        row_num = MAX_ROW;
    }

    matrix M;
    M.col_num = col_num;
    M.row_num = row_num;
    memset(M.data, 0, sizeof(M.data)); // 初始化数据为0
    M.print = print_matrix;
    M.transpose = transpose;
    return M;
}

void run_tests() {
    printf("Running tests...\n");

    // Test 1: Normal initialization
    printf("Test 1: Normal initialization (3x3 matrix)\n");
    matrix M1 = matrix_init(3, 3);
    for (int i = 0; i < M1.row_num; ++i) {
        for (int j = 0; j < M1.col_num; ++j) {
            M1.data[i * M1.col_num + j] = i * M1.col_num + j + 1;  // 示例数据
        }
    }
    M1.print(&M1);
    M1.transpose(&M1);
    printf("Transposed matrix:\n");
    M1.print(&M1);
    printf("\n");

    // Test 2: Exceeding column limit
    printf("Test 2: Exceeding column limit (150 columns)\n");
    matrix M2 = matrix_init(150, 5);  // 应该被限制为 MAX_COL
    for (int i = 0; i < M2.row_num; ++i) {
        for (int j = 0; j < M2.col_num; ++j) {
            M2.data[i * M2.col_num + j] = i * M2.col_num + j + 1;  // 示例数据
        }
    }
    M2.print(&M2);
    M2.transpose(&M2);
    printf("Transposed matrix:\n");
    M2.print(&M2);
    printf("\n");

    // Test 3: Exceeding row limit
    printf("Test 3: Exceeding row limit (150 rows)\n");
    matrix M3 = matrix_init(5, 150);  // 应该被限制为 MAX_ROW
    for (int i = 0; i < M3.row_num; ++i) {
        for (int j = 0; j < M3.col_num; ++j) {
            M3.data[i * M3.col_num + j] = i * M3.col_num + j + 1;  // 示例数据
        }
    }
    M3.print(&M3);
    M3.transpose(&M3);
    printf("Transposed matrix:\n");
    M3.print(&M3);
    printf("\n");

    // Test 4: Maximum size
    printf("Test 4: Maximum size initialization (100x100 matrix)\n");
    matrix M4 = matrix_init(MAX_COL, MAX_ROW);
    for (int i = 0; i < M4.row_num; ++i) {
        for (int j = 0; j < M4.col_num; ++j) {
            M4.data[i * M4.col_num + j] = i * M4.col_num + j + 1;  // 示例数据
        }
    }
    M4.print(&M4);
    M4.transpose(&M4);
    printf("Transposed matrix:\n");
    M4.print(&M4);
    printf("\n");

    // Test 5: Edge case with zero dimensions
    printf("Test 5: Edge case with zero dimensions (0x0 matrix)\n");
    matrix M5 = matrix_init(0, 0);
    M5.print(&M5);  // 应该什么也不输出
    printf("\n");

    // Free allocated matrices if needed (for dynamic allocation, not used in this static example)
}

int main() {
  //  run_tests();
    return 0;
}