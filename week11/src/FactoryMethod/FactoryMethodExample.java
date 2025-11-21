package FactoryMethod;

// 1. Product
interface Document {
    void open();
    void save();
}

// 2. ConcreteProduct
class WordDocument implements Document {
    public void open() { System.out.println("Opening Word document..."); }
    public void save() { System.out.println("Saving Word document..."); }
}

class PdfDocument implements Document {
    public void open() { System.out.println("Opening PDF document..."); }
    public void save() { System.out.println("Saving PDF document..."); }
}

// 3. Creator
abstract class DocumentCreator {
    public abstract Document createDocument();

    public void newDocument() {
        Document doc = createDocument();
        doc.open();
    }
}

// 4. ConcreteCreator
class WordDocumentCreator extends DocumentCreator {
    public Document createDocument() {
        return new WordDocument();
    }
}

class PdfDocumentCreator extends DocumentCreator {
    public Document createDocument() {
        return new PdfDocument();
    }
}

// 5. Client
public class FactoryMethodExample {
    public static void main(String[] args) {
        System.out.println("Client: I need a Word document.");
        DocumentCreator wordCreator = new WordDocumentCreator();
        wordCreator.newDocument();

        System.out.println("\nClient: Now I need a PDF document.");
        DocumentCreator pdfCreator = new PdfDocumentCreator();
        pdfCreator.newDocument();
    }
}
