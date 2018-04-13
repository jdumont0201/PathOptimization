//
// Created by jbmdu
//

#include <iostream>
#include <queue>
#include <deque>
#include "Djikstra.h"
#include "../Graph/Graph.h"
#include "../Graph/Node.h"
#include <algorithm>



void Djikstra::solve(Problem &P) {
    std::cout << "Solving using Djikstra " << std::endl;

    //SETUP
    double INFINITY = 1000000.;
     Graph &g = P.cgetGraph();
    const pNode initial = P.cgetInitial();
    const pNode goal = P.cgetGoal();
    bool isReached = false;
    pNode x;
    std::priority_queue<std::pair<double,pNode>,std::vector<std::pair<double,pNode>>,std::greater<std::pair<double,pNode>> > Q; //weight is first because first is default for compare
    Q.push(std::make_pair(0,initial));
    std::vector<bool> visited(g.getNbNodes());visited[0]=true;

    int xId,xxId;
    double dx;
    std::vector<pNode> path;
    std::vector<double> distance(g.getNbNodes());  for(int i=0;i< distance.size();++i) distance[i]=INFINITY; distance[initial->getId()]=0;
    std::vector<int> pred(g.getNbNodes());

    //RUN
    while (!Q.empty()) {
        auto p = Q.top();
        Q.pop();
        x=p.second;
        xId=x->getId();
        dx=distance[xId];
        if (xId == goal->getId()) {
            isReached = true;
            break;
        } else {
            for (auto xx:x->getAdjacents()) {
                xxId=xx->getId();
                double d=dx+g.getWeight(xId,xxId);
                if (!visited[xxId]) {
                    visited[xxId] = true;
                    distance[xxId]=d;
                    pred[xxId]=xId;
                    Q.push(make_pair(d,xx));
                } else {
                    if(distance[xxId]>d){
                        distance[xxId]=d;
                        pred[xxId]=xId;
                    }
                }
            }
        }
    }
    for(int i=0;i<distance.size();++i){
        std::cout << "Distance \t"<<i <<"=\t"<<distance[i]<< std::endl;
    }


}