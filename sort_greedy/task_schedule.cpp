//
// Created by luoxiYun on 2021/9/3.
//
/*
 * 牛客：任务调度问题
 * 使用带下标的优先队列求解
 */
#include "indexed_priority_queue.h"

class taskScheduler {

    struct tasks {
        int task_id;
        int pd_id;
        int create_time;
        int priority;
        int cost;

        tasks( int id, int pd_id, int create, int pri, int cost ){
            this->task_id = id;
            this->pd_id = pd_id;
            this->create_time = create;
            this->priority = pri;
            this->cost = cost;
        }
        bool operator<(const tasks &rht) const {
            if (this->priority != rht.priority)
                return this->priority < rht.priority;
            else if (this->cost != rht.cost)
                return this->cost > rht.cost;
            else
                return this->create_time < rht.create_time;
        }
    };

    struct select_standard{

        int id;
        int cost;
        int pd_id;

        select_standard( int id, int cost, int pd_id ){
            this->id = id;
            this->cost = cost;
            this->pd_id = pd_id;
        }
        bool operator<( const select_standard &rht ) const {
            if( this->cost != rht.cost )
                return this->cost > rht.cost;
            else
                return this->pd_id > rht.pd_id;
        }
    };

private:
    vector<tasks> candidates;
    vector<priority_queue<tasks>> pd_tasks;
    indexed_priority_queue<int, select_standard> ipq;
public:
    taskScheduler( int pd_num ){
        pd_tasks = vector<priority_queue<tasks>>( pd_num );
    }
    void add_task( int id, int pd_id, int create, int priority, int cost ){
        candidates.emplace_back( id, pd_id, create, priority, cost );
    }
    void add_task_to_pq( const tasks &t ){
        pd_tasks[t.pd_id].push( t );
        select_standard rule = select_standard( t.task_id, t.cost, t.pd_id );
        if( ipq.get_value_index(t.pd_id) != -1 )
            ipq.changeKey(t.pd_id, rule);
        else
            ipq.push( t.pd_id, rule );
    }

    vector<int> schedule_task( int m ){
        int n = candidates.size();
        vector<int> results(n);
        auto taskStartCmp = [](const tasks &lf, const tasks &rh ){
            return lf.create_time > rh.create_time;
        };
        priority_queue<tasks, vector<tasks>, decltype(taskStartCmp)> task_start_pq(taskStartCmp);
        for( tasks &t : candidates){
            task_start_pq.push(t);
        }
        priority_queue<int,vector<int>, greater<> > consumer_ready_pq; //队列中存放消费者的就绪时的时间点
        for( int i = 0; i < m; i++ )
            consumer_ready_pq.push(1);
        int finished = 0;
        while ( finished != n ){
            int consumer_ready_time = consumer_ready_pq.top();
            consumer_ready_pq.pop();
            while( !task_start_pq.empty() ){
                if( task_start_pq.top().create_time > consumer_ready_time )
                    break;
                add_task_to_pq(task_start_pq.top());
                task_start_pq.pop();
            }
            if( ipq.empty() ){
                consumer_ready_pq.push(task_start_pq.top().create_time);
            }else{
                int index = ipq.top().first;
                select_standard rule = ipq.top().second;
                pd_tasks[index].pop();
                if( pd_tasks[index].empty() )
                    ipq.pop();
                else {
                    select_standard next_rule = select_standard( pd_tasks[index].top().task_id, pd_tasks[index].top().cost, index );
                    ipq.changeKey( index, next_rule );
                }
                results[rule.id] = rule.cost + consumer_ready_time;
                consumer_ready_pq.push( results[rule.id] );
                finished++;
            }
        }
        return results;
    }
};

int main(){
    int n, m, p;
    cin>>n>>m>>p;
    taskScheduler task_scheduler(n);
    int pm_id, create_time, priority, cost;
    for( int i = 0; i < p; i++ ) {
        cin >> pm_id >> create_time >> priority >>cost;
        task_scheduler.add_task(i, pm_id-1, create_time, priority, cost );
    }
    auto res = task_scheduler.schedule_task(m);
    for( int time : res )
        cout<<time<<" ";
    cout<<endl;
    return 0;
}