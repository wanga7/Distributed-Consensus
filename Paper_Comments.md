- Significance on
- “Your Coffee Shop Doesn’t Use Two-Phase Commit”

In really world systems, sometimes maximizing throughput is put at a higher priority. Often, the optimization for throughput results in a concurrent and asynchronous processing model, so that requests aren’t necessarily completed in the same sequence in which they initiated.

In such systems, the so-called correlation problem, of knowing to which requester each finished task belongs to, needs to be addressed. One possible solution to such problem is to use a correlation identifier to tag each requester and task.

Exception handling is also extremely important in such a concurrent and asynchronous model. There are mainly four strategies for exception handling. The first one is write-off, or to discard what have been done. This is especially useful when the loss is acceptably small but building an error-correction solution might be more expensive. The second one is retrying the failed components. The third one is called compensating action, which tries to to undo already completed operations to return the system to a consistent state. The fourth one is using transaction coordinator with properties of a two-phase commit, although by doing so can hurt the free flow of messages because it requires the allocation of a stateful transaction resource. In doing so, optimistic approach can be implemented if the loss of failure is acceptable, while pessimistic approach is more appropriate if otherwise.

In some sense, asynchrony is a matter of perspective, with some system components expecting a synchronous interaction but some other components expecting an asynchronous interaction. In application, it is sometimes more applicable to build a system where being asynchronous often applies only to part of the interaction. In such so-called half-sync, half-async pattern, the main ingredient to solving both parties’ requirements is a message buffer that lets the asynchronous participant deliver messages asynchronously without having to wait for the synchronous participant. [1]

Looking at daily life scenarios can help to provide insights. Real-world experiences tell us that an asynchronous messaging architecture can often be a more natural way to model many types of interactions. 

Reference:
[1], Gregor Hohpe, 2005, Your Coffee Shop Doesn’t Use Two-Phase Commit, http://www.enterpriseintegrationpatterns.com/docs/IEEE_Software_Design_2PC.pdf
