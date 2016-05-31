.section .text
.globl bigint_mul_add_rshift_inplace_x2_1
.type bigint_mul_add_rshift_inplace_x2_1, @function
.globl bigint_mul_add_rshift_inplace_x2_2
.type bigint_mul_add_rshift_inplace_x2_2, @function
.globl bigint_mul_add_rshift_inplace_x2_3
.type bigint_mul_add_rshift_inplace_x2_3, @function
.globl bigint_mul_add_rshift_inplace_x2_4
.type bigint_mul_add_rshift_inplace_x2_4, @function
.globl bigint_mul_add_rshift_inplace_x2_5
.type bigint_mul_add_rshift_inplace_x2_5, @function
.globl bigint_mul_add_rshift_inplace_x2_6
.type bigint_mul_add_rshift_inplace_x2_6, @function
.globl bigint_mul_add_rshift_inplace_x2_7
.type bigint_mul_add_rshift_inplace_x2_7, @function
.globl bigint_mul_add_rshift_inplace_x2_8
.type bigint_mul_add_rshift_inplace_x2_8, @function
.globl bigint_mul_add_rshift_inplace_x2_9
.type bigint_mul_add_rshift_inplace_x2_9, @function
.globl bigint_mul_add_rshift_inplace_x2_10
.type bigint_mul_add_rshift_inplace_x2_10, @function

bigint_mul_add_rshift_inplace_x2_1:
        pushq     %rbp                                          #202.1
        movq      %rdx, %rax                                    #202.1
        movq      __bigint_buffer(%rip), %r10                   #202.1
        testq     %rax, %rax                                    #202.1
        je        ..B1.5        # Prob 50%                      #202.1
        testq     %r8, %r8                                      #202.1
        je        ..B1.4        # Prob 50%                      #202.1
        movq      32(%rsi), %rdx                                #202.1
        xorl      %ebp, %ebp                                    #202.1
        xorl      %esi, %esi                                    #202.1
        mulx      %rax, %r11, %r9                               #202.1
        movl      %ebp, %eax                                    #202.1
        adcx      32(%rdi), %r9                                 #202.1
        movl      $0, %esi                                      #202.1
        movq      %r9, 2272(%r10)                               #202.1
        adox      %ebp, %eax                                    #202.1
        movl      %ebp, %eax                                    #202.1
        adox      %rsi, %r11                                    #202.1
        adcx      40(%rdi), %r11                                #202.1
        movq      %r11, 2280(%r10)                              #202.1
        movl      %ebp, %r10d                                   #202.1
        setb      %al                                           #202.1
        clc                                                     #202.1
        movq      32(%rcx), %rdx                                #202.1
        mulx      %r8, %rdx, %rcx                               #202.1
        movl      %ebp, %r8d                                    #202.1
        adcx      %rcx, %r9                                     #202.1
        adox      %ebp, %r8d                                    #202.1
        adox      %rsi, %rdx                                    #202.1
        seto      %r10b                                         #202.1
        adcx      %rdx, %r11                                    #202.1
        movq      %r11, 32(%rdi)                                #202.1
        setb      %bpl                                          #202.1
        addq      48(%rdi), %rax                                #202.1
        addq      %rbp, %rax                                    #202.1
        movq      %rax, 40(%rdi)                                #202.1
        movq      %rsi, 48(%rdi)                                #202.1
        popq      %rbp                                          #202.1
        ret                                                     #202.1
..B1.4:                         # Preds ..B1.2
        movq      32(%rsi), %rdx                                #202.1
        xorl      %r9d, %r9d                                    #202.1
        mulx      %rax, %r10, %rcx                              #202.1
        xorl      %ebp, %ebp                                    #202.1
        xorl      %esi, %esi                                    #202.1
        xorl      %r8d, %r8d                                    #202.1
        xorl      %eax, %eax                                    #202.1
        adcx      32(%rdi), %rcx                                #202.1
        movq      40(%rdi), %r11                                #202.1
        adox      %r9d, %ebp                                    #202.1
        adox      %rsi, %r10                                    #202.1
        seto      %r8b                                          #202.1
        adcx      %r11, %r10                                    #202.1
        movq      %r10, 32(%rdi)                                #202.1
        setb      %r9b                                          #202.1
        addq      %r9, %r11                                     #202.1
        movq      %r11, 40(%rdi)                                #202.1
        popq      %rbp                                          #202.1
        ret                                                     #202.1
..B1.5:                         # Preds ..B1.1
        testq     %r8, %r8                                      #202.1
        je        ..B1.7        # Prob 50%                      #202.1
        movq      32(%rcx), %rdx                                #202.1
        xorl      %r9d, %r9d                                    #202.1
        xorl      %ebp, %ebp                                    #202.1
        xorl      %esi, %esi                                    #202.1
        xorl      %eax, %eax                                    #202.1
        mulx      %r8, %r10, %rcx                               #202.1
        adcx      32(%rdi), %rcx                                #202.1
        movl      %r9d, %r8d                                    #202.1
        movq      40(%rdi), %r11                                #202.1
        adox      %r9d, %ebp                                    #202.1
        adox      %rsi, %r10                                    #202.1
        seto      %r8b                                          #202.1
        adcx      %r11, %r10                                    #202.1
        movq      %r10, 32(%rdi)                                #202.1
        setb      %r9b                                          #202.1
        addq      %r9, %r11                                     #202.1
        movq      %r11, 40(%rdi)                                #202.1
        popq      %rbp                                          #202.1
        ret                                                     #202.1
..B1.7:                         # Preds ..B1.5
        movq      40(%rdi), %rax                                #202.1
        movq      48(%rdi), %rdx                                #202.1
        movq      %rax, 32(%rdi)                                #202.1
        movq      %rdx, 40(%rdi)                                #202.1
        movq      $0, 48(%rdi)                                  #202.1
        popq      %rbp                                          #202.1
        ret                                                     #202.1
bigint_mul_add_rshift_inplace_x2_2:
        pushq     %r14                                          #203.1
        pushq     %rbp                                          #203.1
        movq      %rdx, %rax                                    #203.1
        movq      __bigint_buffer(%rip), %r10                   #203.1
        testq     %rax, %rax                                    #203.1
        je        ..B2.5        # Prob 50%                      #203.1
        testq     %r8, %r8                                      #203.1
        je        ..B2.4        # Prob 50%                      #203.1
        movq      32(%rsi), %rdx                                #203.1
        xorl      %ebp, %ebp                                    #203.1
        xorl      %r9d, %r9d                                    #203.1
        mulx      %rax, %r11, %r14                              #203.1
        movl      $0, %r9d                                      #203.1
        adcx      32(%rdi), %r14                                #203.1
        movq      %r14, 2272(%r10)                              #203.1
        movq      40(%rsi), %rdx                                #203.1
        movl      %ebp, %esi                                    #203.1
        adox      %ebp, %esi                                    #203.1
        mulx      %rax, %rax, %rdx                              #203.1
        adox      %rdx, %r11                                    #203.1
        adcx      40(%rdi), %r11                                #203.1
        movq      %r11, 2280(%r10)                              #203.1
        adox      %r9, %rax                                     #203.1
        adcx      48(%rdi), %rax                                #203.1
        movl      %ebp, %esi                                    #203.1
        movq      %rax, 2288(%r10)                              #203.1
        setb      %sil                                          #203.1
        clc                                                     #203.1
        movq      32(%rcx), %rdx                                #203.1
        mulx      %r8, %rax, %rdx                               #203.1
        adcx      %rdx, %r14                                    #203.1
        movq      40(%rcx), %rdx                                #203.1
        mulx      %r8, %rcx, %rdx                               #203.1
        movl      %ebp, %r8d                                    #203.1
        adox      %ebp, %r8d                                    #203.1
        adox      %rdx, %rax                                    #203.1
        adcx      %rax, %r11                                    #203.1
        movl      %ebp, %eax                                    #203.1
        movq      %r11, 32(%rdi)                                #203.1
        adox      %r9, %rcx                                     #203.1
        seto      %al                                           #203.1
        adcx      2288(%r10), %rcx                              #203.1
        movq      %rcx, 40(%rdi)                                #203.1
        setb      %bpl                                          #203.1
        addq      56(%rdi), %rsi                                #203.1
        addq      %rbp, %rsi                                    #203.1
        movq      %rsi, 48(%rdi)                                #203.1
        movq      %r9, 56(%rdi)                                 #203.1
        popq      %rbp                                          #203.1
        popq      %r14                                          #203.1
        ret                                                     #203.1
..B2.4:                         # Preds ..B2.2
        movq      32(%rsi), %rdx                                #203.1
        xorl      %r11d, %r11d                                  #203.1
        xorl      %r9d, %r9d                                    #203.1
        xorl      %r10d, %r10d                                  #203.1
        xorl      %ecx, %ecx                                    #203.1
        mulx      %rax, %r8, %rbp                               #203.1
        adcx      32(%rdi), %rbp                                #203.1
        movq      40(%rsi), %rdx                                #203.1
        mulx      %rax, %r14, %rsi                              #203.1
        movl      %r11d, %eax                                   #203.1
        adox      %r11d, %eax                                   #203.1
        movq      48(%rdi), %rax                                #203.1
        adox      %rsi, %r8                                     #203.1
        adcx      40(%rdi), %r8                                 #203.1
        movq      %r8, 32(%rdi)                                 #203.1
        adox      %r9, %r14                                     #203.1
        seto      %r10b                                         #203.1
        adcx      %rax, %r14                                    #203.1
        movq      %r14, 40(%rdi)                                #203.1
        setb      %r11b                                         #203.1
        addq      %r11, %rax                                    #203.1
        movq      %rax, 48(%rdi)                                #203.1
        popq      %rbp                                          #203.1
        popq      %r14                                          #203.1
        ret                                                     #203.1
..B2.5:                         # Preds ..B2.1
        testq     %r8, %r8                                      #203.1
        je        ..B2.7        # Prob 50%                      #203.1
        movq      32(%rcx), %rdx                                #203.1
        xorl      %r11d, %r11d                                  #203.1
        xorl      %r9d, %r9d                                    #203.1
        xorl      %r10d, %r10d                                  #203.1
        xorl      %eax, %eax                                    #203.1
        mulx      %r8, %rsi, %rbp                               #203.1
        adcx      32(%rdi), %rbp                                #203.1
        movq      40(%rcx), %rdx                                #203.1
        movl      %r11d, %ecx                                   #203.1
        adox      %r11d, %ecx                                   #203.1
        mulx      %r8, %r14, %r8                                #203.1
        adox      %r8, %rsi                                     #203.1
        movq      48(%rdi), %rax                                #203.1
        adcx      40(%rdi), %rsi                                #203.1
        movq      %rsi, 32(%rdi)                                #203.1
        adox      %r9, %r14                                     #203.1
        seto      %r10b                                         #203.1
        adcx      %rax, %r14                                    #203.1
        movq      %r14, 40(%rdi)                                #203.1
        setb      %r11b                                         #203.1
        addq      %r11, %rax                                    #203.1
        movq      %rax, 48(%rdi)                                #203.1
        popq      %rbp                                          #203.1
        popq      %r14                                          #203.1
        ret                                                     #203.1
..B2.7:                         # Preds ..B2.5
        movq      40(%rdi), %rax                                #203.1
        movq      48(%rdi), %rdx                                #203.1
        movq      56(%rdi), %rcx                                #203.1
        movq      %rax, 32(%rdi)                                #203.1
        movq      %rdx, 40(%rdi)                                #203.1
        movq      %rcx, 48(%rdi)                                #203.1
        movq      $0, 56(%rdi)                                  #203.1
        popq      %rbp                                          #203.1
        popq      %r14                                          #203.1
        ret                                                     #203.1
