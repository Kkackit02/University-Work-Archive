package Prototype;

import java.io.IOException;

public class PrototypeDemo {
    public static void main(String[] args) throws IOException {
        int eid = 100301;
        String ename = "홍길동";
        String edesignation = "직함";
        double esalary = 2000000;
        String eaddress = "서울시 서초구";

        EmployeeRecord e1 = new EmployeeRecord(eid, ename, edesignation, esalary, eaddress);
        System.out.print("e1객체 ");
        e1.showRecord();

        System.out.println("\n");

        EmployeeRecord e2 = (EmployeeRecord) e1.getClone();
        System.out.print("e2객체 ");
        e2.showRecord();
    }
}

