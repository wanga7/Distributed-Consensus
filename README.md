# Distributed Consensus Project

**Team member:** Anjie Wang & Jiachen Wang

# Overview  

A classical problem in distributed computing is the task of agreeing on a data value needed for computation even if there are some faulty processes. This is the consensus problem. Achieving consensus allows the distributed computing processes to behave as a single entity. Example of applications of consensus include agreeing on committing a transaction to a distributed database, state machine replication, and event chronology. Real-word applications include clock synchronization, state estimation in power grids, server load balancing and crypto currencies.  

In this project, we implemented a decentralized bank account ledger using the two-phase commit protocol on a single computer. The distributed computing idea used here is that there is no "central" database. That being said, this is a distributed system that maintains consistency using a simple consensus protocol, and all running instances in the system maintain the same piece of data.

Here's a flowchart of our 2-phase-commit protocol:
![graph](https://github.com/cs3281/final-project-Distributed-Wangs/blob/master/2pc_flowchart.JPG)

# Implementations
This project is written in C++. The project is implemented by having 5 running instances of the same program running on a single machine. UDP sockets are used to communicate with different processes, each of which with a unique port. The port of an instance and the ports of its 4 neighbors are provided during launch time through command line arguments. 

Any running bank ledger (process) supports three types of interactions. The first one is credit, which runs the consensus protocol and credits money to the account. The second one is debit, which runs consensus protocol and debits money from the account. The third one is query, which can return the local value of the balance. For simplicity, only one bank account is supported currently and the default initial balance is $0.

The `UDPTools.h` program mainly wraps around UDP socket utilization functions, including sending message to a specific port, receiving message from any port, and sending message to a specific port and waiting for that port to reply.

Upon launching the ledger program, the initialize function will be executed first. First of all, all arguments provided by the user will be parsed. Afterwards, if this ledger failed before and is currently restarting, it will “ask around” other running ledgers through UDP socket connections of the current balance and consequently update it’s balance value.

From then on, two threads, `coordinator` and `participant`, will be launched in parallel. To prevent race conditions, a mutex lock is required in each thread when it enters a critical section. The `coordinator` thread waits on a user input from the terminal, and after a input is parsed and understood, this ledger will be elected as the coordinator in the two phase commit. It will perform tasks including asking around for consensus, collecting answers and finally giving decisions to participants. On the other hand, the `participant` thread will act as a participant in the two phase commit, continuously looping to receive requests from other processes. It will perform tasks including answering query request, giving a yes/no answer or giving a commit/not commit message during the two phase commit.

# Build & Run

To build inside the cloned the project directory:

    $mkdir build
    $cd build
    $cmake ..
    $make
Afterwards, an executable named Ledger will be created inside the build directory.
  
The command of running the executable should be in the format like: `./Ledger 5000 4 5001 5002 5003 5004`
    
- the first argument 5000 indicates the port of current Ledger to be assigned
- the second argument 4 indicates that this Ledger will have 4 neighbours which have been or will be started
- the following arguments indicate the ports that this Ledger's neighbours will use

In this example, to start the remaining four Ledgers, you may open 4 other seperate terminals, cd into the right directory and type in commands respectively:

- `./Ledger 5001 4 5000 5002 5003 5004`
- `./Ledger 5002 4 5000 5001 5003 5004`
- `./Ledger 5003 4 5000 5001 5002 5004`
- `./Ledger 5004 4 5000 5001 5002 5003`

**Note:** to make it possible for a certain Ledger to synthesize with other running Ledgers upon launching, you must add argument `R` in the end of the command like: `./Ledger 5002 4 5000 5001 5003 5004 R` (For example, when you want to restart a failed ledger, you must add the argument `R` to make sure it synthesize with other ledgers.)
  
# Testing
After launched, this interactive shell supports three types of commands:

 - C for credit(add money)
 - D for debit(withdraw money)
 - Q for query

A numerical value must follow right after the C or D type commands, for example, C100, D25. Q command does not need any other information following it.

The system will then print out a message indicating on whether the transaction is successful and then you can keep interacting with the shell. The most important feature of this distributed system is that every transaction step is synthesized, which means if you credit money on one running process, the remaining running Ledgers will almost immediately see and update the change (if the transaction is successful), so that the entire system will always be in a consensus.



