package filesprocessing;

import filesprocessing.Parser;
import filesprocessing.Section;
import filesprocessing.TypeTwoExeption;

import java.io.File;
import java.util.*;

public class DirectoryProcessor {

	private static final int NO_ERROR = -1;
	private static final String BAD_ARG__NUM_MSG = "ERROR:<2 args needed>";
	private static final String COMMAND_FILE_NOT_FOUND_MSG = "ERROR:<command file not found>";
	private static final String SOURCE_DIR_NOT_FOUND_MSG = "ERROR:<source directory not found>";
	private static final String COMMAND_FILE_NOT_FILE_MSG = "ERROR:<command file not file>";
	private static final String SOURCE_DIR_NOT_DIRECTORY_MSG = "ERROR:<source directory not directory>";

	public static void main(String[] args){
		if(args.length != 2){
			handleTypeTwoExeptions(BAD_ARG__NUM_MSG);
		}
		File commandFile = new File(args[1]);
		if (!commandFile.exists()){
			handleTypeTwoExeptions(COMMAND_FILE_NOT_FOUND_MSG);
		}
		if (!commandFile.isFile()){
			handleTypeTwoExeptions(COMMAND_FILE_NOT_FILE_MSG);
		}
		Section[] mySections = new Section[0];
		Parser myParser = new Parser(commandFile);
		try {
			mySections = myParser.parse();
		}
		catch (TypeTwoExeption e){
			handleTypeTwoExeptions(e.getMsg());
		}
		File sourceDir = new File(args[0]);
		if (!sourceDir.exists()){
			handleTypeTwoExeptions(SOURCE_DIR_NOT_FOUND_MSG);
		}
		if (!sourceDir.isDirectory()){
			handleTypeTwoExeptions(SOURCE_DIR_NOT_DIRECTORY_MSG);
		}
		File[] listThings = sourceDir.listFiles();
		List<File> fileList = new ArrayList<File>();
		for (File myFile: listThings){
			if (myFile.isFile()){
				fileList.add(myFile);
			}
		}
		for (Section mySection: mySections){
			printLineErrors(mySection.getErrorLine());
			List<File> filteredFiles = new ArrayList<File>();
			for (File aFile: fileList){
				if (mySection.getFilter().isPass(aFile)){
					filteredFiles.add(aFile);
				}
			}
			File[] filtered = filteredFiles.toArray(new File[filteredFiles.size()]);
			Arrays.sort(filtered, mySection.getOrder());
			for (File printFile: filtered ){
				System.out.println(printFile.getName());
			}
		}
	}

	public static void handleTypeTwoExeptions(String msg){
		System.err.println(msg);
		System.exit(0);
	}

	public static void printLineErrors(int line){
		if (line != NO_ERROR){
			System.err.println("Warning in line " + String.valueOf(line));
		}
	}


}
