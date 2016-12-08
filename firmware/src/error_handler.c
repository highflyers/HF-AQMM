#include <error_handler.h>
#include <rgb_pwm.h>

void error_handler()
{
	RGB_Set_Pattern_Color(1, 0, 0);
}

void error_handler_str(const char *str)
{
	RGB_Set_Pattern_Color(1, 0, 0);
	fprintf(stderr, "%s\n", str);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	RGB_Set_Pattern_Color(1, 0, 0);
	fprintf("Assert falied: %s, line %lu", (char*) file, line);
}
