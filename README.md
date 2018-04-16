# CS 3281 Projects

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


-->>How to compile, run and test the program:

To compile inside the cloned the project directory:
  - $mkdir build
  - $cmake ..
  - $make
  - Afterwards, five executable name Ledger1 through Ledger5 will be created inside the build directory
  
The command of running each executable is similar:
  - for example, ./Ledger1 5000 4 5001 5002 5003 5004
    - the first argument 5000 means that the port of Ledger1 will be assigned
    - the second argument 4 means that this Ledger will have 4 neighbours which have been or will be started
    - the following arguments indicate the ports that this Ledger's neighbours will use
    - in this example, to start the remaining four Ledgers, you may open other 4 seperate terminals, cd into the right directories and type in commands respectively
      - ./Ledger2 5001 4 5000 5002 5003 5004
      - ./Ledger3 5002 4 5000 5001 5003 5004
      - ./Ledger4 5003 4 5000 5001 5002 5004
      - ./Ledger5 5004 4 5000 5001 5002 5003
  Note: to make it possible for a certain Ledger to synthesize with other running Ledgers upon launching, you can add argument R in the end of the command, for example, ./Ledger3 5002 4 5000 5001 5003 5004 R
