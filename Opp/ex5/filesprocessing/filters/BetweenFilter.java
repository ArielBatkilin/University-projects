package filesprocessing.filters;

import java.io.File;

public class BetweenFilter implements Filter {

	protected boolean isNot;
	protected double size1;
	protected double size2;
	protected BetweenFilter(boolean isNot, double size1ToCheck, double size2ToCheck){
		this.size1 = size1ToCheck;
		this.size2 = size2ToCheck;
		this.isNot = isNot;
	}

	public boolean isPass(File f){
		if ((f.length() >= (this.size1 * Filter.KBYTES_TO_BYTES) && f.length() <= (this.size2* Filter.KBYTES_TO_BYTES)) !=
				this.isNot){
			return true;
		}
		else{
			return false;
		}
	}
}
