---Disclaimer---
I guess this program could be made more efficient/elegant in some places. A few more security checks would probably also be nice. I just wanted a quick solution. If you add anything sensible, let me know ;-).
------

This is a program to check if you have won something in the Taiwanese lottery.
	 	
---How it works---
Using your favorite text editor (emacs, vim, Excel, …) you write the correct numbers in a .csv file. Note that you can always get the correct numbers from
	  
http://service.etax.nat.gov.tw/etwmain/front/ETW183W6

Lets call the file containing the correct numbers 'correctNumbers.csv' from now on. Please write the from top to bottom as they appear on the website or else the program won't work. That is, the order should be 
	 	  	  	   			  	  		  
Special prize
Grand prize
First prize 1
First prize 2		
First prize 3
Additional sixth prize 1
Additional sixth prize 2	
Additional sixth prize 3	
Additional sixth prize 4	

An example of such a file would be:

//Beginning of file//
01099147
55517602
16246076
78369053
06816904
021
398
991
028
//End of file//

In a similar fashion you write the numbers from your 7-11/OK-Mart/Hi-Life tickets into a file. We will call this file 'yourNumbers.csv'. The file containing your numbers could look like this	  	 

42155168
54891863
...
			
No numerical characters are allowed in both files. Whitespace and tabs will be ignored.


---How to call the program--   			 
	   
After compiling the program (write me on facebook if you don't know how to do that), call it like

checkLotteryNumbers correctNumbers.csv myNumbers.csv
									   
How this works also depends on your operating system. Ask me, if you run into trouble. 
		 

That's it. I hope it will save you some time!

---Example---
The code will come with two files (testCorrectNumbers.csv and testMyNumbers.csv). Take a look at those and do some experiments if want to.
