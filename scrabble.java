import java.util.HashMap;
import java.util.Scanner;

public class scrabble {

	static char[] letters;
	static char[][] words;
	
	static boolean draw;
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int g = sc.nextInt();
		
		for (int i = 0; i < g; i++) {
			int n = sc.nextInt(); // number of usable letters
			int m = sc.nextInt(); // number of words
			
			draw = false;
			
			letters = sc.next().toCharArray();
			words = new char[m][];
			
			for (int j = 0; j < m; j++) {
				words[j] = sc.next().toCharArray();
			}
			

			Trie t = new Trie();
			
			for (int j = 0; j < m; j++) {
				t.add(words[j]);
			}
			
			int val = canwin(t);
			
			System.out.printf("Game #%d: %s%n", i+1, val == 0 ? ("Draw") : (val == 1 ? "Alice wins" : "Bob wins"));
			
		}
	}
	
	public static int canwin(Trie t) {
		// In order for a player to win, the subtree they play in must exhaustively result in a victory.
		// no matter what play the other player makes must still result in a victory for the initial player.
		
		boolean drawfound = false;
		boolean winningfound = false;
		for (int move = 0; move < letters.length; move++) {
			if (t.map.containsKey(letters[move])) {
				if (t.map.get(letters[move]).end > 0) { // this is a winning move
					winningfound =  true;
				}else {
					int get = canwin(t.map.get(letters[move]));
					
					if (get == 1) {
						// next player wins
					}else if (get == 0) {
						// next player draws
						drawfound = true;
					}else if (get == 2) {
						// next player loses
						winningfound = true;
					}
				}
			}else {
				drawfound = true;
			}
		}
		
		
		if (winningfound) {
			return 1;
		}
		if (drawfound) {
			return 0;
		}
		return 2;
	}

	static class Trie {
		int end;
		HashMap<Character, Trie> map;
		char value;
		
		public Trie() {
			this('#', 0);
		}
		
		public Trie(char c, int end) {
			this.value = c;
			this.end = end;
			map = new HashMap<>();
		}
		
		public Trie add(char[] w) {
			Trie root = this;
			
			int index = 0;
			while (index < w.length) {
				char next = w[index++];
				
				if (root.map.containsKey(next) == false) {
					root.map.put(next, new Trie(next, 0));
				}
				
				root = root.map.get(next);
			}
			
			root.end++;
			return this;
		}

		public String toString() {
			return map+" end=" + end + "val =" + value;
		}
	}
	
}

/*

4
3 4
abc
aaa
ab
ba
cccc
3 3
abc
aaa
ab
ba
3 1
abc
cccc
3 3
def
def
d
dedede

*/