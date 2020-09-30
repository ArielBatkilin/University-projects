package filesprocessing.filters;

import java.io.File;

public class WriteableFilter implements Filter {

	protected boolean isNot;
	protected boolean writeable;
	protected WriteableFilter(boolean isNot, boolean needToBeWritable){
		this.isNot = isNot;
		this.writeable = needToBeWritable;
	}

	public boolean isPass(File f){
		if (f.canWrite() == this.writeable){
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
