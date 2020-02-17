import java.io.IOException;

class ImmortalRabbits {

  public static long calculateRabbits(long numMonths, long numOffspring) {
    if (numMonths == 1) {
      return 1;
    } else if (numMonths == 2) {
      return numOffspring;
    }
    long oneGen = calculateRabbits(numMonths - 1, numOffspring);
    long twoGen = calculateRabbits(numMonths - 2, numOffspring);
    if (numMonths <= 4) {
      return (oneGen + twoGen);
    }
    return (oneGen + (twoGen * numOffspring));
  }

  public static void main(String[] args) {
    try {
      long[] data = IOHandler.inputData("./res/input.txt");
      long pairs = calculateRabbits(data[0], data[1]);
      IOHandler.outputData("./res/output.txt", String.valueOf(pairs));
    } catch (IOException e) {
      System.err.println("IO error!");
      e.printStackTrace();
    }
  }
}
