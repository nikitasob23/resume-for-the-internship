import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

class RestrictionSites {

  static Map<Character, Character> reversedChars = Map.of(
    'C','G',
    'G','C',
    'A','T',
    'T','A'
  );

  public static String[] findMatches(String data) {

    final int MIN_LEN = 4;
    final int MAX_LEN = 12;
    
    int len = data.length();
    List<String> matches = new ArrayList<>();

    for (int i = 0; i < len; i++) {
      for (int j = i + MIN_LEN; j <= len && j <= i + MAX_LEN; j += 2) {
        String line = data.substring(i, j);
        if (line.equals(reverse(line))) {
          matches.add(String.valueOf(i + 1) + " " + String.valueOf(line.length()));
        }
      }
    }
    return matches.stream().toArray(String[]::new);
  }

  public static String reverse(String line) {
    StringBuilder reversed = new StringBuilder();
    line.chars().boxed().forEach(c -> reversed.append(reversedChars.get(c)));
    return reversed.reverse().toString();
  }

  public static void main(String[] args) {
    try {
      String data = IOHandler.inputData("./res/input.txt");
      String[] matches = findMatches(data);
      IOHandler.outputData("./res/output.txt", matches);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
