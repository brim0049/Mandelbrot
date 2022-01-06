        .file	"complex.cpp"
        .intel_syntax noprefix
        .text
        .align 2
        .p2align 4
        .globl	_ZNK7complexplERKS_
        .type	_ZNK7complexplERKS_, @function
_ZNK7complexplERKS_:
.LFB267:
        .cfi_startproc
        endbr64

        ## rdi: ou stocker le resultat 
        ## rsi: this
        ## rdx: other

        ## movd : move dword (32)
        ## movq : move qword (64)
	
	##monsieur Steven ca fonctiooon XD!!!! 
	#ma colonne vertébrale hahaha -c 0.7790-i0.1175 -s 0.001
	movq xmm0,[rsi]
	movq xmm1,[rdx]
	addps xmm0,xmm1
	movq [rdi], xmm0
        ret
        
        .cfi_endproc
.LFE267:
        .size	_ZNK7complexplERKS_, .-_ZNK7complexplERKS_
        .align 2
        .p2align 4
        .globl	_ZNK7complexmlERKS_
        .type	_ZNK7complexmlERKS_, @function
_ZNK7complexmlERKS_:
.LFB268:
        .cfi_startproc
        endbr64

        ## rdi: où stocker le resultat
        ## rsi: this
        ## rdx: other

	movq 	xmm0, [rsi] 		#b,a
	shufps  xmm0, xmm0, 0xe0 	#a,a
	movq	xmm1, [rdx] 		#d,c
	mulps	xmm1, xmm0 		#ad, ac
	movq 	xmm0, [rsi]		#b,a
	shufps  xmm0, xmm0, 0xe5	#b,b
	movq	xmm2, [rdx] 		#d,c
	mulps	xmm0, xmm2		#db,cb
	shufps  xmm0, xmm0, 0xe1	#cb,bd
	addsubps xmm1, xmm0		#ad+bc,ac-bd
	movq	[rdi], xmm1
        ret
        
        .cfi_endproc
.LFE268:
        .size	_ZNK7complexmlERKS_, .-_ZNK7complexmlERKS_
        .align 2
        .p2align 4
        .globl	_ZNK7complex3absEv
        .type	_ZNK7complex3absEv, @function
_ZNK7complex3absEv:
.LFB269:
        .cfi_startproc
        endbr64

        ## rdi: this
        
        movq xmm0, [rdi]
        dpps xmm0, xmm0, 0x31		#get 0011 set result 0001 
        sqrtss xmm0,xmm0
        ret
        #code1
	#movss	xmm0, DWORD PTR [rdi]	#a
	#mulss  xmm0, xmm0	#a*a
	#movss	xmm1, DWORD PTR 4[rdi]
	#mulss  xmm1, xmm1	#b*b
 	#addss	xmm0, xmm1	#z=a*a+b*b
	#sqrtss xmm0, xmm0 	#sqrt z
	
        #code 2			
	#movq xmm0, [rdi]
	#mulps xmm0,xmm0 		##a**2, b**2
	#shufps xmm1, xmm0, 0x1E	#b**2 a**2
	#addss xmm0,xmm1		a**2+b**2
	#sqrtss xmm0, xmm0 
	
	#code 3
	#movq xmm0, [rdi]
	#mulps xmm0,xmm0 		##a**2, b**2	
	#haddps xmm0,xmm0		a**2+b**2
	#sqrtss xmm0, xmm0 

        
        .cfi_endproc
.LFE269:
        .size	_ZNK7complex3absEv, .-_ZNK7complex3absEv
        .ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
        .section	.note.GNU-stack,"",@progbits
        .section	.note.gnu.property,"a"
        .align 8
        .long	 1f - 0f
        .long	 4f - 1f
        .long	 5
0:
        .string	 "GNU"
1:
        .align 8
        .long	 0xc0000002
        .long	 3f - 2f
2:
        .long	 0x3
3:
        .align 8
4:
