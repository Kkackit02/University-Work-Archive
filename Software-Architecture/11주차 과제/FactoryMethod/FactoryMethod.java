package FactoryMethod;

// ===== 1. Product (제품) =====
// 제품의 공통 인터페이스
interface Document {
    void open();
    void save();
}

// ===== 2. ConcreteProduct (실제 제품) =====
// 실제 워드 문서
class WordDocument implements Document {
    @Override
    public void open() {
        System.out.println("Opening Word document...");
    }

    @Override
    public void save() {
        System.out.println("Saving Word document...");
    }
}

// 실제 PDF 문서
class PdfDocument implements Document {
    @Override
    public void open() {
        System.out.println("Opening PDF document...");
    }

    @Override
    public void save() {
        System.out.println("Saving PDF document...");
    }
}

// ===== 3. Creator (생성자) =====
// 생성자의 공통 인터페이스 (핵심: 팩토리 메소드)
abstract class DocumentCreator {
    // 팩토리 메소드: 서브클래스가 구현해야 함
    public abstract Document createDocument();

    // 팩토리 메소드를 사용하는 공통 로직
    public void newDocument() {
        Document doc = createDocument();
        doc.open();
    }
}

// ===== 4. ConcreteCreator (실제 생성자) =====
// 워드 문서를 만드는 생성자
class WordDocumentCreator extends DocumentCreator {
    @Override
    public Document createDocument() {
        // "어떤" 문서를 만들지 서브클래스가 결정
        return new WordDocument();
    }
}

// PDF 문서를 만드는 생성자
class PdfDocumentCreator extends DocumentCreator {
    @Override
    public Document createDocument() {
        // "어떤" 문서를 만들지 서브클래스가 결정
        return new PdfDocument();
    }
}

// ===== 5. Client (사용자) =====
public class FactoryMethod {
    public static void main(String[] args) {
        // 사용자는 "어떤" 문서가 생성되는지 모름
        // 오직 "어떤 생성자"를 쓸지만 결정
        System.out.println("Client: I need a Word document.");
        DocumentCreator wordCreator = new WordDocumentCreator();
        wordCreator.newDocument(); // "Opening Word document..." 출력

        System.out.println("\nClient: Now I need a PDF document.");
        DocumentCreator pdfCreator = new PdfDocumentCreator();
        pdfCreator.newDocument(); // "Opening PDF document..." 출력
    }
}
