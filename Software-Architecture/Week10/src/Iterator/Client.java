package Iterator;

public class Client {
    public static void main(String[] args) {
        Collection bs = new Collection(5);
        bs.setBookAt(new InventoryItem("노인과바다"));
        bs.setBookAt(new InventoryItem("논리야놀자"));
        bs.setBookAt(new InventoryItem("수학의정석"));
        bs.setBookAt(new InventoryItem("Patterns in Java Volume 1"));
        bs.setBookAt(new InventoryItem("202112346 정근녕"));

        InventoryIteratorIF it = bs.iterator();
        while (it.hasNext()) {
            System.out.println(((InventoryItem) it.next()).getName());
        }
    }
}
