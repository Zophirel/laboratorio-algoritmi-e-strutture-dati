package csvreader;
import java.io.*;
import edge.*;
import grafo.*;

public class Csvreader{
    public Grafo<String, Double> csvToGraph(String filePath, boolean directed){ 
        Grafo<String, Double> g = new Grafo<>(directed);      
        try{    
            BufferedReader csvReader = new BufferedReader(new FileReader(filePath));
            String row;
            while ((row = csvReader.readLine()) != null) {  
                String[] data = row.split(","); 
                Edge<String, Double> e = new Edge<>(data[0], data[1], Double.parseDouble(data[2]));
                g.restoring = true;
                g.addNode(e.src);
                g.addNode(e.dest);
                g.addEdge(e);
            }
            g.restoring = false;
            csvReader.close();
        }catch(Exception err){
            System.out.println(err);
        }
        return g;
    }
}