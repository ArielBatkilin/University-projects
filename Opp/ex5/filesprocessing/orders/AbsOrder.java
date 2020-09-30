package filesprocessing.orders;

import java.io.File;
import java.util.Comparator;

public class AbsOrder implements Order, Comparator<File> {

	public int compare(File a, File b){
		if (a.getAbsolutePath().compareTo(b.getAbsolutePath()) > 0){
			return 1;
		}
		else{
			return -1;
		}
	}
}
