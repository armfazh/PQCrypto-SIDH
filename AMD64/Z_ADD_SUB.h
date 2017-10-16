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
#ifndef _ADDSUB_H_
#define _ADDSUB_H_

/////////////////////////////////////////////////////////
//                    ADDITIONS
////////////////////////////////////////////////////////

// Integer addition of 6-word operands
// c = a + b, the function allows c = c + b when a=c
inline void ADD_6x6(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%1), %%rax\n\t" "addq   (%2), %%rax\n\t" "movq %%rax,   (%0) \n\t"
        "movq  8(%1), %%rbx\n\t" "adcq  8(%2), %%rbx\n\t" "movq %%rbx,  8(%0) \n\t"
        "movq 16(%1), %%rcx\n\t" "adcq 16(%2), %%rcx\n\t" "movq %%rcx, 16(%0) \n\t"
        "movq 24(%1), %%rdx\n\t" "adcq 24(%2), %%rdx\n\t" "movq %%rdx, 24(%0) \n\t"
        "movq 32(%1), %%rsi\n\t" "adcq 32(%2), %%rsi\n\t" "movq %%rsi, 32(%0) \n\t"
        "movq 40(%1), %%rdi\n\t" "adcq 40(%2), %%rdi\n\t" "movq %%rdi, 40(%0) \n\t"
        "movq    $0,  %%r8 \n\t" "adcq     $0, %%r8 \n\t" "movq %%r8 , 48(%0) \n\t"
         :
         : "r"(c), "r" (a), "r"(b)
         : "%rax", "%rbx", "%rcx", "%rdx",
           "%rsi", "%rdi", "%r8", "memory");
}

// Integer addition of a 7-word operand with a 6-word operand
// c = a + 2b, the function allows c = c + 2b when a=c
inline void ADD_7x6_D(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%1), %%rax\n\t" "addq   (%2), %%rax\n\t"
        "movq  8(%1), %%rbx\n\t" "adcq  8(%2), %%rbx\n\t"
        "movq 16(%1), %%rcx\n\t" "adcq 16(%2), %%rcx\n\t"
        "movq 24(%1), %%rdx\n\t" "adcq 24(%2), %%rdx\n\t"
        "movq 32(%1), %%rsi\n\t" "adcq 32(%2), %%rsi\n\t"
        "movq 40(%1), %%rdi\n\t" "adcq 40(%2), %%rdi\n\t"
        "movq 48(%1), %%r8 \n\t" "adcq     $0, %%r8 \n\t"

        "addq   (%2), %%rax\n\t" "movq %%rax,   (%0) \n\t"
        "adcq  8(%2), %%rbx\n\t" "movq %%rbx,  8(%0) \n\t"
        "adcq 16(%2), %%rcx\n\t" "movq %%rcx, 16(%0) \n\t"
        "adcq 24(%2), %%rdx\n\t" "movq %%rdx, 24(%0) \n\t"
        "adcq 32(%2), %%rsi\n\t" "movq %%rsi, 32(%0) \n\t"
        "adcq 40(%2), %%rdi\n\t" "movq %%rdi, 40(%0) \n\t"
        "adcq     $0, %%r8 \n\t" "movq %%r8 , 48(%0) \n\t"
         :
         : "r"(c), "r" (a), "r"(b)
         : "%rax", "%rbx", "%rcx", "%rdx",
           "%rsi", "%rdi", "%r8", "memory");
}

