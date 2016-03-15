We worked together at the same time using one computer in order to minimize 
pulling/pushing conflicts. However, we debugged our program on separate 
machines to make the debugging process faster. We also talked about/planned 
our algorithms beforehand together.

We furthered our simple_heuristic function by taking into account weights 
of the corners and spot next to corners. We also added a minmax function 
to calculate the best move using a 2-ply minmax decision. However, we were 
unable to (due to time limitations) construct a minmax tree so we could not 
go further in depth than 2 layers as of right now. In order to be 
competitive in the tournament, we probably will need to go a few more layers
further. Near the beginning, we wanted to see how just selecting the first 
valid move on the board (left-top-most) would do against the SimplePlayer. 
It seems that this method is not sufficient to compete with a randomly 
selecting strategy.
