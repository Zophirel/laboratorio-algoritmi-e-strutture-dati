package grafo;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import edge.Edge;

public class Grafo_Test {
    private Grafo<Integer, Double> g;
    private Integer k1, k2, k3;
    private Edge<Integer, Double> e;
    
    @Before
    public void GrafoSetup(){
        g = new Grafo<>(false);
        
        k1 = 10;
        k2 = -1;
    }

    //It is an expected behavior since the hashtable
    //doesn't accept null keys and null values
    @Test(expected = NullPointerException.class)
    public void test_graphDoNotAllowNullKeys(){   
        g.addNode(k3);
    }
    
    @Test(expected = Grafo_Exception.class)
    public void test_graphDoNotAllowEdgesWithNullParameters() throws Grafo_Exception{   
        e = new Edge<Integer,Double>(k1, null, null);
        g.addNode(k1);
        g.addEdge(e);
    }

    @Test
    public void test_graphDoNotAcceptEdgesWhereDestNodeIsNotInTheGraph() throws Grafo_Exception{
        g.addNode(k1);
        e = new Edge<Integer,Double>(k1, k2, 10.10);
        g.addEdge(e);
        assertFalse(g.containsEdge(k1, e));
    }

    @Test
    public void test_graphDoNotAcceptDuplicateKeys(){
        g.addNode(k1);
        g.addNode(k1);
        g.addNode(10); //k1 = 10;
        assertEquals(g.nNodes(), 1);
    }

    @Test
    public void test_graphDoNotAcceptDuplicateEdges() throws Grafo_Exception{
        g.addNode(k1);
        g.addNode(k2);
        e = new Edge<Integer,Double>(k1, k2, 10.10);
        g.addEdge(e);
        g.addEdge(e);
        assertEquals(g.nEdges(), 1);
    }

    @Test
    public void test_addNode(){
        g.addNode(k1);
        assertTrue(g.containsNode(k1));
    }

    @Test
    public void test_removeNode(){
        g.addNode(k1);
        g.removeNode(k1);
        assertFalse(g.containsNode(k1));
    }

    @Test
    public void test_addEdge() throws Grafo_Exception{
        g.addNode(k1);
        g.addNode(k2);
        e = new Edge<Integer,Double>(k1, k2, 10.10);
        g.addEdge(e);
        assertTrue(g.containsEdge(k1, e));
    }

    @Test
    public void test_removeEdge() throws Grafo_Exception{
        g.addNode(k1);
        g.addNode(k2);
        e = new Edge<Integer,Double>(k1, k2, 10.10);
        g.addEdge(e);
        g.removeEdge(e);
        assertFalse(g.containsEdge(k1, e));
    }
    

    @Test
    public void test_removingANodeWillRemoveEveryEdgeWithTheNodeInsideFromTheGraph() throws Grafo_Exception{
        k3 = 100;
        g.addNode(k1);
        g.addNode(k2);
        g.addNode(k3);
    
        g.addEdge(new Edge<Integer,Double>(k1, k2, 10.10));
        g.addEdge(new Edge<Integer,Double>(k3, k2, 10.10));

        g.removeNode(k2);
        
        assertEquals(g.nEdges(), 0);
    }

    @Test
    public void test_getLabel() throws Grafo_Exception{
        Double label = 10.10;
        g.addNode(k1);
        g.addNode(k2);
    
        g.addEdge(new Edge<Integer,Double>(k1, k2, label));

        assertEquals(g.getLabel(k1, k2), label);
    }

    @Test
    public void test_adjNodes() throws Grafo_Exception{
        Double label = 10.10;
        g.addNode(k1);
        g.addNode(k2);
    
        g.addEdge(new Edge<Integer,Double>(k1, k2, label));

        assertEquals(g.getAdjNodes(k1).size(), 1);
        assertEquals(g.getAdjNodes(k1).getFirst(), k2);
    }

    @Test
    public void test_restore() throws Grafo_Exception{
        List<Edge<Integer,Double>> edges = new ArrayList<>();
        
        edges.add(new Edge<Integer,Double>(k1, k2, 10.10));
        edges.add(new Edge<Integer,Double>(k3, k2, 10.10));
        
        GrafoSetup(); g.restore(edges, false);

    }
}
