#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      return 0;
    }
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

/*
int main(void) {
	printf("test 0xa2 + 0xa\n%s\n", arithmatoy_add(16, "a2", "a"));
	printf("test 0xfff + 0x1234\n%s\n", arithmatoy_add(16, "fff", "1234"));
	printf("test 0x123 + 0x1234\n%s\n", arithmatoy_add(16, "123", "1234"));
}*/

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "sub: entering function\n");
  }

  // Fill the function, the goal is to compute lhs - rhs (assuming lhs > rhs)
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
}

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

  // Fill the function, the goal is to compute lhs * rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
}

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

