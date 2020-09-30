package filesprocessing.filters;

import java.io.File;

public interface Filter {

	public final double KBYTES_TO_BYTES = 1024;
	boolean isPass(File f);
}
