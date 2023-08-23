#include "shell.h"

/**
 * strtow - Splits a string into words using a given delimiter.
 * @str: The input string to be split.
 * @d: The delimiter used to split the string.
 *
 * Return: pointer to arr of str, or NULL on failure.
 */

char **strtow(char *str, char *d)
{
  int ind1, ind2, ind3, ind4, num_words = 0;
  char **result_array;

  if (!str || str[0] == '\0')
  {
    return (NULL);
  }

  if (!d)
  {
    d = " ";
  }

  for (ind1 = 0; str[ind1] != '\0'; ind1++)
  {
    if (!is_delim(str[ind1], d) &&
        (is_delim(str[ind1 + 1], d) || !str[ind1 + 1]))
    {
      num_words++;
    }
  }

  if (num_words == 0)
  {
    return (NULL);
  }

  result_array = malloc((1 + num_words) * sizeof(char *));
  if (!result_array)
  {
    return (NULL);
  }

  for (ind1 = 0, ind2 = 0; ind2 < num_words; ind2++)
  {
    while (is_delim(str[ind1], d))
    {
      ind1++;
    }

    ind3 = 0;
    while (!is_delim(str[ind1 + ind3], d) && str[ind1 + ind3])
    {
      ind3++;
    }

    result_array[ind2] = malloc((ind3 + 1) * sizeof(char));
    if (!result_array[ind2])
    {
      for (ind3 = 0; ind3 < ind2; ind3++)
      {
        free(result_array[ind3]);
      }
      free(result_array);
      return (NULL);
    }

    for (ind4 = 0; ind4 < ind3; ind4++)
    {
      result_array[ind2][ind4] = str[ind1++];
    }

    result_array[ind2][ind4] = '\0';
  }

  result_array[ind2] = (NULL);
  return result_array;
}

/**
 * strtow2 - Splits a string into words using a single delimiter character.
 * @str: The input string to be split.
 * @d: The delimiter character used to split the string.
 *
 * Returns: pointer to an arr of str, or NULL on failure.
 */

char **strtow2(char *str, char d)
{
  int ind1, ind2, ind3, ind4, num_words = 0;
  char **result_array;

  if (!str || str[0] == '\0')
  {
    return (NULL);
  }

  for (ind1 = 0; str[ind1] != '\0'; ind1++)
  {
    if ((str[ind1] != d && str[ind1 + 1] == d) ||
        (str[ind1] != d && !str[ind1 + 1]) || str[ind1 + 1] == d)
    {
      num_words++;
    }
  }

  if (num_words == 0)
  {
    return (NULL);
  }

  result_array = malloc((1 + num_words) * sizeof(char *));
  if (!result_array)
  {
    return (NULL);
  }

  for (ind1 = 0, ind2 = 0; ind2 < num_words; ind2++)
  {
    while (str[ind1] == d && str[ind1] != d)
    {
      ind1++;
    }

    ind3 = 0;
    while (str[ind1 + ind3] != d && str[ind1 + ind3] && str[ind1 + ind3] != d)
    {
      ind3++;
    }

    result_array[ind2] = malloc((ind3 + 1) * sizeof(char));
    if (!result_array[ind2])
    {
      for (ind3 = 0; ind3 < ind2; ind3++)
      {
        free(result_array[ind3]);
      }
      free(result_array);
      return (NULL);
    }

    for (ind4 = 0; ind4 < ind3; ind4++)
    {
      result_array[ind2][ind4] = str[ind1++];
    }

    result_array[ind2][ind4] = '\0';
  }

  result_array[ind2] = (NULL);
  return result_array;
}

