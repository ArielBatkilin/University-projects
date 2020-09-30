package filesprocessing.filters;

import filesprocessing.TypeOneExeption;

public class FilterFactory {

	private final String THERE_IS_NOT = "NOT";
	private final String VALID_INPUT = "YAA";

	/**
	 *
	 * @param filterName
	 * @param otherParam - array of string of the other param
	 * @return
	 */
	public Filter getFillter(String filterName, String[] otherParam) throws TypeOneExeption {
		boolean isNot = false;
		if (filterName.compareTo("greater_than")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			double size = Double.parseDouble(otherParam[0]);
			if (!nonNegCheck(size)){
				throw new TypeOneExeption();
			}
			return new GreaterThanFilter(isNot, size);
		}
		else if (filterName.compareTo("smaller_than")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			double size = Double.parseDouble(otherParam[0]);
			if (!nonNegCheck(size)){
				throw new TypeOneExeption();
			};
			return new SmallerThanFilter(isNot, size);
		}
		else if (filterName.compareTo("between")==0){
			if (otherParam.length != 3){
				throw new TypeOneExeption();
			}
			if(otherParam[2].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[2].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			double size1 = Double.parseDouble(otherParam[0]);
			double size2 = Double.parseDouble(otherParam[1]);
			if (!(nonNegCheck(size1)&&nonNegCheck(size2)&&biggerCheck(size1,size2))){
				throw new TypeOneExeption();
			}
			return new BetweenFilter(isNot, size1, size2);
		}
		else if (filterName.compareTo("file")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			String nameToCheck = otherParam[0];
			return new FileFilter(isNot, nameToCheck);
		}
		else if (filterName.compareTo("contains")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			String nameToCheck = otherParam[0];
			return new ContainsFilter(isNot, nameToCheck);
		}
		else if (filterName.compareTo("prefix")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			String nameToCheck = otherParam[0];
			return new PrefixFilter(isNot, nameToCheck);
		}
		else if (filterName.compareTo("suffix")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			String nameToCheck = otherParam[0];
			return new SuffixFilter(isNot, nameToCheck);
		}
		else if (filterName.compareTo("writable")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			boolean needToBeWritable = true;
			if (!stringIsYesOrNo(otherParam[0])){
				throw new TypeOneExeption();
			}
			else {
				if (otherParam[0].compareTo("YES") == 0){
					needToBeWritable = true;
				}
				else needToBeWritable = false;
			}
			return new WriteableFilter(isNot, needToBeWritable);
		}
		else if (filterName.compareTo("executable")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			boolean needToBeExecutable = true;
			if (!stringIsYesOrNo(otherParam[0])){
				throw new TypeOneExeption();
			}
			else {
				if (otherParam[0].compareTo("YES") == 0){
					needToBeExecutable = true;
				}
				else needToBeExecutable = false;
			}
			return new ExecutableFiltter(isNot, needToBeExecutable);
		}
		else if (filterName.compareTo("hidden")==0){
			if (otherParam.length != 2){
				throw new TypeOneExeption();
			}
			if(otherParam[1].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[1].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			boolean needToBeHidden = true;
			if (!stringIsYesOrNo(otherParam[0])){
				throw new TypeOneExeption();
			}
			else {
				if (otherParam[0].compareTo("YES") == 0){
					needToBeHidden = true;
				}
				else needToBeHidden = false;
			}
			return new HiddenFilter(isNot, needToBeHidden);
		}
		else if (filterName.compareTo("all")==0){
			if (otherParam.length != 1){
				throw new TypeOneExeption();
			}
			if(otherParam[0].compareTo(THERE_IS_NOT) == 0){
				isNot = true;
			}
			else if (otherParam[0].compareTo(VALID_INPUT) != 0){
				throw new TypeOneExeption();
			}
			return new AllFilter(isNot);
		}
		else {
			throw new TypeOneExeption();
		}
	}

	private boolean nonNegCheck(double num){
		if (num >= 0){
			return true;
		}
		return false;
	}

	private boolean biggerCheck(double a, double b){
		if (a>=b){
			return true;
		}
		return false;
	}

	private boolean stringIsYesOrNo(String s){
		if (s.compareTo("YES") * s.compareTo("NO") == 0){
			return true;
		}
		return false;
	}
}
