# MPICH playground
Experimenting with MPI

Install `MPICH` on mac with brew

```
brew install mpich
```

## Multi-processes
Compile C++ with

```
mpic++ main.cc -o main
```

and execute with k processes with

```
mpiexec -n k ./main
```

## Cluster
Todo
