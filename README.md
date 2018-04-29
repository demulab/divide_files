# divide_files
Divide all data into training data and test data, and make a test.list and a training.list for for training of YOLO. 

## Compile:  
```
gcc -o divide_files divide_files.c    
```

## Usage:
```
./divide_files
or  
./divide_files [portion]
```
portion: the portion of test data. The default value is 0.2.
