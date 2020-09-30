/**
 * This class represents a book, which has a title, author, year of publication and different literary aspects.
 */
class Patron {

	/** the next avaliable id */
	static int currentId = 1;

	/** the patrons id */
	final int patronId;

	/** The first name of the patron. */
	final String firstName;

	/** The last name of the patron. */
	final String lastName;

	/** The weight the patron assigns to the comic aspects of books. */
	int comicValue;

	/** The weight the patron assigns to the dramatic aspects of books. */
	int dramaticValue;

	/** The weight the patron assigns to the educational aspects of books. */
	int educationalValue;

	/** The minimal literary value a book must have for this patron to enjoy it. */
	int enjoymentThershold;

	/*----=  Constructors  =-----*/

	/**
	 * Creates a new patron with the given characteristics.
	 * @param patronFirstName  The first name of the patron.
	 * @param patronLastName The last name of the patron.
	 * @param comicTendency The weight the patron assigns to the comic aspects of books.
	 * @param dramaticTendency The weight the patron assigns to the dramatic aspects of books.
	 * @param educationalTendency The weight the patron assigns to the educational aspects of books.
	 * @param patronEnjoymentThreshold The minimal literary value a book must have for this patron to enjoy it.
	 */
	Patron(String patronFirstName, String patronLastName, int comicTendency, int dramaticTendency, int
			educationalTendency, int patronEnjoymentThreshold){
		firstName = patronFirstName;
		lastName = patronLastName;
		comicValue = comicTendency;
		dramaticValue = dramaticTendency;
		educationalValue = educationalTendency;
		enjoymentThershold = patronEnjoymentThreshold;
		patronId = currentId;
		currentId += 1;
	}

	/*----=  Instance Methods  =-----*/

	/**
	 * Returns a string representation of the patron, which is a sequence of its first and last name,
	 * separated by a single white space. For example, if the patron's first name is "Ricky" and his last name
	 * is "Bobby", this method will return the String "Ricky Bobby".
	 * @return the String representation of this patron.
	 */
	String stringRepresentation(){
		return firstName + " " + lastName;
	}

	/**
	 * Returns the literary value this patron assigns to the given book.
	 * @param book The book to asses.
	 * @return the literary value this patron assigns to the given book.
	 */
	int getBookScore(Book book){
		int bookScore = book.getComicValue()*comicValue + book.getEducationalValue()*educationalValue + book
				.getDramaticValue()*dramaticValue;
		return bookScore;
	}

	/**
	 * Returns true of this patron will enjoy the given book, false otherwise.
	 * @param book The book to asses.
	 * @return true of this patron will enjoy the given book, false otherwise.
	 */
	boolean willEnjoyBook(Book book){
		int bookScore = getBookScore(book);
		if (bookScore >= enjoymentThershold){
			return true;
		}else {
			return false;
		}
	}

	/**
	 * returns the patron id
	 * @return patrons id
	 */
	int getPatronId() {
		return patronId;
	}
}
