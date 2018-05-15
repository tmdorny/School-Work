Tim Dorny	u0829896
Tanner Marshall	u0840815

I certify that the work to create this GUI was done entirely by myself and my partner - Tim Dorny, Tanner Marshall


Additional Feature(s)

The additional features we decided to add were copy/paste/delete functionality. These allow you to copy the data from one cell to another, or remove the data from a cell.
When deleting a cell used by a formula, slight problems occur. If we had access to the dependents of cells, it would be an easy fix, but we do not and we have
run out of time to try and eloquently solve this issue.


Design Decisions

We "borrowed" code from the demo project for the new spreadsheet creation.
We ran into a few problems with the gui generator, causing a few of our methods to have unusual/outdated names...


Resources

We looked at Microsoft's documentation quite a bit. We also looked at a number of stack overflow posts.


Guidelines

We followed the assignment guidelines as close as possible.


Notes

Background worker has been added. Was somewhat confused on what we were doing, but it seems to be working.
Let us know if there is an issue with our implementation.


Problems

UI testing has been a major struggle to get working. Generating and running tests has been very difficult.
On my personal machine, I cannot even create a "coded ui test" project. (Tim)

Had an issue with exceptions being thrown from the lookup function in the formula evaluate method, but after
way too long, we got it working.