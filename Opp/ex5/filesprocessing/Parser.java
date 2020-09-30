package filesprocessing;

import filesprocessing.filters.Filter;
import filesprocessing.filters.FilterFactory;
import filesprocessing.orders.OrderFactory;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

public class Parser{

	private File file;
	private String filterName;
	private String[] otherFilterParts;
	private String orderName;
	private boolean orderIsRev;
	private Filter filter;
	private Comparator order;
	private static final OrderFactory ORDER_FACTORY = new OrderFactory();
	private static final FilterFactory FILTER_FACTORY = new FilterFactory();
	private Comparator<File> default_order;
	private Filter default_filter;
	private static final String NO_NOT = "YAA";
	private static final String FILTER_LINE = "FILTER";
	private static final String ORDER_LINE = "ORDER";
	private static final String ERROR_CMDFILE_MSG = "ERROR:\n error in commands file";
	private static final String ERROP_IO_MSG = "ERROR:\n IO error";
	private static final int FILTER_TITLE_LINE = 1;
	private static final int FILTER_ACTION_LINE = 2;
	private static final int ORDER_TITLE_LINE = 3;
	private static final int ORDER_ACTION_LINE = 4;
	private static final int NO_ERROR = -1;
	private  static final String IS_REV = "REVERSE";


	public Parser(File aFile){
		this.file = aFile;
		try {
			this.default_order = ORDER_FACTORY.getOrder("abs", false);
			String[] regular = {NO_NOT};
			this.default_filter = FILTER_FACTORY.getFillter("all", regular);
		}
		catch (Exception ignore){
		}
	}

	public Section[] parse() throws TypeTwoExeption {

		List<Section> sections = new ArrayList<Section>();
		try {
			BufferedReader buff = new BufferedReader(new FileReader(this.file));
			String line;
			int lineCounter = 0;
			int inSectionCounter = 0;
			while ((line = buff.readLine()) != null){
				lineCounter += 1;
				inSectionCounter += 1;
				if (inSectionCounter == FILTER_TITLE_LINE){
					if (line.compareTo(FILTER_LINE) != 0){
						throw new TypeTwoExeption(ERROR_CMDFILE_MSG);
					}
					else {
						continue;
					}
				}
				else if (inSectionCounter == FILTER_ACTION_LINE){
					String[] filterParts = filterComandParse(line);
					this.filterName = filterParts[0];
					this.otherFilterParts = Arrays.copyOfRange(filterParts, 1, filterParts.length);
				}
				else if (inSectionCounter == ORDER_TITLE_LINE){
					if (line.compareTo(ORDER_LINE) != 0){
						throw new TypeTwoExeption(ERROR_CMDFILE_MSG);
					}
					else {
						continue;
					}
				}
				else if (inSectionCounter == ORDER_ACTION_LINE){
					inSectionCounter = 0;
					Section mySection;
					int errorAtLine = NO_ERROR;
					try {
						this.filter = FILTER_FACTORY.getFillter(this.filterName, this.otherFilterParts);
					}
					catch (TypeOneExeption e){
						errorAtLine = lineCounter-2;
						this.filter = this.default_filter;
					}
					if (line.compareTo(FILTER_LINE) == 0){
						this.order = this.default_order;
						inSectionCounter = 1;
					}
					else {
						String[] orderParts = orderComandParse(line);
						this.orderName = orderParts[0];
						if (orderParts[orderParts.length-1].compareTo(IS_REV) == 0){
							this.orderIsRev = true;
						}
						else {
							this.orderIsRev = false;
						}
						try {
							this.order = ORDER_FACTORY.getOrder(this.orderName, this.orderIsRev);
						}
						catch (TypeOneExeption e){
							errorAtLine = lineCounter;
							this.order = this.default_order;
						}
					}
					mySection = new Section(this.filter, this.order, errorAtLine);
					sections.add(mySection);
				}
			}
		}
		catch (IOException e){
			throw new TypeTwoExeption(ERROP_IO_MSG);
		}
		Section[] mySections = sections.toArray(new Section[sections.size()]);
		return mySections;
	}

	private String[] filterComandParse(String line){
		List<String> parts = new ArrayList<String>(Arrays.asList(line.split("#")));
		if (parts.get(parts.size()-1).compareTo("NOT") != 0){
			parts.add(NO_NOT);
		}
		String[] myParts = parts.toArray(new String[parts.size()]);
		return myParts;
	}

	private String[] orderComandParse(String line){
		String[] myParts = line.split("#");
		return myParts;
	}
}
