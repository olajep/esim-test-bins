#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <e_lib.h>

#define ROWS 4
#define COLS 4
#define FIRST_ROW 0x20    // First row in group
#define FIRST_COL 0x8     // First col in group
#define FIRST_CORE 0x808  // Coreid of first core in group

#define E_ROW(x) ((x) >> 6)
#define E_COL(x) ((x) & ((1<<6)-1))
#define E_CORE(r, c) (((r) << 6) | (c))

#define LEADER FIRST_CORE

/* Core mem address for message box */
#define MSG_BOX 0x6000

/* Can't hook up to sync since e-server traps it */
void interrupt_handler() __attribute__ ((interrupt ("message")));
void pass_message();
void print_route();

int main()
{
  int i;

  e_irq_global_mask(E_TRUE);
  e_irq_mask(E_MESSAGE_INT, E_FALSE);
  e_irq_attach(E_MESSAGE_INT, interrupt_handler);

  if (e_get_coreid() == LEADER)
    {
      /* Give other processes time to go to idle */
      for (i=0; i < 10000000; ++i) ;
      pass_message();
    }

  e_irq_global_mask(E_FALSE);
  asm("idle");
  return 0;

}

void interrupt_handler()
{
  if (e_get_coreid() == LEADER)
    {
      /* Print route message took */
      print_route();
      exit(3);
    }
  else
    {
      /* Pass message to next core in path */
      pass_message();
      _exit(2); // Normal exit seems to close other processes stdout ???
    }
}

e_coreid_t next_hop()
{
  enum direction_t { LEFT, RIGHT } direction;

  e_coreid_t coreid;
  unsigned row, col, rel_row, rel_col;

  coreid = e_get_coreid();
  row = E_ROW(coreid);
  col = E_COL(coreid);
  rel_row = row - FIRST_ROW;
  rel_col = col - FIRST_COL;

  direction = (rel_row & 1) ? LEFT : RIGHT;

  if (coreid == LEADER)
    return E_CORE(row, col+1);

  if (!rel_col)
    return E_CORE(row-1, col);

  if (rel_row == ROWS-1)
    return E_CORE(row, col-1);

  switch (direction)
    {
    case LEFT:
      if (rel_col == 1)
	return E_CORE(row+1, col);
      else
	return E_CORE(row, col-1);

    case RIGHT:
      if (rel_col == COLS-1)
	return E_CORE(row+1, col);
      else
	return E_CORE(row, col+1);
    }

  return FIRST_CORE;

}

void pass_message()
{
  e_coreid_t next;
  unsigned n;
  unsigned *next_msgbox;
  unsigned *msgbox = (unsigned *) MSG_BOX;

  if (e_get_coreid() == LEADER)
    {
      *msgbox = 0;
    }

  msgbox[0]++;
  n = msgbox[0];
  msgbox[n] = (unsigned) e_get_coreid();

  next = next_hop();
  next_msgbox = (unsigned *)
    e_get_global_address(E_ROW(next), E_COL(next), (void *) MSG_BOX);
  memcpy((void *) next_msgbox, (void *) msgbox, (n+1)*sizeof(unsigned));

  printf("Passing message to 0x%x\n", next);
  e_irq_set(E_ROW(next), E_COL(next), E_MESSAGE_INT);
}

void print_route()
{
  int i,j;
  e_coreid_t core;
  unsigned row, col;
  unsigned path[ROWS][COLS];
  unsigned *msgbox = (unsigned *) MSG_BOX;

  printf("Got %d messages\n", msgbox[0]);
  printf("Message path:\n");
  for (i=0; i < msgbox[0]; i++)
    {
      core = msgbox[i+1];
      if (core)
	{
	  row = E_ROW(core) - FIRST_ROW;
	  col = E_COL(core) - FIRST_COL;
	  path[row][col] = i;
	}
    }
  for (i=0; i < ROWS; i++)
    {
      for (j=0; j < COLS; j++)
	printf("%d\t", path[i][j]);

      printf("\n");
    }
}
