package filesprocessing.filters;

import java.io.File;

public class SuffixFilter implements Filter {

	protected boolean isNot;
	protected String name;
	protected SuffixFilter(boolean isNot, String nameToCheck){
		this.isNot = isNot;
		this.name = nameToCheck;
	}

	public boolean isPass(File f){
		if (f.getName().endsWith(this.name) != isNot){
			return true;
		}
		else {
			return false;
		}
	}
}
