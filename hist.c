/*
Copyright (c) 2020 Jeremy Iverson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* assert */
#include <assert.h>

/* EXIT_SUCCESS, rand */
#include <stdlib.h>

/* strtol */
#include <stdio.h>

/* memset */
#include <string.h>

static int
hist_ref(unsigned const n,
         unsigned const k,
         unsigned const * const in,
         unsigned       * const out)
{
  memset(out, 0, k * sizeof(*out));

  for (unsigned i = 0; i < n; i++) {
    out[in[i]]++;
  }

  return 0;
}

static int
hist(unsigned const n,
     unsigned const k,
     unsigned const * const in,
     unsigned       * const out)
{
  return hist_ref(n, k, in, out);
}

int
main(int argc, char *argv[]) {
  int ret;

  /* Get array size from command line */
  unsigned n = strtol(argv[1], NULL, 10);

  /* Get key size from command line */
  unsigned k = strtol(argv[2], NULL, 10);

  /* Allocate memory */
  unsigned * const a = malloc(n * sizeof(*a));
  unsigned * const b = malloc((1u << k) * sizeof(*b));
  unsigned * const c = malloc((1u << k) * sizeof(*c));

  /* Populate with random values */
  for (unsigned i = 0; i < n; i++) {
    a[i] = rand() % (1u << k);
  }

  /* Reference implementation */
  ret = hist_ref(n, 1u << k, a, b);
  assert(0 == ret);

  /* Parallel implementation */
  ret = hist(n, 1u << k, a, c);
  assert(0 == ret);

  /* Validate sorted array */
  for (unsigned i = 0; i < 1u << k; i++) {
    assert(b[i] == c[i]);
  }

  /* Free memory */
  free(a);
  free(b);
  free(c);

  return EXIT_SUCCESS;
}
