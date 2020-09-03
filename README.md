[![Build Status](https://travis-ci.com/FermiQC/Lints.svg?branch=master)](https://travis-ci.com/FermiQC/Lints)
[![Coverage Status](https://coveralls.io/repos/github/FermiQC/Lints/badge.svg?branch=master)](https://coveralls.io/github/FermiQC/Lints?branch=master)
# The Julia Interface to Libint2 

Lints.jl provides an interface to the Libint2 molecular integral generation library.

## Current Limitations
Only the default Libint library is supported, and is distributed as a binary when Lints is installed. Practically speaking, this means
that nuclear gradients and Hessians are currently unavailable. This is not a technical issue, it just has not yet been required by the
developers. If you want a Libint library with different features, please open an issue and we will take care of it!

## Example
Example of using Lints to compute overlap integrals for a molecule with the cc-pVDZ basis set.

```
using Lints
@lints begin
    mol = Lints.Molecule([8,1,1],[[0.0,0.0,0.0],
                                  [1.0,0.0,0.0],
                                  [0.0,1.0,0.0]])
    bas = Lints.BasisSet("cc-pVDZ",mol)
    S = Lints.make_S(bas)
end
```

Wrapping the code that uses Lints in `@lints begin ... end` takes care of initializing and finalizing Libint2 for you.
Technically, only some Lints functions are required to be in an `@lints` block, but its easiest to remember to just put
all Lints-using code inside of one of these blocks.

## Integrals Available
| Integral type       | Function signature                                 |
|---------------------|----------------------------------------------------|
| Overlap             | `make_S(basis::BasisSet)`                          |
| Kinetic             | `make_T(basis::BasisSet)`                          |
| Nuclear Attraction  | `make_V(basis::BasisSet)`                          |
| 4 center ERI (mn|rs)| `make_ERI4(basis::BasisSet)`                       |
| 3-center ERI (Q|mn) | `make_ERI3(basis::BasisSet,dfbasis::BasisSet)`     |
| 2-center ERI (P|Q)  | `make_ERI2(basis::BasisSet)`                       |
