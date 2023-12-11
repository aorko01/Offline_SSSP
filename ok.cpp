if (dist[{source_node_no, dest_node_no}] <= c)
            {
                if (fuel_left >= dist[{source_node_no, dest_node_no}])
                {
                    int present_cost = fuel_left * price[source_node_no] + dp[source_node_no][0];
                    if (present_cost < dp[dest_node_no][fuel_left - dist[{source_node_no, dest_node_no}]])
                    {
                        dp[dest_node_no][fuel_left - dist[{source_node_no, dest_node_no}]] = present_cost + dp[source_node_no][fuel_left];
                        pq.push({dest_node_no, fuel_left - dist[{source_node_no, dest_node_no}]});
                    }
                    // dp[dest_node_no][fuel_left-dist[{source_node_no,dest_node_no}]]=min(dp[dest_node_no][fuel_left-dist[{source_node_no,dest_node_no}]],present_cost);
                    // // pq.push({dest_node_no,fuel_left-dist[{source_node_no,dest_node_no}]});
                }
            }