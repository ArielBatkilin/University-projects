package filesprocessing;

import filesprocessing.filters.Filter;

import java.util.Comparator;

public class Section {

	private Filter filter;
	private Comparator order;
	private int errorLine;

	public Section(Filter aFilter, Comparator anOrder, int errorInLine){
		this.filter = aFilter;
		this.order = anOrder;
		this.errorLine = errorInLine;
	}

	public Filter getFilter() {
		return filter;
	}

	public Comparator getOrder() {
		return order;
	}

	public int getErrorLine() {
		return errorLine;
	}
}
