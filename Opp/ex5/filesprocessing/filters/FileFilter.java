package filesprocessing.filters;

import java.io.File;

public class FileFilter implements Filter {

	protected boolean isNot;
	protected String name;
	protected FileFilter(boolean isNot, String nameToCheck){
		this.isNot = isNot;
		this.name = nameToCheck;
	}

	public boolean isPass(File f){
		if (f.getName().compareTo(this.name) == 0){
			if (isNot){
				return false;
			}
			else{
				return true;
			}
		}
		else{
			if (isNot){
				return true;
			}
			else{
				return false;
			}
		}
	}
}
