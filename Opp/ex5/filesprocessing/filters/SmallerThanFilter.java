package filesprocessing.filters;

import java.io.File;

public class SmallerThanFilter implements Filter {

	protected boolean isNot;
	protected double size;
	protected SmallerThanFilter(boolean isNot, double sizeToCheck){
		this.isNot = isNot;
		this.size = sizeToCheck;
	}

	public boolean isPass(File f){
		if (f.length() < (this.size*KBYTES_TO_BYTES) != this.isNot){
			return true;
		}
		else{
			return false;
		}
	}
}