// Integer addition of 12-word operands without carry out
// c = a + b, the function allows c = c + b when a=c
inline void ADD_wco(digit_t* c, const digit_t* a, const  digit_t* b)
{
    __asm__ __volatile__("movq   (%1), %%rax\n\t" "addq   (%2), %%rax\n\t"  "movq %%rax,   (%0)\n\t"
        "movq  8(%1), %%rbx\n\t" "adcq  8(%2), %%rbx\n\t"  "movq %%rbx,  8(%0)\n\t"
        "movq 16(%1), %%rcx\n\t" "adcq 16(%2), %%rcx\n\t"  "movq %%rcx, 16(%0)\n\t"
        "movq 24(%1), %%rdx\n\t" "adcq 24(%2), %%rdx\n\t"  "movq %%rdx, 24(%0)\n\t"
        "movq 32(%1), %%rsi\n\t" "adcq 32(%2), %%rsi\n\t"  "movq %%rsi, 32(%0)\n\t"
        "movq 40(%1), %%rdi\n\t" "adcq 40(%2), %%rdi\n\t"  "movq %%rdi, 40(%0)\n\t" "movq 88(%1), %%rbx \n\t"
        "movq 48(%1), %%r8 \n\t" "adcq 48(%2), %%r8 \n\t"  "movq %%r8 , 48(%0)\n\t"
        "movq 56(%1), %%r9 \n\t" "adcq 56(%2), %%r9 \n\t"  "movq %%r9 , 56(%0)\n\t"
        "movq 64(%1), %%r10\n\t" "adcq 64(%2), %%r10\n\t"  "movq %%r10, 64(%0)\n\t"
        "movq 72(%1), %%r12\n\t" "adcq 72(%2), %%r12\n\t"  "movq %%r12, 72(%0)\n\t"
        "movq 80(%1), %%r13\n\t" "adcq 80(%2), %%r13\n\t"  "movq %%r13, 80(%0)\n\t"
                                 "adcq 88(%2), %%rbx\n\t"  "movq  %%rbx,88(%0)\n\t"
         :
         : "r"(c), "r" (a), "r"(b)
         : "%rax", "%rbx", "%rcx", "%rdx",
           "%rsi", "%rdi", "%r8", "%r9",
           "%r10", "%r12", "%r13", "memory");
}

// Integer addition of a 13-word operand with a 12-word operand
// c = a + 2b, the function allows c = c + 2b when a=c
inline void ADD_13x12_D(digit_t* c, const digit_t* a)
{
    __asm__ __volatile__("xorq  %%r11, %%r11\n\t"
        "movq   (%0), %%rax\n\t"  "addq   (%1), %%rax\n\t"
        "movq  8(%0), %%rbx\n\t"  "adcq  8(%1), %%rbx\n\t"
        "movq 16(%0), %%rcx\n\t"  "adcq 16(%1), %%rcx\n\t"
        "movq 24(%0), %%rdx\n\t"  "adcq 24(%1), %%rdx\n\t"
        "movq 32(%0), %%rsi\n\t"  "adcq 32(%1), %%rsi\n\t"
        "movq 40(%0), %%rdi\n\t"  "adcq 40(%1), %%rdi\n\t"
        "movq 48(%0), %%r8 \n\t"  "adcq 48(%1), %%r8 \n\t"
        "movq 56(%0), %%r9 \n\t"  "adcq 56(%1), %%r9 \n\t"
        "movq 64(%0), %%r10\n\t"  "adcq 64(%1), %%r10\n\t"
        "movq 72(%0), %%r12\n\t"  "adcq 72(%1), %%r12\n\t"
        "movq 80(%0), %%r13\n\t"  "adcq 80(%1), %%r13\n\t"
                                  "adcq     $0, %%r11\n\t"

         "addq   (%1), %%rax\n\t"  "movq %%rax,   (%0)\n\t"
         "adcq  8(%1), %%rbx\n\t"  "movq %%rbx,  8(%0)\n\t"
         "adcq 16(%1), %%rcx\n\t"  "movq %%rcx, 16(%0)\n\t"
         "adcq 24(%1), %%rdx\n\t"  "movq %%rdx, 24(%0)\n\t"
         "adcq 32(%1), %%rsi\n\t"  "movq %%rsi, 32(%0)\n\t"
         "adcq 40(%1), %%rdi\n\t"  "movq %%rdi, 40(%0)\n\t"
         "adcq 48(%1), %%r8 \n\t"  "movq %%r8 , 48(%0)\n\t"
         "adcq 56(%1), %%r9 \n\t"  "movq %%r9 , 56(%0)\n\t"
         "adcq 64(%1), %%r10\n\t"  "movq %%r10, 64(%0)\n\t"
         "adcq 72(%1), %%r12\n\t"  "movq %%r12, 72(%0)\n\t"
         "adcq 80(%1), %%r13\n\t"  "movq %%r13, 80(%0)\n\t"
         "adcq     $0, %%r11\n\t"


         "movq 88(%0), %%rax \n\t" "adcq 88(%1), %%rax \n\t"
         "movq 96(%0), %%rbx \n\t" "adcq     $0, %%rbx \n\t"
                                   "adcq 88(%1), %%rax \n\t"
                                   "adcq     $0, %%rbx \n\t"
         "addq  %%r11, %%rax \n\t"
         "movq  %%rax, 88(%0)\n\t"
         "movq  %%rbx, 96(%0)\n\t"
         :
         : "r"(c), "r" (a)
         : "%rax", "%rbx", "%rcx", "%rdx",
           "%rsi", "%rdi", "%r8", "%r9",
           "%r10", "%r11", "%r12", "%r13", "memory");
}

