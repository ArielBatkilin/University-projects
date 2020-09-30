package filesprocessing.filters;

import filesprocessing.filters.Filter;

import java.io.File;

public class GreaterThanFilter implements Filter {

	protected boolean isNot;
	protected double size;
	protected GreaterThanFilter(boolean isNot, double sizeToCheck){
		this.isNot = isNot;
		this.size = sizeToCheck;
	}

	public boolean isPass(File f){
		if (f.length() > (this.size * Filter.KBYTES_TO_BYTES) != this.isNot){
			return true;
		}
		else{
			return false;
		}
	}
}
