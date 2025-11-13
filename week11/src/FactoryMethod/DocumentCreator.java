package FactoryMethod;

public abstract class DocumentCreator {
    public abstract Document createDocument();

    public void newDocument() {
        Document doc = createDocument();
        doc.open();
    }
}
