## How to compile the mutant generator?

```console
ubuntu@pp10:~/Research/mutantgenerator$ cmake .
ubuntu@pp10:~/Research/mutantgenerator$ cmake --build .
```
## How to use the mutant generator to generate Minepump and ADAPRO mutants (STEP 1)?

```console
ubuntu@pp10:~/Research/mutantgenerator$ ./mutantgenerator 1 '#include "./ltl.inc" ./models/minepump/original.pml
ubuntu@pp10:~/Research/mutantgenerator$ ./mutantgenerator 1 '#include "./Theory.prp" ./models/minepump/original.pml
```

Where 1 is the number of iteration of mutant generation, #include is the include file containing the properties and ./models is the path to the model file.

## How to assess the mutants (step 2)?

```console
ubuntu@pp10:~/Research/mutantgenerator$ cd ./models/minepump/
ubuntu@pp10:~/Research/mutantgenerator$ python3 script.py
```
mutation scores are written in log.txt
