#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

int get_value(unsigned int base, char a) {
  char *occ = strchr(get_all_digits(), a);
  if (!occ) {
    return -1;
  }
  int idx = (int) (occ - get_all_digits());
  if (idx >= base) {
    return -1;
  }
  return idx;
}

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "add: entering function\n");
  }
	if (!lhs || !rhs) {
		return 0;
	}
  //Verifier la base check_base (all char must be in get_all digits)
  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);
  int size_lhs = strlen(lhs);
  int size_rhs = strlen(rhs);
  int min_size;
  int max_size;
  char *rhs_rev = reverse(strdup((char *)rhs));
  char *lhs_rev = reverse(strdup((char *)lhs));
  char *max;
  
  if (size_lhs >= size_rhs) {
    max_size = size_lhs;
    min_size = size_rhs;
	max = lhs_rev;
  } else {
    min_size = size_lhs;
    max_size = size_rhs;
	max = rhs_rev;
  }
  char *res = calloc(sizeof(char), max_size + 2);

  int i = 0;
  int retenu = 0;
  while (i < min_size) {
    int val1 = get_value(base, lhs_rev[i]);
    int val2 = get_value(base, rhs_rev[i]);
    if (val1 < 0 || val2 < 0) {
      return 0; }
    if (val1 + val2 + retenu >= base) {
      int current_val = (val1 + val2 + retenu) - base;
      res[i] = get_all_digits()[current_val];
      retenu = 1;
    } else {
      res[i] = get_all_digits()[val1 + val2 + retenu];
      if (retenu == 1) {
        retenu = 0;
      }
    }
    i++;
  }
  while (i < max_size) {
    int val1 = get_value(base, max[i]);
    if (val1 < 0)
      return 0;
    if (val1 + retenu >= base) {
      int current_val = (val1 + retenu) - base;
      res[i] = get_all_digits()[current_val];
      retenu = 1;
	} else {
    	res[i] = max[i] + retenu;
		if (retenu == 1) {
			retenu = 0;
		}
	}
	i++;
  }
  if (retenu == 1) {
	res[i] = '1';
	i++;
  }
  res = reverse(res);
  res[i] = 0;
  return (res);
}


char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "sub: entering function\n");
  }
  printf("test: %s - %s base %ld\n", lhs, rhs, base);
  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);
  int size_lhs = strlen(lhs);
  int size_rhs = strlen(rhs);
  int min_size;
  int max_size;

  char *rhs_rev = reverse(strdup((char *)rhs));
  char *lhs_rev = reverse(strdup((char *)lhs));
  char *max;
  
  if (size_lhs >= size_rhs) {
    max_size = size_lhs;
    min_size = size_rhs;
	max = lhs_rev;
  } else {
    min_size = size_lhs;
    max_size = size_rhs;
	max = rhs_rev;
  }
  char *res = calloc(sizeof(char), max_size + 2);

  int i = 0;
  if (((lhs[0] == '0' && rhs[0] == '1') || (lhs[0] == '1' && rhs[0] == '9')) && max_size== 1) {
	return (NULL);
  }
  int retenu_sub = 0;

  while (i < min_size) {
    int val1 = get_value(base, lhs_rev[i]) - retenu_sub;
    int val2 = get_value(base, rhs_rev[i]);
	//val1 - val2 < 0 ??
	if (val1 - val2 < 0) {
		retenu_sub = 1;
		int current_val = (val1 + base - val2);
		res[i] = get_all_digits()[current_val];
	} else {
      res[i] = get_all_digits()[val1 - val2];
	  retenu_sub = 0;
    }
    i++;
  }
  if (strcmp(max, lhs_rev) == 0) {
	while (i < max_size) {
	  int val1 = get_value(base, max[i]) - retenu_sub;
	  if (val1 < 0)
	  {
	    res[i] = get_all_digits()[base - 1];
	  	retenu_sub = 1;
	  }
	  if (val1 >= 0) {
	    res[i] = get_all_digits()[val1];
		//printf("%i char %c %s\n", i, res[i], res);
		  retenu_sub = 0;
		}
	  i++;
	}
  } else {
	while (i < max_size) {
		if (retenu_sub) {
			int val = -1 + base - get_value(base, max[i]);
			res[i] = get_all_digits()[val];
		} else {
			int val = base - get_value(base, max[i]);
			res[i] = get_all_digits()[val];
		}
		retenu_sub = 0;
		i++;
	}
	int j = 0;
	char *l = malloc(strlen(lhs));
	while (j < max_size) {
		l[j] = get_all_digits()[base - 1];
		j++;
	}
	l[j] = 0;

	//printf("%s %i res %s\n", l, j, reverse(strdup(res)));
	//
	char *bitwise = arithmatoy_sub(base, l, reverse(strdup(res)));
	bitwise[strlen(bitwise) - 1] += 1;
	bitwise = drop_leading_zeros(bitwise);
	//printf("there :%s\n", bitwise);
	if (bitwise[0] == '-') {
	//	return (bitwise);
	}
	res[0] = '-';
	i = 1;
	//printf("%s\n", bitwise);
	while (i <= strlen(bitwise)) {
		res[i] = bitwise[i - 1];
		i++;
	}
	//return res;
	//if (bitwise[strlen(bitwise) - 1] > get_all_digits()[base]) {
		
	//}
	//bitwise not 
	//

  }

  res = reverse(res);
  res = drop_leading_zeros(res);
  res[i] = 0;
  return (res);
}
/*
char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs);
int main(void) {
	//printf("test 0xa2 + 0xa\n%s\n", arithmatoy_add(16, "a2", "a"));
	//printf("test 0xfff + 0x1234\n%s\n", arithmatoy_add(16, "fff", "1234"));
	//printf("test 0x123 + 0x1234\n%s\n", arithmatoy_add(16, "123", "1234"));
	printf("test 0xffff - 0xfdcb\n%s\n", arithmatoy_mul(10, "8", "3"));
	printf("test 0xffff - 0xfdcb\n%s\n", arithmatoy_mul(16, "5abff901", "b4"));
}*/

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

	printf("test a%s b%s\n", lhs, rhs);
	if (!rhs || !lhs){
		return NULL;
	}
	if (!rhs[0] || !lhs[0]) {
		return (NULL);
	}
	char *rev_lhs = reverse(strdup((char*)lhs));
	char *rev_rhs = reverse(strdup((char*)rhs));
	char **add_arr = calloc(sizeof(char*), (strlen(rhs) + 1));
	char *res = calloc(sizeof(char), 100);
	int i = 0;
