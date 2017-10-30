declblock{
	int data[100] ;
	int i, sum ;
}

codeblock{
	i = 0;
	sum = 1;
	data[50] = 100;
	data[51] = data[50] + sum;
	print "Sum value: ", sum ;

	if i == 1 {
		data[i] = i ; 
	} else {
		data[i] = i - 1;
	}
	
	for i = 1, 100 {
		data[i] = i ; 
	}

	for i = sum, data[i], data[100] {
		data[i] = i ; 
		sum = i + data[i];
	}
}