// Integer addition of a 14-word operand with a 13-word operand
// c = a + 2, the function allows c = c + b when a=c
inline void ADD_14x13(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq    (%1), %%rax\n\t" "addq   (%2), %%rax\n\t" "movq %%rax,   (%0)\n\t"
        "movq   8(%1), %%rbx\n\t" "adcq  8(%2), %%rbx\n\t" "movq %%rbx,  8(%0)\n\t"
        "movq  16(%1), %%rcx\n\t" "adcq 16(%2), %%rcx\n\t" "movq %%rcx, 16(%0)\n\t"
        "movq  24(%1), %%rdx\n\t" "adcq 24(%2), %%rdx\n\t" "movq %%rdx, 24(%0)\n\t"
        "movq  32(%1), %%rsi\n\t" "adcq 32(%2), %%rsi\n\t" "movq %%rsi, 32(%0)\n\t"
        "movq  40(%1), %%rdi\n\t" "adcq 40(%2), %%rdi\n\t" "movq %%rdi, 40(%0)\n\t"
        "movq  48(%1), %%r8 \n\t" "adcq 48(%2), %%r8 \n\t" "movq %%r8 , 48(%0)\n\t"
        "movq  56(%1), %%r9 \n\t" "adcq 56(%2), %%r9 \n\t" "movq %%r9 , 56(%0)\n\t"
        "movq  64(%1), %%r10\n\t" "adcq 64(%2), %%r10\n\t" "movq %%r10, 64(%0)\n\t"
        "movq  72(%1), %%r12\n\t" "adcq 72(%2), %%r12\n\t" "movq %%r12, 72(%0)\n\t"
        "movq  80(%1), %%r13\n\t" "adcq 80(%2), %%r13\n\t" "movq %%r13, 80(%0)\n\t"
        "movq  88(%1), %%rax\n\t" "adcq 88(%2), %%rax\n\t" "movq %%rax, 88(%0)\n\t"
        "movq  96(%1), %%rbx\n\t" "adcq 96(%2), %%rbx\n\t" "movq %%rbx, 96(%0)\n\t"
        "movq 104(%1), %%rcx\n\t" "adcq     $0, %%rcx\n\t" "movq %%rcx,104(%0)\n\t"
          
         :            \
         : "r"(c), "r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r10", "%r12", "%r13", "memory");
}

