#include <stdio.h>
int now_line_counter = 1;

static double add_minus_parse(void);
static int is_number_or_not(void);
static int char_to_int(void);
static double number(void);
static double OutFactor(void);
static double multiply_divide_parse(void);
static double add_minus_parse(void);
static double return_eval(const char*);
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
static double number(void) {
	double answer = 0;
	
	while (is_number_or_not()) {
		int n = char_to_int();  //將字元轉為字串
		
		answer = answer*10 + n;		
		state++;  
	}	
	if (*state == '.') {  //有浮點數的部分
		state++;
		double dec = 0.1;
		
		while (is_number_or_not()) {
			int n = char_to_int();
			
			answer += n * dec;
			dec *= 0.1;
			
			++state;
		}
	}
	return answer;
}

// 處理負號、左右括號的問題
static double OutFactor(void) {
	switch (*state) {
		case '+': 
            state++; 
            return  OutFactor();
		case '-': 
            state++; 
            return -OutFactor();
		case '(': 
			state++; // 換下一個，將'('跳過去
			double answer = add_minus_parse();
			state++; // 跳過')'			
			return answer;		
		default: 
            return number();
	}
}

// 當遇到乘除
static double multiply_divide_parse(void) {
	double left = OutFactor();
	
	while (*state == '*' || *state == '/') {
		char op = *state++;
		double right = OutFactor();		
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
static double add_minus_parse(void) {
	double left = multiply_divide_parse();
	
	while (*state == '+' || *state == '-') {
		char op = *state++;
		double right = multiply_divide_parse();
		
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
static double return_eval(const char* str) {
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
		printf("Answer%d: => %.0f\n", now_line_counter, return_eval(save_arr));
        now_line_counter++;
    }
	return input_len;  //如果都沒有讀到東西那main的while迴圈就會停止
}