bigint_mul_add_rshift_inplace_x2_3:
        pushq     %r12                                          #204.1
        pushq     %r14                                          #204.1
        pushq     %rbx                                          #204.1
        movq      %rdx, %rax                                    #204.1
        movq      __bigint_buffer(%rip), %r11                   #204.1
        testq     %rax, %rax                                    #204.1
        je        ..B3.5        # Prob 50%                      #204.1
        testq     %r8, %r8                                      #204.1
        je        ..B3.4        # Prob 50%                      #204.1
        movq      32(%rsi), %rdx                                #204.1
        xorl      %r14d, %r14d                                  #204.1
        xorl      %r12d, %r12d                                  #204.1
        mulx      %rax, %r10, %r9                               #204.1
        adcx      32(%rdi), %r9                                 #204.1
        movq      %r9, 2272(%r11)                               #204.1
        adox      %r12d, %r14d                                  #204.1
        movq      40(%rsi), %rdx                                #204.1
        mulx      %rax, %rbx, %rdx                              #204.1
        adox      %rdx, %r10                                    #204.1
        adcx      40(%rdi), %r10                                #204.1
        movq      %r10, 2280(%r11)                              #204.1
        movq      48(%rsi), %rdx                                #204.1
        mulx      %rax, %rsi, %rax                              #204.1
        adox      %rax, %rbx                                    #204.1
        movl      $0, %eax                                      #204.1
        adcx      48(%rdi), %rbx                                #204.1
        movq      %rbx, 2288(%r11)                              #204.1
        adox      %rax, %rsi                                    #204.1
        adcx      56(%rdi), %rsi                                #204.1
        movl      %r12d, %ebx                                   #204.1
        movq      %rsi, 2296(%r11)                              #204.1
        setb      %bl                                           #204.1
        clc                                                     #204.1
        movq      32(%rcx), %rdx                                #204.1
        mulx      %r8, %r14, %rsi                               #204.1
        adcx      %rsi, %r9                                     #204.1
        movl      %r12d, %r9d                                   #204.1
        adox      %r12d, %r9d                                   #204.1
        movq      40(%rcx), %rdx                                #204.1
        mulx      %r8, %rsi, %rdx                               #204.1
        adox      %rdx, %r14                                    #204.1
        adcx      %r14, %r10                                    #204.1
        movq      %r10, 32(%rdi)                                #204.1
        movq      48(%rcx), %rdx                                #204.1
        mulx      %r8, %rdx, %rcx                               #204.1
        movl      %r12d, %r8d                                   #204.1
        adox      %rcx, %rsi                                    #204.1
        adcx      2288(%r11), %rsi                              #204.1
        movq      %rsi, 40(%rdi)                                #204.1
        adox      %rax, %rdx                                    #204.1
        seto      %r8b                                          #204.1
        adcx      2296(%r11), %rdx                              #204.1
        movq      %rdx, 48(%rdi)                                #204.1
        setb      %r12b                                         #204.1
        addq      64(%rdi), %rbx                                #204.1
        addq      %r12, %rbx                                    #204.1
        movq      %rbx, 56(%rdi)                                #204.1
        movq      %rax, 64(%rdi)                                #204.1
        jmp       ..B3.8        # Prob 100%                     #204.1
..B3.4:                         # Preds ..B3.2
        movq      32(%rsi), %rdx                                #204.1
        xorl      %ecx, %ecx                                    #204.1
        xorl      %r8d, %r8d                                    #204.1
        xorl      %r12d, %r12d                                  #204.1
        xorl      %r10d, %r10d                                  #204.1
        mulx      %rax, %r9, %r11                               #204.1
        adcx      32(%rdi), %r11                                #204.1
        movq      40(%rdi), %r10                                #204.1
        adcx      %rcx, %r10                                    #204.1
        movq      40(%rsi), %rdx                                #204.1
        adox      %r8d, %r12d                                   #204.1
        mulx      %rax, %rbx, %r14                              #204.1
        adox      %r14, %r9                                     #204.1
        movq      %r10, 32(%rdi)                                #204.1
        adcx      48(%rdi), %r9                                 #204.1
        movq      48(%rsi), %rdx                                #204.1
        movl      %r8d, %esi                                    #204.1
        mulx      %rax, %rdx, %rax                              #204.1
        adox      %rax, %rbx                                    #204.1
        movq      56(%rdi), %rax                                #204.1
        adox      %rcx, %rdx                                    #204.1
        movq      %r9, 40(%rdi)                                 #204.1
        seto      %sil                                          #204.1
        adcx      %rax, %rdx                                    #204.1
        movq      %rdx, 48(%rdi)                                #204.1
        setb      %r8b                                          #204.1
        addq      %r8, %rax                                     #204.1
        movq      %rax, 56(%rdi)                                #204.1
        jmp       ..B3.8        # Prob 100%                     #204.1
..B3.5:                         # Preds ..B3.1
        testq     %r8, %r8                                      #204.1
        je        ..B3.7        # Prob 50%                      #204.1
        movq      32(%rcx), %rdx                                #204.1
        xorl      %eax, %eax                                    #204.1
        xorl      %esi, %esi                                    #204.1
        xorl      %r12d, %r12d                                  #204.1
        xorl      %r10d, %r10d                                  #204.1
        mulx      %r8, %r9, %r11                                #204.1
        adcx      32(%rdi), %r11                                #204.1
        movq      40(%rdi), %r10                                #204.1
        adcx      %rax, %r10                                    #204.1
        movq      40(%rcx), %rdx                                #204.1
        adox      %esi, %r12d                                   #204.1
        mulx      %r8, %rbx, %r14                               #204.1
        adox      %r14, %r9                                     #204.1
        movq      %r10, 32(%rdi)                                #204.1
        adcx      48(%rdi), %r9                                 #204.1
        movq      48(%rcx), %rdx                                #204.1
        mulx      %r8, %rdx, %rcx                               #204.1
        movl      %esi, %r8d                                    #204.1
        adox      %rcx, %rbx                                    #204.1
        movq      %r9, 40(%rdi)                                 #204.1
        adox      %rax, %rdx                                    #204.1
        movq      56(%rdi), %rax                                #204.1
        seto      %r8b                                          #204.1
        adcx      %rax, %rdx                                    #204.1
        movq      %rdx, 48(%rdi)                                #204.1
        setb      %sil                                          #204.1
        addq      %rsi, %rax                                    #204.1
        movq      %rax, 56(%rdi)                                #204.1
        jmp       ..B3.8        # Prob 100%                     #204.1
..B3.7:                         # Preds ..B3.5
        vmovdqu   40(%rdi), %ymm0                               #204.1
        vmovdqu   %ymm0, 32(%rdi)                               #204.1
        movq      $0, 64(%rdi)                                  #204.1
..B3.8:                         # Preds ..B3.4 ..B3.6 ..B3.7 ..B3.3
        vzeroupper                                              #204.1
        popq      %rbx                                          #204.1
        popq      %r14                                          #204.1
        popq      %r12                                          #204.1
        ret                                                     #204.1
bigint_mul_add_rshift_inplace_x2_4:
        pushq     %r13                                          #205.1
        pushq     %r15                                          #205.1
        pushq     %rbx                                          #205.1
        movq      %rdx, %rax                                    #205.1
        movq      __bigint_buffer(%rip), %rbx                   #205.1
        testq     %rax, %rax                                    #205.1
        je        ..B4.5        # Prob 50%                      #205.1
        testq     %r8, %r8                                      #205.1
        je        ..B4.4        # Prob 50%                      #205.1
        movq      32(%rsi), %rdx                                #205.1
        xorl      %r13d, %r13d                                  #205.1
        xorl      %r10d, %r10d                                  #205.1
        mulx      %rax, %r11, %r9                               #205.1
        adcx      32(%rdi), %r9                                 #205.1
        movq      %r9, 2272(%rbx)                               #205.1
        adox      %r10d, %r13d                                  #205.1
        movq      40(%rsi), %rdx                                #205.1
        mulx      %rax, %r15, %rdx                              #205.1
        adox      %rdx, %r11                                    #205.1
        adcx      40(%rdi), %r11                                #205.1
        movq      %r11, 2280(%rbx)                              #205.1
        movq      48(%rsi), %rdx                                #205.1
        mulx      %rax, %r13, %rdx                              #205.1
        adox      %rdx, %r15                                    #205.1
        adcx      48(%rdi), %r15                                #205.1
        movq      %r15, 2288(%rbx)                              #205.1
        movq      56(%rsi), %rdx                                #205.1
        mulx      %rax, %rdx, %rsi                              #205.1
        adox      %rsi, %r13                                    #205.1
        movl      $0, %esi                                      #205.1
        adcx      56(%rdi), %r13                                #205.1
        movq      %r13, 2296(%rbx)                              #205.1
        adox      %rsi, %rdx                                    #205.1
        adcx      64(%rdi), %rdx                                #205.1
        movl      %r10d, %eax                                   #205.1
        movq      %rdx, 2304(%rbx)                              #205.1
        setb      %al                                           #205.1
        clc                                                     #205.1
        movq      32(%rcx), %rdx                                #205.1
        mulx      %r8, %r13, %r15                               #205.1
        adcx      %r15, %r9                                     #205.1
        movq      40(%rcx), %rdx                                #205.1
        mulx      %r8, %r9, %r15                                #205.1
        movl      %r10d, %edx                                   #205.1
        adox      %r10d, %edx                                   #205.1
        adox      %r15, %r13                                    #205.1
        adcx      %r13, %r11                                    #205.1
        movq      %r11, 32(%rdi)                                #205.1
        movq      48(%rcx), %rdx                                #205.1
        mulx      %r8, %r15, %r11                               #205.1
        adox      %r11, %r9                                     #205.1
        adcx      2288(%rbx), %r9                               #205.1
        movq      %r9, 40(%rdi)                                 #205.1
        movq      56(%rcx), %rdx                                #205.1
        mulx      %r8, %rdx, %rcx                               #205.1
        movl      %r10d, %r8d                                   #205.1
        adox      %rcx, %r15                                    #205.1
        adcx      2296(%rbx), %r15                              #205.1
        movq      %r15, 48(%rdi)                                #205.1
        adox      %rsi, %rdx                                    #205.1
        seto      %r8b                                          #205.1
        adcx      2304(%rbx), %rdx                              #205.1
        movq      %rdx, 56(%rdi)                                #205.1
        setb      %r10b                                         #205.1
        addq      72(%rdi), %rax                                #205.1
        addq      %r10, %rax                                    #205.1
        movq      %rax, 64(%rdi)                                #205.1
        movq      %rsi, 72(%rdi)                                #205.1
        jmp       ..B4.8        # Prob 100%                     #205.1
..B4.4:                         # Preds ..B4.2
        movq      32(%rsi), %rdx                                #205.1
        xorl      %ebx, %ebx                                    #205.1
        xorl      %r8d, %r8d                                    #205.1
        xorl      %r13d, %r13d                                  #205.1
        xorl      %r10d, %r10d                                  #205.1
        mulx      %rax, %r9, %r11                               #205.1
        adcx      32(%rdi), %r11                                #205.1
        movq      40(%rdi), %r10                                #205.1
        adcx      %rbx, %r10                                    #205.1
        movq      40(%rsi), %rdx                                #205.1
        adox      %r8d, %r13d                                   #205.1
        mulx      %rax, %rcx, %r15                              #205.1
        adox      %r15, %r9                                     #205.1
        movq      %r10, 32(%rdi)                                #205.1
        adcx      48(%rdi), %r9                                 #205.1
        movq      48(%rsi), %rdx                                #205.1
        mulx      %rax, %r13, %r11                              #205.1
        adox      %r11, %rcx                                    #205.1
        movq      %r9, 40(%rdi)                                 #205.1
        adcx      56(%rdi), %rcx                                #205.1
        movq      56(%rsi), %rdx                                #205.1
        movl      %r8d, %esi                                    #205.1
        mulx      %rax, %rdx, %rax                              #205.1
        adox      %rax, %r13                                    #205.1
        movq      64(%rdi), %rax                                #205.1
        adox      %rbx, %rdx                                    #205.1
        movq      %rcx, 48(%rdi)                                #205.1
        seto      %sil                                          #205.1
        adcx      %rax, %rdx                                    #205.1
        movq      %rdx, 56(%rdi)                                #205.1
        setb      %r8b                                          #205.1
        addq      %r8, %rax                                     #205.1
        movq      %rax, 64(%rdi)                                #205.1
        jmp       ..B4.8        # Prob 100%                     #205.1
