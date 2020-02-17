import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class IOHandler {

  static public long[] inputData(String filePath) throws IOException {
    String[] input = Files.lines(Paths.get(filePath)).findFirst().get().split(" ");
    long[] inputLong = new long[3];
    for (int i = 0; i < input.length; i++) {
      inputLong[i] = Long.valueOf(input[i]);
    }
    return inputLong;
  }

  static public void outputData(String filePath, String data) throws IOException {
    Files.write(Paths.get(filePath), data.getBytes());
  }
}
