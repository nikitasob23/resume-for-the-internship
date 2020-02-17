class SharedMotif {

  public static String findMotif(String[] data) {
    int numStrings = data.length;

    String refString = data[0]; // Reference String
    int len = refString.length();

    String motif = "";

    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j <= len; j++) {

        String stem = refString.substring(i, j); // Generate all possible substrings
        
        int k = 1;
        for (k = 1; k < numStrings; k++) {
          if (!data[k].contains(stem)) break;
        }

        if (k == numStrings && motif.length() < stem.length()) motif = stem;
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
      e.printStackTrace();
    }
  }
}
