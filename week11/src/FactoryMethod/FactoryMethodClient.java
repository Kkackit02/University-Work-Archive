package FactoryMethod;

public class FactoryMethodClient {
    public static void main(String[] args) {
        System.out.println("Client: I need a Word document.");
        DocumentCreator wordCreator = new WordDocumentCreator();
        wordCreator.newDocument();

        System.out.println("\nClient: Now I need a PDF document.");
        DocumentCreator pdfCreator = new PdfDocumentCreator();
        pdfCreator.newDocument();
    }
}
