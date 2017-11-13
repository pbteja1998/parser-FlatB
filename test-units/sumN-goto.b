declblock{
	int data[100];
	int i, sum;
}

codeblock{
	i = 0;

L1:	data[i] = i ;
	i = i + 1;
	print i;
	goto L2;
	println "here";

	sum = 0;
	sum = sum + data[i-2];
	i = i + 1;

L2:	goto L1 if i > 5;
	println "here22";
	i = i + 1;
	a = 0;

	for i = 1 , 2 {
		a = a + 1;
	}
}

