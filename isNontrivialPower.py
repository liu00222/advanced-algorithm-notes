import math

def isNontrivialPower(n):
	flag = True
	i = 2
	while i <= math.sqrt(n):
		m = n
		k = 0
		while m % i == 0:
			m = m / i
			k = k + 1
		if m == 1 and k > 1:
			#print(str(n) + " is a nontrivial power.")
			#print("There exists an integer " + str(i) + " whose " + str(k) + "th power is " + str(n))
			flag = False
			return True
		i += 1
	if flag:
		return False
		

def isNontrivialPower2(n):
	if n < 2:
		return False
	k = 2
	lst = list(range(2, int(math.sqrt(n))+1))
	
	while k <= (math.log(n)/math.log(2)):	# O(beta)
		# Use a binary search to find such an a. This is in O(log(sqrt(n)))
		first = 0
		last = len(lst) - 1
		result = False
		
		while first <= last and not result:
			midpoint = (first + last) // 2
			
			if pow(lst[midpoint], k) == n:
				print(str(n) + " is a nontrivial power. ")
				print("There exists an integer " + str(lst[midpoint]) + " whose " + str(k) + "th power is " + str(n))
				return True
			else:
				if pow(lst[midpoint], k) < n:
					first = midpoint + 1
				else:
					last = midpoint - 1
		k += 1
	return False

print(isNontrivialPower2(10000000))
#num = 1
#while num <= 100000:
#	print(isNontrivialPower(num) == isNontrivialPower2(num))
##	num += 1
