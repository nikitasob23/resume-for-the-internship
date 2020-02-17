import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

class FindingSplicedMotif {

  public static String findMotif(String[] data) {
    String dna = data[0];
    char[] searching = data[1].toCharArray();
    List<Integer> positions = new ArrayList<>();

    int i = 0;
    for (char c : searching) {
      for (i++; i < dna.length(); i++) {
        if (c == dna.charAt(i)) {
          positions.add(i + 1);
          break;
        }
      }
    }

    return positions.stream().map(Object::toString).collect(Collectors.joining(" "));
  }

  public static void main(String[] args) {
    try {
      String[] input = IOHandler.inputData("./res/input.txt");
      String result = findMotif(input);
      IOHandler.outputData("./res/output.txt", result);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
