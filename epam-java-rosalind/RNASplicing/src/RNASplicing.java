import java.io.IOException;

class RNASplicing {

  public static String transcribe(String[] data) {
    String dna = data[0];
    for (int i = 1; i < data.length; i++) {
      String intron = data[i];
      dna = dna.replace(intron, "");
    }
    return dna.replace("T", "U");
  }

  public static void main(String[] args) {
    try {
      String[] input = IOHandler.inputData("./res/input.txt");
      String protein = RNAtoProtein.translate(transcribe(input));
      IOHandler.outputData("./res/output.txt", protein);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
