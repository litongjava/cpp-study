#include <stdio.h>

int main(int argc, char const *argv[]){
    int sum=0;
    for(int i=1;i<101;i++){
        sum+=i;
    }
    printf("%d \n",sum);
    return 0;
}
