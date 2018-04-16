﻿# CS 3281 Projects

Please complete the project form at https://goo.gl/forms/M9x3DVEKMjTTpJXl2. Deadline of project selection is March 26 2018.

Projects will be performed in a group of two. Grades will be based on the following items.

- Initial design (due two weeks from project announcement): 10%   (April 6 2018)
  - A one page document pushed to GitHub describing how you plan on implementing your project and the resources you plan on using

- Code, documentation, and final report (due April 23): 65%
  - Code: pushed to GitHub. This should include comments and error checking.
  - Documentation: a README in your repo with instructions on how to build, run and test your project.
  - Report: A document with an overview of your project, the implementation details, the main challenges, the division of work, and the result.

- Presentation and demonstration (done at the time of the final exam, or earlier by appointment): 25%
  - A 6 slide presentation (title slide, overview, implementation, challenges, division of work, results)
  - Short demonstration of your project on your laptop


# Build & Run

To build inside the cloned the project directory:

    $mkdir build
    $cmake ..
    $make
Afterwards, five executable named Ledger1 through Ledger5 will be created inside the build directory.
  
The command of running each executable is similar. For example: `./Ledger1 5000 4 5001 5002 5003 5004`
    - the first argument 5000 indicates the port of Ledger1 to be assigned
    - the second argument 4 indicates that this Ledger will have 4 neighbours which have been or will be started
    - the following arguments indicate the ports that this Ledger's neighbours will use

In this example, to start the remaining four Ledgers, you may open 4 other seperate terminals, cd into the right directory and type in commands respectively:
`./Ledger2 5001 4 5000 5002 5003 5004`
	    `./Ledger3 5002 4 5000 5001 5003 5004`
	     `./Ledger4 5003 4 5000 5001 5002 5004`
	     `./Ledger5 5004 4 5000 5001 5002 5003`

**Note:** to make it possible for a certain Ledger to synthesize with other running Ledgers upon launching, you must add argument R in the end of the command: `./Ledger3 5002 4 5000 5001 5003 5004 R` (For example, when you want to restart a failed ledger, you must add the argument R to make sure it synthesize with other ledgers.)
  
# Testing
After launched, this interactive shell supports three types of commands:

 - C for credit(add money)
 - D for debit(withdraw money)
 - Q for query

A numerical value must follow right after the C or D type commands, for example, C100, D25. Q command does not need any other information following it.

The system will then print out a message indicating on whether the transaction is successful and then you can keep interacting with the shell. The most important feature of this distributed system is that every transaction step is synthesized, which means if you credit money on one running process, the remaining running Ledgers will almost immediately see and update the change (if the transaction is successful), so that the entire system will always be in a consensus.
