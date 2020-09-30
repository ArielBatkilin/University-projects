
/**
 * This class represents a library, which hold a collection of books. Patrons can register at the library
 * to be able to check out books, if a copy of the requested book is available.
 */
class Library {

	/**
	 * The maximal number of books this library can hold.
	 */
	static Book[] booksArray;

	/**
	 * The maximal number of books this library allows a single patron to borrow at the same time.
	 */
	int maxBooksForPatron;

	/**
	 * The maximal number of registered patrons this library can handle.
	 */
	static Patron[] patronsArray;

	/**
	 * will hold the information of the numbers of books a patron has(it will be in the same place in the
	 * array like the patron
	 */
	static int[] patronsNumberOfBooks;

	/*----=  Constructors  =-----*/

	/**
	 * Creates a new library with the given parameters.
	 *
	 * @param maxBookCapacity - The maximal number of books this library can hold.
	 * @param maxBorrowedBooks - The maximal number of books this library allows a single patron to borrow
	 *                           at the same time.
	 * @param maxPatronCapacity - The maximal number of registered patrons this library can handle.
	 */
	Library(int maxBookCapacity, int maxBorrowedBooks, int maxPatronCapacity){
		booksArray = new Book[maxBookCapacity];
		maxBooksForPatron = maxBorrowedBooks;
		patronsArray = new Patron[maxPatronCapacity];
		patronsNumberOfBooks = new int[maxPatronCapacity];
	}

	/**
	 * Adds the given book to this library, if there is place available, and it isn't already in the library.
	 *
	 * @param book to add to this library.
	 * @return a non-negative id number for the book if there was a spot and the book was successfully added,
	 * or if the book was already in the library; a negative number otherwise
	 */
	int addBookToLibrary(Book book){
		int availableSpot = -1;
		for (int i=0; i<booksArray.length; i++){
			if (booksArray[i] == null){
				availableSpot = i;
				continue;
			} if (book.getBookId() == booksArray[i].getBookId()){
				return book.getBookId();
			}
		} if (availableSpot == -1){
			return -1;
		} else
			booksArray[availableSpot] = book;
		return book.getBookId();
	}

	/**
	 * Returns true if the given number is an id of some book in the library, false otherwise.
	 *
	 * @param bookId id to check
	 * @return true if the given number is an id of some book in the library, false otherwise.
	 */
	boolean isBookIdValid(int bookId){
		for (int i=0; i<booksArray.length; i++){
			if (booksArray[i] == null){
				continue;
			} else if (booksArray[i].getBookId() == bookId){
				return true;
			}
		}
		return false;
	}

	/**
	 * Returns the non-negative id number of the given book if he is owned by this library, -1 otherwise.
	 *
	 * @param book book for which to find the id number.
	 * @return a non-negative id number of the given book if he is owned by this library, -1 otherwise.
	 */
	int getBookId(Book book){
		if (book == null){
			return -1;
		}
		for (int i=0; i<booksArray.length; i++){
			if (booksArray[i] == null){
				continue;
			}
			if (booksArray[i].getBookId() == book.getBookId()){
				return book.getBookId();
			}
		}
		return -1;
	}

	/**
	 * if the book is in the library we return its place, -1 otherwise.
	 *
	 * @param bookId book for which to find the id number.
	 * @return the place in the array the book at.
	 */
	int getBookPlace(int bookId){
		for (int i=0; i<booksArray.length; i++){
			if (booksArray[i].getBookId() == bookId){
				return i;
			}
		}
		return -1;
	}

	/**
	 * Returns true if the book with the given id is available, false otherwise.
	 *
	 * @param bookId id number of the book to check.
	 * @return true if the book with the given id is available, false otherwise.
	 */
	boolean isBookAvailable(int bookId){
		if (isBookIdValid(bookId)==true){
			int bookPlace = getBookPlace(bookId);
			if (booksArray[bookPlace].getCurrentBorrowerId() == -1){
				return true;
			}
		}
		return false;
	}

