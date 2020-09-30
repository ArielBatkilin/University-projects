package filesprocessing.orders;

import java.io.File;
import java.util.Comparator;

public class TypeOrder implements Order, Comparator<File> {

	public int compare(File a, File b){
		String fileType1 = getType(a.getName());
		String fileType2 = getType(b.getName());
		if (fileType1.compareTo(fileType2) > 0){
			return 1;
		}
		else if (fileType1.compareTo(fileType2) < 0){
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

	private String getType(String name){
		String[] parts = name.split(".");
		String type = parts[parts.length-1];
		return type;
	}
}