..B4.5:                         # Preds ..B4.1
        testq     %r8, %r8                                      #205.1
        je        ..B4.7        # Prob 50%                      #205.1
        movq      32(%rcx), %rdx                                #205.1
        xorl      %ebx, %ebx                                    #205.1
        xorl      %esi, %esi                                    #205.1
        xorl      %r13d, %r13d                                  #205.1
        xorl      %r10d, %r10d                                  #205.1
        mulx      %r8, %r9, %r11                                #205.1
        adcx      32(%rdi), %r11                                #205.1
        movq      40(%rdi), %r10                                #205.1
        adcx      %rbx, %r10                                    #205.1
        movq      40(%rcx), %rdx                                #205.1
        adox      %esi, %r13d                                   #205.1
        mulx      %r8, %rax, %r15                               #205.1
        adox      %r15, %r9                                     #205.1
        movq      %r10, 32(%rdi)                                #205.1
        adcx      48(%rdi), %r9                                 #205.1
        movq      48(%rcx), %rdx                                #205.1
        mulx      %r8, %r11, %rdx                               #205.1
        adox      %rdx, %rax                                    #205.1
        movq      %r9, 40(%rdi)                                 #205.1
        adcx      56(%rdi), %rax                                #205.1
        movq      56(%rcx), %rdx                                #205.1
        mulx      %r8, %rdx, %rcx                               #205.1
        movl      %esi, %r8d                                    #205.1
        adox      %rcx, %r11                                    #205.1
        movq      %rax, 48(%rdi)                                #205.1
        adox      %rbx, %rdx                                    #205.1
        movq      64(%rdi), %rax                                #205.1
        seto      %r8b                                          #205.1
        adcx      %rax, %rdx                                    #205.1
        movq      %rdx, 56(%rdi)                                #205.1
        setb      %sil                                          #205.1
        addq      %rsi, %rax                                    #205.1
        movq      %rax, 64(%rdi)                                #205.1
        jmp       ..B4.8        # Prob 100%                     #205.1
..B4.7:                         # Preds ..B4.5
        vmovdqu   40(%rdi), %ymm0                               #205.1
        movq      72(%rdi), %rax                                #205.1
        vmovdqu   %ymm0, 32(%rdi)                               #205.1
        movq      %rax, 64(%rdi)                                #205.1
        movq      $0, 72(%rdi)                                  #205.1
..B4.8:                         # Preds ..B4.4 ..B4.6 ..B4.7 ..B4.3
        vzeroupper                                              #205.1
        popq      %rbx                                          #205.1
        popq      %r15                                          #205.1
        popq      %r13                                          #205.1
        ret                                                     #205.1
bigint_mul_add_rshift_inplace_x2_5:
        pushq     %r13                                          #206.1
        pushq     %r14                                          #206.1
        pushq     %rbx                                          #206.1
        movq      %rdx, %r11                                    #206.1
        movq      __bigint_buffer(%rip), %rbx                   #206.1
        testq     %r11, %r11                                    #206.1
        je        ..B5.5        # Prob 50%                      #206.1
        testq     %r8, %r8                                      #206.1
        je        ..B5.4        # Prob 50%                      #206.1
        movq      32(%rsi), %rdx                                #206.1
        xorl      %r13d, %r13d                                  #206.1
        xorl      %eax, %eax                                    #206.1
        mulx      %r11, %r10, %r9                               #206.1
        adcx      32(%rdi), %r9                                 #206.1
        movq      %r9, 2272(%rbx)                               #206.1
        adox      %eax, %r13d                                   #206.1
        movq      40(%rsi), %rdx                                #206.1
        mulx      %r11, %r14, %rdx                              #206.1
        adox      %rdx, %r10                                    #206.1
        adcx      40(%rdi), %r10                                #206.1
        movq      %r10, 2280(%rbx)                              #206.1
        movq      48(%rsi), %rdx                                #206.1
        mulx      %r11, %r13, %rdx                              #206.1
        adox      %rdx, %r14                                    #206.1
        adcx      48(%rdi), %r14                                #206.1
        movq      %r14, 2288(%rbx)                              #206.1
        movq      56(%rsi), %rdx                                #206.1
        mulx      %r11, %r14, %rdx                              #206.1
        adox      %rdx, %r13                                    #206.1
        adcx      56(%rdi), %r13                                #206.1
        movq      %r13, 2296(%rbx)                              #206.1
        movq      64(%rsi), %rdx                                #206.1
        mulx      %r11, %rdx, %r11                              #206.1
        adox      %r11, %r14                                    #206.1
        movl      $0, %r11d                                     #206.1
        adcx      64(%rdi), %r14                                #206.1
        movq      %r14, 2304(%rbx)                              #206.1
        adox      %r11, %rdx                                    #206.1
        adcx      72(%rdi), %rdx                                #206.1
        movl      %eax, %esi                                    #206.1
        movq      %rdx, 2312(%rbx)                              #206.1
        setb      %sil                                          #206.1
        clc                                                     #206.1
        movq      32(%rcx), %rdx                                #206.1
        mulx      %r8, %r13, %r14                               #206.1
        adcx      %r14, %r9                                     #206.1
        movl      %eax, %r9d                                    #206.1
        adox      %eax, %r9d                                    #206.1
        movq      40(%rcx), %rdx                                #206.1
        mulx      %r8, %r14, %rdx                               #206.1
        adox      %rdx, %r13                                    #206.1
        adcx      %r13, %r10                                    #206.1
        movq      %r10, 32(%rdi)                                #206.1
        movq      48(%rcx), %rdx                                #206.1
        mulx      %r8, %r9, %r10                                #206.1
        adox      %r10, %r14                                    #206.1
        adcx      2288(%rbx), %r14                              #206.1
        movq      %r14, 40(%rdi)                                #206.1
        movq      56(%rcx), %rdx                                #206.1
        mulx      %r8, %r10, %r13                               #206.1
        adox      %r13, %r9                                     #206.1
        adcx      2296(%rbx), %r9                               #206.1
        movq      %r9, 48(%rdi)                                 #206.1
        movq      64(%rcx), %rdx                                #206.1
        mulx      %r8, %rdx, %rcx                               #206.1
        movl      %eax, %r8d                                    #206.1
        adox      %rcx, %r10                                    #206.1
        adcx      2304(%rbx), %r10                              #206.1
        movq      %r10, 56(%rdi)                                #206.1
        adox      %r11, %rdx                                    #206.1
        seto      %r8b                                          #206.1
        adcx      2312(%rbx), %rdx                              #206.1
        movq      %rdx, 64(%rdi)                                #206.1
        setb      %al                                           #206.1
        addq      80(%rdi), %rsi                                #206.1
        addq      %rax, %rsi                                    #206.1
        movq      %rsi, 72(%rdi)                                #206.1
        movq      %r11, 80(%rdi)                                #206.1
        jmp       ..B5.8        # Prob 100%                     #206.1
..B5.4:                         # Preds ..B5.2
        movq      32(%rsi), %rdx                                #206.1
        xorl      %ebx, %ebx                                    #206.1
        xorl      %r8d, %r8d                                    #206.1
        xorl      %r14d, %r14d                                  #206.1
        xorl      %r10d, %r10d                                  #206.1
        mulx      %r11, %r9, %r13                               #206.1
        adcx      32(%rdi), %r13                                #206.1
        movq      40(%rdi), %r10                                #206.1
        adcx      %rbx, %r10                                    #206.1
        movq      40(%rsi), %rdx                                #206.1
        adox      %r8d, %r14d                                   #206.1
        mulx      %r11, %rcx, %rax                              #206.1
        adox      %rax, %r9                                     #206.1
        movq      %r10, 32(%rdi)                                #206.1
        adcx      48(%rdi), %r9                                 #206.1
        movq      48(%rsi), %rdx                                #206.1
        mulx      %r11, %rax, %r13                              #206.1
        adox      %r13, %rcx                                    #206.1
        movq      %r9, 40(%rdi)                                 #206.1
        adcx      56(%rdi), %rcx                                #206.1
        movq      56(%rsi), %rdx                                #206.1
        mulx      %r11, %r10, %r9                               #206.1
        adox      %r9, %rax                                     #206.1
        movq      %rcx, 48(%rdi)                                #206.1
        adcx      64(%rdi), %rax                                #206.1
        movq      64(%rsi), %rdx                                #206.1
        mulx      %r11, %rdx, %rsi                              #206.1
        movl      %r8d, %r11d                                   #206.1
        adox      %rsi, %r10                                    #206.1
        movq      %rax, 56(%rdi)                                #206.1
        adox      %rbx, %rdx                                    #206.1
        movq      72(%rdi), %rax                                #206.1
        seto      %r11b                                         #206.1
        adcx      %rax, %rdx                                    #206.1
        movq      %rdx, 64(%rdi)                                #206.1
        setb      %r8b                                          #206.1
        addq      %r8, %rax                                     #206.1
        movq      %rax, 72(%rdi)                                #206.1
        jmp       ..B5.8        # Prob 100%                     #206.1
..B5.5:                         # Preds ..B5.1
        testq     %r8, %r8                                      #206.1
        je        ..B5.7        # Prob 50%                      #206.1
        movq      32(%rcx), %rdx                                #206.1
        xorl      %esi, %esi                                    #206.1
        xorl      %r9d, %r9d                                    #206.1
        xorl      %r14d, %r14d                                  #206.1
        xorl      %r11d, %r11d                                  #206.1
        mulx      %r8, %r10, %r13                               #206.1
        adcx      32(%rdi), %r13                                #206.1
        movq      40(%rdi), %r11                                #206.1
        adcx      %rsi, %r11                                    #206.1
        movq      40(%rcx), %rdx                                #206.1
        adox      %r9d, %r14d                                   #206.1
        mulx      %r8, %rbx, %rax                               #206.1
        adox      %rax, %r10                                    #206.1
        movq      %r11, 32(%rdi)                                #206.1
        adcx      48(%rdi), %r10                                #206.1
        movq      48(%rcx), %rdx                                #206.1
        mulx      %r8, %rax, %rdx                               #206.1
        adox      %rdx, %rbx                                    #206.1
        movq      %r10, 40(%rdi)                                #206.1
        adcx      56(%rdi), %rbx                                #206.1
        movq      56(%rcx), %rdx                                #206.1
        mulx      %r8, %r13, %r10                               #206.1
        adox      %r10, %rax                                    #206.1
        movq      %rbx, 48(%rdi)                                #206.1
        adcx      64(%rdi), %rax                                #206.1
        movq      64(%rcx), %rdx                                #206.1
        mulx      %r8, %rdx, %rcx                               #206.1
        movl      %r9d, %r8d                                    #206.1
        adox      %rcx, %r13                                    #206.1
        movq      %rax, 56(%rdi)                                #206.1
        adox      %rsi, %rdx                                    #206.1
        movq      72(%rdi), %rax                                #206.1
        seto      %r8b                                          #206.1
        adcx      %rax, %rdx                                    #206.1
        movq      %rdx, 64(%rdi)                                #206.1
        setb      %r9b                                          #206.1
        addq      %r9, %rax                                     #206.1
        movq      %rax, 72(%rdi)                                #206.1
        jmp       ..B5.8        # Prob 100%                     #206.1
..B5.7:                         # Preds ..B5.5
        vmovdqu   40(%rdi), %ymm0                               #206.1
        movq      72(%rdi), %rax                                #206.1
        movq      80(%rdi), %rdx                                #206.1
        vmovdqu   %ymm0, 32(%rdi)                               #206.1
        movq      %rax, 64(%rdi)                                #206.1
        movq      %rdx, 72(%rdi)                                #206.1
        movq      $0, 80(%rdi)                                  #206.1
..B5.8:                         # Preds ..B5.4 ..B5.6 ..B5.7 ..B5.3
        vzeroupper                                              #206.1
        popq      %rbx                                          #206.1
        popq      %r14                                          #206.1
        popq      %r13                                          #206.1
        ret                                                     #206.1
