package filesprocessing;

public class TypeTwoExeption extends Exception {

	private String msg;
	public TypeTwoExeption(String aMsg){
		this.msg = aMsg;
	}

	public String getMsg() {
		return msg;
	}
}
