// Digraph.hpp
//
// ICS 46 Spring 2020
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>

#include<queue>
#include<iostream>
#include<string>
#include <iterator>


// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    std::map <int, DigraphVertex<VertexInfo,EdgeInfo>> maininfo;
    bool checkstrongr(int current, std::vector<int> visited) const;
    int findshortest(const std::vector<int>& vertices, const std::map<int, double> &shortDistances) const; 

    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{

    this->maininfo = d.maininfo;

}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    std::swap(maininfo,d.maininfo);

}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
    maininfo.clear();
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    this->maininfo = d.maininfo;

    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{

    std::swap(maininfo,d.maininfo);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{

    std::vector<int> totalvertices;

    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator it=maininfo.begin();it!=maininfo.end();it++)
        totalvertices.push_back(it->first);
    // typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::iterator it = maininfo.begin();

    // for (; it != maininfo.end(); it++)
    // {
    //     totalvertices.push_back(it->first);
    // }

    return totalvertices;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int,int>> totaledges;

    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iteri=maininfo.begin();iteri!=maininfo.end();iteri++)
    {
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator iterj = iteri->second.edges.begin();iterj!=iteri->second.edges.end();iterj++)
        {
            std::pair<int,int> eachedge;
            eachedge.first = iterj->fromVertex;
            eachedge.second= iterj->toVertex;
            totaledges.push_back(eachedge);
        }
    }
    return totaledges;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    if (maininfo.find(vertex)==maininfo.end())
        throw DigraphException("Vertex not found.");

    std::vector<std::pair<int,int>> totaledges;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iteri=maininfo.begin();iteri!=maininfo.end();iteri++)
    {
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator iterj = iteri->second.edges.begin();iterj!=iteri->second.edges.end();iterj++)
        {
            if (iterj->fromVertex == vertex)
            {
                std::pair<int,int> eachedge;
                eachedge.first = iterj->fromVertex;
                eachedge.second= iterj->toVertex;
                totaledges.push_back(eachedge);
            }

        }
    }

    return totaledges;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{

    if (maininfo.find(vertex)==maininfo.end())
    {
        throw DigraphException("vertex not found");
    }
    
    return maininfo.at(vertex).vinfo;
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{

    EdgeInfo tempinfo;
    bool find = false;


    if(maininfo.count(fromVertex)==0 or maininfo.count(toVertex)==0)
        throw DigraphException("edge not found.");

    
    for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator iteri = maininfo.at(fromVertex).edges.begin(); iteri!=maininfo.at(fromVertex).edges.end();iteri++)
    {
  //      std::cout<<"finding edge"<<iteri->fromVertex<< iteri->toVertex << std::endl;

        if(iteri->toVertex==toVertex)
        {
            tempinfo = iteri->einfo;
            find=true;
        }
    }

    if (!find)
        throw DigraphException("edge not found.");

    return tempinfo;

}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if (maininfo.count(vertex)>0)
        throw DigraphException("Vertex has already been created.");


    


    DigraphVertex<VertexInfo,EdgeInfo> newvertexinfo= DigraphVertex<VertexInfo,EdgeInfo>{vinfo};
    
    std::pair<int,DigraphVertex<VertexInfo,EdgeInfo>> newvertex;

    newvertex.first=vertex;
    newvertex.second=newvertexinfo;

    maininfo.insert(newvertex);
 //   std::cout<<"add "<<"->"<<vertex<< std::endl;


}




