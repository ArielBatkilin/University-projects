import java.util.TreeSet;
import java.util.LinkedList;
import java.util.HashSet;

public class SimpleSetPerformanceAnalyzer {
	private static final String CHECK1 = "hi";
	private static final String CHECK2 = "-1317089015";
	private static final String CHECK3 = "23";
	private static final String PATH1 = "D:/school/OOP2/ex4/Ex4 supplied material-20190516/data1.txt";
	private static final String PATH2 = "D:/school/OOP2/ex4/Ex4 supplied material-20190516/data2.txt";
	private static String[][] myFiles;
	private static SimpleSet[][] myHashes;

	protected SimpleSetPerformanceAnalyzer() {
		myFiles = new String[2][];
		myFiles[0] = Ex4Utils.file2array(PATH1);
		myFiles[1] = Ex4Utils.file2array(PATH2);

		myHashes = new SimpleSet[2][3];
		myHashes[1][0] = new OpenHashSet();
		myHashes[1][1] = new OpenHashSet();
		myHashes[1][2] = new OpenHashSet();
		myHashes[0][0] = new ClosedHashSet();
		myHashes[0][1] = new ClosedHashSet();
		myHashes[0][2] = new ClosedHashSet();
	}

	private void timeInitializing() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				long timeStart = System.nanoTime();
				for (int k = 0; k < myFiles[i].length; k++) {
					myHashes[j][i].add(myFiles[i][k]);
				}
				long timeEnd = System.nanoTime();
				long time = (timeEnd - timeStart)/1000000;
				System.out.println(time);
			}
		}
	}

	private void timeContains(int dataIndex, String string) {
		for (int j = 0; j < 2; j++){
			for (long i = 0; i < 25000; i++) {
				myHashes[j][dataIndex].contains(string);
			}
			long beforeTime = System.nanoTime();
			for (long i = 0; i < 25000; i++) {
				myHashes[j][dataIndex].contains(string);
			}
			long difference = (System.nanoTime() - beforeTime);
			System.out.println(difference);
		}
	}

	public static void main(String[] args) {
		SimpleSetPerformanceAnalyzer myAnalyzer = new SimpleSetPerformanceAnalyzer();
//		myAnalyzer.timeInitializing();
		myAnalyzer.timeContains(0, CHECK1);
		myAnalyzer.timeContains(0, CHECK2);
		myAnalyzer.timeContains(1, CHECK3);
		myAnalyzer.timeContains(1, CHECK1);
	}
}