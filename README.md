# Threaded-Binary-Search
simple program that compares runtime of single and multithreaded BinarySearch operation.
## Approach / Implementation
This program utilizes the running PCs thread count to launch the amount of logical threads available to run the binary search task. The vector was partitioned based on the amount of available threads, with each threads performing a binary search on each partition. A vector of futures was utilized to store all of the return values for each thread.
## Thoughts and Glaring Problems
If you are already familiar with the Binary Search algorithm you might have had a clue to the outcome of the runtimes between the two implementations, threaded and non-threaded Binary Search. The way binary search traverses the path to find the target index means that there is only one path and it only traverses that path, essentially as if its a linked list. Partitioning the vector for more threads to work on each partition does nothing to speed up the algorithm as since there is only one partition that will find the target index and the rest will never find it.

Overall this was a good exersize working with a systems available threads and C++ futures.
