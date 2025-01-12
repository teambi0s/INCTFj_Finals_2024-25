# Twisted Souls

These mixed souls must be separated—can you uncover the hidden message?

### Handout 
```
MD5 hash :
2db2419310ac9e918e71124fdc24e58c  chall1.png
acb744c0ece5db3809ffa0dfb6b7edd9  chall2.png
cc2f58c8206131a9cb7aab3759aef650  chall3.png
```

### Writeup
Solve script

```py
from PIL import Image
import numpy as np
image1Path = "chall1.png"
image2Path = "chall2.png"
image3Path = "chall3.png"
image1 = Image.open(image1Path)
image2 = Image.open(image2Path)
image3 = Image.open(image3Path)
buffer1 = np.asarray(image1)
buffer2 = np.asarray(image2)
diff = np.asarray(image3)
buffer3 = buffer1 + buffer2
bufferlast = diff - buffer3
differenceImage = Image.fromarray(bufferlast)
differenceImage.show()
```

### Flag 

```
inctfj{Gh0st_1n_th3_M@ch1n3}
```

### Author 
`kr4z31n`
