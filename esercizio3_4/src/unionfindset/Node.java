//Data structure for the production of Disjoint Sets
package unionfindset;
import java.util.Objects;

public class Node<T>{
    private T elem;
    private Node<T> parent;
    private int rank;

    public void makeSet(T elem) throws Node_Exception{
        if(elem == null)
            throw new Node_Exception("Node elem cannot be null");
        else
            this.elem = elem;
            this.parent = this;
            this.rank = 0;
    }
    
    //Contructor for the production of a Vertex / Node 
    //that will be used to compose the graph
    public Node(){}

    //function to find the rapresentative of a certain set, it uses
    //the path compression heuristic
    public Node<T> find(){
        if(this != this.getParent()){
            Node<T> prev = this.parent;
            this.parent = prev.find();
            return this.parent;
        }else{
            return this;
        }
    }
    
    //function to make the union of two given vertex / node
    //it uses the union by rank heuristic
    public void union(Node<T> b) throws Node_Exception{
        Node<T> rootA = this.find();
        Node<T> rootB = b.find();
        if(this.getElem() == null)
            throw new Node_Exception("Cannot join not initialized (by makeSet()) Nodes");
        if(rootA == rootB)
            return;        
        if(rootA.rank < rootB.rank){
            rootA.parent = rootB;
        }
        if(rootA.rank > rootB.rank){
            rootB.parent = rootA;
        }else{
            rootA.parent = rootB;
            rootB.rank +=1;
        }
    }

    //function to return vertex value assigned 
    //during the initialization
    public T getElem(){  
        return this.elem;
    }
    
    public T getRank(){  
        return this.elem;
    }

    public Node<T> getParent(){
        return this.parent;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(obj == null)
            return false;
        if(obj instanceof Node){
            Node<?> tmp = (Node<?>) obj;
            if(tmp.getElem() == this.getElem()){
                return true;
            }
        }
        return false;
    }

    @Override
    public int hashCode() {
        return 31 * Objects.hashCode(this.getElem());
    }
}