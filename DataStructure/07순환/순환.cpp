#include <stdio.h>
#include <string.h>
#include <time.h>

static int freq[11];
long fibo(int n) {
	freq[n]++; // 각 배열의 n 번째 항에 freq[n] = fre[n]+1을 해줌 why? 호출되었을 때 그 인덱스에 맞는 피보나치가 몇번 호출되었는지 카운드 해주는 것임.
	if (n <= 1) return n;
	return fibo(n - 1) + fibo(n - 2);//여기서 각각 트리 형식으로 찢어지는 것임
}
static void initFreq() { //일종의 생성자 같은 느낌으로, 각 인덱스에 피보나치 순환 횟수를 카운트 해줄건데 시작하자마자 모든 인덱스를 0으로 초기화해줌.
	int i;
	for (i = 0; i <= 10; i++)
		freq[i] = 0;
}
static void printFreq() {
	int i;
	for (i = 10; i >= 0; i--)
		printf("Fibo(%2d) = %2d\n", i, freq[i]);//freq배열을 뒤에 인덱스 값 부터 순서대로 출력
}
long fiboIter(int n) {//예외 처리 함수
	long f0 = 0, f1 = 1, f;
	int i;
	if (n == 0) return f0;
	if (n == 1) return f1;
	for (i = 2; i <= n; i++) {
		f = f0 + f1;
		f0 = f1;
		f1 = f;
	}
	return f;
}





void reverse(char* str, int left, int right) {//함수 reverse에서 매개변수str left right를 받음. 즉 배열과 그 배열의 길이를 받음.

	char tmp;
	if (left < right) {
		tmp = str[right];//제일 오른쪽 글자를 tmp에 저장.
		str[right] = str[left];//제일 왼쪽의 값을 오른쪽 끝으로 보냄.
		str[left] = tmp;//처음에 저장해뒀던 제일 오른쪽 문자를 왼쪽 끝으로 보냄.
		reverse(str, left + 1, right - 1);//이 방식을 계속 순환.
	}
}



int main()
{
	int		i,j;
	long	maxfibo;
	char	str[80] = "Soongsil University!";

	printf("각각의 순환 횟수: fibo(10)\n");
	initFreq();//배열의 각각 인덱스에 0을 초기화 해줌.
	fibo(10);
	printFreq();


	printf(" 초기값 %s\n", str);   
	reverse(str, 0, strlen(str)-1);
	printf(" 변화후%s \n", str);


 
}
