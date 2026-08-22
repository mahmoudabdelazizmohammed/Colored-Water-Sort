#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State
{
    vector<vector<int>> tubes;
    int parent;
    int source;
    int destination;
};

int getTopColor(const vector<int>& tube)
{
    for (int i = (int)tube.size() - 1; i >= 0; i--)
    {
        if (tube[i] != 0)
            return tube[i];
    }
    return 0;
}

int getTopCount(const vector<int>& tube)
{
    int topIndex = -1;

    for (int i = (int)tube.size() - 1; i >= 0; i--)
    {
        if (tube[i] != 0)
        {
            topIndex = i;
            break;
        }
    }

    if (topIndex == -1)
        return 0;

    int color = tube[topIndex];
    int count = 0;

    for (int i = topIndex; i >= 0; i--)
    {
        if (tube[i] == color)
            count++;
        else
            break;
    }

    return count;
}

int getEmptyPosition(const vector<int>& tube)
{
    for (int i = 0; i < (int)tube.size(); i++)
    {
        if (tube[i] == 0)
            return i;
    }
    return -1;
}

bool isSolved(const vector<vector<int>>& tubes)
{
    for (int i = 0; i < (int)tubes.size(); i++)
    {
        if (tubes[i][0] == 0)
            continue;

        for (int j = 0; j < (int)tubes[i].size(); j++)
        {
            if (tubes[i][j] == 0)
                return false;
        }

        int color = tubes[i][0];

        for (int j = 1; j < (int)tubes[i].size(); j++)
        {
            if (tubes[i][j] != color)
                return false;
        }
    }

    return true;
}

bool canPour(const vector<int>& source,
             const vector<int>& destination)
{
    int sourceColor = getTopColor(source);

    if (sourceColor == 0)
        return false;

    int destinationColor = getTopColor(destination);

    if (getEmptyPosition(destination) == -1)
        return false;

    if (destinationColor != 0 && destinationColor != sourceColor)
        return false;

    int emptySpaces = 0;

    for (int i = 0; i < (int)destination.size(); i++)
    {
        if (destination[i] == 0)
            emptySpaces++;
    }

    if (emptySpaces < getTopCount(source))
        return false;

    return true;
}

void pour(vector<int>& source, vector<int>& destination)
{
    int topColor = getTopColor(source);
    int count = getTopCount(source);
    int destinationPosition = getEmptyPosition(destination);

    for (int i = 0; i < count; i++)
        destination[destinationPosition + i] = topColor;

    for (int i = (int)source.size() - 1; i >= 0 && count > 0; i--)
    {
        if (source[i] == topColor)
        {
            source[i] = 0;
            count--;
        }
    }
}

bool sameState(const vector<vector<int>>& first,
               const vector<vector<int>>& second)
{
    if (first.size() != second.size())
        return false;

    for (int i = 0; i < (int)first.size(); i++)
    {
        if (first[i].size() != second[i].size())
            return false;

        for (int j = 0; j < (int)first[i].size(); j++)
        {
            if (first[i][j] != second[i][j])
                return false;
        }
    }

    return true;
}

bool isVisited(const vector<vector<vector<int>>>& visited,
               const vector<vector<int>>& state)
{
    for (int i = 0; i < (int)visited.size(); i++)
    {
        if (sameState(visited[i], state))
            return true;
    }

    return false;
}

vector<pair<int, int>> solve(const vector<vector<int>>& tubes)
{
    vector<State> states;
    vector<vector<vector<int>>> visited;
    queue<int> q;

    State initial;
    initial.tubes = tubes;
    initial.parent = -1;
    initial.source = -1;
    initial.destination = -1;

    states.push_back(initial);
    visited.push_back(tubes);
    q.push(0);

    while (!q.empty())
    {
        int currentIndex = q.front();
        q.pop();

        State current = states[currentIndex];

        if (isSolved(current.tubes))
        {
            vector<pair<int, int>> moves;
            int index = currentIndex;

            while (states[index].parent != -1)
            {
                moves.push_back({
                    states[index].source,
                    states[index].destination
                });
                index = states[index].parent;
            }

            int left = 0;
            int right = (int)moves.size() - 1;

            while (left < right)
            {
                pair<int, int> temp = moves[left];
                moves[left] = moves[right];
                moves[right] = temp;
                left++;
                right--;
            }

            return moves;
        }

        int numberOfTubes = current.tubes.size();

        for (int source = 0; source < numberOfTubes; source++)
        {
            for (int destination = 0; destination < numberOfTubes; destination++)
            {
                if (source == destination)
                    continue;

                if (!canPour(current.tubes[source], current.tubes[destination]))
                    continue;

                State next;
                next.tubes = current.tubes;
                next.parent = currentIndex;
                next.source = source;
                next.destination = destination;

                pour(next.tubes[source], next.tubes[destination]);

                if (isVisited(visited, next.tubes))
                    continue;

                visited.push_back(next.tubes);
                states.push_back(next);
                q.push((int)states.size() - 1);
            }
        }
    }

    return {};
}

void printState(const vector<vector<int>>& tubes)
{
    for (int i = 0; i < (int)tubes.size(); i++)
    {
        cout << "Tube " << i + 1 << ": [";

        for (int j = 0; j < (int)tubes[i].size(); j++)
        {
            cout << tubes[i][j];

            if (j < (int)tubes[i].size() - 1)
                cout << ",";
        }

        cout << "]" << endl;
    }
}

int main()
{
    int N, C;
    cin >> N;
    cin >> C;

    vector<vector<int>> tubes(N, vector<int>(C));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < C; j++)
            cin >> tubes[i][j];
    }

    vector<pair<int, int>> moves = solve(tubes);

    if (moves.empty())
    {
        if (isSolved(tubes))
        {
            cout << "Solution found." << endl;
            cout << "Minimum moves: 0" << endl;
            cout << "Final state:" << endl;
            printState(tubes);
        }
        else
        {
            cout << "No solution exists." << endl;
        }
    }
    else
    {
        cout << "Solution found." << endl;
        cout << "Minimum moves: " << moves.size() << endl;

        for (int i = 0; i < (int)moves.size(); i++)
        {
            cout << i + 1 << ". Tube "
                 << moves[i].first + 1
                 << " -> Tube "
                 << moves[i].second + 1
                 << endl;
        }

        vector<vector<int>> finalState = tubes;

        for (int i = 0; i < (int)moves.size(); i++)
            pour(finalState[moves[i].first], finalState[moves[i].second]);

        cout << "Final state:" << endl;
        printState(finalState);
    }

    return 0;
}
