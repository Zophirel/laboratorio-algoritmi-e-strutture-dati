package unionfindset;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class Node_Test{
    private Node<Integer> intNode1, intNode2, intNode3;
    private Node<Object> EmptyNode;
    
    @Before
    public void initSomeNode() throws Node_Exception{
        EmptyNode = new Node<>();
        intNode1 = new Node<>();
        intNode2 = new Node<>();
        intNode3 = new Node<>();
        
        intNode1.makeSet(1);
        intNode2.makeSet(2);
        intNode3.makeSet(3); 
    }

    @Test
    public void test_oneIsNotTwo(){
        assertNotEquals(intNode1,intNode2);
    }

    @Test
    public void test_newNodesAreEquals(){
        assertEquals(new Node<>(),new Node<>());
    } 

    @Test
    public void test_makeSetElemAssignament(){
        assertTrue(intNode1.getElem().equals(1));
    }

    @Test
    public void test_makeSettedNodeHasItSelfAsParent(){
        assertEquals(intNode1, intNode1.getParent());
    }

    @Test
    public void test_WhenTwoRootNodeJoinTheSecondWillBeTheNewParent() throws Node_Exception{
        intNode1.union(intNode2);
        assertEquals(intNode1.getParent(), intNode2);
    }

    @Test 
    public void test_findAlwaysReturnTheRepOfTheDisjointSetOfAGivenNode() throws Node_Exception{
        Node<Integer> intNode4 = new Node<>();
        intNode4.makeSet(4);

        intNode1.union(intNode2);   //(2[parent]) -> (1)
        intNode4.union(intNode3);   //(3[parent]) -> (4)
        
        intNode2.union(intNode4);   /*      (3)       *
                                    *       / \       *
                                    *     (4) (2)     *
                                    *          |      *
                                    *         (1)     */
                                    
        assertEquals(intNode1.find(), intNode3);
        assertEquals(intNode2.find(), intNode3);
        assertEquals(intNode4.find(), intNode3);
    }

    @Test
    public void test_notMakeSettedNodesHaveNullParameters(){
        assertEquals(EmptyNode.getElem(), null);
        assertEquals(EmptyNode.getParent(), null);
        assertEquals(EmptyNode.getRank(), null);
    }

}