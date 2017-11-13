declblock{
	int flag, n;
}

codeblock{
	read n;
	for i = 2, n {
		flag = 0;
		for j = 2, i-1 {					
			if i%j == 0 {
				flag = 1;
			} 
		}
		if flag == 0 {
			print i;
		}
	}
}


