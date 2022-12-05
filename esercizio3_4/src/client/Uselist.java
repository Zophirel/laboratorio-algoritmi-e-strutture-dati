package client;

import csvreader.Csvreader;
import grafo.*;
import java.io.*;
import kruskal.*;

public class Uselist{
    public static void main(String[] args) {
        Csvreader reader = new Csvreader();
        Kruskal<String, Double> k = new Kruskal<>();
        
        try{
            Grafo<String, Double> g = reader.csvToGraph("./italian_dist_graph.csv", false);
            
            PrintStream stdout = System.out;
            System.setOut(new PrintStream("./out.txt"));
            
            Grafo<String, Double> mstG = k.MSTKruskal(g);
            mstG.printAdj();

            System.setOut(stdout);
            System.out.println("I nodi totali sono: " + mstG.nNodes());
            System.out.println("Gli archi totali sono: " + mstG.nEdges()); 
        }
        catch(Exception e){
            System.out.println("Uselist: " + e);
        }         
    }
}
