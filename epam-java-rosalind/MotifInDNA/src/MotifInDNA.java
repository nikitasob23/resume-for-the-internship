import java.io.IOException;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class MotifInDNA {

  public static String findMotif(String input, String motif) {
    return IntStream.range(0, input.length())
      .filter(i -> input.startsWith(motif, i))
      .map(i -> i + 1)
      .mapToObj(Integer::toString)
      .collect(Collectors.joining(" "));
  }

  public static void main(String[] args) {
    try {
      String[] input = IOHandler.inputData("./res/input.txt");
      String motifs = findMotif(input[0], input[1]);
      IOHandler.outputData("./res/output.txt", motifs);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
