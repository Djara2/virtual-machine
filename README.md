# virtual-machine

Making a virtual machine for the fun of it 

# Syntax 

Intel style; `instruction, destination, src1, src2, immediate` 

```
8 bits  -> instruction 
8 bits  -> destination register   
8 bits -> source register 1 
8 bits -> source register 2 
32 bits -> immediate  
```

If you want to use an immediate larger than 32 bits, *just don't.* Put the immediate in a register and use the register instructions. 