template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if (maininfo.count(fromVertex)==0 or maininfo.count(toVertex)==0)
        throw DigraphException("one or two vertex(s) not found.");
    
    std::vector<std::pair<int,int>> checkdata = edges(fromVertex);


    if (std::find(checkdata.begin(), checkdata.end(), std::pair<int,int> {fromVertex, toVertex} ) != checkdata.end())
    throw DigraphException("this edge has already been created.");


    maininfo.at(fromVertex).edges.push_back(DigraphEdge<EdgeInfo>{fromVertex,toVertex,einfo});
 //   std::cout<<"add "<<fromVertex<<"->"<<toVertex<< std::endl;

}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    if (maininfo.count(vertex)==0)
        throw DigraphException("one vertex not found.");

    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::iterator iteri=maininfo.begin();iteri!=maininfo.end();iteri++)
    {
       for (typename std::list<DigraphEdge<EdgeInfo>>::iterator iterj=iteri->second.edges.begin(); iterj != iteri->second.edges.end(); iterj++)
       {
           if (iterj->toVertex == vertex)
           {
               iteri->second.edges.erase(iterj);
           }
       }
    }

    maininfo.erase(vertex);
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    bool find = false;

    if (maininfo.count(fromVertex)==0 or maininfo.count(toVertex)==0)
        throw DigraphException("one or two vertex(s) not found.");
    std::vector<std::pair<int,int>> checkdata = edges(fromVertex);

    if (std::find(checkdata.begin(), checkdata.end(), std::pair<int,int> {fromVertex, toVertex} )== checkdata.end()   )
        throw DigraphException("this edge is not found.");

    
 //   std::cout<<"for looping"<<std::endl;
    for (typename std::list<DigraphEdge<EdgeInfo>>::iterator iteri=maininfo.at(fromVertex).edges.begin();iteri != maininfo.at(fromVertex).edges.end(); iteri++)
    {

  //      std::cout<<iteri->fromVertex<<" -> "<< iteri->toVertex<<std::endl;
        if (iteri->toVertex == toVertex)
        {
            maininfo.at(fromVertex).edges.erase(iteri);
            find=true;
  //          std::cout<<"removed "<< fromVertex<<"->"<<toVertex<<std::endl;
        }
    }   

    if (!find)
        throw DigraphException("edge not found");


}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    
    return maininfo.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    unsigned int countedges=0;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iteri=maininfo.begin();iteri!=maininfo.end();iteri++)
        countedges += iteri->second.edges.size();
    return countedges;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    unsigned int countedges=0;
    for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator iteri= maininfo.at(vertex).edges.begin();iteri!=maininfo.at(vertex).edges.end();iteri++)
    {
        countedges++;

    }
    return countedges;
}





template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::checkstrongr(int current, std::vector<int> visited) const
{

    visited.push_back(current);
    std::queue<int> lines;
    lines.push(current);
    while (!lines.empty())
    {
        int current = lines.front();
        lines.pop();
       for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator iteri = maininfo.at(current).edges.begin();iteri!=maininfo.at(current).edges.end();iteri++)
       {
           if (std::find(visited.begin(),visited.end(),iteri->toVertex)==visited.end())
           {
               visited.push_back(iteri->toVertex);
               lines.push(iteri->toVertex);
           }
       }
    }


    if (visited.size() == maininfo.size())
    {
        return true;
    }
    
    return false;
        

}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    std::vector<bool> isallpass;
    std::vector<int> visited;
    for (typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iteri=maininfo.begin();iteri!=maininfo.end();iteri++)
    {
        isallpass.push_back(checkstrongr(iteri->first,visited));
       // std::cout<<checkstrongr(iteri->first,visited) <<"----";
    }
    if (std::find(isallpass.begin(),isallpass.end(),false) ==isallpass.end())
    {
        return true;
    }

    return false;

}



template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{

    struct comparing
    {
        bool operator()(std::pair<int, double> a, std::pair<int, double> b)
        {
            return a.second > b.second;
        }
    };


    std::priority_queue <std::pair<int,double>,std::vector<std::pair<int,double>>,comparing > queuei;
    std::map<int, int> bestpath;
    std::map<int,std::pair<double,bool>> ipath;

    //for each vertex v
    for (typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator iteri = maininfo.begin();iteri!=maininfo.end();iteri++)
    {
        ipath[iteri->first] = std::pair<double,bool> {90000000,false}; 


        if (iteri->first==startVertex)
            ipath[startVertex]=std::pair<double, bool>{0,false};
            bestpath[startVertex]=startVertex;

    } //ini all 
    
    queuei.push(std::pair<int,double>{startVertex,0});

    while(queuei.size()!=0)
    {
        // pop the shortest.
        std::pair<int,double> current = queuei.top();
        queuei.pop();
        int vertexi = current.first;


        if (!ipath[vertexi].second) //bool if is false
        {
            ipath[vertexi].second=true;




            //for each w such v-w
            for (typename std::list<DigraphEdge<EdgeInfo>>::const_iterator iteri = maininfo.at(vertexi).edges.begin(); iteri !=  maininfo.at(vertexi).edges.end() ; iteri++)
            {
                int dw= iteri->toVertex;
                double length = edgeWeightFunc(iteri->einfo);

                if (ipath[dw].first> ipath[vertexi].first +length)
                {
                    ipath[dw].first = ipath[vertexi].first + length;

                    bestpath[dw] = vertexi;

                    queuei.push(std::pair<int,double>{dw,ipath[dw].first});

                }
            }
        }
    }


    return bestpath;

}



#endif // DIGRAPH_HPP

