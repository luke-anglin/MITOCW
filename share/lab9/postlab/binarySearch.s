; Luke Anglin
; lta9vw
; Date:  
; binarySearch .s

; Prototype

; extern "C" int binarySearch(int * arr, int left, int right, int target);

; Params and corresponding registers: 
; rdi - int * arr 
; esi - int left
; edx - int right
; ecx - int target

global binarySearch
section .text

binarySearch: 
	; Prologue
    push    rbp ; push on base pointer
    mov     rbp, rsp ; put base and stack pointer in same location
	sub     rsp, 8 ; Make space

	mov QWORD [rbp - 8], rdi ; hold our array so we can restore later


	; Zero out scratch reg for later 
	xor r10, r10
	; First condition check. Is right >= l? 
	cmp edx, esi
	jge begin
	jl not_found


	begin: 

		; mid = left + (right - left) / 2
		; let's use reg r10d as a scratch reg for mid 
		; this way, we can continue to pass it through in the recursive process
		mov r10d, edx
		sub r10d, esi ; mid = r - l
		sar r10d, 1 ; mid = mid / 2
		add r10d, esi ; mid += 1
		cdqe		; convert double word to quad word
		; Now, in mid should be the correct value. 

		; Does arr[mid] == target?
		; First, let's store arr[mid]
		mov rax, rdi
		mov r11d, [rax+r10*4] ;r11d = arr[mid];
		cmp r11d, ecx ; if arr[mid] == x
		je found
		jg go_left
		jl go_right

	go_left:
		; fix all params
		; arr is the needs to be restored
		mov rdi, QWORD [rbp - 8]
		; right needs to be mid - 1
		mov edx, r10d
		sub edx, 1
		call binarySearch
		leave
		ret

	go_right:

		; fix all params
		; arr needs to be restored
		mov rdi, QWORD [rbp - 8]
		; left, which is esi, needs to hold mid + 1
		mov esi, r10d 
		add esi, 1		; left = mid + 1
		; right
		call binarySearch
		leave
		ret

	found: 
		xor rax, rax ; zero out some of the excess bits int the rax register
		mov eax, r10d ; put mid into eax
		leave
		ret

	not_found:
		mov eax, -1
		leave
		ret









