# Imagews
Implementation of Image codecs.

## Functions
Currently the project has the implementation of the following codecs:
|Format|Coder|Decoder|
|---|---|---|
|BMP| No | No |
|QOI| No | Yes |

## Dependencies
This project uses no external dependencies.  
This project uses C++17 standard.

## Building
Building with Cmake consists of configuring the project, and then building it.
```bash
mkdir build/
cd build
cmake ..
cmake --build .
```

## Tests
The project contains a few test vectors. To run the test vectors first configure the project with `ENABLE_TESTING`, then build.
```bash
cmake -DENABLE_TESTING:BOOL=TRUE ..
cmake --build .
```
Then run the command.
```bash
ctest -C Debug
```

## Reference
https://qoiformat.org/qoi-specification.pdf
https://www.youtube.com/watch?v=EFUYNoFRHQI