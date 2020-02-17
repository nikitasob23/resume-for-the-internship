import java.io.IOException;
import java.util.Properties;

class RNAtoProtein {

  static Properties table = IOHandler.readProps("./res/RNACodonTable");

  public static String translate(String RNASample) {
    Properties table = IOHandler.readProps("./res/RNACodonTable");
    String[] data = split(RNASample, 3);
    StringBuilder protein = new StringBuilder();
    String value = "";
    for (String codon : data) {
      value = table.get(codon).toString();
      if (value.equals("Stop")) {
        return protein.toString();
      }
      protein.append(value);
    }
    return protein.toString();
  }

  private static String[] split(String string, int partitionSize) {
    List<String> parts = new ArrayList<String>();
    int len = string.length();
    for (int i = 0; i < len; i += partitionSize) {
      parts.add(string.substring(i, Math.min(len, i + partitionSize)));
    }
    return parts.toArray(String[]::new);
  }

  public static void main(String[] args) {
    try {
      String rna = IOHandler.inputData("./res/input.txt");
      String protein = translate(rna);
      IOHandler.outputData("./res/output.txt", protein);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
