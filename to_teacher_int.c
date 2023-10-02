#include <stdio.h>
int now_line_counter = 1;

static int add_minus_parse(void);
static int is_number_or_not(void);
static int char_to_int(void);
static int number(void);
static int OutFactor(void);
static int multiply_divide_parse(void);
static int add_minus_parse(void);
static int return_eval(const char*);
static int read_input(void);
static const char* state;

int main() {
	while (read_input() > 0);
	return 0;
}

static int is_number_or_not(void) {  //確認目前的是否為數字部分
	return *state >= '0' && *state <= '9';
}

static int char_to_int(void) {  //將數字的型態轉為int
	return *state - '0';
}

// 逐步Parser數字，個十百千萬都擺好
static int number(void) {
	int answer = 0;
	
	while (is_number_or_not()) {
		int n = char_to_int();  //將字元轉為字串
		
		answer = answer*10 + n;		
		state++;  
	}
	return answer;
}

// 處理負號、左右括號的問題
static int OutFactor(void) {
	switch (*state) {
		case '+': 
            state++; 
            return  OutFactor();
		case '-': 
            state++; 
            return -OutFactor();
		case '(': 
			state++; // 換下一個，將'('跳過去
			int answer = add_minus_parse();
			state++; // 跳過')'			
			return answer;		
		default: 
            return number();
	}
}

// 當遇到乘除
static int multiply_divide_parse(void) {
	int left = OutFactor();
	
	while (*state == '*' || *state == '/') {
		char op = *state++;
		int right = OutFactor();		
		if (op == '*'){
			left *= right;
        }
		else{
			left /= right;
        }
	}	
	return left;
}

// 遇到加減
static int add_minus_parse(void) {
	int left = multiply_divide_parse();
	
	while (*state == '+' || *state == '-') {
		char op = *state++;
		int right = multiply_divide_parse();
		
		if (op == '+'){
			left += right;
        }
		else{
			left -= right;
        }
	}	
	return left;
}

// 最後回傳成答案
static int return_eval(const char* str) {
	state = str;
	return add_minus_parse();
}

static int read_input(void) {
	char save_arr[100], now_char;
	int input_len = 0;
	printf("Input: ");
	while (now_char = getchar(), now_char != '\n') {  //不斷的讀取整行的字串直到遇到換行才停止
		save_arr[input_len] = now_char;
		
		// 如果遇到空白就直接跳過
		if (now_char != ' '){ input_len++; }
	}
	save_arr[input_len] = 0;
	if (input_len > 0){
		printf("Answer%d: => %d\n", now_line_counter, return_eval(save_arr));
        now_line_counter++;
    }
	return input_len;  //如果都沒有讀到東西那main的while迴圈就會停止
}