int isPrime(int n){
    int isPrime = 1;
    for(int i=2;i<n;i++){
        int x = n%i;
        if(x == 0){
            isPrime = 0;
            break;
        }
    }
    return isPrime;
}