# screen-photo-to-text
C++/OpenCV script to turn photos taken from a screen into plain text

Initial project generated based on:
https://www.youtube.com/watch?v=fz2gDUO6XkM

Install Tesseract from: 
https://github.com/tesseract-ocr/tesseract

steps:
clone
cd <directory>
mkdir build && cd build
cmake ../
make
  
or visit https://github.com/tesseract-ocr/tesseract/blob/master/INSTALL.GIT.md for more instructions

Install Leptonica from:
https://github.com/DanBloomberg/leptonica

same steps as above

Possible erros when compiling:

ld: library not found for -llept
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [startProject] Error 1
make[1]: *** [CMakeFiles/startProject.dir/all] Error 2
make: *** [all] Error 2

Fix:

CMakeFiles/startProject.dir/link -> remove command -llept