/*
// Integer addition of 24-word operands without carry out
// c = a + b, the function allows c = c + 2b when a=c
inline void ADD_24x24_wco(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq    (%1), %%rax\n\t" "addq    (%2), %%rax\n\t" "movq %%rax,    (%0)\n\t"
        "movq   8(%1), %%rbx\n\t" "adcq   8(%2), %%rbx\n\t" "movq %%rbx,   8(%0)\n\t"
        "movq  16(%1), %%rcx\n\t" "adcq  16(%2), %%rcx\n\t" "movq %%rcx,  16(%0)\n\t"
        "movq  24(%1), %%rdx\n\t" "adcq  24(%2), %%rdx\n\t" "movq %%rdx,  24(%0)\n\t"
        "movq  32(%1), %%rsi\n\t" "adcq  32(%2), %%rsi\n\t" "movq %%rsi,  32(%0)\n\t"
        "movq  40(%1), %%rdi\n\t" "adcq  40(%2), %%rdi\n\t" "movq %%rdi,  40(%0)\n\t"
        "movq  48(%1), %%r8 \n\t" "adcq  48(%2), %%r8 \n\t" "movq %%r8 ,  48(%0)\n\t"
        "movq  56(%1), %%r9 \n\t" "adcq  56(%2), %%r9 \n\t" "movq %%r9 ,  56(%0)\n\t"
        "movq  64(%1), %%r10\n\t" "adcq  64(%2), %%r10\n\t" "movq %%r10,  64(%0)\n\t"
        "movq  72(%1), %%r12\n\t" "adcq  72(%2), %%r12\n\t" "movq %%r12,  72(%0)\n\t"
        "movq  80(%1), %%r13\n\t" "adcq  80(%2), %%r13\n\t" "movq %%r13,  80(%0)\n\t"
        "movq  88(%1), %%rax\n\t" "adcq  88(%2), %%rax\n\t" "movq %%rax,  88(%0)\n\t"
        "movq  96(%1), %%rbx\n\t" "adcq  96(%2), %%rbx\n\t" "movq %%rbx,  96(%0)\n\t"
        "movq 104(%1), %%rcx\n\t" "adcq 104(%2), %%rcx\n\t" "movq %%rcx, 104(%0)\n\t"
        "movq 112(%1), %%rdx\n\t" "adcq 112(%2), %%rdx\n\t" "movq %%rdx, 112(%0)\n\t"
        "movq 120(%1), %%rsi\n\t" "adcq 120(%2), %%rsi\n\t" "movq %%rsi, 120(%0)\n\t"
        "movq 128(%1), %%rdi\n\t" "adcq 128(%2), %%rdi\n\t" "movq %%rdi, 128(%0)\n\t"
        "movq 136(%1), %%r8 \n\t" "adcq 136(%2), %%r8 \n\t" "movq %%r8 , 136(%0)\n\t"
        "movq 144(%1), %%r9 \n\t" "adcq 144(%2), %%r9 \n\t" "movq %%r9 , 144(%0)\n\t"
        "movq 152(%1), %%r10\n\t" "adcq 152(%2), %%r10\n\t" "movq %%r10, 152(%0)\n\t"
        "movq 160(%1), %%r12\n\t" "adcq 160(%2), %%r12\n\t" "movq %%r12, 160(%0)\n\t"
        "movq 168(%1), %%r13\n\t" "adcq 168(%2), %%r13\n\t" "movq %%r13, 168(%0)\n\t"
        "movq 176(%1), %%rax\n\t" "adcq 176(%2), %%rax\n\t" "movq %%rax, 176(%0)\n\t"
        "movq 184(%1), %%rbx\n\t" "adcq 184(%2), %%rbx\n\t" "movq %%rbx, 184(%0)\n\t"
         :
         : "r"(c),"r" (a), "r"(b)
         : "%rax", "%rbx", "%rcx", "%rdx",
           "%rsi", "%rdi", "%r8", "%r9",
           "%r10", "%r12", "%r13", "memory");
}
*/

/////////////////////////////////////////////////////////
//                  SUBTRACTIONS
/////////////////////////////////////////////////////////

