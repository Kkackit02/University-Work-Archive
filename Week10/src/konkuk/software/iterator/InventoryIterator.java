package konkuk.software.iterator;

public class InventoryIterator implements InventoryIteratorIF {
    private Collection bookShelf;
    private int index;

    public InventoryIterator(Collection bookShelf) {
        this.bookShelf = bookShelf;
        this.index = 0;
    }

    public boolean hasNext() {
        if (index < bookShelf.getLength()) {
            return true;
        } else {
            return false;
        }
    }

    public Object next() {
        InventoryItem book = bookShelf.getBookAt(index);
        index++;
        return book;
    }
}
