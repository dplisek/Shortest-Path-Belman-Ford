//
//  main.cpp
//  BelmanFord
//
//  Created by Dominik Plíšek on 5/22/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

#define INF_DIST 9999
#define NO_NODE 0


#ifndef __PROGTEST__
#include "CGraph.h"
#include "t_edge.h"
#include "t_node.h"
#endif

void initPaths(CGraph& g, const int startIndex) {
    for (int i = 1; i <= g.getNodeCounter(); ++i) {
        t_node node = g.getNode(i);
        if (i == startIndex) {
            node.distance = 0;
        } else {
            node.distance = INF_DIST;
        }
        node.predecessorIndex = NO_NODE;
        g.setNode(i, node);
    }
}

void relax(CGraph& g, int edgeIndex) {
    t_edge edge = g.getEdge(edgeIndex);
    int sourceDist = g.getNode(edge.sourceIndex).distance;
    if (sourceDist == INF_DIST) return;
    t_node destNode = g.getNode(edge.destinationIndex);
    int destDist = destNode.distance;
    int newDestDist = sourceDist + edge.value;
    if (newDestDist >= destDist) return;
    destNode.distance = newDestDist;
    destNode.predecessorIndex = edge.sourceIndex;
    g.setNode(edge.destinationIndex, destNode);
}

void relaxAllEdges(CGraph& g) {
    for (int i = 1; i <= g.getEdgeCounter(); ++i) {
        relax(g, i);
    }
}

void relaxAllEdgesRepetetively(CGraph& g) {
    for (int i = 0; i < g.getNodeCounter() - 1; ++i) {
        relaxAllEdges(g);
    }
}

bool hasNegativeCycles(CGraph& g) {
    for (int i = 1; i <= g.getEdgeCounter(); ++i) {
        t_edge edge = g.getEdge(i);
        int sourceDist = g.getNode(edge.sourceIndex).distance;
        if (sourceDist == INF_DIST) continue;
        t_node destNode = g.getNode(edge.destinationIndex);
        int destDist = destNode.distance;
        int newDestDist = sourceDist + edge.value;
        if (newDestDist < destDist) return true;
    }
    return false;
}

bool BF(CGraph& g, const int startIndex) {
    initPaths(g, startIndex);
    relaxAllEdgesRepetetively(g);
    return !hasNegativeCycles(g);
}

#ifndef __PROGTEST__
int main(int argc, const char * argv[]) {
    CGraph g;
    t_node node1;
    t_node node2;
    t_node node3;
    t_node node4;
    t_node node5;
    t_node node6;
    t_node node7;
    t_node node8;
    t_node node9;
    t_node node10;
    t_node node11;
    g.addNode(node1);
    g.addNode(node2);
    g.addNode(node3);
    g.addNode(node4);
    g.addNode(node5);
    g.addNode(node6);
    g.addNode(node7);
    g.addNode(node8);
    g.addNode(node9);
    g.addNode(node10);
    g.addNode(node11);
    t_edge edge1(1, 2, 67);
    t_edge edge2(1, 3, 33);
    t_edge edge3(1, 4, 2);
    t_edge edge4(1, 9, 53);
    t_edge edge5(2, 9, 69);
    t_edge edge6(3, 2, 24);
    t_edge edge7(3, 7, 51);
    t_edge edge8(4, 3, 76);
    t_edge edge9(4, 11, 60);
    t_edge edge10(5, 8, 41);
    t_edge edge11(5, 9, 18);
    t_edge edge12(6, 2, 10);
    t_edge edge13(6, 8, 55);
    t_edge edge14(7, 4, 22);
    t_edge edge15(7, 6, 44);
    t_edge edge16(7, 11, 28);
    t_edge edge17(9, 7, 44);
    t_edge edge18(10, 4, 35);
    t_edge edge19(10, 5, 74);
    t_edge edge20(10, 11, 62);
    t_edge edge21(11, 2, 73);
    t_edge edge22(11, 4, -5);
    g.addEdge(edge1);
    g.addEdge(edge2);
    g.addEdge(edge3);
    g.addEdge(edge4);
    g.addEdge(edge5);
    g.addEdge(edge6);
    g.addEdge(edge7);
    g.addEdge(edge8);
    g.addEdge(edge9);
    g.addEdge(edge10);
    g.addEdge(edge11);
    g.addEdge(edge12);
    g.addEdge(edge13);
    g.addEdge(edge14);
    g.addEdge(edge15);
    g.addEdge(edge16);
    g.addEdge(edge17);
    g.addEdge(edge18);
    g.addEdge(edge19);
    g.addEdge(edge20);
    g.addEdge(edge21);
    g.addEdge(edge22);
    
    if (BF(g, 8)) {
        cout << g << endl;
    } else {
        cout << "negative cycles!" << endl;
    }
    
    
    return 0;
}
#endif

