import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Collectors;

public class IOHandler {

  static public String inputData(String filePath) throws IOException {
    return Files.lines(Paths.get(filePath))
      .filter(s -> !s.startsWith(">"))
      .collect(Collectors.joining(""));
  }

  static public void outputData(String filePath, String[] data) throws IOException {
    try (BufferedWriter bw = new BufferedWriter(new FileWriter(filePath));) {
      for (String line : data) {
        bw.write(line);
        bw.newLine();
      }
    }
  }
}
