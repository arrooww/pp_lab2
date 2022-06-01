#include <stdio.h>
#include <math.h>
#include <pthread.h>

struct data
{
    float a;
    float b;
    int n;
    float h;
};
struct func
{
    float f1;
    float f2;
    float f3;
};
struct data arg;
struct func res;

pthread_barrier_t barrier;

void *f1(void *arg)
{
    struct data *p = (struct data *) arg;

    for (int i = 0; i <= p->n; i++)
    {
        float x;
        x = p->a + (float)i*p->h;
        res.f1 = cos(x)*cos(x) + sin(x);
        pthread_barrier_wait(&barrier);
    }
    return 0;
}

void *f2(void *arg)
{
    struct data *p = (struct data *) arg;

    for (int i = 0; i <= p->n; i++)
    {
        float x;
        x = p->a + ((float)i*p->h);
        res.f2 = (sin(x)*sin(x)) * (1 + cos(x));
        pthread_barrier_wait(&barrier);
    }
    return 0;
}

void *f3(void *arg)
{
    struct data *p = (struct data *) arg;

    for (int i = 0; i <= p->n; i++)
    {
        float x;
        x = p->a + (float)i*p->h;
        res.f3 = sin(x) * (1 + (cos(x)*cos(x)));
        pthread_barrier_wait(&barrier);
    }
    return 0;
}


int main()
{
    arg.a = -M_PI;//-pi
    arg.b = M_PI;//pi
    arg.n = 8;
    arg.h = (arg.b - arg.a) / (float)arg.n;

    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;

    pthread_barrier_init(&barrier, NULL, 4);

    pthread_create(&pthread1, NULL, &f1, &arg);
    pthread_create(&pthread2, NULL, &f2, &arg);
    pthread_create(&pthread3, NULL, &f3, &arg);


    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("|\t   X\t\t|   cos(x)^2 + sin(x)\t| sin(x)^2 * (1 + cos(x))| sin(x) * (1 + cos(x)^2 |\n");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    for (int i = 0; i <= 8; i++)
    {
        float x = arg.a + ((float)i * arg.h);
        printf("|\t %f\t|", x);
        printf("\t %f\t|", res.f1);
        printf("\t %f\t |", res.f2);
        printf("\t %f\t  |", res.f3);
        printf("\n");
        pthread_barrier_wait(&barrier);
    }
    printf("|-------------------------------------------------------------------------------------------------|\n");

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    pthread_barrier_destroy(&barrier);
    return 0;
}