bigint_mul_add_rshift_inplace_x2_6:
        pushq     %r12                                          #207.1
        pushq     %r13                                          #207.1
        pushq     %rbx                                          #207.1
        movq      %rdx, %rax                                    #207.1
        movq      __bigint_buffer(%rip), %r10                   #207.1
        testq     %rax, %rax                                    #207.1
        je        ..B6.5        # Prob 50%                      #207.1
        testq     %r8, %r8                                      #207.1
        je        ..B6.4        # Prob 50%                      #207.1
        movq      32(%rsi), %rdx                                #207.1
        xorl      %r13d, %r13d                                  #207.1
        xorl      %r11d, %r11d                                  #207.1
        mulx      %rax, %r9, %r12                               #207.1
        adcx      32(%rdi), %r12                                #207.1
        movq      %r12, 2272(%r10)                              #207.1
        adox      %r11d, %r13d                                  #207.1
        movq      40(%rsi), %rdx                                #207.1
        mulx      %rax, %rbx, %rdx                              #207.1
        adox      %rdx, %r9                                     #207.1
        adcx      40(%rdi), %r9                                 #207.1
        movq      %r9, 2280(%r10)                               #207.1
        movq      48(%rsi), %rdx                                #207.1
        mulx      %rax, %r13, %rdx                              #207.1
        adox      %rdx, %rbx                                    #207.1
        adcx      48(%rdi), %rbx                                #207.1
        movq      %rbx, 2288(%r10)                              #207.1
        movq      56(%rsi), %rdx                                #207.1
        mulx      %rax, %rbx, %rdx                              #207.1
        adox      %rdx, %r13                                    #207.1
        adcx      56(%rdi), %r13                                #207.1
        movq      %r13, 2296(%r10)                              #207.1
        movq      64(%rsi), %rdx                                #207.1
        mulx      %rax, %r13, %rdx                              #207.1
        adox      %rdx, %rbx                                    #207.1
        adcx      64(%rdi), %rbx                                #207.1
        movq      %rbx, 2304(%r10)                              #207.1
        movq      72(%rsi), %rdx                                #207.1
        mulx      %rax, %rdx, %rsi                              #207.1
        adox      %rsi, %r13                                    #207.1
        movl      $0, %esi                                      #207.1
        adcx      72(%rdi), %r13                                #207.1
        movq      %r13, 2312(%r10)                              #207.1
        adox      %rsi, %rdx                                    #207.1
        adcx      80(%rdi), %rdx                                #207.1
        movl      %r11d, %eax                                   #207.1
        movq      %rdx, 2320(%r10)                              #207.1
        setb      %al                                           #207.1
        clc                                                     #207.1
        movq      32(%rcx), %rdx                                #207.1
        mulx      %r8, %r13, %rbx                               #207.1
        adcx      %rbx, %r12                                    #207.1
        movl      %r11d, %r12d                                  #207.1
        adox      %r11d, %r12d                                  #207.1
        movq      40(%rcx), %rdx                                #207.1
        mulx      %r8, %rbx, %rdx                               #207.1
        adox      %rdx, %r13                                    #207.1
        adcx      %r13, %r9                                     #207.1
        movq      %r9, 32(%rdi)                                 #207.1
        movq      48(%rcx), %rdx                                #207.1
        mulx      %r8, %r13, %r9                                #207.1
        adox      %r9, %rbx                                     #207.1
        adcx      2288(%r10), %rbx                              #207.1
        movq      %rbx, 40(%rdi)                                #207.1
        movq      56(%rcx), %rdx                                #207.1
        mulx      %r8, %r12, %r9                                #207.1
        adox      %r9, %r13                                     #207.1
        adcx      2296(%r10), %r13                              #207.1
        movq      %r13, 48(%rdi)                                #207.1
        movq      64(%rcx), %rdx                                #207.1
        mulx      %r8, %r9, %r13                                #207.1
        adox      %r13, %r12                                    #207.1
        adcx      2304(%r10), %r12                              #207.1
        movq      %r12, 56(%rdi)                                #207.1
        movq      72(%rcx), %rdx                                #207.1
        mulx      %r8, %rdx, %rcx                               #207.1
        movl      %r11d, %r8d                                   #207.1
        adox      %rcx, %r9                                     #207.1
        adcx      2312(%r10), %r9                               #207.1
        movq      %r9, 64(%rdi)                                 #207.1
        adox      %rsi, %rdx                                    #207.1
        seto      %r8b                                          #207.1
        adcx      2320(%r10), %rdx                              #207.1
        movq      %rdx, 72(%rdi)                                #207.1
        setb      %r11b                                         #207.1
        addq      88(%rdi), %rax                                #207.1
        addq      %r11, %rax                                    #207.1
        movq      %rax, 80(%rdi)                                #207.1
        movq      %rsi, 88(%rdi)                                #207.1
        jmp       ..B6.8        # Prob 100%                     #207.1
..B6.4:                         # Preds ..B6.2
        movq      32(%rsi), %rdx                                #207.1
        xorl      %r8d, %r8d                                    #207.1
        xorl      %r10d, %r10d                                  #207.1
        xorl      %ecx, %ecx                                    #207.1
        xorl      %r12d, %r12d                                  #207.1
        mulx      %rax, %r11, %r13                              #207.1
        adcx      32(%rdi), %r13                                #207.1
        movq      40(%rdi), %r12                                #207.1
        adcx      %r8, %r12                                     #207.1
        movq      40(%rsi), %rdx                                #207.1
        adox      %r10d, %ecx                                   #207.1
        mulx      %rax, %r9, %rbx                               #207.1
        adox      %rbx, %r11                                    #207.1
        movq      %r12, 32(%rdi)                                #207.1
        adcx      48(%rdi), %r11                                #207.1
        movq      48(%rsi), %rdx                                #207.1
        mulx      %rax, %rbx, %r13                              #207.1
        adox      %r13, %r9                                     #207.1
        movq      %r11, 40(%rdi)                                #207.1
        adcx      56(%rdi), %r9                                 #207.1
        movq      56(%rsi), %rdx                                #207.1
        mulx      %rax, %rcx, %r11                              #207.1
        adox      %r11, %rbx                                    #207.1
        movq      %r9, 48(%rdi)                                 #207.1
        adcx      64(%rdi), %rbx                                #207.1
        movq      64(%rsi), %rdx                                #207.1
        mulx      %rax, %r11, %r9                               #207.1
        adox      %r9, %rcx                                     #207.1
        movq      %rbx, 56(%rdi)                                #207.1
        adcx      72(%rdi), %rcx                                #207.1
        movq      72(%rsi), %rdx                                #207.1
        movl      %r10d, %esi                                   #207.1
        mulx      %rax, %rdx, %rax                              #207.1
        adox      %rax, %r11                                    #207.1
        movq      80(%rdi), %rax                                #207.1
        adox      %r8, %rdx                                     #207.1
        movq      %rcx, 64(%rdi)                                #207.1
        seto      %sil                                          #207.1
        adcx      %rax, %rdx                                    #207.1
        movq      %rdx, 72(%rdi)                                #207.1
        setb      %r10b                                         #207.1
        addq      %r10, %rax                                    #207.1
        movq      %rax, 80(%rdi)                                #207.1
        jmp       ..B6.8        # Prob 100%                     #207.1
..B6.5:                         # Preds ..B6.1
        testq     %r8, %r8                                      #207.1
        je        ..B6.7        # Prob 50%                      #207.1
        movq      32(%rcx), %rdx                                #207.1
        xorl      %esi, %esi                                    #207.1
        xorl      %r10d, %r10d                                  #207.1
        xorl      %eax, %eax                                    #207.1
        xorl      %r12d, %r12d                                  #207.1
        mulx      %r8, %r11, %r13                               #207.1
        adcx      32(%rdi), %r13                                #207.1
        movq      40(%rdi), %r12                                #207.1
        adcx      %rsi, %r12                                    #207.1
        movq      40(%rcx), %rdx                                #207.1
        adox      %r10d, %eax                                   #207.1
        mulx      %r8, %r9, %rbx                                #207.1
        adox      %rbx, %r11                                    #207.1
        movq      %r12, 32(%rdi)                                #207.1
        adcx      48(%rdi), %r11                                #207.1
        movq      48(%rcx), %rdx                                #207.1
        mulx      %r8, %rbx, %rdx                               #207.1
        adox      %rdx, %r9                                     #207.1
        movq      %r11, 40(%rdi)                                #207.1
        adcx      56(%rdi), %r9                                 #207.1
        movq      56(%rcx), %rdx                                #207.1
        mulx      %r8, %rax, %r11                               #207.1
        adox      %r11, %rbx                                    #207.1
        movq      %r9, 48(%rdi)                                 #207.1
        adcx      64(%rdi), %rbx                                #207.1
        movq      64(%rcx), %rdx                                #207.1
        mulx      %r8, %r11, %r9                                #207.1
        adox      %r9, %rax                                     #207.1
        movq      %rbx, 56(%rdi)                                #207.1
        adcx      72(%rdi), %rax                                #207.1
        movq      72(%rcx), %rdx                                #207.1
        mulx      %r8, %rdx, %rcx                               #207.1
        movl      %r10d, %r8d                                   #207.1
        adox      %rcx, %r11                                    #207.1
        movq      %rax, 64(%rdi)                                #207.1
        adox      %rsi, %rdx                                    #207.1
        movq      80(%rdi), %rax                                #207.1
        seto      %r8b                                          #207.1
        adcx      %rax, %rdx                                    #207.1
        movq      %rdx, 72(%rdi)                                #207.1
        setb      %r10b                                         #207.1
        addq      %r10, %rax                                    #207.1
        movq      %rax, 80(%rdi)                                #207.1
        jmp       ..B6.8        # Prob 100%                     #207.1
..B6.7:                         # Preds ..B6.5
        vmovdqu   40(%rdi), %ymm0                               #207.1
        movq      72(%rdi), %rax                                #207.1
        movq      80(%rdi), %rdx                                #207.1
        movq      88(%rdi), %rcx                                #207.1
        vmovdqu   %ymm0, 32(%rdi)                               #207.1
        movq      %rax, 64(%rdi)                                #207.1
        movq      %rdx, 72(%rdi)                                #207.1
        movq      %rcx, 80(%rdi)                                #207.1
        movq      $0, 88(%rdi)                                  #207.1
..B6.8:                         # Preds ..B6.4 ..B6.6 ..B6.7 ..B6.3
        vzeroupper                                              #207.1
        popq      %rbx                                          #207.1
        popq      %r13                                          #207.1
        popq      %r12                                          #207.1
        ret                                                     #207.1
bigint_mul_add_rshift_inplace_x2_7:
        pushq     %r13                                          #208.1
        pushq     %r14                                          #208.1
        pushq     %r15                                          #208.1
        movq      %rdx, %rax                                    #208.1
        movq      __bigint_buffer(%rip), %r11                   #208.1
        testq     %rax, %rax                                    #208.1
        je        ..B7.5        # Prob 50%                      #208.1
        testq     %r8, %r8                                      #208.1
        je        ..B7.4        # Prob 50%                      #208.1
        movq      32(%rsi), %rdx                                #208.1
        xorl      %r9d, %r9d                                    #208.1
        xorl      %r13d, %r13d                                  #208.1
        mulx      %rax, %r10, %r14                              #208.1
        adcx      32(%rdi), %r14                                #208.1
        movq      %r14, 2272(%r11)                              #208.1
        adox      %r13d, %r9d                                   #208.1
        movq      40(%rsi), %rdx                                #208.1
        mulx      %rax, %r15, %rdx                              #208.1
        adox      %rdx, %r10                                    #208.1
        adcx      40(%rdi), %r10                                #208.1
        movq      %r10, 2280(%r11)                              #208.1
        movq      48(%rsi), %rdx                                #208.1
        mulx      %rax, %r9, %rdx                               #208.1
        adox      %rdx, %r15                                    #208.1
        adcx      48(%rdi), %r15                                #208.1
        movq      %r15, 2288(%r11)                              #208.1
        movq      56(%rsi), %rdx                                #208.1
        mulx      %rax, %r15, %rdx                              #208.1
        adox      %rdx, %r9                                     #208.1
        adcx      56(%rdi), %r9                                 #208.1
        movq      %r9, 2296(%r11)                               #208.1
        movq      64(%rsi), %rdx                                #208.1
        mulx      %rax, %r9, %rdx                               #208.1
        adox      %rdx, %r15                                    #208.1
        adcx      64(%rdi), %r15                                #208.1
        movq      %r15, 2304(%r11)                              #208.1
        movq      72(%rsi), %rdx                                #208.1
        mulx      %rax, %r15, %rdx                              #208.1
        adox      %rdx, %r9                                     #208.1
        adcx      72(%rdi), %r9                                 #208.1
        movq      %r9, 2312(%r11)                               #208.1
        movq      80(%rsi), %rdx                                #208.1
        mulx      %rax, %rdx, %rsi                              #208.1
        adox      %rsi, %r15                                    #208.1
        movl      $0, %esi                                      #208.1
        adcx      80(%rdi), %r15                                #208.1
        movq      %r15, 2320(%r11)                              #208.1
        adox      %rsi, %rdx                                    #208.1
        adcx      88(%rdi), %rdx                                #208.1
        movl      %r13d, %eax                                   #208.1
        movq      %rdx, 2328(%r11)                              #208.1
        setb      %al                                           #208.1
        clc                                                     #208.1
        movq      32(%rcx), %rdx                                #208.1
        mulx      %r8, %r15, %r9                                #208.1
        adcx      %r9, %r14                                     #208.1
        movq      40(%rcx), %rdx                                #208.1
        mulx      %r8, %r14, %r9                                #208.1
        movl      %r13d, %edx                                   #208.1
        adox      %r13d, %edx                                   #208.1
        adox      %r9, %r15                                     #208.1
        adcx      %r15, %r10                                    #208.1
        movq      %r10, 32(%rdi)                                #208.1
        movq      48(%rcx), %rdx                                #208.1
        mulx      %r8, %r9, %r10                                #208.1
        adox      %r10, %r14                                    #208.1
        adcx      2288(%r11), %r14                              #208.1
        movq      %r14, 40(%rdi)                                #208.1
        movq      56(%rcx), %rdx                                #208.1
        mulx      %r8, %r15, %r14                               #208.1
        adox      %r14, %r9                                     #208.1
        adcx      2296(%r11), %r9                               #208.1
        movq      %r9, 48(%rdi)                                 #208.1
        movq      64(%rcx), %rdx                                #208.1
        mulx      %r8, %r14, %r10                               #208.1
        adox      %r10, %r15                                    #208.1
        adcx      2304(%r11), %r15                              #208.1
        movq      %r15, 56(%rdi)                                #208.1
        movq      72(%rcx), %rdx                                #208.1
        mulx      %r8, %r10, %r15                               #208.1
        adox      %r15, %r14                                    #208.1
        adcx      2312(%r11), %r14                              #208.1
        movq      %r14, 64(%rdi)                                #208.1
        movq      80(%rcx), %rdx                                #208.1
        mulx      %r8, %rdx, %rcx                               #208.1
        movl      %r13d, %r8d                                   #208.1
        adox      %rcx, %r10                                    #208.1
        adcx      2320(%r11), %r10                              #208.1
        movq      %r10, 72(%rdi)                                #208.1
        adox      %rsi, %rdx                                    #208.1
        seto      %r8b                                          #208.1
        adcx      2328(%r11), %rdx                              #208.1
        movq      %rdx, 80(%rdi)                                #208.1
        setb      %r13b                                         #208.1
        addq      96(%rdi), %rax                                #208.1
        addq      %r13, %rax                                    #208.1
        movq      %rax, 88(%rdi)                                #208.1
        movq      %rsi, 96(%rdi)                                #208.1
        jmp       ..B7.8        # Prob 100%                     #208.1
