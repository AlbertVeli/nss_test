Small program to use libnss3 to test if the mozilla master password is correct.

## Create master password
- Install Mozilla Firefox and set a **master password** (also known as **primary password**) for saved passwords
- Find the *key4.db* file
  - macOS: ~/Library/Application Support/Firefox/Profiles/profile name/key4.db
  - Linux: ~/.mozilla/firefox/profile name/key4.db

## Build the C-program
First change the path to your mozilla firefox profile inside the c-code.
Then make sure libnss3-dev is installed and run make.

    gdb testnss
    (gdb) start
    (gdb) n
    (gdb) n
    (gdb) n
    (gdb) n
    (gdb) print *slot
