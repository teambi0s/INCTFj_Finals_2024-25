# Joke API

### Difficulty
medium

### Challenge Description

Anyone can take a joke, but can you take a secret joke?

### Short Writeup

+ Get the public key by making use of LFI.
+ Then using the public key change the algorithm from RS to HS and then sign the key.
+ Then visit the `/jokes` endpoint to get the SECRET joke. 

### Flag

inctfj{Why_do_programmers_prefer_dark_mode?_Because_light_attracts_bugs!}

### Author

**exigent07**