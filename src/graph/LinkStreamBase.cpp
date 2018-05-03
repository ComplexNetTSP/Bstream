///-------------------------------------------------------------------------------------------------
///
/// @file       LinkStreamBase.cpp
/// @brief      LinkStreamBase Implementation
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       08/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include <limits>
#include <boost/icl/interval_set.hpp>

#include "LinkStreamBase.hpp"
#include "CSVReader.hpp"

using namespace std;

namespace boost::bstream
{
    ///**************************************************************************************************
    ///
    ///  Constructor
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    LinkStreamBase<DirectedS>::LinkStreamBase():
            LinkStreamBase(default_min_interval, default_max_interval)
    {}

    template<typename DirectedS>
    LinkStreamBase<DirectedS>::LinkStreamBase(int num_vertex)
            : LinkStreamBase(num_vertex, default_min_interval, default_max_interval)
    {}

    template<typename DirectedS>
    LinkStreamBase<DirectedS>::LinkStreamBase(time_t b, time_t e)
    {
        interval_def = make_time_interval(b, e);
    }

    template<typename DirectedS>
    LinkStreamBase<DirectedS>::LinkStreamBase(int num_vertex, time_t b, time_t e): LinkStreamBase(b, e)
    {
        for (auto i = 0; i < num_vertex; ++i)
            this->add_vertex();
    }

    ///**************************************************************************************************
    ///
    ///  Graph methods
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    time_t LinkStreamBase<DirectedS>::definition_length()
    {
        return interval_def.upper() - interval_def.lower();
    }

    template<typename DirectedS>
    std::pair<time_t, time_t> LinkStreamBase<DirectedS>::definition() const
    {
        return std::make_pair<time_t, time_t>(interval_def.lower(), interval_def.upper());
    }

    template<typename DirectedS>
    void LinkStreamBase<DirectedS>::set_definition(const time_t t1, time_t t2)
    {
        interval_def = make_time_interval(t1, t2);
    }

    template<typename DirectedS>
    void LinkStreamBase<DirectedS>::print_edges()
    {
        cout << *this << endl;
        auto e_iterator = this->edges();
        for (auto it = e_iterator.first; it != e_iterator.second; ++it) {
            auto s = boost::source(*it, this->G);
            auto t = boost::target(*it, this->G);
            auto s_name = this->label(s);
            auto t_name = this->label(t);
            cout << "\t" << TimeIntervalSetVertexMap[*it] << " x "
                 << "(" << s << "," << t << ")";
            if (!s_name.empty() && !t_name.empty())
                cout << " with name (" << s_name << "," << t_name << ")";
            cout << endl;
        }
    }

    template<typename DirectedS>
    double LinkStreamBase<DirectedS>::num_edges()
    {
        auto edge_it = this->edges();
        double sum = 0;
        for (auto it = edge_it.first; it != edge_it.second; ++it)
            sum += TimeIntervalSetVertexMap[*it].length();
        return sum / (interval_def.upper() - interval_def.lower());
    }

    template<typename DirectedS>
    double LinkStreamBase<DirectedS>::density()
    {
        double sumL = 0.0;
        for (auto it = this->edges().first; it != this->edges().second; ++it)
            sumL += TimeIntervalSetVertexMap[*it].length();
        auto temp = sumL /
                    (this->num_vertices() * (this->num_vertices() - 1) * (interval_def.upper() - interval_def.lower()));
        if (this->is_directed())
            return temp;
        else
            return 2 * temp;
    }

    template<typename DirectedS>
    void LinkStreamBase<DirectedS>::read_csv(std::string path, char delimiter)
    {
        auto cvs = CSVReader(delimiter);
        auto graph = cvs.read(path);
        int min_interval = std::numeric_limits<int>::max();
        int max_interval = 0;
        for (auto edge_it = graph.begin(); edge_it != graph.end(); ++edge_it) {
            if (min_interval > std::stoi((*edge_it)[2]))
                min_interval = std::stoi((*edge_it)[2]);
            if (max_interval < std::stoi((*edge_it)[3]))
                max_interval = std::stoi((*edge_it)[3]);
        }

        this->set_definition(min_interval, max_interval);

        for (auto edge_it = graph.begin(); edge_it != graph.end(); ++edge_it) {
            min_interval = std::stoi((*edge_it)[2]);
            max_interval = std::stoi((*edge_it)[3]);
            this->add_edge_w_time((*edge_it)[0], (*edge_it)[1], min_interval, max_interval);
        }
    }


