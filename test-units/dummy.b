declblock{
	int a, B[100];
	int D[50], e;
}

codeblock{
	a = 0;
	for i = 1, 10, 3 {
		B[i] = D[i];		
	}

L1:	while a > 0 {
		a = a + 1;
	}

	goto L1 if a > 0;

	if a >= 0{
		a = a + 1;
	}
	else{
		B[0] = B[0] + 1;
	}

	print "Hi, this is test program", a, A[0];

	println "This is a new line";

	read e;

}
