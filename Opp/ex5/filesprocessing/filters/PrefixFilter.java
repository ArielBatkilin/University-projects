package filesprocessing.filters;

import java.io.File;

public class PrefixFilter implements Filter {

	protected boolean isNot;
	protected String name;
	protected PrefixFilter(boolean isNot, String nameToCheck){
		this.isNot = isNot;
		this.name = nameToCheck;
	}

	public boolean isPass(File f){
		if (f.getName().startsWith(this.name) != isNot){
			return true;
		}
		else {
			return false;
		}
	}
}
