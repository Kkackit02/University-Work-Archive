package konkuk.software.iterator;

public class Collection implements CollectionIF {
    private InventoryItem[] books;
    private int last = 0;

    public Collection(int maxsize) {
        this.books = new InventoryItem[maxsize];
    }

    public InventoryItem getBookAt(int inx) {
        return books[inx];
    }

    public void setBookAt(InventoryItem book) {
        this.books[last] = book;
        last++;
    }

    public int getLength() {
        return last;
    }

    @Override
    public InventoryIteratorIF iterator() {
        return new InventoryIterator(this);
    }
}
