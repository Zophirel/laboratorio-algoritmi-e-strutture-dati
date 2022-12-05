package kruskal;
import unionfindset.*;
import grafo.*;
import edge.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Hashtable;

public class Kruskal<T, V extends Comparable<V>> {

    private void merge(List<Edge<T, V>> left, List<Edge<T, V>> right, List<Edge<T, V>> list) {
        int leftIndex = 0;
        int rightIndex = 0;
        int listIndex = 0;

        while (leftIndex < left.size() && rightIndex < right.size()) {
            if (left.get(leftIndex).weight.compareTo(right.get(rightIndex).weight) < 0) {
                list.set(listIndex++, left.get(leftIndex++));
            } else {
                list.set(listIndex++, right.get(rightIndex++));
            }
        }
        while (leftIndex < left.size()) {
            list.set(listIndex++, left.get(leftIndex++));
        }
        while (rightIndex < right.size()) {
            list.set(listIndex++, right.get(rightIndex++));
        }
    }

    public void sort(List<Edge<T, V>> list) {
        if (list.size() < 2) {
            return;
        }
        
        int mid = list.size()/2;
        List<Edge<T, V>> left = new ArrayList<Edge<T, V>>(list.subList(0, mid));
        List<Edge<T, V>> right = new ArrayList<Edge<T, V>>(list.subList(mid, list.size()));
    
        sort(left);
        sort(right);
        merge(left, right, list);
    }

    public Grafo<T,V> MSTKruskal(Grafo<T,V> g) throws Node_Exception, Grafo_Exception{
        Hashtable<T, Node<T>> allVertici = new Hashtable<>();        
        
        for(T key : g.adjTable.keySet()){
            Node<T> v = new Node<>();
            v.makeSet(key);
            allVertici.put(key, v);
        }
        
        List<Edge<T,V>> allEdges = g.getEdges();
        sort(allEdges);
        List<Edge<T,V>> mstEdges = new ArrayList<>();

        for(Edge<T,V> e : allEdges){
            if(allVertici.get(e.src).find() != allVertici.get(e.dest).find()){
                mstEdges.add(e);
                allVertici.get(e.src).union(allVertici.get(e.dest));
            }
        }
        return g.restore(mstEdges, false);
    }
}