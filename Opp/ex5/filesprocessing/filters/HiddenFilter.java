package filesprocessing.filters;

import filesprocessing.filters.Filter;

import java.io.File;

public class HiddenFilter implements Filter {

	protected boolean isNot;
	protected boolean hidden;
	protected HiddenFilter(boolean isNot, boolean needToBeHidden){
		this.isNot = isNot;
		this.hidden = needToBeHidden;
	}

	public boolean isPass(File f){
		if (f.isHidden() == hidden){
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
