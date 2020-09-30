package filesprocessing.orders;

import java.io.File;
import java.util.Comparator;

public class SizeOrder implements Order, Comparator<File> {

	public int compare(File a, File b){
		long fileSize1 = a.length();
		long fileSize2 = b.length();
		if (fileSize1 > fileSize2){
			return 1;
		}
		else if (fileSize1 < fileSize2){
			return -1;
		}
		else {
			if (a.getAbsolutePath().compareTo(b.getAbsolutePath()) > 0){
				return 1;
			}
			else{
				return -1;
			}
		}
	}
}
