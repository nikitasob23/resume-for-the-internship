import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class IOHandler {

  static public String[] inputData(String file) throws IOException {
    List<String> data = new ArrayList<>();
    StringBuilder sb = new StringBuilder();

    try (Stream<String> stream = Files.lines(Paths.get(file));) {
      stream.forEach(line -> {
        if (line.startsWith(">")) {
          if (sb.length() != 0) {
            data.add(sb.toString());
            sb.setLength(0);
          }
          return;
        }
        sb.append(line);
      });
    }

    data.add(sb.toString());
    return data.toArray(new String[data.size()]);
  }

  static public void outputData(String filePath, String data) throws IOException {
    Files.write(Paths.get(filePath), data.getBytes());
  }
}
