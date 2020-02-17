import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

class RNAtoProtein {
  
  public static String translate(String RNASample) throws IOException {
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
}
