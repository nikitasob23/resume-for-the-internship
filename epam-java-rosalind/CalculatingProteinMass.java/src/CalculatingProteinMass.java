import java.io.IOException;
import java.util.Properties;

class CalculatingProteinMass {
  
  
  public static String calculateMass(String protein, Properties table) {
    
    double mass = 0;

    for (int i = 0 ; i < protein.length(); i++) {
      String propertyKey = String.valueOf(protein.charAt(i));
      double aminoAcidMass = Double.valueOf(table.get(propertyKey).toString());
      mass += aminoAcidMass;
    }
    
    return String.valueOf(mass);
  }
  
  public static void main(String[] args) {
    try {
      Properties table = IOHandler.readProps("./res/MassTable");
      String protein = IOHandler.inputData("./res/input.txt");
      String mass = calculateMass(protein, table);
      IOHandler.outputData("./res/output.txt", mass);
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