// Integer subtraction without carry out
// c = c-a-b; with c > (a+b)
// and |a|= 24 words, |b|= 24 words and |c|=24 words
inline void SUB_D_24x24_woc(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%0), %%rax\n\t \
         movq  8(%0), %%rbx\n\t \
         movq 16(%0), %%rcx\n\t \
         movq 24(%0), %%rdx\n\t \
         movq 32(%0), %%rsi\n\t \
         movq 40(%0), %%rdi\n\t \
         movq 48(%0), %%r8 \n\t \
         movq 56(%0), %%r9 \n\t \
         movq 64(%0), %%r10\n\t \
         movq 72(%0), %%r12\n\t \
         movq     $0, %%r13\n\t \
         \
         subq   (%1), %%rax\n\t \
         sbbq  8(%1), %%rbx\n\t \
         sbbq 16(%1), %%rcx\n\t \
         sbbq 24(%1), %%rdx\n\t \
         sbbq 32(%1), %%rsi\n\t \
         sbbq 40(%1), %%rdi\n\t \
         sbbq 48(%1), %%r8 \n\t \
         sbbq 56(%1), %%r9 \n\t \
         sbbq 64(%1), %%r10\n\t \
         sbbq 72(%1), %%r12\n\t \
         adcq     $0, %%r13\n\t \
         subq   (%2), %%rax\n\t \
         sbbq  8(%2), %%rbx\n\t \
         sbbq 16(%2), %%rcx\n\t \
         sbbq 24(%2), %%rdx\n\t \
         sbbq 32(%2), %%rsi\n\t \
         sbbq 40(%2), %%rdi\n\t \
         sbbq 48(%2), %%r8 \n\t \
         sbbq 56(%2), %%r9 \n\t \
         sbbq 64(%2), %%r10\n\t \
         sbbq 72(%2), %%r12\n\t \
         adcq     $0, %%r13\n\t \
         \
         movq %%rax,   (%0)\n\t \
         movq %%rbx,  8(%0)\n\t \
         movq %%rcx,  16(%0)\n\t \
         movq %%rdx,  24(%0)\n\t \
         movq %%rsi,  32(%0)\n\t \
         movq %%rdi,  40(%0)\n\t \
         movq %%r8 ,  48(%0)\n\t \
         movq %%r9 ,  56(%0)\n\t \
         movq %%r10,  64(%0)\n\t \
         movq %%r12,  72(%0)\n\t \
         \
         movq  80(%0), %%rax\n\t \
         movq  88(%0), %%rbx\n\t \
         movq  96(%0), %%rcx\n\t \
         movq 104(%0), %%rdx\n\t \
         movq 112(%0), %%rsi\n\t \
         movq 120(%0), %%rdi\n\t \
         movq 128(%0), %%r8 \n\t \
         movq 136(%0), %%r9 \n\t \
         movq 144(%0), %%r10\n\t \
         movq 152(%0), %%r12\n\t \
         \
         subq   %%r13, %%rax\n\t \
         movq      $0, %%r13\n\t \
         sbbq  80(%1), %%rax\n\t \
         sbbq  88(%1), %%rbx\n\t \
         sbbq  96(%1), %%rcx\n\t \
         sbbq 104(%1), %%rdx\n\t \
         sbbq 112(%1), %%rsi\n\t \
         sbbq 120(%1), %%rdi\n\t \
         sbbq 128(%1), %%r8 \n\t \
         sbbq 136(%1), %%r9 \n\t \
         sbbq 144(%1), %%r10\n\t \
         sbbq 152(%1), %%r12\n\t \
         adcq      $0, %%r13\n\t \
         subq  80(%2), %%rax\n\t \
         sbbq  88(%2), %%rbx\n\t \
         sbbq  96(%2), %%rcx\n\t \
         sbbq 104(%2), %%rdx\n\t \
         sbbq 112(%2), %%rsi\n\t \
         sbbq 120(%2), %%rdi\n\t \
         sbbq 128(%2), %%r8 \n\t \
         sbbq 136(%2), %%r9 \n\t \
         sbbq 144(%2), %%r10\n\t \
         sbbq 152(%2), %%r12\n\t \
         adcq      $0, %%r13\n\t \
         \
         movq %%rax,  80(%0)\n\t \
         movq %%rbx,  88(%0)\n\t \
         movq %%rcx,  96(%0)\n\t \
         movq %%rdx, 104(%0)\n\t \
         movq %%rsi, 112(%0)\n\t \
         movq %%rdi, 120(%0)\n\t \
         movq %%r8 , 128(%0)\n\t \
         movq %%r9 , 136(%0)\n\t \
         movq %%r10, 144(%0)\n\t \
         movq %%r12, 152(%0)\n\t \
         \
         movq 160(%0), %%rax\n\t \
         movq 168(%0), %%rbx\n\t \
         movq 176(%0), %%rcx\n\t \
         movq 184(%0), %%rdx\n\t \
         \
         subq   %%r13, %%rax\n\t \
         sbbq 160(%1), %%rax\n\t \
         sbbq 168(%1), %%rbx\n\t \
         sbbq 176(%1), %%rcx\n\t \
         sbbq 184(%1), %%rdx\n\t \
         subq 160(%2), %%rax\n\t \
         sbbq 168(%2), %%rbx\n\t \
         sbbq 176(%2), %%rcx\n\t \
         sbbq 184(%2), %%rdx\n\t \
         \
         movq %%rax, 160(%0)\n\t \
         movq %%rbx, 168(%0)\n\t \
         movq %%rcx, 176(%0)\n\t \
         movq %%rdx, 184(%0)\n\t \
         "\
         :            \
         : "r"(c), "r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r10", "%r12", "%r13", "memory");
}

