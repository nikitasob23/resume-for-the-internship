import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;

public class IOHandler {

  static public Map<String, String> inputData(String file) throws IOException {
    Map<String, String> data = new HashMap<String, String>();
    StringBuilder sb = new StringBuilder();
    final String[] key = new String[]{""};

    try (Stream<String> stream = Files.lines(Paths.get(file));) {
      stream.forEach(line -> {
        if (line.startsWith(">")) {

          if (sb.length() != 0) {
            data.put(key[0], sb.toString());
            sb.setLength(0);
          }
          
          key[0] = line.substring(1);
          return;
        }
        sb.append(line);
      });
    }

    data.put(key[0], sb.toString());

    return data;
  }

  static public void outputData(String file, String[] data) throws IOException {
    try (BufferedWriter bw = new BufferedWriter(new FileWriter(file));) {
      for (String line : data) {
        bw.write(line);
        bw.newLine();
      }
    }
  }
}