..B7.4:                         # Preds ..B7.2
        movq      32(%rsi), %rdx                                #208.1
        xorl      %r11d, %r11d                                  #208.1
        xorl      %ecx, %ecx                                    #208.1
        xorl      %r15d, %r15d                                  #208.1
        mulx      %rax, %r13, %r14                              #208.1
        adcx      32(%rdi), %r14                                #208.1
        movq      40(%rdi), %r9                                 #208.1
        movl      $0, %r14d                                     #208.1
        adcx      %r11, %r9                                     #208.1
        movq      40(%rsi), %rdx                                #208.1
        adox      %r14d, %ecx                                   #208.1
        mulx      %rax, %r10, %r8                               #208.1
        adox      %r8, %r13                                     #208.1
        movq      %r9, 32(%rdi)                                 #208.1
        adcx      48(%rdi), %r13                                #208.1
        movq      48(%rsi), %rdx                                #208.1
        mulx      %rax, %r9, %r15                               #208.1
        adox      %r15, %r10                                    #208.1
        movq      %r13, 40(%rdi)                                #208.1
        adcx      56(%rdi), %r10                                #208.1
        movq      56(%rsi), %rdx                                #208.1
        mulx      %rax, %r8, %r13                               #208.1
        adox      %r13, %r9                                     #208.1
        movq      %r10, 48(%rdi)                                #208.1
        adcx      64(%rdi), %r9                                 #208.1
        movq      64(%rsi), %rdx                                #208.1
        mulx      %rax, %rcx, %r10                              #208.1
        adox      %r10, %r8                                     #208.1
        movq      %r9, 56(%rdi)                                 #208.1
        adcx      72(%rdi), %r8                                 #208.1
        movq      72(%rsi), %rdx                                #208.1
        mulx      %rax, %r13, %r9                               #208.1
        adox      %r9, %rcx                                     #208.1
        movq      %r8, 64(%rdi)                                 #208.1
        adcx      80(%rdi), %rcx                                #208.1
        movq      80(%rsi), %rdx                                #208.1
        movl      %r14d, %esi                                   #208.1
        mulx      %rax, %rdx, %rax                              #208.1
        adox      %rax, %r13                                    #208.1
        movq      88(%rdi), %rax                                #208.1
        adox      %r11, %rdx                                    #208.1
        movq      %rcx, 72(%rdi)                                #208.1
        seto      %sil                                          #208.1
        adcx      %rax, %rdx                                    #208.1
        movq      %rdx, 80(%rdi)                                #208.1
        setb      %r14b                                         #208.1
        addq      %r14, %rax                                    #208.1
        movq      %rax, 88(%rdi)                                #208.1
        jmp       ..B7.8        # Prob 100%                     #208.1
..B7.5:                         # Preds ..B7.1
        testq     %r8, %r8                                      #208.1
        je        ..B7.7        # Prob 50%                      #208.1
        movq      32(%rcx), %rdx                                #208.1
        xorl      %r11d, %r11d                                  #208.1
        xorl      %eax, %eax                                    #208.1
        xorl      %r15d, %r15d                                  #208.1
        mulx      %r8, %r13, %r14                               #208.1
        adcx      32(%rdi), %r14                                #208.1
        movq      40(%rdi), %r9                                 #208.1
        movl      $0, %r14d                                     #208.1
        adcx      %r11, %r9                                     #208.1
        movq      40(%rcx), %rdx                                #208.1
        adox      %r14d, %eax                                   #208.1
        mulx      %r8, %r10, %rsi                               #208.1
        adox      %rsi, %r13                                    #208.1
        movq      %r9, 32(%rdi)                                 #208.1
        adcx      48(%rdi), %r13                                #208.1
        movq      48(%rcx), %rdx                                #208.1
        mulx      %r8, %r9, %rdx                                #208.1
        adox      %rdx, %r10                                    #208.1
        movq      %r13, 40(%rdi)                                #208.1
        adcx      56(%rdi), %r10                                #208.1
        movq      56(%rcx), %rdx                                #208.1
        mulx      %r8, %rsi, %r13                               #208.1
        adox      %r13, %r9                                     #208.1
        movq      %r10, 48(%rdi)                                #208.1
        adcx      64(%rdi), %r9                                 #208.1
        movq      64(%rcx), %rdx                                #208.1
        mulx      %r8, %rax, %r10                               #208.1
        adox      %r10, %rsi                                    #208.1
        movq      %r9, 56(%rdi)                                 #208.1
        adcx      72(%rdi), %rsi                                #208.1
        movq      72(%rcx), %rdx                                #208.1
        mulx      %r8, %r9, %r15                                #208.1
        adox      %r15, %rax                                    #208.1
        movq      %rsi, 64(%rdi)                                #208.1
        adcx      80(%rdi), %rax                                #208.1
        movq      80(%rcx), %rdx                                #208.1
        mulx      %r8, %rdx, %rcx                               #208.1
        movl      %r14d, %r8d                                   #208.1
        adox      %rcx, %r9                                     #208.1
        movq      %rax, 72(%rdi)                                #208.1
        adox      %r11, %rdx                                    #208.1
        movq      88(%rdi), %rax                                #208.1
        seto      %r8b                                          #208.1
        adcx      %rax, %rdx                                    #208.1
        movq      %rdx, 80(%rdi)                                #208.1
        setb      %r14b                                         #208.1
        addq      %r14, %rax                                    #208.1
        movq      %rax, 88(%rdi)                                #208.1
        jmp       ..B7.8        # Prob 100%                     #208.1
..B7.7:                         # Preds ..B7.5
        vmovdqu   40(%rdi), %ymm0                               #208.1
        vmovdqu   72(%rdi), %ymm1                               #208.1
        vmovdqu   %ymm0, 32(%rdi)                               #208.1
        vmovdqu   %ymm1, 64(%rdi)                               #208.1
        movq      $0, 96(%rdi)                                  #208.1
..B7.8:                         # Preds ..B7.4 ..B7.6 ..B7.7 ..B7.3
        vzeroupper                                              #208.1
        popq      %r15                                          #208.1
        popq      %r14                                          #208.1
        popq      %r13                                          #208.1
        ret                                                     #208.1
bigint_mul_add_rshift_inplace_x2_8:
        pushq     %r12                                          #209.1
        pushq     %r14                                          #209.1
        pushq     %r15                                          #209.1
        movq      %rdx, %rax                                    #209.1
        movq      __bigint_buffer(%rip), %r10                   #209.1
        testq     %rax, %rax                                    #209.1
        je        ..B8.5        # Prob 50%                      #209.1
        testq     %r8, %r8                                      #209.1
        je        ..B8.4        # Prob 50%                      #209.1
        movq      32(%rsi), %rdx                                #209.1
        xorl      %r14d, %r14d                                  #209.1
        xorl      %r11d, %r11d                                  #209.1
        mulx      %rax, %r9, %r12                               #209.1
        adcx      32(%rdi), %r12                                #209.1
        movq      %r12, 2272(%r10)                              #209.1
        adox      %r11d, %r14d                                  #209.1
        movq      40(%rsi), %rdx                                #209.1
        mulx      %rax, %r15, %rdx                              #209.1
        adox      %rdx, %r9                                     #209.1
        adcx      40(%rdi), %r9                                 #209.1
        movq      %r9, 2280(%r10)                               #209.1
        movq      48(%rsi), %rdx                                #209.1
        mulx      %rax, %r14, %rdx                              #209.1
        adox      %rdx, %r15                                    #209.1
        adcx      48(%rdi), %r15                                #209.1
        movq      %r15, 2288(%r10)                              #209.1
        movq      56(%rsi), %rdx                                #209.1
        mulx      %rax, %r15, %rdx                              #209.1
        adox      %rdx, %r14                                    #209.1
        adcx      56(%rdi), %r14                                #209.1
        movq      %r14, 2296(%r10)                              #209.1
        movq      64(%rsi), %rdx                                #209.1
        mulx      %rax, %r14, %rdx                              #209.1
        adox      %rdx, %r15                                    #209.1
        adcx      64(%rdi), %r15                                #209.1
        movq      %r15, 2304(%r10)                              #209.1
        movq      72(%rsi), %rdx                                #209.1
        mulx      %rax, %r15, %rdx                              #209.1
        adox      %rdx, %r14                                    #209.1
        adcx      72(%rdi), %r14                                #209.1
        movq      %r14, 2312(%r10)                              #209.1
        movq      80(%rsi), %rdx                                #209.1
        mulx      %rax, %r14, %rdx                              #209.1
        adox      %rdx, %r15                                    #209.1
        adcx      80(%rdi), %r15                                #209.1
        movq      %r15, 2320(%r10)                              #209.1
        movq      88(%rsi), %rdx                                #209.1
        mulx      %rax, %rdx, %rsi                              #209.1
        adox      %rsi, %r14                                    #209.1
        movl      $0, %esi                                      #209.1
        adcx      88(%rdi), %r14                                #209.1
        movq      %r14, 2328(%r10)                              #209.1
        adox      %rsi, %rdx                                    #209.1
        adcx      96(%rdi), %rdx                                #209.1
        movl      %r11d, %eax                                   #209.1
        movq      %rdx, 2336(%r10)                              #209.1
        setb      %al                                           #209.1
        clc                                                     #209.1
        movq      32(%rcx), %rdx                                #209.1
        mulx      %r8, %r14, %r15                               #209.1
        adcx      %r15, %r12                                    #209.1
        movq      40(%rcx), %rdx                                #209.1
        mulx      %r8, %r12, %r15                               #209.1
        movl      %r11d, %edx                                   #209.1
        adox      %r11d, %edx                                   #209.1
        adox      %r15, %r14                                    #209.1
        adcx      %r14, %r9                                     #209.1
        movq      %r9, 32(%rdi)                                 #209.1
        movq      48(%rcx), %rdx                                #209.1
        mulx      %r8, %r9, %r14                                #209.1
        adox      %r14, %r12                                    #209.1
        adcx      2288(%r10), %r12                              #209.1
        movq      %r12, 40(%rdi)                                #209.1
        movq      56(%rcx), %rdx                                #209.1
        mulx      %r8, %r15, %r12                               #209.1
        adox      %r12, %r9                                     #209.1
        adcx      2296(%r10), %r9                               #209.1
        movq      %r9, 48(%rdi)                                 #209.1
        movq      64(%rcx), %rdx                                #209.1
        mulx      %r8, %r14, %r9                                #209.1
        adox      %r9, %r15                                     #209.1
        adcx      2304(%r10), %r15                              #209.1
        movq      %r15, 56(%rdi)                                #209.1
        movq      72(%rcx), %rdx                                #209.1
        mulx      %r8, %r12, %r9                                #209.1
        adox      %r9, %r14                                     #209.1
        adcx      2312(%r10), %r14                              #209.1
        movq      %r14, 64(%rdi)                                #209.1
        movq      80(%rcx), %rdx                                #209.1
        mulx      %r8, %r9, %rdx                                #209.1
        adox      %rdx, %r12                                    #209.1
        adcx      2320(%r10), %r12                              #209.1
        movq      %r12, 72(%rdi)                                #209.1
        movq      88(%rcx), %rdx                                #209.1
        mulx      %r8, %rdx, %rcx                               #209.1
        movl      %r11d, %r8d                                   #209.1
        adox      %rcx, %r9                                     #209.1
        adcx      2328(%r10), %r9                               #209.1
        movq      %r9, 80(%rdi)                                 #209.1
        adox      %rsi, %rdx                                    #209.1
        seto      %r8b                                          #209.1
        adcx      2336(%r10), %rdx                              #209.1
        movq      %rdx, 88(%rdi)                                #209.1
        setb      %r11b                                         #209.1
        addq      104(%rdi), %rax                               #209.1
        addq      %r11, %rax                                    #209.1
        movq      %rax, 96(%rdi)                                #209.1
        movq      %rsi, 104(%rdi)                               #209.1
        jmp       ..B8.8        # Prob 100%                     #209.1