	/**
	 * Registers the given Patron to this library, if there is a spot available.
	 *
	 * @param patron patron to register to this library.
	 * @return a non-negative id number for the patron if there was a spot and the patron was successfully
	 * registered, a negative number otherwise.
	 */
	int registerPatronToLibrary(Patron patron) {
		int avalaibleSpot = -1;
		for (int i = 0; i < patronsArray.length; i++) {
			if (patronsArray[i] == null) {
				avalaibleSpot = i;
				continue;
			} if (patron.getPatronId() == patronsArray[i].getPatronId()) {
				return patron.getPatronId();
			}
		}
		if (avalaibleSpot == -1) {
			return -1;
		} else
			patronsArray[avalaibleSpot] = patron;
		return patron.getPatronId();
	}

	/**
	 * Returns true if the given number is an id of a patron in the library, false otherwise.
	 *
	 * @param patronId - The id to check.
	 * @return true if the given number is an id of a patron in the library, false otherwise.
	 */
	boolean isPatronIdValid(int patronId){
		for (int i=0; i<patronsArray.length; i++){
			if (patronsArray[i] == null){
				continue;
			} if (patronId == patronsArray[i].getPatronId()){
				return true;
			}
		}
		return false;
	}


	/**
	 *Returns the non-negative id number of the given patron if he is registered to this library,
	 *  -1 otherwise.
	 *
	 * @param patron - The patron for which to find the id number.
	 * @return a non-negative id number of the given patron if he is registered to this library, -1 otherwise.
	 */
	int getPatronId(Patron patron){
		for (int i=0; i<patronsArray.length; i++){
			if (patron.getPatronId() == patronsArray[i].getPatronId()){
				return patron.getPatronId();
			}
		}
		return -1;
	}

	/**
	 *
	 * @param patronId - the id to check
	 * @return the place the patron located in the array, -1 if not in the array.
	 */
	int getPatronPlace(int patronId){
		for (int i=0; i<patronsArray.length; i++){
			if (patronsArray[i] == null){
				continue;
			} if (patronId == patronsArray[i].getPatronId()){
				return i;
			}
		}
		return -1;
	}

	/**
	 * Marks the book with the given id number as borrowed by the patron with the given patron id, if this
	 * book is available, the given patron isn't already borrowing the maximal number of books allowed, and
	 * if the patron will enjoy this book.
	 *
	 * @param bookId - The id number of the book to borrow.
	 * @param patronId - The id number of the patron that will borrow the book.
	 * @return true if the book was borrowed successfully, false otherwise.
	 */
	boolean borrowBook(int bookId, int patronId){
		if (isBookAvailable(bookId)){
			int patronsPlace = getPatronPlace(patronId);
			if (patronsPlace == -1){
				return false;
			} if (patronsNumberOfBooks[patronsPlace] < maxBooksForPatron){
				int booksPlace = getBookPlace(bookId);
				if (patronsArray[patronsPlace].willEnjoyBook(booksArray[booksPlace])){
					patronsNumberOfBooks[patronsPlace]+=1;
					booksArray[booksPlace].setBorrowerId(patronId);
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Return the given book.
	 *
	 * @param bookId - The id number of the book to return.
	 */
	void returnBook(int bookId){
		int booksPlace = getBookPlace(bookId);
		int myPatronsId = booksArray[booksPlace].getCurrentBorrowerId();
		int patronsPlace = getPatronPlace(myPatronsId);
		booksArray[booksPlace].setBorrowerId(-1);
		patronsNumberOfBooks[patronsPlace]-=1;
	}

	/**
	 * Suggest the patron with the given id the book he will enjoy the most, out of all available books he
	 * will enjoy, if any such exist.
	 *
	 * @param patronId - The id number of the patron to suggest the book to.
	 * @return The available book the patron with the given will enjoy the most. Null if no book is available.
	 */
	Book suggestBookToPatron(int patronId){
		int booksId=0;
		int max = -1;
		Book bestBook = null;
		for (int i=0; i<booksArray.length; i++){
			Book myBook = booksArray[i];
			if (myBook == null){
				continue;
			}
			if (isBookAvailable(booksId)){
				int patronsPlace = getPatronPlace(patronId);
				int booksPlace = getBookPlace(booksId);
				if (patronsArray[patronsPlace].willEnjoyBook(myBook)){
					if (patronsArray[patronsPlace].getBookScore(myBook)>max){
						max = patronsArray[patronsPlace].getBookScore(myBook);
						bestBook = myBook;
					}
				}
			}
		}
		return bestBook;
	}
}
