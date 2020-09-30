package filesprocessing.filters;

import filesprocessing.filters.Filter;

import java.io.File;

public class ExecutableFiltter implements Filter {

	protected boolean isNot;
	protected boolean executable;
	protected ExecutableFiltter(boolean isNot, boolean needToBeExecutable){
		this.isNot = isNot;
		this.executable = needToBeExecutable;
	}

	public boolean isPass(File f){
		if (f.canExecute() == this.executable){
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
