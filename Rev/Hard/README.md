# weird server 

### Challenge Description 
There was a breach at bi0s recently, and all we were able to recover was this weird file and a packet capture that one of our forensics agents kept running. Can you combine the knowledge from both to figure what it was doing?

### Short Writeup 
- The `client` file makes a connection to `172.23.85.106:1337`
- The server (if it exists) is expected to return a byte buffer 
- This byte buffer is decrypted on the client side and the client checks to see if the string "inctfj{}" exists in said buffer
- If yes, it prints a "success" message. Else, nothing happens 
- A .pcap file is also provided to give players the encrypted buffer they need to decrypt 

### Flag
inctfj{well_well_well_looks_like_someone_is_getting_good_at_rev! :)}

# Author 
the.m3chanic 