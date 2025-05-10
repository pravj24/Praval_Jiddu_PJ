**OVERTHEWIRE ASSIGNMENT**

Lv 0 \= ssh [bandit0@bandit.labs.overthewire.org](mailto:bandit0@bandit.labs.overthewire.org) \-p 2220  
          Password \= bandit0  
            $ exit  
Lv1 \== $ ssh [bandit1@bandit.labs.overthewire.org](mailto:bandit1@bandit.labs.overthewird.org) \-p 2220  
            $ ls   
            $ cat readme  
            $ cat ./-  
            $ exit   
Lv2 \== $ ssh [bandit2@bandit.labs.overthewire.org](mailto:bandit1@bandit.labs.overthewird.org) \-p 2220  
            $ cat ‘spaces in this filename’  
            $ exit   
Lv3 \== $ ssh [bandit3@bandit.labs.overthewire.org](mailto:bandit1@bandit.labs.overthewird.org) \-p 2220  
            $ ls \-A  
            $ cd inhere  
            $ find .  
            $ cat …Hiding-From-You  
            $ exit   
Lv4 \== $ ssh [bandit4@bandit.labs.overthewire.org](mailto:bandit1@bandit.labs.overthewird.org) \-p 2220  
            $ ls    
            $ cd inhere  
            $ find . \-type f \-exec grep \-I . {} \\; \- print  
            $ exit   
Lv5 \== $ ssh [bandit5@bandit.labs.overthewire.org](mailto:bandit1@bandit.labs.overthewird.org) \-p 2220    
            $ ls    
            $ cd inhere   
            $ find \! \-executable \-size 1033c  
            $ file ./maybehere07/.file2   
            $ cat ./maybehere07/.file2  
            $ exit  
Lv6 \== $ ssh [bandit6@bandit.labs.overthewire.org](mailto:bandit1@bandit.labs.overthewird.org) \-p 2220      
            $ cd ..  
            $ cd ..  
            $ ls  
            $ find \-user bandit7 \-group bandit6 \-size 33c  
            $ cat ./var/lib/dpkg/info/bandit7.password   
            $ exit  
Lv7 \== $ ssh [bandit7@bandit.labs.overthewire.org](mailto:bandit7@bandit.labs.overthewire.org) \- p 2220  
            $ ls  
            $ grep millionth data.txt  
            $ exit  
Lv8 \==$ ssh [bandit8@bandit.labs.overthewire.org](mailto:bandit8@bandit.labs.overthewire.org) \-p 2220  
           $ ls  
           $ sort data.txt | uniq \-c | grep 1  
            $exit

Lv9 \== $ ssh [bandit9@bandit.labs.overthewire.org](mailto:bandit9@bandit.labs.overthewire.org) \-p 2220  
            $ ls  
            $ strings \-a data.txt | grep \=  
            $ exit  
Lv10 \== $ ssh [bandit10@bandit.labs.overthewire.org](mailto:bandit9@bandit.labs.overthewire.org) \-p 2220  
              $ ls  
              $ strings data.txt | base64 \-di  
              $ exit  
Lv11 \== $ ssh [bandit11@bandit.labs.overthewire.org](mailto:bandit11@bandit.labs.overthewire.org) \-p 2220  
             $ ls  
             $ cat data.txt | tr 'a-z' 'n-za-m' | tr 'A-Z' 'N-ZA-M'  
             $ exit  
Lv12 \==$ ssh [bandit12@bandit.labs.overthewire.org](mailto:bandit12@bandit.labs.overthewire.org) \-p 2220  
             $ dir\_name=$(mktemp \-d)   
             $ cp data.txt $dir\_name  
             $ cd $dir\_name  
             $ file data.txt \# got ASCII  
             $ xxd \-r data.txt \> data2.bin  
             $ file data2.bin  
             $ mv data2.bin data2.gz && gunzip data2.gz  
             $ ls  
             $ file data2  
             $ bunzip2 data2  
             $ file data2.out  
             $ mv data2.out data3.gz && gunzip data3.gz  
             $ ls   
             $ file data3  
             $ tar \-x \-f data3  
             $ ls  
             $ file data5.bin  
             $ tar \-x \-f data5.bin  
             $ ls  
             $ file data6.bin  
             $ bunzip2 data6.bin  
             $ file data6.bin.out  
             $ tar \-xf data6.bin.out  
             $ file data8.bin  
             $ mv data8.bin data8.gz && gunzip data8.gz  
             $ file data8  
             $ cat data8  
             $ exit  
Lv 13 \== $ ssh [bandit13@bandit.labs.overthewire.org](mailto:bandit9@bandit.labs.overthewire.org) \-p 2220  
               $ ls  
               $ ssh \-i sshkey.private bandit14@bandit.labs.overthewire.org \-p 2220  
               $ cd /etc/bandit\_pass/  
               $ cat bandit14  
                $exit  
Lv 14 \==  $ ssh [bandit14@bandit.labs.overthewire.org](mailto:bandit9@bandit.labs.overthewire.org) \-p 2220  
                $ cat /etc/bandit\_pass/bandit14 | nc 127.0.0.1 30000  
                $exit  
Lv 15 \== $ ssh [bandit15@bandit.labs.overthewire.org](mailto:bandit15@bandit.labs.overthewire.org) \-p 2220  
               $ ncat \- –ssl localhost 30001  
               8xCjnmgoKbGLhHFAZlGE5Tmu4M2tKJQo  
               $ exit

     
               
            