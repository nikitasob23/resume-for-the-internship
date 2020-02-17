import java.io.IOException;

class SharedMotif {

  public static String findMotif(String[] data) {
    int n = data.length;

    String s = data[0]; // Reference String
    int len = s.length();

    String motif = "";

    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j <= len; j++) {

        String stem = s.substring(i, j); // Generate all possible substrings

        int k = 1;
        for (k = 1; k < n; k++) {
          if (!data[k].contains(stem)) {
            break;
          }
        }

        if (k == n && motif.length() < stem.length())
          motif = stem;
      }
    }
    return motif;
  }

  public static void main(String[] args) {
    try {
      String[] data = IOHandler.inputData("./res/input.txt");
      String motif = findMotif(data);
      IOHandler.outputData("./res/output.txt", motif);
    } catch (IOException e) {
      System.err.println("IO error!");
    }
  }
}
