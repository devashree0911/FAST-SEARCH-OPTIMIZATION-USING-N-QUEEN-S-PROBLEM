# FAST-SEARCH-OPTIMIZATION-USING-N-QUEEN-S-PROBLEM

N-Queens model requires n processors, one processor for each queen. The
algorithm is based on the serial algorithm. The parallelism is introduced by breaking
the requirement that queens must be placed in successive columns. In the parallel
algorithm, processors randomly and in parallel select columns to place queens.
Conflicts that might occur between selections from different processors are
resolved in parallel as well. The parallel algorithm consists of the same two steps as
the serial algorithm, the initial step and the final step. 

To achieve parallelization in the n-queen’s problem, first we need to configure the
cores in the processors according to our convenience. According to our concept, we
will be deploying the 4 cores in order to perform the search operation faster. We 
will configure the cores in such a way that they work in 4 different directions,
considering square blocks of 8*8 together. Each of them will be able to search
independently and there is a high possibility that one of them will find the file
stored in the desired memory location faster than the other 3. The 4 cores can be
deployed in many configurations. Here are two such scenarios:
 
 Each of the 4 on the 4 corners of square and each of them in a different
row/column.
 
 Two starting from the center spirally going outwards and two from diagonally
opposite corner ends going spirally inwards
