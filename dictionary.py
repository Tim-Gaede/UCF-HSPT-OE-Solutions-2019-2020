# Solution for Dictionary
#	For UCF 2019 Online set Div2
#	By Dylan Lyon

# Creates a unique value from any word's compareArray entry.
# Based on the word having at most 20 letters and there being at
# most 10^5 words. Basically a hash.
def customKey( a ):
	retkey = 0
	for index in range(0,26):
		retkey *= 20
		retkey += a[index]

	# The ordering for this hash is odd; we want descending order for
	#	letter frequencies and ascending order for lexico order; this sign
	#	solves that problem
	retkey *= -10**5
	retkey += a[26]
	return retkey

# Number of tests
t = int(input())

for test in range(1,t+1):
	# Number of words
	n = int(input())

	# Read input
	words = [""]*n

	for word in range(0,n):
		words[word] = str(input())

	# Sort by lexiographical order
	words.sort()

	# Our compareArray has 27 entries
	compareArray = [[0]*27 for x in range(0,n)]

	for x in range(0,n):
		# The first 26 entries of compareArray are the letter frequencies
		for character in words[x]:
			tmp = ord(character) - ord('a')
			if (tmp >= 0 and tmp <= 25):
				compareArray[x][tmp] += 1
		# the 27th entry is the lexicographical ranking, in case
		#	we're comparing two words that are anagrams
		compareArray[x][26] = x

	# Now we sort by the words' custom keys, which already accounts
	#	for anagrams
	compareArray = sorted(compareArray,key=customKey)

	# Print out the results!!!
	print("Dictionary #",test,":",sep='')
	for tmpCmp in compareArray:
		print(words[tmpCmp[26]])
	print()
