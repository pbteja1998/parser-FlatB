declblock{
    int n, temp;
    int A[100], i, j;
}
codeblock{  
    print "size of array";
    read n;

    print "Read array variables";
    for i = 0, n-1 {
        read A[i];
    }

    for i = 0, n-2 {
        for j = 0, n-i-2 {        
            if A[j] > A[j+1] {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
    print "sorted array";
    for i = 0, n-1 {
        print A[i];        
    }
}