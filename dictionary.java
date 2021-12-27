import java.util.Arrays;
import java.util.Scanner;

public class dictionary {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int t = sc.nextInt(); // Number of test cases

		for (int i = 0; i < t; i++) {
			int n = sc.nextInt(); // Number of words

			// Create an array of our custom Word object.
			Word[] words = new Word[n];

			for (int j = 0; j < n; j++) {
				words[j] = new Word(sc.next());
			}

			Arrays.sort(words);

			System.out.println("Dictionary #" +(i+1)+":");
			for (Word w : words) {
				System.out.println(w.letters);
			}
			System.out.println();
		}
	}

	// Since we are not sorting normally, we cannot just use
	// String objects and sort them. We have to use a custom object,
	// which I called Word and make it sortable using the "implements
	// Comparable<Word>"
	static class Word implements Comparable<Word> {

		// Storing the given word in a String.
		String letters;
		// Stores the number of each letter of the alphabet.
		int[] num;

		public Word(String in) {
			// Store the input string in our char array.
			letters = in;

			// Initialize num to letters of the alphabet.
			num = new int[26];

			// Go through each letter and increment the number we
			// have of that letter
			for (int i = 0; i < letters.length(); i++) {

				int letteridx = letters.charAt(i) - 'a';

				num[letteridx]++;
			}
		}

		// Method that defines how we are going to sort.
		public int compareTo(Word o) {
			// Sort them by the count of letters in alphabetical order.
			for (int i =0; i < 26; i++) {
				if (num[i] != o.num[i]) {
					return o.num[i] - num[i];
				}
			}

			// If they have the same number of letters
			// just sort them lexicographically.
			return letters.compareTo(o.letters);
		}

	}

}
