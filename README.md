[![Build Status](https://travis-ci.com/FermiQC/Lints.svg?branch=master)](https://travis-ci.com/FermiQC/Lints)
# The Julia Interface to Libint2 

Lints.jl provides an interface to the Libint2 molecular integral generation library.

## Current Limitations
Only the default Libint library is supported, and is distributed as a binary when Lints is installed.

## Example
Example of using Lints to compute overlap integrals for a molecule with the cc-pVDZ basis set.

```
using Lints
Lints.libint2_init()
mol = Lints.Molecule("/tmp/molfile.xyz")
bas = Lints.BasisSet("cc-pvdz",mol)
nprim = Lints.max_nprim(bas)
l = Lints.max_l(bas)
S_engine = Lints.KineticEngine(nprim,l)
nao = Lints.nao(bas)
S = zeros(nao,nao)
Lints.make_2D(S,S_engine,bas)
Lints.libint2_finalize()
```