    ///**************************************************************************************************
    ///
    ///  Edge method
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    typename LinkStreamBase<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge(const typename LinkStreamBase<DirectedS>::vertex_t &s,
                                        const typename LinkStreamBase<DirectedS>::vertex_t &t)
    {
        if (!this->has_vertex(s) or !this->has_vertex(t)) {
            std::string msg = "the vertex " + std::to_string(s) + " or " + std::to_string(s) + " doesn't exist";
            throw LinkStreamBaseException(msg);
        }

        typename GraphBase<DirectedS>::edge_t e_exist;
        bool ok;
        std::tie(e_exist, ok) = boost::edge(s, t, this->G);
        if (ok) {
            return e_exist;
        } else {
            auto e = GraphBase<DirectedS>::add_edge(s, t);
            TimeIntervalSetVertexMap[e].append(interval_def.lower(), interval_def.upper());
            return e;
        }
    }

    template<typename DirectedS>
    typename LinkStreamBase<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge(const std::string &s, const std::string &t)
    {
        if (!this->has_vertex(s))
            this->add_vertex(s);
        if (!this->has_vertex(t))
            this->add_vertex(t);
        return this->add_edge(this->vertex(s), this->vertex(t));
    }

    template<typename DirectedS>
    typename LinkStreamBase<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge_w_time(const typename GraphBase<DirectedS>::vertex_t &s,
                                               const typename GraphBase<DirectedS>::vertex_t &t,
                                               time_t b, time_t e)
    {
        typename GraphBase<DirectedS>::edge_t edge_exist;
        bool ok;

        ///< check that the edge time interval is in the linkstream definition interval
        if (!icl::contains(interval_def, make_time_interval(b, e))) {
            std::ostringstream msg;
            msg << "Edge TimeInterval " << make_time_interval(b, e)
                << "is not contains inside " << interval_def << endl;
            throw LinkStreamBaseException(msg.str());
        }

        std::tie(edge_exist, ok) = boost::edge(s, t, this->G);
        if (ok) {
            TimeIntervalSetVertexMap[edge_exist].append(b, e);
            return edge_exist;
        } else {
            auto edge = GraphBase<DirectedS>::add_edge(s, t);
            TimeIntervalSetVertexMap[edge].append(b, e);
            return edge;
        }
    }

    template<typename DirectedS>
    typename LinkStreamBase<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge_w_time(const std::string &s, const std::string &t, time_t b, time_t e)
    {
        ///< add vertex if it didn't exist
        if (!this->has_vertex(s))
            this->add_vertex(s);
        if (!this->has_vertex(t))
            this->add_vertex(t);
        ///< add edge
        return this->add_edge_w_time(this->vertex(s), this->vertex(t), b, e);
    }


    template<typename DirectedS>
    typename LinkStreamBase<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge_w_time(const std::string &s, const std::string &t, TimeIntervalSet &tis)
    {
        ///< add vertices if needed
        if (!this->has_vertex(s))
            this->add_vertex(s);
        if (!this->has_vertex(t))
            this->add_vertex(t);

        ///< add edge
        auto e = boost::edge(this->vertex(s), this->vertex(t), this->G);
        if (!e.second) {
            auto new_edge = GraphBase<DirectedS>::add_edge(s, t);
            TimeIntervalSetVertexMap[new_edge] = tis;
            return new_edge;
        } else {
            for (auto tis_it = tis.begin(); tis_it != tis.end(); ++tis_it) {
                TimeIntervalSetVertexMap[e.first].append(tis_it->lower(), tis_it->upper());
            }
            return e.first;
        }
    }

