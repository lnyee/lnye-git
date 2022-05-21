#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <SDL2/SDL.h>
#include"function.h"

void test_init(void){
    int a = init('a');
    int b = init(0);
    int c = init(1);
    CU_ASSERT_EQUAL(a, -1);
    CU_ASSERT_EQUAL(b, -1);
    CU_ASSERT_EQUAL(c, 0);
    destroy();
}

void test_fileinit(void){
    FILE *file = fopen("test.txt", "r");
    FILE *wrongfile = fopen("a.txt", "r");
    int *m[3], *n[3];
    int a[3][3], b[3][3];
    for(int i=0; i<3; i++){
        m[i] = a[i];
        n[i] = b[i];
    }
    CU_ASSERT_EQUAL(fileinit(file, m, n, 3, 3), 0);
    CU_ASSERT_EQUAL(a[0][0], 1);
    CU_ASSERT_EQUAL(a[0][1], 0);
    CU_ASSERT_EQUAL(a[0][2], 1);
    CU_ASSERT_EQUAL(a[1][0], 0);
    CU_ASSERT_EQUAL(a[1][1], 1);
    CU_ASSERT_EQUAL(a[1][2], 0);
    CU_ASSERT_EQUAL(a[2][0], 1);
    CU_ASSERT_EQUAL(a[2][1], 0);
    CU_ASSERT_EQUAL(a[2][2], 1);
    CU_ASSERT_EQUAL(fileinit(wrongfile, m, n, 3, 3), -1);
}

void test_update(void){
    int *m[5], *n[5];
    int a[5][5], b[5][5];
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            a[i][j] = 0;
        }
    }
    a[1][2] = 1;
    a[2][0] = 1;
    a[2][2] = 1;
    a[3][1] = 1;
    a[3][2] = 1;
    for(int i=0; i<5; i++){
        m[i] = a[i];
        n[i] = b[i];
    }
    update(m, n, 5, 5);
    CU_ASSERT_EQUAL(b[1][1], 1);
    CU_ASSERT_EQUAL(b[2][2], 1);
    CU_ASSERT_EQUAL(b[2][3], 1);
    CU_ASSERT_EQUAL(b[3][1], 1);
    CU_ASSERT_EQUAL(b[3][2], 1);
}

void test_gameover(void){
    int *m[3], *n[3], *p[3], *q[3];
    int a[3][3] = {{0,1,0},{0,1,0},{0,1,0}};
    int b[3][3] = {{0,0,0},{1,1,1},{0,0,0}};
    int c[3][3] = {{0,0,0},{0,1,1},{0,1,1}};
    int d[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    for(int i=0; i<3; i++){
        m[i] = a[i];
        n[i] = b[i];
        p[i] = c[i];
        q[i] = d[i];
    }
    CU_ASSERT_EQUAL(gameover(p, p, q, 3, 3), 1);
    CU_ASSERT_EQUAL(gameover(m, n, q, 3, 3), 2);
    CU_ASSERT_EQUAL(gameover(m, p, q, 3, 3), 0);
}

static int initsuite(void)
{
    return 0;
}

static int cleansuite(void)
{
    return 0;
}

int Run_test(void)
{
    CU_pSuite pSuite = NULL;
    
    if (CU_initialize_registry() != CUE_SUCCESS) {
        printf("Failed to initialize!\n");
        return -1;
    }
    
    pSuite = CU_add_suite("Suite", initsuite, cleansuite);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "test_init", test_init) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "test_fileinit", test_fileinit) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "test_update", test_update) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
   
    if (CU_add_test(pSuite, "test_gameover", test_gameover) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

int main()
{
    Run_test();
    return 0;
}
