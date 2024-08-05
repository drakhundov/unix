typedef struct
{
	unsigned ignore_case: 1,	   // Ignore uppercase and lowercase;
			 return_reversed: 1,  // Return sorted data reversed.
			 sort_as_numeric: 1,  // Compare elements as doubles (not strings).
			 ignore_spaces: 1;
} options;
typedef struct
{
	int start, end;
	options params;
} field;