    template<typename DirectedS>
    typename LinkStreamBase<DirectedS>::edge_t
    LinkStreamBase<DirectedS>::add_edge_w_time(const typename LinkStreamBase<DirectedS>::vertex_t &s,
                                               const typename LinkStreamBase<DirectedS>::vertex_t &t,
                                               TimeIntervalSet &tis)
    {
        ///< add vertices if needed
        if (!this->has_vertex(s))
            throw LinkStreamBaseException("Missing vertex");
        if (!this->has_vertex(t))
            throw LinkStreamBaseException("Missing vertex");

        ///< add edge
        auto e = boost::edge(s, t, this->G);
        if (!e.second) {
            auto new_edge = GraphBase<DirectedS>::add_edge(s, t);
            TimeIntervalSetVertexMap[new_edge] = tis;
            return new_edge;
        } else {
            for (auto tis_it = tis.begin(); tis_it != tis.end(); ++tis_it) {
                TimeIntervalSetVertexMap[e.first].append(tis_it->lower(), tis_it->upper());
            }
            return e.first;
        }

    }

    template<typename DirectedS>
    TimeIntervalSet
    LinkStreamBase<DirectedS>::edges_tinterval_set(const std::string &s, const std::string &t)
    {
        auto e = this->edge(s, t);
        if (e.second)
            return TimeIntervalSetVertexMap[e.first];
        else
            throw LinkStreamBaseException("edge doesn't exist");
    }

    template<typename DirectedS>
    TimeIntervalSet
    LinkStreamBase<DirectedS>::edges_tinterval_set(const typename LinkStreamBase<DirectedS>::vertex_t &s,
                                                   const typename LinkStreamBase<DirectedS>::vertex_t &t)
    {
        auto e = this->edge(s, t);
        if (e.second)
            return TimeIntervalSetVertexMap[e.first];
        else
            throw LinkStreamBaseException("edge doesn't exist");
    }

    template<typename DirectedS>
    TimeIntervalSet
    LinkStreamBase<DirectedS>::edges_tinterval_set(const typename LinkStreamBase<DirectedS>::edge_t &e)
    {
        return TimeIntervalSetVertexMap[e];
    }

    template<typename DirectedS>
    pair<typename GraphBase<DirectedS>::edge_t, bool>
    LinkStreamBase<DirectedS>::is_edge_active(
            const typename GraphBase<DirectedS>::vertex_t &s,
            const typename GraphBase<DirectedS>::vertex_t &t,
            time_t b, time_t e)
    {
        auto res = boost::edge(s, t, this->G);
        if (res.second) {
            auto edge_tis = TimeIntervalSetVertexMap[res.first];
            if (edge_tis.contains(b, e)) {
                return res;
            } else {
                res.second = false;
                return res;
            }
        } else {
            return res;
        }
    }

    ///**************************************************************************************************
    ///
    ///  Vertex method
    ///
    ///**************************************************************************************************

    template<typename DirectedS>
    double LinkStreamBase<DirectedS>::degree(const typename GraphBase<DirectedS>::vertex_t &v)
    {
        double sum = 0;
        auto n_it = this->neighbors(v);
        for (auto it = n_it.first; it != n_it.second; ++it) {
            auto e = boost::edge(v, *it, this->G);
            sum += TimeIntervalSetVertexMap[e.first].length();
        }
        return sum / (interval_def.upper() - interval_def.lower());
    }

    template<typename DirectedS>
    void LinkStreamBase<DirectedS>::remove_vertex(const std::string &v)
    {
        for (auto it = this->neighbors(v).first; it != this->neighbors(v).second; ++it) {
            auto edge = this->edge(this->vertex(v), *it);
            if (edge.second) {
                TimeIntervalSetVertexMap.erase(edge.first);
            }
        }
        GraphBase<DirectedS>::remove_vertex(v);
    }

    template
    class LinkStreamBase<boost::undirectedS>;

    template
    class LinkStreamBase<boost::bidirectionalS>;

}
