We will read in a 10x10 world and then process it.

The program is run from the command line as follows:
```
$ go run life.go
```

Language Features:
```
The Golang run time handles scheduling and resource allocation for the goroutines internally.
Goroutines are not OS threads, but they are not exactly Green Threads as well. Go's mechanism for hosting goroutines is an implementation of what's called an M:N scheduler, which means it maps M green threads to N OS threads. Goroutines are then scheduled onto the green threads.
```