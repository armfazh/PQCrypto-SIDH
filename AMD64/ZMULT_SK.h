/********************************************************************************************
 * Copyright (c) Sept,2017 Ochoa-Jiménez
 * Computer Science Department
 * CINVESTAV-IPN. Mexico.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
********************************************************************************************/
#ifndef _MULT_H_
#define _MULT_H_

#include "./Z_ADD_SUB.h"

extern const uint64_t p751p1[NWORDS_FIELD];
extern const uint64_t p751[NWORDS_FIELD];

const uint64_t zero[NWORDS_FIELD]   = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

extern void REDC(digit_t* c, const digit_t* a);

// Schoolbook integer multiplication of 3-word operands
// c = a*b
void MULT_3x3(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%2), %%rdx       \n\t \
         mulx   (%1), %%r12, %%r13\n\t \
         mulx  8(%1), %%rax, %%rsi\n\t \
         addq  %%rax, %%r13       \n\t \
         mulx 16(%1), %%rax, %%rdi\n\t \
         adcq  %%rax, %%rsi       \n\t \
         adcq     $0, %%rdi       \n\t \
         \
         xorq  %%r8 , %%r8        \n\t \
         movq  8(%2), %%rdx       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         adcq     $0, %%r8        \n\t \
         \
         xorq  %%r9 , %%r9        \n\t \
         movq 16(%2), %%rdx       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         adcq     $0, %%r9        \n\t \
         \
         movq %%r12,    (%0)      \n\t \
         movq %%r13,   8(%0)      \n\t \
         movq %%rsi,  16(%0)      \n\t \
         movq %%rdi,  24(%0)      \n\t \
         movq %%r8 ,  32(%0)      \n\t \
         movq %%r9 ,  40(%0)      \n\t \
         "\
         :                             \
         : "r"(c), "r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r12", "%r13", "memory");
}

