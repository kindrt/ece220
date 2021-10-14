int factorial(int n)  {
    int fn;
    if (n > 1) 
        fn = n * factorial(n-1);
    else 
        fn = 1;
    return fn;
}
