C Array List
============

C Array List


A dynamic array type for C.
A dynamic array is one which begins life at a given size (n), allocated
to hold space for n elements. After n elements have been added, and you
are adding the n+1 element, the dynamic array will efficiently resize
itself to accommodate the extra element defined 'efficiently' as log(n). I.e., once new space
is needed, the allocated space is doubled. For those of you
familiar with C++ or Java, this type of data structure is known as
a vector (C++) or an ArrayList (Java). 

Error handling functionality via return codes from all ArrayList functions.

Speed test included for large values of inserts to show C efficiency.
