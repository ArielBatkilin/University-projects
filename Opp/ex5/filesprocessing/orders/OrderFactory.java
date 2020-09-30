package filesprocessing.orders;

import filesprocessing.TypeOneExeption;

import java.io.File;
import java.util.Comparator;

public class OrderFactory {

	public Comparator getOrder(String orderName, boolean isRev) throws TypeOneExeption {
		if (orderName.compareTo("abs") == 0){
			Comparator<File> myOrder = new AbsOrder();
			if (isRev){
				return myOrder.reversed();
			}
			return myOrder;
		}
		else if (orderName.compareTo("type") == 0){
			Comparator<File> myOrder = new TypeOrder();
			if (isRev){
				return myOrder.reversed();
			}
			return myOrder;
		}
		else if (orderName.compareTo("size") == 0){
			Comparator<File> myOrder = new SizeOrder();
			if (isRev){
				return myOrder.reversed();
			}
			return myOrder;
		}
		else {
			throw new TypeOneExeption();
		}
	}
}
