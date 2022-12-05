package edge;
import java.util.Objects;

public class Edge<T, V>{
    public T src;
    public T dest;
    public V weight;
    public Edge(T src, T dest, V weight){
        this.src = src;
        this.dest = dest;
        this.weight = weight;
    }

    //overriding the equals and hashCode Object methods to make
    //two edges equals only if they have the same `dest` since two nodes
    //can share only one edge between them
    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(obj == null)
            return false;
        if(obj instanceof Edge){
            Edge<?,?> tmp = (Edge<?,?>) obj;
            if(tmp.dest == this.dest){
                return true;
            }
        }
        return false;
    }

    @Override
    public int hashCode() {
        return 31 * Objects.hashCode(this.dest);
    }
}