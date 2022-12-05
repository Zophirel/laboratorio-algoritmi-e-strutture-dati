//Data structure implementation for sparse-graph 
package grafo;
import edge.*;
import java.util.Set;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.List;

public class Grafo<T, V> {
    public Hashtable<T, HashSet<Edge<T, V>>> adjTable;
    private boolean directed;
    public boolean restoring = false; //used to silent prints when re-creating a graph from a list of edges
    
    public Grafo(boolean directed){
        this.adjTable = new Hashtable<>();
        this.directed = directed;
    }

    public void addNode(T v){
        if(!this.containsNode(v))    
            this.adjTable.put(v, new HashSet<Edge<T, V>>());
        else{
            if(restoring == false)
                System.err.println("Vertex already exist inside the graph");
        }
    }

    public void addEdge(Edge<T, V> a) throws Grafo_Exception{
        if(a.src == null | a.dest == null | a.weight == null)
            throw new Grafo_Exception("An edge with null parameters cannot be added");

        if(this.containsNode(a.src)){
            if(this.containsNode(a.dest)){
                if(!this.containsEdge(a.src, a)){
                    if(this.directed == true){    
                        this.adjTable.get(a.src).add(a);
                   
                    }
                    else{
                        this.adjTable.get(a.src).add(a);
                        Edge<T,V> tmp = new Edge<T,V>(a.dest, a.src, a.weight);
                        this.adjTable.get(tmp.src).add(tmp);
                    }

                }else{
                    if(restoring == false)
                        System.err.println("First vertex already contains the given edge");
                }
            }else{
                if(restoring == false)
                    System.err.println("Second vertex not found");
            }
        }else{
            if(restoring == false)
                System.err.println("First vertex not found");
        }
    }

    public void printAdj(){
        for(T key : this.adjTable.keySet()){
            for(Edge<T, V> e : this.adjTable.get(key)){
                System.out.print(key + " -> " + e.dest + " (" + e.weight + ")" + " ");
            }    
            if(this.adjTable.get(key).size() == 0){
                System.out.print(key);
            }
            System.out.println();
        }
        System.out.println();
    }

    public void printEdges(HashSet<Edge<T,V>> Edges){
        for(Edge<T,V> e : Edges){
            System.out.println(e.src + " -> " + e.dest + " " + "(" + e.weight + ")");
        }
    }

    public boolean containsNode(T v){
        if(this.adjTable.containsKey(v)) 
            return true;
        else   
            return false;
    }

    public boolean containsEdge(T v, Edge<T,V> a){
        if(this.adjTable.get(v).contains(a))
            return true;
        else
            return false;
    }

    public void removeNode(T v){
        if(this.adjTable.containsKey(v)){
            if(this.adjTable.get(v).size() != 0){    
                for(T tmpV : this.adjTable.keySet()){
                    if(this.adjTable.get(tmpV).contains(new Edge<T,V>(null, v, null))){
                        this.adjTable.get(tmpV).remove(new Edge<T,V>(null, v, null));
                    }
                }
            }
            this.adjTable.remove(v);
        }
        else 
            System.err.println("The given vertex doesn't exist");
    }

    public void removeEdge(Edge<T,V> a){
        if(this.containsNode(a.src)){
            if(this.containsEdge(a.src, a))
                if(this.directed == true)
                    this.adjTable.get(a.src).remove(a);
                else{
                    this.adjTable.get(a.src).remove(a);
                    Edge<T,V> tmp = new Edge<T,V>(a.dest, a.src, a.weight);
                    this.adjTable.get(tmp.src).remove(tmp);
                }
            else{
                System.err.println("The given edge dosen't exist");
                return;
            }
        }else{
            System.err.println("The vertex form which the edge has to be removed dose not exist");
            return;
        }
    }

    public int nNodes(){
        return this.adjTable.keySet().size();
    }

    public int nEdges(){
        int num = 0;
        for(T key : this.adjTable.keySet()){
            num += this.adjTable.get(key).size();
        }
        if(directed == false)
            return num / 2;
        return num;
    }

    public Set<T> getNodes(){
        return this.adjTable.keySet();
    }

    public List<Edge<T,V>> getEdges(){
        List<Edge<T,V>> tmp = new ArrayList<>();
        for(T key : this.adjTable.keySet()){
            tmp.addAll(this.adjTable.get(key));
        }
        return tmp;
    }

    public LinkedList<T> getAdjNodes(T v){
        LinkedList<T> vAdjList = new LinkedList<T>();
        for(Edge<T,V> e : this.adjTable.get(v)){
            vAdjList.add(e.dest);
        }
        return vAdjList;
    }

    public V getLabel(T v, T v2){
        if(this.containsNode(v)){
            if(this.containsNode(v2)){
                for(Edge<T,V> e : this.adjTable.get(v)){
                    if(e.dest.equals(v2)){
                        return e.weight;
                    }
                }
                System.err.println("The first vertex is not adjacent to the second one");
            }else{
                System.err.println("Second vertex not found");
            }
        }else{
            System.err.println("First vertex not found");
        }
        return null;
    }

    //return a new Graph built from a given list of edges
    public Grafo<T,V> restore(List<Edge<T,V>> edges, boolean directed) throws Grafo_Exception{
        Grafo<T,V> g = new Grafo<>(directed);
        g.restoring = true;
        for(Edge<T,V> e : edges){
            g.addNode(e.src);
            g.addNode(e.dest);
            g.addEdge(e);
        }
        g.restoring = false;
        return g;
    }
}