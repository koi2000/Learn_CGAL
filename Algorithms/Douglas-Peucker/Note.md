# Douglas-Peucker
## Method-1
1. 将曲线的第一个点（作为anchor）和最后一个点（作为floater）连成一条直线，计算中间所有点到该直线的最大距离Dmax。
2. 如果Dmax<D(预先设置的阈值)，则只保留第一个和最后一个点，中间所有点全部删除，该曲线处理结束；
   如果Dmax>=D,则将用Dmax对应的点做新的floater。
3. 重复第一步和第二步，floater慢慢移向anchor点，直到最大距离Dmax满足条件。这时将floater点作为新的anchor，又将原始曲线的最后一个点作为floater，重复第一步、第二步和第三步。
4. 最后将作过anchor的点组成简化后的曲线。


## Method-2
将曲线的第一个点（作为anchor）和最后一个点（作为floater）连成一条直线，计算所有中间点到该直线的最大距离Dmax。

如果Dmax<D(预先设置的阈值)，则该段只保留第一个和最后一个点，该段处理结束；
反之，用Dmax对应的中间点将曲线分为两段，对这两段重复第一步和第二步。

直到递归结束后，将保留的点依次连接，组成简化后的曲线。
![算法示意图](20200203143642333.gif)