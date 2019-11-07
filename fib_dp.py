# O(n)-time dp algorithm to compute the nth fib number
# it uses botton-up method
def fib(n):
	env = [1, 1]
	i = 2
	while i <= n:
		env += [env[i-1] + env[i-2]]
		i += 1
	return env[n]


# main function
sentinel = 'y'
while sentinel == 'y':
	n = input("Please enter the number of n: ")
	print("The " + str(n) + "th Fibonacci number is: " + str(fib(int(n))))
	sentinel = input("\nEnter 'y' to continue, or enter 'n' to quit: ")
	print("\t")
