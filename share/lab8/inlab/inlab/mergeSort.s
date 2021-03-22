
; University of Virginia
; CS 2150 In-Lab 8
; Spring 2018
; mergeSort.s	

global _mergeSort
global _merge

section .text

; Parameter 1 is a pointer to the int array (rdi) 
; Parameter 2 is the left index in the array (rsi)
; Parameter 3 is the right index in the array (rdx)
; Return type is void (rax) 

_mergeSort:
		; Prologue
        push    rbp ; push on base pointer
        mov     rbp, rsp ; put base and stack pointer in same location
        sub     rsp, 20  ; We have 8 + 4 + 4 + 4 for the pointer and three (one for mid, which we'll make the first dw)
        ; Now, let's make room for locals 
        ; Two integers: left and right, four bytes, so e rather than r
        mov     DWORD  [rbp-16], esi ; This is left 
        mov     DWORD  [rbp-20], edx ; This is right 
        ; One array pointer, thats a QWORD
        mov     QWORD  [rbp-12], rdi ; This is arr, still r reg b/c 8
        mov     eax, DWORD  [rbp-16] ; Put left into eax
        cmp     eax, DWORD [rbp-20] ; Compare that with right. If l >= r, we're done.
        ; Base case done.
        jge     done

        ; Recursive Step
        ; int m = 1 + (r - l) / 2
        ; r - l part below
        mov     eax, DWORD  [rbp-20] ; eax holds r
        sub     eax, DWORD  [rbp-16] ; eax holds r - l
        ; Divide eax by two by bitwise shift - how cool!!! 
        sar 	eax, 1
        ; add l 
        add     eax, DWORD [rbp - 16]
        ; Put mid in the dword 
        mov     DWORD [rbp - 4], eax
        
        ; Ensure all our parameters are kosher according to the calling conventions in the slides
        mov     edx, DWORD  [rbp-4] ; The last parameter, right, should be mid, which is stored at rbp -4 
        mov     esi, DWORD  [rbp-16] ; left is the same, the second parameter, esi
        mov     rdi, QWORD  [rbp-12] ; Array is the 1st parameter, rdi
       ; Call the function. Pray. 
        call   _mergeSort

        ; Ensure all parameters are good again
        ; Store midpoint in r10d, a scratch reg
        mov     r10d, DWORD  [rbp-4]
        ; Increment the midpoint
        inc 	r10d
        ; r10d = m + 1
        ; Move parameters into correct locations
        mov     edx, DWORD  [rbp-20]
        mov     rdi, QWORD  [rbp-12]
        mov     esi, r10d
        call    _mergeSort
        ; Again, get params right
        mov     ecx, DWORD  [rbp-20] ; right
        mov     edx, DWORD  [rbp-4] ; mid
        mov     esi, DWORD  [rbp-16] ; left
        mov     rax, QWORD  [rbp-12] ; arr
        call    _merge
	done:
        leave 
        ret
	


; Parameter 1 is a pointer to the int array 
; Parameter 2 is the left index in the array
; Parameter 3 is the middle index in the array 
; Parameter 4 is the right index in the array
; Return type is void 
_merge:
; Save callee-save registers
; Store local variables 
push rbx			; int i
push r12			; int j
push r13			; int k
push r14			; int n1
push r15			; int n2

mov r14, rdx			; n1 = mid - left + 1
sub r14, rsi
inc r14

mov r15, rcx			; n2 = right - mid 
sub r15, rdx

lea r11, [r14+r15]		; r11 = rsp offset = 4(n1 + n2)
lea r11, [4*r11]		
sub rsp, r11			; allocate space for temp arrays

mov rbx, 0			; i = 0
mov r12, 0			; j = 0

; Copy elements of arr[] into L[]	
copyLloop:
cmp rbx, r14			; is i >= n1?
jge copyRloop
; L[i] = arr[left + i]
lea r10, [rsi+rbx]		
mov r10d, DWORD [rdi+4*r10]	; r10 = arr[left + i]
mov DWORD [rsp+4*rbx], r10d	; L[i] = r10
inc rbx				; i++
jmp copyLloop

; Copy elements of arr[] into R[]
copyRloop:
cmp r12, r15			; is j >= n2?
jge endcopyR
; R[j] = arr[mid + 1 + j]
lea r10, [rdx+r12+1]	
mov r10d, DWORD [rdi+4*r10]	; r10 = arr[mid + 1 + j]
lea rax, [r12+r14]		
mov DWORD [rsp+4*rax], r10d	; R[j] = r10
inc r12				; j++
jmp copyRloop

endcopyR:	
mov rbx, 0			; i = 0
mov r12, 0			; j = 0
mov r13, rsi			; k = left

; Merge L[] and R[] into arr[]
mergeLoop:
cmp rbx, r14			; is i >= n1 or j >= n2?
jge loopL
cmp r12, r15
jge loopL
lea r10, [r12+r14]
mov r10d, DWORD [rsp+4*r10] 	; r10d = R[j]
cmp DWORD [rsp+4*rbx], r10d	; is L[i] <= R[j]?
jle if
mov DWORD [rdi+4*r13], r10d	; arr[k] = R[j]
inc r12				; j++
jmp endif 
if:
mov r10d, DWORD [rsp+4*rbx] 
mov DWORD [rdi+4*r13], r10d	; arr[k] = L[i] 
inc rbx				; i++
endif:	
inc r13				; k++	
jmp mergeLoop

; Copy elements of L[] into arr[]
loopL:				
cmp rbx, r14			; is i >= n1?
jge loopR
mov r10d, DWORD [rsp+4*rbx] 
mov DWORD [rdi+4*r13], r10d	; arr[k] = L[i]
inc rbx				; i++
inc r13				; k++
jmp loopL

; Copy elements of R[] into arr[]
loopR:	
cmp r12, r15			; is j >= n2?
jge endR
lea r10, [r12+r14]
mov r10d, DWORD [rsp+4*r10] 	
mov DWORD [rdi+4*r13], r10d	; arr[k] = R[j]

inc r12				; j++
inc r13				; k++
jmp loopR

endR:
; deallocate temp arrays
; restore callee-save registers
add rsp, r11	
pop r15			
pop r14
pop r13
pop r12
pop rbx
ret