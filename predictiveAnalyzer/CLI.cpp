#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define DEFAULT_BUF_SIZE 256
#define DEFAULT_WD_LEN 32

typedef enum { ET_UNKNOWN, ET_IO, ET_MEM, ET_PARSE }ErrorType;
typedef char(*Words)[DEFAULT_WD_LEN];

void RepportError(ErrorType et, const char * fmt, ...)
{
    char buffer[DEFAULT_BUF_SIZE];
    // memset(buffer, 0, DEFAULT_BUF_SIZE);
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, DEFAULT_BUF_SIZE, fmt, ap);
    va_end(ap);
    if (et == ET_IO || ET_MEM || ET_UNKNOWN)
        fprintf(stderr, buffer);
    else
        fprintf(stderr, "Error at %dL in function \"%s()\"\n%s", __LINE__, __func__, buffer);
    exit(1);
}
#define IO_ERROR(...)\
    RepportError(ET_IO, __VA_ARGS__)
#define MEM_ERROR(...)\
    RepportError(ET_MEM, __VA_ARGS__)
#define PARSE_ERROR(...)\
    RepportError(ET_PARSE, __VA_ARGS__)
#define OTHER_ERROR(...)\
    RepportError(ET_UNKNOWN, __VA_ARGS__)

struct _G {
    Words V_n, V_t, P;
    char S[DEFAULT_WD_LEN];
    int n_num, t_num, p_num;
}G;

void InitG()
{
    printf("非终结符的个数:");
    scanf("%d", &G.n_num);
    if (!(G.n_num > 0 && G.n_num < DEFAULT_WD_LEN)) IO_ERROR("Illegal parameter.\n");
    G.V_n = (char(*)[DEFAULT_WD_LEN])calloc(sizeof(char[DEFAULT_WD_LEN]), G.n_num);
    printf("输入非终结符（各符号以回车隔开）:");
    for (int i = 0; i < G.n_num; i++)
        scanf("%s", G.V_n[i]);
    printf("终结符的个数:");
    scanf("%d", &G.t_num);
    if (!(G.n_num > 0 && G.n_num < DEFAULT_WD_LEN)) IO_ERROR("Illegal parameter.\n");
    G.V_t = (char(*)[DEFAULT_WD_LEN])calloc(sizeof(char[DEFAULT_WD_LEN]), G.t_num);
    printf("输入终结符（各符号以回车隔开）:");
    for (int i = 0; i < G.t_num; i++)
        scanf("%s", G.V_t[i]);
    printf("产生式的个数:");
    scanf("%d", &G.p_num);
    if (!(G.n_num > 0 && G.n_num < DEFAULT_WD_LEN)) IO_ERROR("Illegal parameter.\n");
    G.P = (char(*)[DEFAULT_WD_LEN])calloc(sizeof(char[DEFAULT_WD_LEN]), G.p_num);
    printf("输入产生式（例：E->TE'）:");
    for (int i = 0; i < G.p_num; i++)
        scanf("%s", G.P[i]);
    printf("输入起始推导符号:");
    scanf("%s", &G.S);
}

int main(int argc, char * argv[])
{
    if (argc != 2)
        IO_ERROR("Illegal parameter.\n");

    InitG();

    getchar();
    return 0;
}