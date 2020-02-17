import java.io.IOException;

class TransitionsTransversions {

  public static String calculateRatio(String str1, String str2) {
    
    int transitions = 0;
    int transversions = 0;

    for (int i = 0; i < str1.length(); i++) {
      char c1 = str1.charAt(i);
      char c2 = str2.charAt(i);
      if (c1 != c2) {
        if (checkTransversion(c1, c2)){
          transversions++;
          continue;
        }
        transitions++;
      }
    }

    double ratio = (double)transversions / (double)transitions;
    return String.valueOf(ratio);
  }

  private static boolean checkTransversion(char c1, char c2) {
    if (c1 == 'A' && c2 == 'G' || c1 == 'G' && c2 == 'A' ||
      c1 == 'C' && c2 == 'T' || c1 == 'T' && c2 == 'C') {
        return true;
    }
    return false;
  }

  public static void main(String[] args) {
    try {
      String[] data = IOHandler.inputData("./res/input.txt");
      String result = calculateRatio(data[0], data[1]);
      IOHandler.outputData("./res/output.txt", result);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
