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

bool noNegativeCycles(CGraph& g) {
    for (int i = 1; i <= g.getEdgeCounter(); ++i) {
        t_edge edge = g.getEdge(i);
        int sourceDist = g.getNode(edge.sourceIndex).distance;
        t_node destNode = g.getNode(edge.destinationIndex);
        int destDist = destNode.distance;
        int newDestDist = sourceDist + edge.value;
        if (newDestDist < destDist) return false;
    }
    return true;
}

bool BF(CGraph& g, const int startIndex) {
    initPaths(g, startIndex);
    relaxAllEdgesRepetetively(g);
    return noNegativeCycles(g);
}

#ifndef __PROGTEST__
int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
#endif

