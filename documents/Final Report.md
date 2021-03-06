
# Final Report

**Project:** Distributed Consensus

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

# Challenges

The main challenge during the development is ledger failure case handlings during the two phase commit protocol, and we spent lots of time coming up tsolutions to handle different cases:

**Case 1**- in phase one, coordinator fails before sending/ receiving messages from all participants.

- In our design, each participant sets a timer after replying to the coordinator’s request. If timeout happens, meaning that the participant does not receive callback message from the coordinate whether to commit or not commit, then this whole request will be discarded by each participant to ensure consensus.

**Case 2** - in phase one, one or more participants fails to send reply messages back to the coordinator.

- In our design, the coordinator sets a timer after distributing requests to the participants. If timeout happens, meaning that the coordinator fails to receive one or more messages from one or more participants, then the request will be canceled to prevent the coordinator from waiting infinitely.

**Case 3** - in phase two, one participant fails.

- In this case, the coordinator will continue to send commit/not commit messages to each participant, and every healthy participant will commit successfully. When the failed process recovers from failure, it will ask around other processes for the current balance upon initialization.

**Case 4** - in phase two, the coordinator fails.

- The case cannot be handled by two phase commit protocol, as described in the first paper. That means a modification of the two phase commit is needed such as electing a watchdog to watch the coordinator.

# Division of work
Anjie Wang is mainly in charge of the building blocks of UDP socket communication between processes and the design of the Ledger program.

Jiachen Wang is mainly in charge of building the logic and error handling of the Two Phase Protocol, as well as wrapping up things in the report and presentation PPT.

  

# Result
The decentralized bank account system (on one computer) was successfully implemented and tested. A generic ledger program `Ledger.cpp` is in the project repository. 

Details on how to run and test the system are listed in the `README.md` file.