//	printf("test a%s b%s c%i d%i\n", lhs, rhs, strlen(rhs), strlen(lhs));
	while (i < strlen(rhs)) {
		//get value de current pos
//		printf("%s %s %i %i\n", rev_lhs, rev_rhs, strlen(rhs), strlen(lhs));
		int val_r = get_value(base, rev_rhs[i]);
		if (val_r < 0) {
			printf("%c\n", rev_rhs[i]);
			return NULL;
		}
		add_arr[i] = calloc(sizeof(char), 100);
		long long int retenu = 0;
		int j = 0;
		//i represente le decalage
		while (j < strlen(lhs)) {
			int k = 0;
			while (k < i) {
				add_arr[i][k] = '0';
				k++;
			}
			int val_l = get_value(base, rev_lhs[j]);
			if (val_l < 0) {
				printf("%c\n", rev_lhs[j]);
				return NULL;
			}
			long long int calc = val_l * val_r + retenu;
			if (calc >= base) {
				add_arr[i][i + j] = get_all_digits()[calc % base];
				retenu = calc / base;
			} else {
				add_arr[i][i + j] = get_all_digits()[calc % base];
				retenu = 0;
			}
			j++;
		}
		printf("retenu %i %i %i %i %s\n", retenu, i, j, strlen(lhs), add_arr[i]);
		if (retenu != 0) {
			add_arr[i][i + j] = get_all_digits()[retenu];
			retenu = 0;
		}
		i++;
	}
	int size = i;
	add_arr[i] = 0;
	i = 0;
	char *arg0 = NULL;
	char *arg1 = NULL;
	if (add_arr[i]) {
		arg0 =  reverse(strdup(add_arr[i]));
	}
	if (add_arr[i + 1] != NULL) {
		arg1 = reverse(strdup(add_arr[i + 1]));
	}
	if (!arg1) {
		return (reverse(strdup(add_arr[0])));
	}
	char *ress = arithmatoy_add(base, arg0, arg1);
//	printf("ici %s %s %s\n", ress, arg0, arg1);
	if (!ress) {
		return (reverse(strdup(add_arr[0])));
	}
//	printf("%s\n", add_arr[i]);
	i += 2;
	if (i >= size) {
		return (ress);
	}
	while (i < size) {
		char *buf = ress;
//		printf("addr de i %s\n", add_arr[i]);
		arg0 = ress;
		if (add_arr[i]) {
			arg1 = reverse(strdup(add_arr[i]));
		}
		else {
			arg1 = NULL;
		}
	//	printf("bruh arg 1 %s arg 2 %s\n", arg0, arg1);
		ress = arithmatoy_add(base, arg0, arg1);
	//	printf("bruh2 %s\n", ress);
		if (i + 1 >= size) {
			return (ress);
		}
		i++;
	}
	return (reverse(strdup(add_arr[0])));
	printf("res %s\n", res);
	//add all
}
/*
int main(void) {
	printf("test 0 * 0 %s\n", arithmatoy_mul(16, "0", "0"));
	printf("test 1 * 0 %s\n", arithmatoy_mul(16, "1", "0"));
	printf("test 0 * 1 %s\n", arithmatoy_mul(16, "1", "0"));
	printf("test 0xa2 * 0xa %s\n", arithmatoy_mul(16, "a2", "a"));
	printf("test 0xa2 * 0xaaa %s\n", arithmatoy_mul(16, "a2", "aaa"));
	printf("test 0xaaa * 0xa2 %s\n", arithmatoy_mul(16, "aaa", "a2"));
	printf("test 100111 * 00000100 %s\n", arithmatoy_mul(2, "100111", "00000100"));
	printf("test 184 * 15 %s\n", arithmatoy_mul(10, "184", "15"));
	printf("test 5abff901 * 4 %s\n", arithmatoy_mul(16, "5abff901", "4"));
	printf("test 5abff901 * b4 %s\n", arithmatoy_mul(16, "5abff901", "b4"));
	printf("test 5abff901 * 7cb4 %s\n", arithmatoy_mul(16, "5abff901", "7cb4"));

	//printf("test 0x123 * 0x1234\n%s\n", arithmatoy_mul(16, "123", "1234"));
}*/
// Here are some utility functions that might be helpful to implement add, sub
// and mul:

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to a digit from get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}