// Integer subtraction without carry out
// c = a-b
inline void SUB_24x24(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%1), %%rax\n\t \
         movq  8(%1), %%rbx\n\t \
         movq 16(%1), %%rcx\n\t \
         movq 24(%1), %%rdx\n\t \
         movq 32(%1), %%rsi\n\t \
         movq 40(%1), %%rdi\n\t \
         movq 48(%1), %%r8 \n\t \
         movq 56(%1), %%r9 \n\t \
         movq 64(%1), %%r10\n\t \
         movq 72(%1), %%r12\n\t \
         movq 80(%1), %%r13\n\t \
         \
         subq   (%2), %%rax\n\t \
         sbbq  8(%2), %%rbx\n\t \
         sbbq 16(%2), %%rcx\n\t \
         sbbq 24(%2), %%rdx\n\t \
         sbbq 32(%2), %%rsi\n\t \
         sbbq 40(%2), %%rdi\n\t \
         sbbq 48(%2), %%r8 \n\t \
         sbbq 56(%2), %%r9 \n\t \
         sbbq 64(%2), %%r10\n\t \
         sbbq 72(%2), %%r12\n\t \
         sbbq 80(%2), %%r13\n\t \
         \
         movq %%rax,   (%0)\n\t \
         movq %%rbx,  8(%0)\n\t \
         movq %%rcx, 16(%0)\n\t \
         movq %%rdx, 24(%0)\n\t \
         movq %%rsi, 32(%0)\n\t \
         movq %%rdi, 40(%0)\n\t \
         movq %%r8 , 48(%0)\n\t \
         movq %%r9 , 56(%0)\n\t \
         movq %%r10, 64(%0)\n\t \
         movq %%r12, 72(%0)\n\t \
         movq %%r13, 80(%0)\n\t \
         \
         movq  88(%1), %%rax\n\t \
         movq  96(%1), %%rbx\n\t \
         movq 104(%1), %%rcx\n\t \
         movq 112(%1), %%rdx\n\t \
         movq 120(%1), %%rsi\n\t \
         movq 128(%1), %%rdi\n\t \
         movq 136(%1), %%r8 \n\t \
         movq 144(%1), %%r9 \n\t \
         movq 152(%1), %%r10\n\t \
         movq 160(%1), %%r12\n\t \
         movq 168(%1), %%r13\n\t \
         \
         sbbq  88(%2), %%rax\n\t \
         sbbq  96(%2), %%rbx\n\t \
         sbbq 104(%2), %%rcx\n\t \
         sbbq 112(%2), %%rdx\n\t \
         sbbq 120(%2), %%rsi\n\t \
         sbbq 128(%2), %%rdi\n\t \
         sbbq 136(%2), %%r8 \n\t \
         sbbq 144(%2), %%r9 \n\t \
         sbbq 152(%2), %%r10\n\t \
         sbbq 160(%2), %%r12\n\t \
         sbbq 168(%2), %%r13\n\t \
         \
         movq %%rax,  88(%0)\n\t \
         movq %%rbx,  96(%0)\n\t \
         movq %%rcx, 104(%0)\n\t \
         movq %%rdx, 112(%0)\n\t \
         movq %%rsi, 120(%0)\n\t \
         movq %%rdi, 128(%0)\n\t \
         movq %%r8 , 136(%0)\n\t \
         movq %%r9 , 144(%0)\n\t \
         movq %%r10, 152(%0)\n\t \
         movq %%r12, 160(%0)\n\t \
         movq %%r13, 168(%0)\n\t \
         \
         movq 176(%1), %%rax\n\t \
         movq 184(%1), %%rbx\n\t \
         sbbq 176(%2), %%rax\n\t \
         sbbq 184(%2), %%rbx\n\t \
         movq %%rax, 176(%0)\n\t \
         movq %%rbx, 184(%0)\n\t \
         "\
         :            \
         : "r"(c),"r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r10", "%r12", "%r13", "memory");
}

