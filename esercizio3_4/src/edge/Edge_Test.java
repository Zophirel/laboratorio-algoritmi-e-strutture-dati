package edge;
/*
* the edge class doesn't have much to be tested since is
* pratically a class without proper methods and even 
* null parameters are allowed, the graph data structure
* will be responsible to not allow the insertion of null edges
*/

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import org.junit.Before;
import org.junit.Test;

public class Edge_Test {
    private Edge<Integer, Double> e1, e2, e3;
    
    @Before
    public void initSomeEdges(){
        e1 = new Edge<Integer,Double>(1, 2, 1.2);
        e2 = new Edge<Integer,Double>(1, null, 1.2);
        e3 = new Edge<Integer,Double>(null, 2, null);
    }

    @Test
    public void test_edgesAreEqualOnlyIfDestIsEqualBetweenThem(){
        assertEquals(e1, e3);
        assertNotEquals(e2, e3);
    }
}
