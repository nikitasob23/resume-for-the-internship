import java.io.IOException;
import java.util.Map;

class ComputingGC {

  public static String[] compute(Map<String, String> data) {

    String key = "";
    double max = 0;
    
    for (Map.Entry<String, String> pair : data.entrySet()) {
      double temp = count(pair.getValue());
      if (max < temp) {
        max = temp;
        key = pair.getKey();
      }
    }

    return new String[]{key, Double.toString(max)};
  }

  public static double count(String line) {
    long count = line.chars().filter(ch -> ch == 'C' || ch == 'G').count();
    return count * 100.0 / line.length();
  }

  public static void main(String[] args) {
    try {
      Map<String, String> data = IOHandler.inputData("./res/input.txt");
      String[] result = compute(data);
      IOHandler.outputData("./res/output.txt", result);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }  
  }
}
