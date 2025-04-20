#include <iostream>
using namespace std;

#define DIRECTION_BITS_OFFSET 0x0
#define OFFSET_BITS_OFFSET 0x1
#define INSTRUMENT_BITS_OFFSET 0x3

#define DIRECTION_BITS_MASK 0x1
#define OFFSET_BITS_MASK 0x3
#define INSTRUMENT_BITS_MASK 0x1FFFFFFF
#define INSTRUMENT_BOUNDARY 0xFFFFF

int get_Direction(int& value) {
	return (value >> DIRECTION_BITS_OFFSET) & DIRECTION_BITS_MASK;
}

int get_Offset(int& value) {
	return (value >> OFFSET_BITS_OFFSET) & OFFSET_BITS_MASK;
}

int get_Instrument(int& value) {
	return (value >> INSTRUMENT_BITS_OFFSET) & INSTRUMENT_BITS_MASK;
}
// new_direction 为0或1时，才设置value，返回0；否则返回-1
int set_Direction(int& value, int new_direction) {
	//使用位运算判断value是0还是1
	if (new_direction & ~DIRECTION_BITS_MASK) {
		return -1;
	}
	value &= ~(DIRECTION_BITS_MASK << DIRECTION_BITS_OFFSET);
	value |= ((new_direction << DIRECTION_BITS_OFFSET) &
	          (DIRECTION_BITS_MASK << DIRECTION_BITS_OFFSET));
	return 0;
}

// new_offset为0~3时，才设置value，返回0；否则返回-1
int set_Offset(int& value, int new_offset) {
	if (new_offset & ~OFFSET_BITS_MASK) {
		return -1;
	}
	value &= ~(OFFSET_BITS_MASK << OFFSET_BITS_OFFSET);
	value |= ((new_offset & OFFSET_BITS_MASK) << OFFSET_BITS_OFFSET);
	return 0;
}

// new_inst为0~1000000时才设置value，返回0；否则返回-1
int set_Instrument(int& value, int new_inst) {
	if (new_inst & ~INSTRUMENT_BOUNDARY) {
		return -1;
	}
	value &= ~(INSTRUMENT_BITS_MASK << INSTRUMENT_BITS_OFFSET);
	value |= (new_inst << INSTRUMENT_BITS_OFFSET);
	return 0;
}

int main() {
	int input_val, input_direction, input_offset, input_instrument;
	int check_val1, check_val2, check_val3;

	std::cin >> input_val;
	std::cin >> input_direction;
	std::cin >> input_offset;
	std::cin >> input_instrument;

	check_val1 = input_val;
	set_Direction(input_val, input_direction);
	check_val2 = input_val;
	set_Offset(input_val, input_offset);
	check_val3 = input_val;
	set_Instrument(input_val, input_instrument);

	std::cout << check_val1 << std::endl;
	std::cout << check_val2 << std::endl;
	std::cout << check_val3 << std::endl;
	std::cout << input_val << std::endl;
	return 0;
}
// 64 位输出请用 printf("%lld")