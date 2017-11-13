declblock{
	int a, B[11], D[11], e;
}

codeblock{
	a = 0;
	for i = 1, 10, 3 {
		B[i] = 0;
		B[i-1] = 1;
	}

L1:	while false {
		a = a + 1;
	}

	if a >= 0{
		a = a + 1;
	}
	else{
		B[0] = B[0] + 1;
	}

	print "Hi, this is test program \n", a, B[0];

	println "This is a new line\n";

	read e;
}