..B8.4:                         # Preds ..B8.2
        movq      32(%rsi), %rdx                                #209.1
        xorl      %r15d, %r15d                                  #209.1
        xorl      %r8d, %r8d                                    #209.1
        xorl      %r14d, %r14d                                  #209.1
        mulx      %rax, %r12, %rcx                              #209.1
        movl      $0, %r14d                                     #209.1
        adcx      32(%rdi), %rcx                                #209.1
        movq      40(%rdi), %r10                                #209.1
        adcx      %r14, %r10                                    #209.1
        movq      40(%rsi), %rdx                                #209.1
        adox      %r15d, %r8d                                   #209.1
        mulx      %rax, %r11, %r9                               #209.1
        adox      %r9, %r12                                     #209.1
        movq      %r10, 32(%rdi)                                #209.1
        adcx      48(%rdi), %r12                                #209.1
        movq      48(%rsi), %rdx                                #209.1
        mulx      %rax, %r10, %rcx                              #209.1
        adox      %rcx, %r11                                    #209.1
        movq      %r12, 40(%rdi)                                #209.1
        adcx      56(%rdi), %r11                                #209.1
        movq      56(%rsi), %rdx                                #209.1
        mulx      %rax, %r9, %r12                               #209.1
        adox      %r12, %r10                                    #209.1
        movq      %r11, 48(%rdi)                                #209.1
        adcx      64(%rdi), %r10                                #209.1
        movq      64(%rsi), %rdx                                #209.1
        mulx      %rax, %r8, %r11                               #209.1
        adox      %r11, %r9                                     #209.1
        movq      %r10, 56(%rdi)                                #209.1
        adcx      72(%rdi), %r9                                 #209.1
        movq      72(%rsi), %rdx                                #209.1
        mulx      %rax, %rcx, %r10                              #209.1
        adox      %r10, %r8                                     #209.1
        movq      %r9, 64(%rdi)                                 #209.1
        adcx      80(%rdi), %r8                                 #209.1
        movq      80(%rsi), %rdx                                #209.1
        mulx      %rax, %r12, %r9                               #209.1
        adox      %r9, %rcx                                     #209.1
        movq      %r8, 72(%rdi)                                 #209.1
        adcx      88(%rdi), %rcx                                #209.1
        movq      88(%rsi), %rdx                                #209.1
        movl      %r15d, %esi                                   #209.1
        mulx      %rax, %rdx, %rax                              #209.1
        adox      %rax, %r12                                    #209.1
        movq      96(%rdi), %rax                                #209.1
        adox      %r14, %rdx                                    #209.1
        movq      %rcx, 80(%rdi)                                #209.1
        seto      %sil                                          #209.1
        adcx      %rax, %rdx                                    #209.1
        movq      %rdx, 88(%rdi)                                #209.1
        setb      %r15b                                         #209.1
        addq      %r15, %rax                                    #209.1
        movq      %rax, 96(%rdi)                                #209.1
        jmp       ..B8.8        # Prob 100%                     #209.1
..B8.5:                         # Preds ..B8.1
        testq     %r8, %r8                                      #209.1
        je        ..B8.7        # Prob 50%                      #209.1
        movq      32(%rcx), %rdx                                #209.1
        xorl      %r15d, %r15d                                  #209.1
        xorl      %esi, %esi                                    #209.1
        xorl      %r14d, %r14d                                  #209.1
        mulx      %r8, %r12, %rax                               #209.1
        movl      $0, %r14d                                     #209.1
        adcx      32(%rdi), %rax                                #209.1
        movq      40(%rdi), %r9                                 #209.1
        adcx      %r14, %r9                                     #209.1
        movq      40(%rcx), %rdx                                #209.1
        adox      %r15d, %esi                                   #209.1
        mulx      %r8, %r11, %rdx                               #209.1
        adox      %rdx, %r12                                    #209.1
        movq      %r9, 32(%rdi)                                 #209.1
        adcx      48(%rdi), %r12                                #209.1
        movq      48(%rcx), %rdx                                #209.1
        mulx      %r8, %r10, %rax                               #209.1
        adox      %rax, %r11                                    #209.1
        movq      %r12, 40(%rdi)                                #209.1
        adcx      56(%rdi), %r11                                #209.1
        movq      56(%rcx), %rdx                                #209.1
        mulx      %r8, %r9, %r12                                #209.1
        adox      %r12, %r10                                    #209.1
        movq      %r11, 48(%rdi)                                #209.1
        adcx      64(%rdi), %r10                                #209.1
        movq      64(%rcx), %rdx                                #209.1
        mulx      %r8, %rsi, %r11                               #209.1
        adox      %r11, %r9                                     #209.1
        movq      %r10, 56(%rdi)                                #209.1
        adcx      72(%rdi), %r9                                 #209.1
        movq      72(%rcx), %rdx                                #209.1
        mulx      %r8, %rax, %r10                               #209.1
        adox      %r10, %rsi                                    #209.1
        movq      %r9, 64(%rdi)                                 #209.1
        adcx      80(%rdi), %rsi                                #209.1
        movq      80(%rcx), %rdx                                #209.1
        mulx      %r8, %r9, %rdx                                #209.1
        adox      %rdx, %rax                                    #209.1
        movq      %rsi, 72(%rdi)                                #209.1
        adcx      88(%rdi), %rax                                #209.1
        movq      88(%rcx), %rdx                                #209.1
        mulx      %r8, %rdx, %rcx                               #209.1
        movl      %r15d, %r8d                                   #209.1
        adox      %rcx, %r9                                     #209.1
        movq      %rax, 80(%rdi)                                #209.1
        adox      %r14, %rdx                                    #209.1
        movq      96(%rdi), %rax                                #209.1
        seto      %r8b                                          #209.1
        adcx      %rax, %rdx                                    #209.1
        movq      %rdx, 88(%rdi)                                #209.1
        setb      %r15b                                         #209.1
        addq      %r15, %rax                                    #209.1
        movq      %rax, 96(%rdi)                                #209.1
        jmp       ..B8.8        # Prob 100%                     #209.1
..B8.7:                         # Preds ..B8.5
        vmovdqu   40(%rdi), %ymm0                               #209.1
        vmovdqu   72(%rdi), %ymm1                               #209.1
        vmovdqu   %ymm0, 32(%rdi)                               #209.1
        vmovdqu   %ymm1, 64(%rdi)                               #209.1
        movq      104(%rdi), %rax                               #209.1
        movq      %rax, 96(%rdi)                                #209.1
        movq      $0, 104(%rdi)                                 #209.1
..B8.8:                         # Preds ..B8.4 ..B8.6 ..B8.7 ..B8.3
        vzeroupper                                              #209.1
        popq      %r15                                          #209.1
        popq      %r14                                          #209.1
        popq      %r12                                          #209.1
        ret                                                     #209.1
bigint_mul_add_rshift_inplace_x2_9:
        pushq     %r12                                          #210.1
        pushq     %r15                                          #210.1
        pushq     %rbx                                          #210.1
        movq      %rdx, %rax                                    #210.1
        movq      __bigint_buffer(%rip), %r11                   #210.1
        testq     %rax, %rax                                    #210.1
        je        ..B9.5        # Prob 50%                      #210.1
        testq     %r8, %r8                                      #210.1
        je        ..B9.4        # Prob 50%                      #210.1
        movq      32(%rsi), %rdx                                #210.1
        xorl      %ebx, %ebx                                    #210.1
        xorl      %r12d, %r12d                                  #210.1
        mulx      %rax, %r10, %r15                              #210.1
        adcx      32(%rdi), %r15                                #210.1
        movq      %r15, 2272(%r11)                              #210.1
        adox      %r12d, %ebx                                   #210.1
        movq      40(%rsi), %rdx                                #210.1
        mulx      %rax, %r9, %rdx                               #210.1
        adox      %rdx, %r10                                    #210.1
        adcx      40(%rdi), %r10                                #210.1
        movq      %r10, 2280(%r11)                              #210.1
        movq      48(%rsi), %rdx                                #210.1
        mulx      %rax, %rbx, %rdx                              #210.1
        adox      %rdx, %r9                                     #210.1
        adcx      48(%rdi), %r9                                 #210.1
        movq      %r9, 2288(%r11)                               #210.1
        movq      56(%rsi), %rdx                                #210.1
        mulx      %rax, %r9, %rdx                               #210.1
        adox      %rdx, %rbx                                    #210.1
        adcx      56(%rdi), %rbx                                #210.1
        movq      %rbx, 2296(%r11)                              #210.1
        movq      64(%rsi), %rdx                                #210.1
        mulx      %rax, %rbx, %rdx                              #210.1
        adox      %rdx, %r9                                     #210.1
        adcx      64(%rdi), %r9                                 #210.1
        movq      %r9, 2304(%r11)                               #210.1
        movq      72(%rsi), %rdx                                #210.1
        mulx      %rax, %r9, %rdx                               #210.1
        adox      %rdx, %rbx                                    #210.1
        adcx      72(%rdi), %rbx                                #210.1
        movq      %rbx, 2312(%r11)                              #210.1
        movq      80(%rsi), %rdx                                #210.1
        mulx      %rax, %rbx, %rdx                              #210.1
        adox      %rdx, %r9                                     #210.1
        adcx      80(%rdi), %r9                                 #210.1
        movq      %r9, 2320(%r11)                               #210.1
        movq      88(%rsi), %rdx                                #210.1
        mulx      %rax, %r9, %rdx                               #210.1
        adox      %rdx, %rbx                                    #210.1
        adcx      88(%rdi), %rbx                                #210.1
        movq      %rbx, 2328(%r11)                              #210.1
        movq      96(%rsi), %rdx                                #210.1
        mulx      %rax, %rdx, %rsi                              #210.1
        adox      %rsi, %r9                                     #210.1
        movl      $0, %esi                                      #210.1
        adcx      96(%rdi), %r9                                 #210.1
        movq      %r9, 2336(%r11)                               #210.1
        adox      %rsi, %rdx                                    #210.1
        adcx      104(%rdi), %rdx                               #210.1
        movl      %r12d, %eax                                   #210.1
        movq      %rdx, 2344(%r11)                              #210.1
        setb      %al                                           #210.1
        clc                                                     #210.1
        movq      32(%rcx), %rdx                                #210.1
        mulx      %r8, %rbx, %r9                                #210.1
        adcx      %r9, %r15                                     #210.1
        movl      %r12d, %r15d                                  #210.1
        adox      %r12d, %r15d                                  #210.1
        movq      40(%rcx), %rdx                                #210.1
        mulx      %r8, %r9, %rdx                                #210.1
        adox      %rdx, %rbx                                    #210.1
        adcx      %rbx, %r10                                    #210.1
        movq      %r10, 32(%rdi)                                #210.1
        movq      48(%rcx), %rdx                                #210.1
        mulx      %r8, %r15, %r10                               #210.1
        adox      %r10, %r9                                     #210.1
        adcx      2288(%r11), %r9                               #210.1
        movq      %r9, 40(%rdi)                                 #210.1
        movq      56(%rcx), %rdx                                #210.1
        mulx      %r8, %r10, %rbx                               #210.1
        adox      %rbx, %r15                                    #210.1
        adcx      2296(%r11), %r15                              #210.1
        movq      %r15, 48(%rdi)                                #210.1
        movq      64(%rcx), %rdx                                #210.1
        mulx      %r8, %rbx, %r15                               #210.1
        adox      %r15, %r10                                    #210.1
        adcx      2304(%r11), %r10                              #210.1
        movq      %r10, 56(%rdi)                                #210.1
        movq      72(%rcx), %rdx                                #210.1
        mulx      %r8, %r9, %r10                                #210.1
        adox      %r10, %rbx                                    #210.1
        adcx      2312(%r11), %rbx                              #210.1
        movq      %rbx, 64(%rdi)                                #210.1
        movq      80(%rcx), %rdx                                #210.1
        mulx      %r8, %r15, %rdx                               #210.1
        adox      %rdx, %r9                                     #210.1
        adcx      2320(%r11), %r9                               #210.1
        movq      %r9, 72(%rdi)                                 #210.1
        movq      88(%rcx), %rdx                                #210.1
        mulx      %r8, %r10, %rbx                               #210.1
        adox      %rbx, %r15                                    #210.1
        adcx      2328(%r11), %r15                              #210.1
        movq      %r15, 80(%rdi)                                #210.1
        movq      96(%rcx), %rdx                                #210.1
        mulx      %r8, %rdx, %rcx                               #210.1
        movl      %r12d, %r8d                                   #210.1
        adox      %rcx, %r10                                    #210.1
        adcx      2336(%r11), %r10                              #210.1
        movq      %r10, 88(%rdi)                                #210.1
        adox      %rsi, %rdx                                    #210.1
        seto      %r8b                                          #210.1
        adcx      2344(%r11), %rdx                              #210.1
        movq      %rdx, 96(%rdi)                                #210.1
        setb      %r12b                                         #210.1
        addq      112(%rdi), %rax                               #210.1
        addq      %r12, %rax                                    #210.1
        movq      %rax, 104(%rdi)                               #210.1
        movq      %rsi, 112(%rdi)                               #210.1
        jmp       ..B9.8        # Prob 100%                     #210.1
