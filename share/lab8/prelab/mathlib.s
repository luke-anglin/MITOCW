; Product Function
; Parameter 1 (in rdi) is the int x, the first integer arg
; Parameter 2 (in rsi) is the int y, the second integer arg
; Return value (in rax) is a long that is the product 
;
; Local var i (in r10) will be zeroed out with an xor, like in vecsum 
; Local var sum (in rax) will be zeroed out with an xor, like in vecsum 
; 
; While loop: 
; Start by using cmp to compare i and y. If they are equal, jump to the done label
; This is also comparing r10 and rsi
; 
; While we're not done, we will do as follows: 
; We will add rdi to rax 
; We will increment r10
; We will jump back to the loop label
; 
; When we're done, we will: 
; ret 

global product 

section .text

product: 

	xor rax, rax
	xor r10, r10

	while: 

		cmp  rsi, r10 
		je done
		add rax, rdi 
		inc r10
		jmp while

	done: 
		ret

; Power Function
; Parameter 1 (in rdi) is the int b, the first integer arg, the base
; Parameter 2 (in rsi) is the int n, the second integer arg, the power
; Return value (in rax) is a long that is the base raised to the power
; 
; Begin with a condition check - does n === 0?
; This would correspond to a je of rsi to the DONE label
;
; After the condition check, assuming the je returned false, then we need to recurse
; This involves using a multiplication, so we must call the product function above. 
; 
; Calling means we're gonna have to save two params, rdi and rsi, by PUSHING them onto the stack, and popping
; them off once the function returns
;
; Additionally, prior to the call, we need to fill registers rdi and rsi with b and n, respectively, using mov
; after that, call
; finally pop
; 
; At the done label, we ret. 
; 
; Rough draft, then we'll edit

global power 

power: 
	; Condition check - base case
	; Does rsi == 0?
	cmp rsi, 0
	je power_done 

	; Otherwise, recurse
	; Move in proper parameters for power function prior to product function
	sub rsi, 1

	; Save our parameters. In this case, only rsi, because rdi (b) is unchanging 
	push rsi
	push rdi 
	; Subtract one from rsi, which holds n, because we are decreasing the exponent by one
	; The base stays the same
	call power
	; rax will now hold the result of power(b, n-1)
	; We need rdi to stay the same, because b doesn't change
	; We need rsi to be the result of power, which is stored in rax 
	; Therefore, we move rax into rsi 
	mov rsi, rax 
	pop rdi 
	; Okay, now we need to call the multiplication of rdi and rsi
	call product
	pop rsi

	ret

	power_done: 

		mov rax, 1
		ret 








