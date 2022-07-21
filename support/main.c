/* Common main.c for the benchmarks

   Copyright (C) 2014 Embecosm Limited and University of Bristol
   Copyright (C) 2018 Embecosm Limited

   Contributor: James Pallister <james.pallister@bristol.ac.uk>
   Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include "support.h"
#include <stdio.h>
#include <stdlib.h>


extern int initialise_benchmark (void);
extern int verify_benchmark (int unused);

int
main (int   argc,
      char *argv[])
{
  int i;
  volatile int result;
  int correct;

  int repeat_factor = REPEAT_FACTOR;

  if (argc > 1)
    {
      int rf = atoi(argv[1]);
      if (rf > 0)
        {
          repeat_factor = atoi(argv[1]);
        }
    }

  initialise_board ();
  initialise_benchmark ();
  start_trigger ();

  for (i = 0; i < repeat_factor; i++)
    {
      initialise_benchmark ();
      result = benchmark ();
    }

  stop_trigger ();
  iprintf("repeat_factor : %u\n", repeat_factor);

  /* bmarks that use arrays will check a global array rather than int result */

  correct = verify_benchmark (result);

  return (!correct);

}	/* main () */

/*
   Local Variables:
   mode: C++
   c-file-style: "gnu"
   End:
*/
