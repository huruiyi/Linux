#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

//自定义alarm函数
unsigned int myalarm( unsigned int __seconds ) {
    struct itimerval it = {{0, 0}, {0, 0}}, oldit;
    it.it_value.tv_sec = __seconds;        //设置下次闹钟时间
    setitimer( ITIMER_REAL, &it, &oldit ); //设置闹钟，同时取旧的闹钟
    return oldit.it_value.tv_sec + (int) ( (float) oldit.it_value.tv_usec / 1000000 + 0.5 );
}

int main() {
    myalarm( 6 );
    sleep( 2 );
    int ret = myalarm( 5 );
    printf( "ret == %d\n", ret );
    while ( 1 ) {
        printf( "who can kill me?\n" );
        sleep( 1 );
    }
    return 0;
}
