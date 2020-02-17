import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Properties;

public class IOHandler {

  static public Properties readProps(String file) throws IOException {
    Properties props = new Properties();
    InputStream input = new FileInputStream(file);
    props.load(input);
    return props;
  }

  static public String inputData(String filePath) throws IOException {
    return Files.lines(Paths.get(filePath)).findFirst().get();
  }

  static public void outputData(String filePath, String data) throws IOException {
    Files.write(Paths.get(filePath), data.getBytes());
  }
}
