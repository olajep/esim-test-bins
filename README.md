esim-testbins
=============

Some test binaries for epiphany simulator.
These have been used to test various functionality
of esim (multi-core simulator based on Epiphany gdb single-core simulator).

esim will be released to the public before end of summer 2014.

Most of the binaries are a mess.

Use at your own risk.

Most interesting program for others is probably zigzag.

Compile with:
make

Running zigzag
cd zigzag
./run.sh

You need esim for this to work.

zigzag should work on real hardware but some adaption is needed and
there might be a race in between a message transfer is completed and the
interrupt is triggered in pass_message().

idle works on both esim and hardware (via  e-server).

swi_external_agent works on both esim and hardware (via e-server).

selfmod works on both esim and hw.

