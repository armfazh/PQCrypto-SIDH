# FLOR-SIDH-x64

This is a fork of the [PQCrypto-SIDH](https://github.com/Microsoft/PQCrypto-SIDH) project of Microsoft.

This software library is a C-language + optimized assembly code that supports an instance of the Super-Singular Isogeny Diffie-Hellman algorithm proposed by Costelo, Longa and Naehrig on CRYPTO 2016.


----

### Additional contributions
 * Improved Calculation of the P+[k]Q operation. 
    * A right-to-left ladder replaces the 3-point ladder algorithm of De Feo et al. accelerating the shared secret phase.
    * A right-to-left ladder with precomputation tables that accelerate key generation phase.
 * New point tripling formulas for Montgomery curves. An improvement of 1M-1S-1A operations in Fp2. 
 * Efficient implementation of arithmetic operations of Fp and Fp2 using MULX and ADCX/ADOX instructions.
    * Around 25% of improvement on Haswell and Skylake processors. 

---

### Research Resources

This source code is part of the research work titled: 
*"A Faster Software Implementation of the Supersingular Isogeny Diffie-Hellman Key Exchange Protocol"*
by the authors:
 * Armando Faz-Hernández, University of Campinas, Brazil.
 * Julio López, University of Campinas, Brazil.
 * Eduardo Ochoa-Jiménez, Computer Science Department, Cinvestav-IPN, Mexico.
 * Francisco Rodríguez-Henríquez, Computer Science Department, Cinvestav-IPN, Mexico.


A pre-print of this document can be found at the IACR ePrint Archive: http://iacr.eprint.org/2017/xxx [[PDF](https://eprint.iacr.org/2017/)]
 

---

### Compilation
Clone repository and configure project using the [CMake](https://cmake.org/) tool:

```sh
 $ git clone https://github.com/armfazh/flor-sidh-x64
 $ cd flor-sidh-x64
 $ mkdir build
 $ cd build
```
You can specify the compiler as follows:
```sh
 $ CC=gcc cmake ..
 $ make
```

----

### Running Benchmark

#### Key Exchange Performance Report
Once compilation was done, you can run the ```kex_haswell``` companion program if you are in a processor supporting MULX instruction, e.g. on Haswell.
```sh
 $ bin/kex_haswell
```

Optionally, you can run the ```kex_skylake``` companion program if you are in a processor supporting MULX and ADCX/ADOX instructions, e.g. on Skylake.
```sh
 $ bin/kex_skylake
```

To run the original arithmetic provided by SIDH v2, you can run:  
```sh
 $ bin/kex_native
```

#### Low level Arithmetic Performance Report
If you want to obtain a detailed benchamrk of the operations in Fp, Fp2, and ECC, you can  execute:  
```sh
 $ bin/arith_haswell
```
Optionally, you can also run ```arith_skylake```  or ```arith_native```. 


----


### Compilation options

There are two implementations of the prime field arithmetic in this library that can be enabled by using the ```ARCH_EX = [native|haswell|skylake]```
flag. 

 * Optimized for Haswell processors (append ARCH_EX=haswell):

```sh
$ make ARCH=x64 CC=[gcc/clang] GENERIC=FALSE SET=EXTENDED ASM=TRUE ARCH_EX=haswell
```

 * Optimized for Skylake processors (append ARCH_EX=skylake):

```sh
$ make ARCH=x64 CC=[gcc/clang] GENERIC=FALSE SET=EXTENDED ASM=TRUE ARCH_EX=skylake
```

 * Compile using the original prime field arithmetic.

```sh
$ make ARCH=x64 CC=[gcc/clang] GENERIC=FALSE SET=EXTENDED ASM=TRUE ARCH_EX=native
```


### License 
GNU Lesser General Public License v3.0 ([LICENSE](https://www.gnu.org/licenses/lgpl-3.0.txt))

----

### Contact 

To report some issues or comments of this project, please use the issues webpage [[here](https://github.com/armfazh/flor-sidh-x64/issues)]. 

----



