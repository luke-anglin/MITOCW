; lta9vw
; Luke anglin
; date
; lienarSearch.s

; Task: Your task for the post-lab is to implement the linearSearch function in assembly. This function will scan through an array from left to right iteratively until it finds the target element or reaches the end of the array. The function takes in three parameters. The first parameter is a pointer to an int array. The second parameter is an integer representing the size of the array. The third parameter is an integer representing the target element to find in the array. The return type of this fuction is int, and will be the index into the array that the target was found, or -1 if it wasn’t. Just like with the testMergeSort program in the in-lab, testLinearSearch will take input from std and pass it on to your linearSearch routine. Make sure you test your function on various sized arrays, both sorted and unsorted.

; PARAMETERS
; rdi - array base address - that's a QWORD 
; esi - array size, n - that's a DWORD 
; edx - target - that's a DWORD 

global linearSearch

section .text

linearSearch: 

		; Prologue
	    push    rbp ; push on base pointer
	    mov     rbp, rsp ; put base and stack pointer in same location
	    sub     rsp, 32 ; Make space


		; Let's start by getting our parameters all nice
		; Move the base address into a QWORD
		mov		QWORD [rbp - 8], rdi ; array pointer
		mov 	DWORD [rbp - 12], esi ; array size, n
		mov 	DWORD [rbp - 16], edx ; target
		mov 	DWORD [rbp - 20], 0 ; int i = 0

		jmp begin

	begin: 
		; Okay. Now, we need to start our loop
		; Ensure that i is still less than n
		mov ecx, DWORD [rbp - 20] ; ecx = i
		cmp ecx, esi ; This is an intermediary step because at least one needs to be a reg
		jge not_found

		; Only increment i if and only if i is not zero 
		cmp DWORD [rbp - 20], 0
		je zero_case
		add rdi, 4
		; Check condition. Does current == target?
		mov 	rax, rdi
		mov 	r10d, [rax] ; r10d = current = a[i]
		cmp		r10d, DWORD [rbp - 16]
		je 	found ; if it does, return that index

		inc 	DWORD [rbp - 20] ; i ++
		jmp		begin				  ; return to loop

	zero_case: 
		; Check condition. Does current == target?
		mov 	rax, rdi
		mov 	r10d, [rax] ; r10d = current = a[i]
		cmp		r10d, DWORD [rbp - 16]
		je 	found ; if it does, return that index
				inc DWORD [rbp - 20]

		jmp		begin				  ; return to loop

	found: 

		mov 	eax, DWORD [rbp - 20] ; put the index in the return register
		leave
		ret

	not_found: 

		mov eax, -1
		leave
		ret






