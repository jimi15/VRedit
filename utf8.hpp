#ifndef UTF8
#define UTF8

#define MYKEY_DELETE 56650
#define MYKEY_END 56680
#define MYKEY_HOME 56582
#define MYKEY_UP 56579
#define MYKEY_DOWN 56578
#define MYKEY_LEFT 56580
#define MYKEY_RIGHT 56581
#define MYKEY_PAGEDN 56658
#define MYKEY_PAGEUP 56659
#define MYKEY_BACKSPACE 56583

unsigned utf8_code(int code_unit1,int code_unit2,int code_unit3,int code_unit4){
	if (code_unit1 < 0x80) {
		return code_unit1;
	} else if (code_unit1 < 0xC2) {
	/* continuation or overlong 2-byte sequence */
		goto ERROR1;
	} else if (code_unit1 < 0xE0) {
	/* 2-byte sequence */
		if ((code_unit2 & 0xC0) != 0x80) goto ERROR2;
		return (code_unit1 << 6) + code_unit2 - 0x3080;
	} else if (code_unit1 < 0xF0) {
	/* 3-byte sequence */
		if ((code_unit2 & 0xC0) != 0x80) goto ERROR2;
		if (code_unit1 == 0xE0 && code_unit2 < 0xA0) goto ERROR2; /* overlong */
		if ((code_unit3 & 0xC0) != 0x80) goto ERROR3;
		return (code_unit1 << 12) + (code_unit2 << 6) + code_unit3 - 0xE2080;
	} else if (code_unit1 < 0xF5) {
	/* 4-byte sequence */
		if ((code_unit2 & 0xC0) != 0x80) goto ERROR2;
		if (code_unit1 == 0xF0 && code_unit2 < 0x90) goto ERROR2; /* overlong */
		if (code_unit1 == 0xF4 && code_unit2 >= 0x90) goto ERROR2; /* > U+10FFFF */
		if ((code_unit3 & 0xC0) != 0x80) goto ERROR3;
		if ((code_unit4 & 0xC0) != 0x80) goto ERROR4;
	return (code_unit1 << 18) + (code_unit2 << 12) + (code_unit3 << 6) + code_unit4 - 0x3C82080;
	} else {
	/* > U+10FFFF */
		goto ERROR1;
	}

	ERROR4:
	ungetc(code_unit4, stdin);
	ERROR3:
	ungetc(code_unit3, stdin);
	ERROR2:
	ungetc(code_unit2, stdin);
	ERROR1:

	return code_unit1 + 0xDC00;
}

#endif // UTF8

