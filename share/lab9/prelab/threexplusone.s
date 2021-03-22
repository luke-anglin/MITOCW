; Luke Anglin
; lta9vw
; Date: 
; threexpinput.s
; OPTIMIZATIONS
; -------------
; 1. Using bitwise shift to divide by two for even numbers
; 2. Check the base case (x == 1) ONLY if the number is odd to eliminate excess branching
; 3. Test instruction only checks if the lowest bit of twos complement num is set, indicating 
; if it is odd or even. the test will give jnz true, if not jz true
; Let's start 
; 4. Utilize lea to mult and add in one step 
; 5. Remove normal function prologue
; 6. Optimize HEAVILY by removing the global variable steps and using the r10d register which can 
; continually be changed by recursive calls and then also subtract one from final ret
global threexplusone
section .text

; Parameter comes in edi: int x, the collatz num
threexplusone: 
	; Check if a boolean flag that we've done an iteration has been set
	; If it has, skip over xoring
	cmp r11d, 1
	je next 
	xor r10d, r10d
	; Prologue
	next: 
	lea r10d, [r10d + 1]
	; edi is int x 
	; check odd or even

	mov eax, edi ; put x into eax for test instruction preparation, eax = x
	; test odd or even
	test eax, 1
	jnz odd
	jz even

	done: 

		lea eax, [r10d - 1]
		ret


	odd: 
		; Set boolean flag
		mov r11d, 1
		; Check the base case (x == 1) only in odd to eliminate repeating that branching step everytime
		cmp edi, 1
		je done

		; if it's not one, make the value of edi = 3x + 1
		; Utilize lea to mult and add in one step
		lea edi, [3*edi + 1]

		call threexplusone
		ret

	even: 
		mov r11d, 1
		; bitwise shift optimization to divide by 2
		sar edi, 1
		call threexplusone
		ret



