package filesprocessing.filters;

import java.io.File;

public class ContainsFilter implements Filter {

	protected boolean isNot;
	protected CharSequence name;
	protected ContainsFilter(boolean isNot, String nameToCheck){
		this.isNot = isNot;
		this.name = nameToCheck;
	}

	public boolean isPass(File f){
		if (f.getName().contains(this.name) != isNot){
			return true;
		}
		else {
			return false;
		}
	}
}
