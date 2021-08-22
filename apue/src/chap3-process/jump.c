//
// Created by wch on 2020/11/26.
//
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

static jmp_buf save;
static void d(void)
{
    printf("%s(): Begin.\n", __FUNCTION__);
    printf("%s: Jump now.\n", __FUNCTION__);
    longjmp(save,6);
    printf("%s(): End.\n", __FUNCTION__);
}

static void c(void)
{
    printf("%s(): Begin.\n", __FUNCTION__);
    printf("%s():Call d(). \n", __FUNCTION__);
    d();
    printf("%s(): d() return . \n", __FUNCTION__);
    printf("%s(): End.\n", __FUNCTION__);
}

static void b(void)
{
    printf("%s(): Begin.\n", __FUNCTION__);
    printf("%s():Call c(). \n", __FUNCTION__);
    c();
    printf("%s(): c() return . \n", __FUNCTION__);
    printf("%s(): End.\n", __FUNCTION__);
}

static void a(void)
{
    int ret;
    printf("%s(): Begin.\n", __FUNCTION__);
    ret = setjmp(save);
    if (ret == 0) { // return normal
        printf("%s():Call b(). \n", __FUNCTION__);
        b();
        printf("%s(): b() return . \n", __FUNCTION__);
    } else { // jump back
        printf("%s(): Jumped back here with code %d\n", __FUNCTION__, ret);
    }
    printf("%s(): End.\n", __FUNCTION__);
}

int main(int argc, char **argv)
{
    printf("%s(): Begin.\n", __FUNCTION__);
    printf("%s():Call a(). \n", __FUNCTION__);
    a();
    printf("%s(): a() return . \n", __FUNCTION__);
    printf("%s(): End.\n", __FUNCTION__);
}