// Schoolbook integer multiplication of 6-word operands
// c = a*b
void MULT_6x6(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%2), %%rdx       \n\t \
         mulx   (%1), %%r12, %%r13\n\t \
         mulx  8(%1), %%rax, %%rsi\n\t \
         addq  %%rax, %%r13       \n\t \
         mulx 16(%1), %%rax, %%rdi\n\t \
         adcq  %%rax, %%rsi       \n\t \
         mulx 24(%1), %%rax,  %%r8\n\t \
         adcq  %%rax, %%rdi       \n\t \
         mulx 32(%1), %%rax,  %%r9\n\t \
         adcq  %%rax, %%r8        \n\t \
         mulx 40(%1), %%rax, %%r10\n\t \
         adcq  %%rax, %%r9        \n\t \
         adcq     $0, %%r10       \n\t \
         \
         movq  8(%2), %%rdx       \n\t \
         xorq  %%rcx, %%rcx       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         adcq     $0, %%rcx       \n\t \
         \
         movq  %%r12,  (%0)       \n\t \
         movq  %%r13, 8(%0)       \n\t \
         movq 16(%2), %%rdx       \n\t \
         xorq  %%r12, %%r12       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rcx       \n\t \
         adox  %%rbx, %%r12       \n\t \
         adcq     $0, %%r12       \n\t \
         \
         movq 24(%2),  %%rdx       \n\t \
         xorq  %%r13,  %%r13       \n\t \
         mulx   (%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%rdi       \n\t \
         adox  %%rbx,  %%r8        \n\t \
         mulx  8(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r8        \n\t \
         adox  %%rbx,  %%r9        \n\t \
         mulx 16(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r9        \n\t \
         adox  %%rbx,  %%r10       \n\t \
         mulx 24(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r10       \n\t \
         adox  %%rbx,  %%rcx       \n\t \
         mulx 32(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%rcx       \n\t \
         adox  %%rbx,  %%r12       \n\t \
         mulx 40(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r12       \n\t \
         adox  %%rbx,  %%r13       \n\t \
         adcq     $0,  %%r13       \n\t \
         \
         movq  %%rsi,  16(%0)      \n\t \
         movq  %%rdi,  24(%0)      \n\t \
         movq 32(%2),  %%rdx       \n\t \
         xorq  %%rsi,  %%rsi       \n\t \
         mulx   (%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r8        \n\t \
         adox  %%rbx,  %%r9        \n\t \
         mulx  8(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r9        \n\t \
         adox  %%rbx,  %%r10       \n\t \
         mulx 16(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r10       \n\t \
         adox  %%rbx,  %%rcx       \n\t \
         mulx 24(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%rcx       \n\t \
         adox  %%rbx,  %%r12       \n\t \
         mulx 32(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r12       \n\t \
         adox  %%rbx,  %%r13       \n\t \
         mulx 40(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r13       \n\t \
         adox  %%rbx,  %%rsi       \n\t \
         adcq     $0,  %%rsi       \n\t \
         \
         movq 40(%2),  %%rdx       \n\t \
         xorq  %%rdi,  %%rdi       \n\t \
         mulx   (%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r9        \n\t \
         adox  %%rbx,  %%r10       \n\t \
         mulx  8(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r10       \n\t \
         adox  %%rbx,  %%rcx       \n\t \
         mulx 16(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%rcx       \n\t \
         adox  %%rbx,  %%r12       \n\t \
         mulx 24(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r12       \n\t \
         adox  %%rbx,  %%r13       \n\t \
         mulx 32(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%r13       \n\t \
         adox  %%rbx,  %%rsi       \n\t \
         mulx 40(%1),  %%rax, %%rbx\n\t \
         adcx  %%rax,  %%rsi       \n\t \
         adox  %%rbx,  %%rdi       \n\t \
         adcq     $0,  %%rdi       \n\t \
         \
         movq  %%r8,  32(%0) \n\t \
         movq  %%r9,  40(%0) \n\t \
         movq %%r10,  48(%0) \n\t \
         movq %%rcx,  56(%0) \n\t \
         movq %%r12,  64(%0) \n\t \
         movq %%r13,  72(%0) \n\t \
         movq %%rsi,  80(%0) \n\t \
         movq %%rdi,  88(%0) \n\t \
         "\
         :                             \
         : "r"(c), "r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r10", "%r12", "%r13", "memory");
}

// Schoolbook integer multiplication of 7-word operands
// c = a*b
void MULT_7x7(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%2), %%rdx       \n\t \
         mulx   (%1), %%r12, %%rcx\n\t \
         mulx  8(%1), %%rax, %%rsi\n\t \
         addq  %%rax, %%rcx       \n\t \
         mulx 16(%1), %%rax, %%rdi\n\t \
         adcq  %%rax, %%rsi       \n\t \
         mulx 24(%1), %%rax,  %%r8\n\t \
         adcq  %%rax, %%rdi       \n\t \
         mulx 32(%1), %%rax,  %%r9\n\t \
         adcq  %%rax, %%r8        \n\t \
         mulx 40(%1), %%rax, %%r10\n\t \
         adcq  %%rax, %%r9        \n\t \
         mulx 48(%1), %%rax, %%r13\n\t \
         adcq  %%rax, %%r10       \n\t \
         adcq     $0, %%r13       \n\t \
         \
         movq  %%r12,  (%0)       \n\t \
         movq  8(%2), %%rdx       \n\t \
	     xorq  %%r12, %%r12       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rcx       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%r13       \n\t \
         mulx 48(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%r12       \n\t \
         adcq     $0, %%r12       \n\t \
         \
         movq  %%rcx, 8(%0)       \n\t \
         movq 16(%2), %%rdx       \n\t \
	     xorq  %%rcx, %%rcx       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%r13       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%r12       \n\t \
         mulx 48(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r12       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         adcq     $0, %%rcx       \n\t \
         \
         movq  %%rsi, 16(%0)      \n\t \
         movq 24(%2), %%rdx       \n\t \
	     xorq  %%rsi, %%rsi       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%r13       \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%r12       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r12       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         mulx 48(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rcx       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         adcq     $0, %%rsi       \n\t \
         \
         movq  %%rdi, 24(%0)      \n\t \
         movq 32(%2), %%rdx       \n\t \
	     xorq  %%rdi, %%rdi       \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%r13       \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%r12       \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r12       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rcx       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         mulx 48(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         adcq     $0, %%rdi       \n\t \
         \
         movq  %%r8 , 32(%0)      \n\t \
         movq 40(%2), %%rdx       \n\t \
	     xorq   %%r8, %%r8        \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r9        \n\t \
         adox  %%rbx, %%r10       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%r13       \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%r12       \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r12       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rcx       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx 48(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         adcq     $0, %%r8        \n\t \
         \
         movq  %%r9 , 40(%0)      \n\t \
         movq 48(%2), %%rdx       \n\t \
	     xorq   %%r9, %%r9        \n\t \
         mulx   (%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r10       \n\t \
         adox  %%rbx, %%r13       \n\t \
         mulx  8(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r13       \n\t \
         adox  %%rbx, %%r12       \n\t \
         mulx 16(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r12       \n\t \
         adox  %%rbx, %%rcx       \n\t \
         mulx 24(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rcx       \n\t \
         adox  %%rbx, %%rsi       \n\t \
         mulx 32(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rsi       \n\t \
         adox  %%rbx, %%rdi       \n\t \
         mulx 40(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%rdi       \n\t \
         adox  %%rbx, %%r8        \n\t \
         mulx 48(%1), %%rax, %%rbx\n\t \
         adcx  %%rax, %%r8        \n\t \
         adox  %%rbx, %%r9        \n\t \
         adcq     $0, %%r9        \n\t \
         \
         movq %%r10,  48(%0) \n\t \
         movq %%r13,  56(%0) \n\t \
         movq %%r12,  64(%0) \n\t \
         movq %%rcx,  72(%0) \n\t \
         movq %%rsi,  80(%0) \n\t \
         movq %%rdi,  88(%0) \n\t \
         movq  %%r8,  96(%0) \n\t \
         movq  %%r9, 104(%0) \n\t \
         "\
         :                             \
         : "r"(c), "r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r10", "%r12", "%r13", "memory");
}

// Schoolbook integer squaring of 3-word operands
// c = a^2
void SQR_3x3(digit_t* c, const digit_t* a)
{
    __asm__ __volatile__("movq   (%1), %%rdx        \n\t \
         mulx  %%rdx, %%rbx, %%rcx \n\t \
         mulx  8(%1), %%rax, %%rsi \n\t \
         mulx 16(%1), %%r9, %%r10  \n\t \
         movq  8(%1), %%rdx        \n\t \
         mulx  %%rdx, %%r8, %%rdi  \n\t \
         mulx 16(%1), %%r11, %%r12 \n\t \
         movq 16(%1), %%rdx        \n\t \
         mulx  %%rdx, %%r13, %%rdx \n\t \
         \
         addq  %%rax, %%rcx        \n\t \
         adcq  %%rsi, %%r8         \n\t \
         adcq  %%r10, %%rdi        \n\t \
         adcq  %%r12, %%r13        \n\t \
         adcq     $0, %%rdx        \n\t \
         addq   %%r9, %%r8         \n\t \
         adcq  %%r11, %%rdi        \n\t \
         adcq     $0, %%r13        \n\t \
         addq  %%rax, %%rcx        \n\t \
         adcq  %%rsi, %%r8         \n\t \
         adcq  %%r10, %%rdi        \n\t \
         adcq  %%r12, %%r13        \n\t \
         adcq     $0, %%rdx        \n\t \
         addq   %%r9, %%r8         \n\t \
         adcq  %%r11, %%rdi        \n\t \
         adcq     $0, %%r13        \n\t \
         \
         movq  %%rbx,   (%0)       \n\t \
         movq  %%rcx,  8(%0)       \n\t \
         movq  %%r8 , 16(%0)       \n\t \
         movq  %%rdi, 24(%0)       \n\t \
         movq  %%r13, 32(%0)       \n\t \
         movq  %%rdx, 40(%0)       \n\t \
         "\
         :                             \
         : "r"(c), "r" (a)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9", "%r11",   \
           "%r10", "%r12", "%r13", "memory");
}

// One-level Karatsuba integer multiplication of 12-word operands
// c = a*b
void MULT(digit_t* c, const digit_t* a, const digit_t* b)
{
    digit_t aux[14];
    digit_t aux1[14];

    ADD_6x6(aux, a, &a[6]);
    ADD_6x6(&aux[7], b, &b[6]);

    MULT_6x6(c, a, b);
    MULT_7x7(aux1, &aux[7], aux);
    MULT_6x6(&c[12], &a[6], &b[6]);

    SUB_D_13x12_woc(aux1, c, &c[12]);
    ADD_14x13(&c[6], &c[6], aux1);
}

// One-level Karatsuba integer squaring of 6-word operands
// c = a^2
void SQR_6x6(digit_t* c, const digit_t* a)
{
    digit_t aux[6];

    SQR_3x3(c, a);
    MULT_3x3(aux, a, &a[3]);
    SQR_3x3(&c[6], &a[3]);

    ADD_7x6_D(&c[3], &c[3], aux);
}

// One-level Karatsuba integer squaring of 12-word operands
// c = a^2
void SQR(digit_t* c, const digit_t* a)
{
    digit_t aux[12];

    SQR_6x6(c, a);
    MULT_6x6(aux, a, &a[6]);
    SQR_6x6(&c[12], &a[6]);

    ADD_13x12_D(&c[6], aux);
}

// Multiplication in Fp2
// c = a*b
void Mult_Fp2(f2elm_t c, const f2elm_t a, const f2elm_t b)
{
    dfelm_t d0, d1, d2;
    felm_t c0, c1;

    ADD_wco(c0, a[0], a[1]);
    ADD_wco(c1, b[0], b[1]);

    MULT(d0, c0, c1);
    MULT(d1, a[0], b[0]);
    MULT(d2, a[1], b[1]);

    //d0 = d0-d1-d2
    SUB_D_24x24_woc(d0, d1, d2);
    SUB_24x24(d1, d1, d2);

    if (0xF000000000000000 & d1[23])
        ADD_wco(&d1[12], &d1[12], p751);
    else
        ADD_wco(&d1[12], &d1[12], zero);

    REDC(c[0], d1);
    REDC(c[1], d0);
}

/*
// Squaring in Fp2
// c = a^2
void Sqr_Fp2(f2elm_t c, const f2elm_t a)
{
    dfelm_t d0, d1, d2;

    SQR(d0, a[0]);
    SQR(d1, a[1]);
    MULT(d2, a[0], a[1]);
    
    SUB_24x24(d0, d0, d1);
    ADD_24x24_wco(d1, d2, d2);
    
    if (0xF000000000000000 & d0[23])
        ADD_wco(&d0[12], &d0[12], p751);
    else
        ADD_wco(&d0[12], &d0[12], zero);

    REDC(c[0], d0);
    REDC(c[1], d1);
}
*/
#endif

