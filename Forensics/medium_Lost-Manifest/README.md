# Lost Manifest

Legends speak of a repository that devs dare not touch, haunted by a file known only as the Lost Manifest. The ZIP inside hums with an otherworldly encryption, defying all attempts to unlock its secrets. Can you uncover the truth hidden within, or will the haunting remain unsolved?

### Handout 

``` MD5 hash : 37ca492c62aac8ba127ca0344ede7de8  ```

### Writeup

The original repository, `Lost-Manifest`, contains files similar to the ones in the encrypted ZIP. Extract a small portion of text from one of the similar files and save it as a separate file.

`echo -n "This repository was once" > plain.txt`

Use the plaintext file to run bkcrack on the encrypted ZIP file. This will recover the decryption keys required to bypass the password.

`./bkcrack -C Lost-Manifest.zip -c Lost-Manifest/manifest/history.txt -p plain.txt`

Use the recovered keys to remove the password protection and extract the contents of the ZIP

`./bkcrack -C Lost-Manifest.zip -k a8b1c969 4b4ed840 c82ab015 -D lost_manifest_recovered.zip`

Inside the decrypted ZIP file, a file named `truth.txt` contains base64-encoded text. By decoding it, flag can be obtained.


### Flag 

```
inctfj{f0und_w1th1n_th3_l05t}
```

### Author 
**```__m1m1__```**