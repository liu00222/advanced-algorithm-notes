# Extended Euclid Algorithm
# Return (g, x, y) s.t. a*x + b*y = g = gcd(a, b)
def gcdExtended(a, b):
	if a == 0:
		return (b, 0, 1)
	else:
		result = gcdExtended(b % a, a)
		g = result[0]
		x = result[1]
		y = result[2]
		return (g, y - (b // a) * x, x)


def ModularEquationSolver(a, b, n):
	
