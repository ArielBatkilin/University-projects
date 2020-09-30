package filesprocessing.filters;

import java.io.File;

public class AllFilter implements Filter {

	protected boolean isNot;
	protected AllFilter(boolean isNot){
		this.isNot = isNot;
	}

	public boolean isPass(File f){
		if (this.isNot){
			return false;
		}
		return true;
	}
}