..B9.4:                         # Preds ..B9.2
        movq      32(%rsi), %rdx                                #210.1
        xorl      %r9d, %r9d                                    #210.1
        xorl      %ebx, %ebx                                    #210.1
        mulx      %rax, %r8, %rcx                               #210.1
        adcx      32(%rdi), %rcx                                #210.1
        movl      $0, %ecx                                      #210.1
        movq      40(%rdi), %r11                                #210.1
        adcx      %rcx, %r11                                    #210.1
        movq      40(%rsi), %rdx                                #210.1
        adox      %ebx, %r9d                                    #210.1
        mulx      %rax, %r15, %r10                              #210.1
        adox      %r10, %r8                                     #210.1
        movq      %r11, 32(%rdi)                                #210.1
        adcx      48(%rdi), %r8                                 #210.1
        movq      48(%rsi), %rdx                                #210.1
        mulx      %rax, %r12, %r9                               #210.1
        adox      %r9, %r15                                     #210.1
        movq      %r8, 40(%rdi)                                 #210.1
        adcx      56(%rdi), %r15                                #210.1
        movq      56(%rsi), %rdx                                #210.1
        mulx      %rax, %r11, %r8                               #210.1
        adox      %r8, %r12                                     #210.1
        movq      %r15, 48(%rdi)                                #210.1
        adcx      64(%rdi), %r12                                #210.1
        movq      64(%rsi), %rdx                                #210.1
        mulx      %rax, %r10, %r15                              #210.1
        adox      %r15, %r11                                    #210.1
        movq      %r12, 56(%rdi)                                #210.1
        adcx      72(%rdi), %r11                                #210.1
        movq      72(%rsi), %rdx                                #210.1
        mulx      %rax, %r9, %r12                               #210.1
        adox      %r12, %r10                                    #210.1
        movq      %r11, 64(%rdi)                                #210.1
        adcx      80(%rdi), %r10                                #210.1
        movq      80(%rsi), %rdx                                #210.1
        mulx      %rax, %r8, %r11                               #210.1
        adox      %r11, %r9                                     #210.1
        movq      %r10, 72(%rdi)                                #210.1
        adcx      88(%rdi), %r9                                 #210.1
        movq      88(%rsi), %rdx                                #210.1
        mulx      %rax, %r15, %r10                              #210.1
        adox      %r10, %r8                                     #210.1
        movq      %r9, 80(%rdi)                                 #210.1
        adcx      96(%rdi), %r8                                 #210.1
        movq      96(%rsi), %rdx                                #210.1
        movl      %ebx, %esi                                    #210.1
        mulx      %rax, %rdx, %rax                              #210.1
        adox      %rax, %r15                                    #210.1
        movq      104(%rdi), %rax                               #210.1
        adox      %rcx, %rdx                                    #210.1
        movq      %r8, 88(%rdi)                                 #210.1
        seto      %sil                                          #210.1
        adcx      %rax, %rdx                                    #210.1
        movq      %rdx, 96(%rdi)                                #210.1
        setb      %bl                                           #210.1
        addq      %rbx, %rax                                    #210.1
        movq      %rax, 104(%rdi)                               #210.1
        jmp       ..B9.8        # Prob 100%                     #210.1
..B9.5:                         # Preds ..B9.1
        testq     %r8, %r8                                      #210.1
        je        ..B9.7        # Prob 50%                      #210.1
        movq      32(%rcx), %rdx                                #210.1
        xorl      %r9d, %r9d                                    #210.1
        xorl      %ebx, %ebx                                    #210.1
        mulx      %r8, %rsi, %rax                               #210.1
        adcx      32(%rdi), %rax                                #210.1
        movl      $0, %eax                                      #210.1
        movq      40(%rdi), %r10                                #210.1
        adcx      %rax, %r10                                    #210.1
        movq      40(%rcx), %rdx                                #210.1
        adox      %ebx, %r9d                                    #210.1
        mulx      %r8, %r15, %rdx                               #210.1
        adox      %rdx, %rsi                                    #210.1
        movq      %r10, 32(%rdi)                                #210.1
        adcx      48(%rdi), %rsi                                #210.1
        movq      48(%rcx), %rdx                                #210.1
        mulx      %r8, %r12, %r11                               #210.1
        adox      %r11, %r15                                    #210.1
        movq      %rsi, 40(%rdi)                                #210.1
        adcx      56(%rdi), %r15                                #210.1
        movq      56(%rcx), %rdx                                #210.1
        mulx      %r8, %r11, %rsi                               #210.1
        adox      %rsi, %r12                                    #210.1
        movq      %r15, 48(%rdi)                                #210.1
        adcx      64(%rdi), %r12                                #210.1
        movq      64(%rcx), %rdx                                #210.1
        mulx      %r8, %r10, %r15                               #210.1
        adox      %r15, %r11                                    #210.1
        movq      %r12, 56(%rdi)                                #210.1
        adcx      72(%rdi), %r11                                #210.1
        movq      72(%rcx), %rdx                                #210.1
        mulx      %r8, %r9, %r12                                #210.1
        adox      %r12, %r10                                    #210.1
        movq      %r11, 64(%rdi)                                #210.1
        adcx      80(%rdi), %r10                                #210.1
        movq      80(%rcx), %rdx                                #210.1
        mulx      %r8, %rsi, %rdx                               #210.1
        adox      %rdx, %r9                                     #210.1
        movq      %r10, 72(%rdi)                                #210.1
        adcx      88(%rdi), %r9                                 #210.1
        movq      88(%rcx), %rdx                                #210.1
        mulx      %r8, %r11, %r10                               #210.1
        adox      %r10, %rsi                                    #210.1
        movq      %r9, 80(%rdi)                                 #210.1
        adcx      96(%rdi), %rsi                                #210.1
        movq      96(%rcx), %rdx                                #210.1
        mulx      %r8, %rdx, %rcx                               #210.1
        movl      %ebx, %r8d                                    #210.1
        adox      %rcx, %r11                                    #210.1
        movq      %rsi, 88(%rdi)                                #210.1
        adox      %rax, %rdx                                    #210.1
        movq      104(%rdi), %rax                               #210.1
        seto      %r8b                                          #210.1
        adcx      %rax, %rdx                                    #210.1
        movq      %rdx, 96(%rdi)                                #210.1
        setb      %bl                                           #210.1
        addq      %rbx, %rax                                    #210.1
        movq      %rax, 104(%rdi)                               #210.1
        jmp       ..B9.8        # Prob 100%                     #210.1
..B9.7:                         # Preds ..B9.5
        vmovdqu   40(%rdi), %ymm0                               #210.1
        vmovdqu   72(%rdi), %ymm1                               #210.1
        vmovdqu   %ymm0, 32(%rdi)                               #210.1
        vmovdqu   %ymm1, 64(%rdi)                               #210.1
        movq      104(%rdi), %rax                               #210.1
        movq      112(%rdi), %rdx                               #210.1
        movq      %rax, 96(%rdi)                                #210.1
        movq      %rdx, 104(%rdi)                               #210.1
        movq      $0, 112(%rdi)                                 #210.1
..B9.8:                         # Preds ..B9.4 ..B9.6 ..B9.7 ..B9.3
        vzeroupper                                              #210.1
        popq      %rbx                                          #210.1
        popq      %r15                                          #210.1
        popq      %r12                                          #210.1
        ret                                                     #210.1
