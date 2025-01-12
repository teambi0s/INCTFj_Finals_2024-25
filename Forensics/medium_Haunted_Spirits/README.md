# Haunted Spirits

Fragments of the past linger in a ghostly vault. Can you revive their restless spirit?

### Handout 

``` MD5 hash : 29b914fbde0751c31c7a7093c9030089  ```

### Writeup

Solve Script:

```py
import zipfile
for i in range(1,501):
    file = f"{i}.zip"
    files = bytearray(open(file, 'rb').read())
    header = files[0:4]
    eocd = files[145:149]
    if header != b'PK\x03\x04':
        files[0:4] = b'PK\x03\x04'
    if eocd != b'PK\x05\x06':
        files[145:149] = b'PK\x05\x06'
    
    with open(f"fixed{i}.zip",'wb') as newfile:
        newfile.write(files)
    zip_file = zipfile.ZipFile(f"fixed{i}.zip", 'r').extractall()
    textfile = open("text.txt", 'r')
    content = textfile.read()
    print(content, end='')
```

### Flag 

```
inctfj{r3v1v3d_th3_sp1r1t_0f_br0k3n_z1p5}
```

### Author 
**```__m1m1__```**