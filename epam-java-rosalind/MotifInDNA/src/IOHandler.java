import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class IOHandler {

  static public String[] inputData(String filePath) throws IOException {
    return Files.lines(Paths.get(filePath)).toArray(String[]::new);
  }

  static public void outputData(String filePath, String data) throws IOException {
    Files.write(Paths.get(filePath), data.getBytes());
  }
}
