#include<iostream>

using namespace std;

void hanoi(int diskSize, int source, int dest, int spare)
{
  if(diskSize == 0)
    {
        cout << "Move disk " << diskSize << " from peg " << source << " to peg " << dest << endl;
    }
    else
    {
        //Move all disks smaller than this one over to the spare.
        //So if diskSize is 5, we move 4 disks to the spare. This leaves us with 1 disk
        //on the source peg.
        //Note the placement of the params.
        //We are now using the dest peg as the spare peg. This causes each recursion to ping-pong
        //the spare and dest pegs.
        hanoi(diskSize - 1, source, spare, dest);

        //Move the remaining disk to the destination peg.
        cout << "Move disk "  << diskSize << " from peg " << source << " to peg " << dest << endl;

        //Move the disks we just moved to the spare back over to the dest peg.
        hanoi(diskSize - 1, spare, dest, source);
    }
}

int main()
{
	hanoi(3,1,3,2);
}
