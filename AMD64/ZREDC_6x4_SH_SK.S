//*******************************************************************************************
// Copyright (c) Sept,2017 Ochoa-Jiménez
// Computer Science Department
// CINVESTAV-IPN. Mexico.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, version 3.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************************/
// Registers that are used for parameter passing:

#define reg_p1  %rdi
#define reg_p2  %rsi
#define reg_p3  %rdx

// p3_239 = 3^239
p3_239:
    .quad  0xC968549F878A8EEB
    .quad  0x59B1A13F7CC76E3E
    .quad  0xE9867D6EBE876DA9
    .quad  0x2B5045CB25748084
    .quad  0x2909F97BADC66856
    .quad  0x6FE5D541F71C0E1

//**********************************************************************
//  Montgomery reduction
//  Based on the algorithm 7 of "Improved algorithms for the 
//  supersingular isogeny Diffie-Hellman key exchange protocol"
//  Operation: c [reg_p2] = a [reg_p1]
//  NOTE: a=c is not allowed (a is destroyed)
//**********************************************************************
.global REDC
REDC:
 
 push %rbx
 push %r12
 push %r13
 push %r14
 push %r15
 sub $16, %rsp

 // X = p3_239*(reg_p2[0-3]))
 // (multiplication of 6-word by 4-word operands)
 movq    (reg_p2), %rdx
 mulx    (p3_239), %r8 , %r9
 mulx  (p3_239+8), %rax, %r10
 addq        %rax, %r9
 mulx (p3_239+16), %rax, %r11
 adcq        %rax, %r10
 mulx (p3_239+24), %rax, %r12
 adcq        %rax, %r11
 mulx (p3_239+32), %rax, %r13
 adcq        %rax, %r12
 mulx (p3_239+40), %rax, %r14
 adcq        %rax, %r13
 adcq          $0, %r14

 movq         %r8, (%rsp)
 movq   8(reg_p2), %rdx
 xorq        %r15, %r15
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r9
 adox        %rcx, %r10
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r10
 adox        %rcx, %r11
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 adcq          $0, %r15

 movq         %r9, 8(%rsp)
 movq  16(reg_p2), %rdx
 xorq         %r8, %r8
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r10
 adox        %rcx, %r11
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r15
 adox        %rcx, %r8
 adcq          $0, %r8

 movq  24(reg_p2), %rdx
 xorq        %r9 , %r9
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r15
 adox        %rcx, %r8
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r8
 adox        %rcx, %r9
 adcq          $0, %r9

 // X = X << 52
 movq      (%rsp), %rax
 movq     8(%rsp), %rcx
 xorq        %rdx, %rdx
 shld   $52, %r9 , %rdx
 shld   $52, %r8 , %r9
 shld   $52, %r15, %r8
 shld   $52, %r14, %r15
 shld   $52, %r13, %r14
 shld   $52, %r12, %r13
 shld   $52, %r11, %r12
 shld   $52, %r10, %r11
 shld   $52, %rcx, %r10
 shld   $52, %rax, %rcx
 shl          $52, %rax

 // reg_p2[5-16] = X + (reg_p2[5-15])
 addq %rax,  40(reg_p2)
 adcq %rcx,  48(reg_p2)
 adcq %r10,  56(reg_p2)
 adcq %r11,  64(reg_p2)
 adcq %r12,  72(reg_p2)
 adcq %r13,  80(reg_p2)
 adcq %r14,  88(reg_p2)
 adcq %r15,  96(reg_p2)
 adcq  %r8, 104(reg_p2)
 adcq  %r9, 112(reg_p2)
 adcq %rdx, 120(reg_p2)
 adcq   $0, 128(reg_p2)



 // X = p3_239*(reg_p2[4-7])
 // (multiplication of 6-word by 4-word operands)
 movq  32(reg_p2), %rdx
 mulx    (p3_239), %r8 , %r9
 mulx  (p3_239+8), %rax, %r10
 addq        %rax, %r9
 mulx (p3_239+16), %rax, %r11
 adcq        %rax, %r10
 mulx (p3_239+24), %rax, %r12
 adcq        %rax, %r11
 mulx (p3_239+32), %rax, %r13
 adcq        %rax, %r12
 mulx (p3_239+40), %rax, %r14
 adcq        %rax, %r13
 adcq          $0, %r14

 movq         %r8, (%rsp)
 movq  40(reg_p2), %rdx
 xorq        %r15, %r15
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r9
 adox        %rcx, %r10
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r10
 adox        %rcx, %r11
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 adcq          $0, %r15

 movq         %r9, 8(%rsp)
 movq  48(reg_p2), %rdx
 xorq         %r8, %r8
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r10
 adox        %rcx, %r11
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r15
 adox        %rcx, %r8
 adcq          $0, %r8

 movq  56(reg_p2), %rdx
 xorq        %r9 , %r9
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r15
 adox        %rcx, %r8
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r8
 adox        %rcx, %r9
 adcq          $0, %r9

 // X = X << 52
 movq      (%rsp), %rax
 movq     8(%rsp), %rcx
 xorq        %rdx, %rdx
 shld   $52, %r9 , %rdx
 shld   $52, %r8 , %r9
 shld   $52, %r15, %r8
 shld   $52, %r14, %r15
 shld   $52, %r13, %r14
 shld   $52, %r12, %r13
 shld   $52, %r11, %r12
 shld   $52, %r10, %r11
 shld   $52, %rcx, %r10
 shld   $52, %rax, %rcx
 shl          $52, %rax

 // reg_p2[9-20] = X + (reg_p2[9-19])
 addq %rax,  72(reg_p2)
 adcq %rcx,  80(reg_p2)
 adcq %r10,  88(reg_p2)
 adcq 96(reg_p2), %r11
 adcq %r12, 104(reg_p2)
 adcq %r13, 112(reg_p2)
 adcq %r14, 120(reg_p2)
 adcq %r15, 128(reg_p2)
 adcq  %r8, 136(reg_p2)
 adcq  %r9, 144(reg_p2)
 adcq %rdx, 152(reg_p2)
 adcq   $0, 160(reg_p2)


 // X = p3_239*(reg_p2[8-11])
 // (multiplication of 6-word by 4-word operands)
 movq        %r11, (reg_p1)
 movq  64(reg_p2), %rdx
 mulx    (p3_239), %r8 , %r9
 mulx  (p3_239+8), %rax, %r10
 addq        %rax, %r9
 mulx (p3_239+16), %rax, %r11
 adcq        %rax, %r10
 mulx (p3_239+24), %rax, %r12
 adcq        %rax, %r11
 mulx (p3_239+32), %rax, %r13
 adcq        %rax, %r12
 mulx (p3_239+40), %rax, %r14
 adcq        %rax, %r13
 adcq          $0, %r14

 movq         %r8, (%rsp)
 movq  72(reg_p2), %rdx
 xorq        %r15, %r15
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r9
 adox        %rcx, %r10
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r10
 adox        %rcx, %r11
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 adcq          $0, %r15

 movq         %r9, 8(%rsp)
 movq  80(reg_p2), %rdx
 xorq         %r8, %r8
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r10
 adox        %rcx, %r11
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r15
 adox        %rcx, %r8
 adcq          $0, %r8

 movq  88(reg_p2), %rdx
 xorq        %r9 , %r9
 mulx    (p3_239), %rax, %rcx
 adcx        %rax, %r11
 adox        %rcx, %r12
 mulx  (p3_239+8), %rax, %rcx
 adcx        %rax, %r12
 adox        %rcx, %r13
 mulx (p3_239+16), %rax, %rcx
 adcx        %rax, %r13
 adox        %rcx, %r14
 mulx (p3_239+24), %rax, %rcx
 adcx        %rax, %r14
 adox        %rcx, %r15
 mulx (p3_239+32), %rax, %rcx
 adcx        %rax, %r15
 adox        %rcx, %r8
 mulx (p3_239+40), %rax, %rcx
 adcx        %rax, %r8
 adox        %rcx, %r9
 adcq          $0, %r9

 // X = X << 52
 movq      (%rsp), %rax
 movq     8(%rsp), %rcx
 xorq        %rdx, %rdx
 shld   $52, %r9 , %rdx
 shld   $52, %r8 , %r9
 shld   $52, %r15, %r8
 shld   $52, %r14, %r15
 shld   $52, %r13, %r14
 shld   $52, %r12, %r13
 shld   $52, %r11, %r12
 shld   $52, %r10, %r11
 shld   $52, %rcx, %r10
 shld   $52, %rax, %rcx
 shl          $52, %rax

 // reg_p1[0-11] = X + (reg_p1[0-11])
 addq 104(reg_p2), %rax
 adcq 112(reg_p2), %rcx
 adcq 120(reg_p2), %r10
 adcq 128(reg_p2), %r11
 adcq 136(reg_p2), %r12
 adcq 144(reg_p2), %r13
 adcq 152(reg_p2), %r14
 adcq 160(reg_p2), %r15
 adcq 168(reg_p2), %r8
 adcq 176(reg_p2), %r9
 adcq 184(reg_p2), %rdx

 
 movq %rax,  8(reg_p1)
 movq %rcx, 16(reg_p1)
 movq %r10, 24(reg_p1)
 movq %r11, 32(reg_p1)
 movq %r12, 40(reg_p1)
 movq %r13, 48(reg_p1)
 movq %r14, 56(reg_p1)
 movq %r15, 64(reg_p1)
 movq %r8 , 72(reg_p1)
 movq %r9 , 80(reg_p1)
 movq %rdx, 88(reg_p1)


 add $16, %rsp
 pop %r15
 pop %r14
 pop %r13
 pop %r12
 pop %rbx

 ret




