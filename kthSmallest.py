# Introduction to Algorithms 3rd edition
# Chapter 9.3 - Selection in worst-case linear time

def select(A, i):
	if i <= 0 or i > len(A):
		raise Exception("ERROR: Invalid input!")
	
	# Implement step 1 and step 2 simultaneously
	# Store the medians of each sublist in medians
	medians = []
	n = len(A)
	j = 0
	
	# The medians of groups with length = 5
	while j < (n // 5):
		medians += [findMedian(A, j*5, j*5 + 5)]
		j += 1
	
	# The median of the last group
	medians += [findMedian(A, j*5, n)]
	j += 1
	
	# Find the median of the medians
	if j > 1:
		medOfMed = select(medians, ((j + 1) // 2))
	else:
		medOfMed = medians[0]
	
	k = partition(A, medOfMed)
	
	if k == i:
		return medOfMed
	elif k > i:
		return select(A[0:(k-1)], i)
	else:
		return select(A[(k-1):(len(A)-1)], i - k)


def findMedian(A, i, n):
	A[i:n] = sorted(A[i:n])
	return A[(i+n-1)//2]


def swap(A, i, j):
	temp = A[i]
	A[i] = A[j]
	A[j] = temp


def partition(A, x):
	i = 0
	while i < len(A):
		if A[i] == x:
			break
		i += 1
	swap(A, i, len(A) - 1)
	
	i = 0
	j = 0
	while j < len(A) - 1:
		if A[j] < x:
			swap(A, i, j)
			i += 1
		j += 1
	return i + 1


testList = [-3, 9, 2, -1, 4, -2, 10, -6, 11, 8, 0]
k = 1
while k <= len(testList):
	print("-------------------------")
	print("The " + str(k) + "'th smallest element is " + str(select(testList, k)))
	k += 1
	print("")
