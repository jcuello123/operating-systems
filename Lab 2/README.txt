FOR PART 1:
    1. Run the command "make clean"
    2. Run the command "make"
    3. Run the command "./main" with any number of threads and any number for the capacity. Example: ./main 10 5

FOR PART 2:
    1. Run the command "cd LKM" to get into the LKM folder
    2. Run the command "make clean"
    3. Run the command "make"
    4. Run the command "sudo insmod main.ko"
    5. Run the command "cd ../" to get back to the previous directory that contains part 1
    6. If you already ran the command "make" in this directory, you can just run the program again with ./main 
       with any number of threads and capacity. If not, follow the steps for Part 1. (Note: you may have to run the
       program with many threads (e.g. 100) in order to catch it in the LMK that is running in the background.)
    7. Run the command "dmesg" to see the parent process id, parent process name, and its children. (Note: you may
       have to scroll up after running the command "dmesg" to see the full results. We have filtered the results
       so that everything you see from running the command "dmesg" is coming from our program.)
    8. Run the command "sudo rmmmod main"