// Integer subtraction without carry out
// c = c-a-b; with c > (a+b) 
// and |a|= 12 words, |b|= 12 words and |c|=13 words
inline void SUB_D_13x12_woc(digit_t* c, const digit_t* a, const digit_t* b)
{
    __asm__ __volatile__("movq   (%0), %%rax\n\t \
         movq  8(%0), %%rbx\n\t \
         movq 16(%0), %%rcx\n\t \
         movq 24(%0), %%rdx\n\t \
         movq 32(%0), %%rsi\n\t \
         movq 40(%0), %%rdi\n\t \
         movq 48(%0), %%r8 \n\t \
         movq 56(%0), %%r9 \n\t \
         movq 64(%0), %%r10\n\t \
         movq 72(%0), %%r12\n\t \
         movq 80(%0), %%r13\n\t \
         \
         subq   (%1), %%rax\n\t \
         sbbq     $0, %%rbx\n\t \
         subq   (%2), %%rax\n\t \
         sbbq  8(%1), %%rbx\n\t \
         sbbq     $0, %%rcx\n\t \
         subq  8(%2), %%rbx\n\t \
         sbbq 16(%1), %%rcx\n\t \
         sbbq     $0, %%rdx\n\t \
         subq 16(%2), %%rcx\n\t \
         sbbq 24(%1), %%rdx\n\t \
         sbbq     $0, %%rsi\n\t \
         subq 24(%2), %%rdx\n\t \
         sbbq 32(%1), %%rsi\n\t \
         sbbq     $0, %%rdi\n\t \
         subq 32(%2), %%rsi\n\t \
         sbbq 40(%1), %%rdi\n\t \
         sbbq     $0, %%r8 \n\t \
         subq 40(%2), %%rdi\n\t \
         sbbq 48(%1), %%r8 \n\t \
         sbbq     $0, %%r9 \n\t \
         subq 48(%2), %%r8 \n\t \
         sbbq 56(%1), %%r9 \n\t \
         sbbq     $0, %%r10\n\t \
         subq 56(%2), %%r9 \n\t \
         sbbq 64(%1), %%r10\n\t \
         sbbq     $0, %%r12\n\t \
         subq 64(%2), %%r10\n\t \
         sbbq 72(%1), %%r12\n\t \
         sbbq     $0, %%r13\n\t \
         subq 72(%2), %%r12\n\t \
         \
         movq %%rax,    (%0)\n\t \
         movq %%rbx,   8(%0)\n\t \
         movq %%rcx,  16(%0)\n\t \
         movq %%rdx,  24(%0)\n\t \
         movq %%rsi,  32(%0)\n\t \
         movq %%rdi,  40(%0)\n\t \
         movq %%r8 ,  48(%0)\n\t \
         movq %%r9 ,  56(%0)\n\t \
         movq %%r10,  64(%0)\n\t \
         movq %%r12,  72(%0)\n\t \
         \
         movq  88(%0), %%rax\n\t \
         movq  96(%0), %%rbx\n\t \
         \
         sbbq  80(%1), %%r13\n\t \
         sbbq      $0, %%rax\n\t \
         subq  80(%2), %%r13\n\t \
         sbbq  88(%1), %%rax\n\t \
         sbbq      $0, %%rbx\n\t \
         subq  88(%2), %%rax\n\t \
         sbbq      $0, %%rbx\n\t \
         \
         movq %%r13,  80(%0)\n\t \
         movq %%rax,  88(%0)\n\t \
         movq %%rbx,  96(%0)\n\t \
         "\
         :            \
         : "r"(c), "r" (a), "r"(b)     \
         : "%rax", "%rbx", "%rcx", "%rdx", \
           "%rsi", "%rdi", "%r8", "%r9",   \
           "%r10", "%r12", "%r13", "memory");
}

#endif