bigint_mul_add_rshift_inplace_x2_10:
        pushq     %r13                                          #211.1
        pushq     %r14                                          #211.1
        pushq     %r15                                          #211.1
        movq      %rdx, %rax                                    #211.1
        movq      __bigint_buffer(%rip), %r11                   #211.1
        testq     %rax, %rax                                    #211.1
        je        ..B10.5       # Prob 50%                      #211.1
        testq     %r8, %r8                                      #211.1
        je        ..B10.4       # Prob 50%                      #211.1
        movq      32(%rsi), %rdx                                #211.1
        xorl      %r15d, %r15d                                  #211.1
        xorl      %r13d, %r13d                                  #211.1
        mulx      %rax, %r10, %r14                              #211.1
        adcx      32(%rdi), %r14                                #211.1
        movq      %r14, 2272(%r11)                              #211.1
        adox      %r13d, %r15d                                  #211.1
        movq      40(%rsi), %rdx                                #211.1
        mulx      %rax, %r9, %rdx                               #211.1
        adox      %rdx, %r10                                    #211.1
        adcx      40(%rdi), %r10                                #211.1
        movq      %r10, 2280(%r11)                              #211.1
        movq      48(%rsi), %rdx                                #211.1
        mulx      %rax, %r15, %rdx                              #211.1
        adox      %rdx, %r9                                     #211.1
        adcx      48(%rdi), %r9                                 #211.1
        movq      %r9, 2288(%r11)                               #211.1
        movq      56(%rsi), %rdx                                #211.1
        mulx      %rax, %r9, %rdx                               #211.1
        adox      %rdx, %r15                                    #211.1
        adcx      56(%rdi), %r15                                #211.1
        movq      %r15, 2296(%r11)                              #211.1
        movq      64(%rsi), %rdx                                #211.1
        mulx      %rax, %r15, %rdx                              #211.1
        adox      %rdx, %r9                                     #211.1
        adcx      64(%rdi), %r9                                 #211.1
        movq      %r9, 2304(%r11)                               #211.1
        movq      72(%rsi), %rdx                                #211.1
        mulx      %rax, %r9, %rdx                               #211.1
        adox      %rdx, %r15                                    #211.1
        adcx      72(%rdi), %r15                                #211.1
        movq      %r15, 2312(%r11)                              #211.1
        movq      80(%rsi), %rdx                                #211.1
        mulx      %rax, %r15, %rdx                              #211.1
        adox      %rdx, %r9                                     #211.1
        adcx      80(%rdi), %r9                                 #211.1
        movq      %r9, 2320(%r11)                               #211.1
        movq      88(%rsi), %rdx                                #211.1
        mulx      %rax, %r9, %rdx                               #211.1
        adox      %rdx, %r15                                    #211.1
        adcx      88(%rdi), %r15                                #211.1
        movq      %r15, 2328(%r11)                              #211.1
        movq      96(%rsi), %rdx                                #211.1
        mulx      %rax, %r15, %rdx                              #211.1
        adox      %rdx, %r9                                     #211.1
        adcx      96(%rdi), %r9                                 #211.1
        movq      %r9, 2336(%r11)                               #211.1
        movq      104(%rsi), %rdx                               #211.1
        mulx      %rax, %rdx, %rsi                              #211.1
        adox      %rsi, %r15                                    #211.1
        movl      $0, %esi                                      #211.1
        adcx      104(%rdi), %r15                               #211.1
        movq      %r15, 2344(%r11)                              #211.1
        adox      %rsi, %rdx                                    #211.1
        adcx      112(%rdi), %rdx                               #211.1
        movl      %r13d, %eax                                   #211.1
        movq      %rdx, 2352(%r11)                              #211.1
        setb      %al                                           #211.1
        clc                                                     #211.1
        movq      32(%rcx), %rdx                                #211.1
        mulx      %r8, %r9, %r15                                #211.1
        adcx      %r15, %r14                                    #211.1
        movq      40(%rcx), %rdx                                #211.1
        mulx      %r8, %r14, %r15                               #211.1
        movl      %r13d, %edx                                   #211.1
        adox      %r13d, %edx                                   #211.1
        adox      %r15, %r9                                     #211.1
        adcx      %r9, %r10                                     #211.1
        movq      %r10, 32(%rdi)                                #211.1
        movq      48(%rcx), %rdx                                #211.1
        mulx      %r8, %r15, %r10                               #211.1
        adox      %r10, %r14                                    #211.1
        adcx      2288(%r11), %r14                              #211.1
        movq      %r14, 40(%rdi)                                #211.1
        movq      56(%rcx), %rdx                                #211.1
        mulx      %r8, %r14, %r10                               #211.1
        adox      %r10, %r15                                    #211.1
        adcx      2296(%r11), %r15                              #211.1
        movq      %r15, 48(%rdi)                                #211.1
        movq      64(%rcx), %rdx                                #211.1
        mulx      %r8, %r10, %r9                                #211.1
        adox      %r9, %r14                                     #211.1
        adcx      2304(%r11), %r14                              #211.1
        movq      %r14, 56(%rdi)                                #211.1
        movq      72(%rcx), %rdx                                #211.1
        mulx      %r8, %r9, %r14                                #211.1
        adox      %r14, %r10                                    #211.1
        adcx      2312(%r11), %r10                              #211.1
        movq      %r10, 64(%rdi)                                #211.1
        movq      80(%rcx), %rdx                                #211.1
        mulx      %r8, %r15, %r10                               #211.1
        adox      %r10, %r9                                     #211.1
        adcx      2320(%r11), %r9                               #211.1
        movq      %r9, 72(%rdi)                                 #211.1
        movq      88(%rcx), %rdx                                #211.1
        mulx      %r8, %r14, %rdx                               #211.1
        adox      %rdx, %r15                                    #211.1
        adcx      2328(%r11), %r15                              #211.1
        movq      %r15, 80(%rdi)                                #211.1
        movq      96(%rcx), %rdx                                #211.1
        mulx      %r8, %r10, %r9                                #211.1
        adox      %r9, %r14                                     #211.1
        adcx      2336(%r11), %r14                              #211.1
        movq      %r14, 88(%rdi)                                #211.1
        movq      104(%rcx), %rdx                               #211.1
        mulx      %r8, %rdx, %rcx                               #211.1
        movl      %r13d, %r8d                                   #211.1
        adox      %rcx, %r10                                    #211.1
        adcx      2344(%r11), %r10                              #211.1
        movq      %r10, 96(%rdi)                                #211.1
        adox      %rsi, %rdx                                    #211.1
        seto      %r8b                                          #211.1
        adcx      2352(%r11), %rdx                              #211.1
        movq      %rdx, 104(%rdi)                               #211.1
        setb      %r13b                                         #211.1
        addq      120(%rdi), %rax                               #211.1
        addq      %r13, %rax                                    #211.1
        movq      %rax, 112(%rdi)                               #211.1
        movq      %rsi, 120(%rdi)                               #211.1
        jmp       ..B10.8       # Prob 100%                     #211.1
..B10.4:                        # Preds ..B10.2
        movq      32(%rsi), %rdx                                #211.1
        xorl      %r11d, %r11d                                  #211.1
        xorl      %r8d, %r8d                                    #211.1
        mulx      %rax, %r10, %rcx                              #211.1
        adcx      32(%rdi), %rcx                                #211.1
        movl      $0, %ecx                                      #211.1
        movq      40(%rdi), %r14                                #211.1
        adcx      %rcx, %r14                                    #211.1
        movq      40(%rsi), %rdx                                #211.1
        adox      %r8d, %r11d                                   #211.1
        mulx      %rax, %r9, %r13                               #211.1
        adox      %r13, %r10                                    #211.1
        movq      %r14, 32(%rdi)                                #211.1
        adcx      48(%rdi), %r10                                #211.1
        movq      48(%rsi), %rdx                                #211.1
        mulx      %rax, %r15, %r11                              #211.1
        adox      %r11, %r9                                     #211.1
        movq      %r10, 40(%rdi)                                #211.1
        adcx      56(%rdi), %r9                                 #211.1
        movq      56(%rsi), %rdx                                #211.1
        mulx      %rax, %r14, %r10                              #211.1
        adox      %r10, %r15                                    #211.1
        movq      %r9, 48(%rdi)                                 #211.1
        adcx      64(%rdi), %r15                                #211.1
        movq      64(%rsi), %rdx                                #211.1
        mulx      %rax, %r13, %r9                               #211.1
        adox      %r9, %r14                                     #211.1
        movq      %r15, 56(%rdi)                                #211.1
        adcx      72(%rdi), %r14                                #211.1
        movq      72(%rsi), %rdx                                #211.1
        mulx      %rax, %r11, %r15                              #211.1
        adox      %r15, %r13                                    #211.1
        movq      %r14, 64(%rdi)                                #211.1
        adcx      80(%rdi), %r13                                #211.1
        movq      80(%rsi), %rdx                                #211.1
        mulx      %rax, %r10, %r9                               #211.1
        adox      %r9, %r11                                     #211.1
        movq      %r13, 72(%rdi)                                #211.1
        adcx      88(%rdi), %r11                                #211.1
        movq      88(%rsi), %rdx                                #211.1
        mulx      %rax, %r9, %r13                               #211.1
        adox      %r13, %r10                                    #211.1
        movq      %r11, 80(%rdi)                                #211.1
        adcx      96(%rdi), %r10                                #211.1
        movq      96(%rsi), %rdx                                #211.1
        mulx      %rax, %r14, %r11                              #211.1
        adox      %r11, %r9                                     #211.1
        movq      %r10, 88(%rdi)                                #211.1
        adcx      104(%rdi), %r9                                #211.1
        movq      104(%rsi), %rdx                               #211.1
        movl      %r8d, %esi                                    #211.1
        mulx      %rax, %rdx, %rax                              #211.1
        adox      %rax, %r14                                    #211.1
        movq      112(%rdi), %rax                               #211.1
        adox      %rcx, %rdx                                    #211.1
        movq      %r9, 96(%rdi)                                 #211.1
        seto      %sil                                          #211.1
        adcx      %rax, %rdx                                    #211.1
        movq      %rdx, 104(%rdi)                               #211.1
        setb      %r8b                                          #211.1
        addq      %r8, %rax                                     #211.1
        movq      %rax, 112(%rdi)                               #211.1
        jmp       ..B10.8       # Prob 100%                     #211.1
..B10.5:                        # Preds ..B10.1
        testq     %r8, %r8                                      #211.1
        je        ..B10.7       # Prob 50%                      #211.1
        movq      32(%rcx), %rdx                                #211.1
        xorl      %esi, %esi                                    #211.1
        mulx      %r8, %r10, %rax                               #211.1
        adcx      32(%rdi), %rax                                #211.1
        movl      $0, %eax                                      #211.1
        movq      40(%rdi), %r13                                #211.1
        adcx      %rax, %r13                                    #211.1
        movq      40(%rcx), %rdx                                #211.1
        mulx      %r8, %r9, %r11                                #211.1
        movl      %esi, %edx                                    #211.1
        adox      %esi, %edx                                    #211.1
        movq      %r13, 32(%rdi)                                #211.1
        adox      %r11, %r10                                    #211.1
        movq      48(%rcx), %rdx                                #211.1
        adcx      48(%rdi), %r10                                #211.1
        mulx      %r8, %r15, %r14                               #211.1
        adox      %r14, %r9                                     #211.1
        movq      %r10, 40(%rdi)                                #211.1
        adcx      56(%rdi), %r9                                 #211.1
        movq      56(%rcx), %rdx                                #211.1
        mulx      %r8, %r14, %r10                               #211.1
        adox      %r10, %r15                                    #211.1
        movq      %r9, 48(%rdi)                                 #211.1
        adcx      64(%rdi), %r15                                #211.1
        movq      64(%rcx), %rdx                                #211.1
        mulx      %r8, %r13, %r9                                #211.1
        adox      %r9, %r14                                     #211.1
        movq      %r15, 56(%rdi)                                #211.1
        adcx      72(%rdi), %r14                                #211.1
        movq      72(%rcx), %rdx                                #211.1
        mulx      %r8, %r11, %r15                               #211.1
        adox      %r15, %r13                                    #211.1
        movq      %r14, 64(%rdi)                                #211.1
        adcx      80(%rdi), %r13                                #211.1
        movq      80(%rcx), %rdx                                #211.1
        mulx      %r8, %r10, %r9                                #211.1
        adox      %r9, %r11                                     #211.1
        movq      %r13, 72(%rdi)                                #211.1
        adcx      88(%rdi), %r11                                #211.1
        movq      88(%rcx), %rdx                                #211.1
        mulx      %r8, %r9, %rdx                                #211.1
        adox      %rdx, %r10                                    #211.1
        movq      %r11, 80(%rdi)                                #211.1
        adcx      96(%rdi), %r10                                #211.1
        movq      96(%rcx), %rdx                                #211.1
        mulx      %r8, %r13, %r11                               #211.1
        adox      %r11, %r9                                     #211.1
        movq      %r10, 88(%rdi)                                #211.1
        adcx      104(%rdi), %r9                                #211.1
        movq      104(%rcx), %rdx                               #211.1
        mulx      %r8, %rdx, %rcx                               #211.1
        movl      %esi, %r8d                                    #211.1
        adox      %rcx, %r13                                    #211.1
        movq      %r9, 96(%rdi)                                 #211.1
        adox      %rax, %rdx                                    #211.1
        movq      112(%rdi), %rax                               #211.1
        seto      %r8b                                          #211.1
        adcx      %rax, %rdx                                    #211.1
        movq      %rdx, 104(%rdi)                               #211.1
        setb      %sil                                          #211.1
        addq      %rsi, %rax                                    #211.1
        movq      %rax, 112(%rdi)                               #211.1
        jmp       ..B10.8       # Prob 100%                     #211.1
..B10.7:                        # Preds ..B10.5
        vmovdqu   40(%rdi), %ymm0                               #211.1
        vmovdqu   72(%rdi), %ymm1                               #211.1
        vmovdqu   %ymm0, 32(%rdi)                               #211.1
        vmovdqu   %ymm1, 64(%rdi)                               #211.1
        movq      104(%rdi), %rax                               #211.1
        movq      112(%rdi), %rdx                               #211.1
        movq      120(%rdi), %rcx                               #211.1
        movq      %rax, 96(%rdi)                                #211.1
        movq      %rdx, 104(%rdi)                               #211.1
        movq      %rcx, 112(%rdi)                               #211.1
        movq      $0, 120(%rdi)                                 #211.1
..B10.8:                        # Preds ..B10.4 ..B10.6 ..B10.7 ..B10.3
        vzeroupper                                              #211.1
        popq      %r15                                          #211.1
        popq      %r14                                          #211.1
        popq      %r13                                          #211.1
        ret                                                     #211.1
