//
// Created by einav on 15/01/19.
//

#include "BestFirstSearch.h"
#include <queue>

using std::priority_queue;
using std::vector;

class Compare {
    public:
        bool operator() (State *firstState, State *secondState)
        {
            return firstState->weigth > secondState->weigth;
        }
    };

/**
 * search function-we use the same method like the search with BFS,
 * the change is only the internal order of the states in the queue,
 * it's a priority queue that allways keep on the order of the state in it
 * according to the weigth of the state.
 * @param searchable
 * @return the struct of the reasult from the search
 */
SearchResult BestFirstSearch::search(Searchable *searchable) {

        //initialize the search result before fill that struct
        SearchResult searchResult;
        searchResult.shortestWeight = 0;
        searchResult.shortestRoute = "";
        searchResult.developedVertices = 0;

        //goal state
        State *stateOfgoal = searchable->getGoalState();

        //our priority queue, compare between the states
        //in the queue with compare function
        priority_queue < State *, vector<State *>, Compare > priorityQueue;
        
        searchable->getStartState()->commingFrom = Start;

        //push the start state to the priority queue
        priorityQueue.push((searchable->getStartState()));

        State *currState;

        while (!priorityQueue.empty()) {
            currState = priorityQueue.top();
            priorityQueue.pop();

            //if that true, we reach the goal
            if (currState == stateOfgoal) { break;}

            //if we reach here, we are on search-
            //four directions of the current state in the searchable structer:

            //top != NULL
            if(currState->top != NULL){
                if(!currState->top->isInfinity){
                    if(currState->top->commingFrom == NotSet){

                        currState->top->commingFrom = Down;
                        priorityQueue.push(currState->top);
                    }
                }
            }

            //bottom != NULL
            if(currState->bottom != NULL){
                if(!currState->bottom->isInfinity){
                    if(currState->bottom->commingFrom == NotSet){

                        currState->bottom->commingFrom = Up;
                        priorityQueue.push(currState->bottom);
                    }
                }
            }

            //left != NULL
            if(currState->left != NULL){
                if(!currState->left->isInfinity){
                    if(currState->left->commingFrom == NotSet){

                        currState->left->commingFrom = Right;
                        priorityQueue.push(currState->left);
                    }
                }
            }

            //right != NULL
            if(currState->right != NULL){
                if(!currState->right->isInfinity){
                    if(currState->right->commingFrom == NotSet){

                        currState->right->commingFrom = Left;
                        priorityQueue.push(currState->right);
                    }
                }
            }

            searchResult.developedVertices++;
        }

        //if we reach here, no path exists
        if (currState != stateOfgoal){
            searchResult.shortestRoute = "";
            searchResult.shortestWeight = -1;
            return searchResult;
        }

        string currDirection;

        bool isStartState = false;

        //restore the data from our progress untill we reach the goal state
        while (!isStartState){
            searchResult.shortestWeight += currState->weigth;
            switch (currState->commingFrom)
            {
                case Up:
                    currState = currState->top;
                    currDirection = "Down, ";
                    break;
                case Down:
                    currState = currState->bottom;
                    currDirection = "Up, ";
                    break;
                case Left:
                    currState = currState->left;
                    currDirection = "Right, ";
                    break;
                case Right:
                    currState = currState->right;
                    currDirection = "Left, ";
                    break;
                case Start:
                    //we reach the start state
                    isStartState = true;
                    break;
                default:
                    throw "not valid progress";
            }
            if (!isStartState)
                searchResult.shortestRoute.insert(0, currDirection);
        }
        searchResult.shortestRoute =
                searchResult.shortestRoute.substr(0,
                                                  searchResult.shortestRoute.length() - 2);

        return searchResult;
    }
