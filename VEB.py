class VEB:
    def high(self, x):
        return int(math.floor(x / math.sqrt(self.u)))

    def low(self, x):
        return int((x % math.ceil(math.sqrt(self.u))))

    def index(self, x, y):
        return int((x * math.floor(math.sqrt(self.u))) + y)
    
    def _init_(self,u): #u is the univrse size
        self.min = None
        self.max = None
        self.u = 2
        while self.u < u:
            self.u = self.u * self.u

        if u > 2:
            # define the cluster vectors
            # number of clusters 0, 1, 2, ..., upper sqrt(u) - 1
            self.clusters = [None for i in range(self.high(self.u))]
            # define the summary vectors
            self.summary = None
            
    def veb_max(self):
        return(self.max)
    
    def veb_min(self):
        return(self.min)

    def successor(self,x):
        if self.u <= 2:						 
            if x == 0 and self.max == 1:		
                return 1
            else:
                return None
        elif self.min != None and x < self.min: # x is less than everything in the tree, returns the minimum
            return self.min
        else:
            h = self.high(x)
            l = self.low(x)
            maxlow = None
            cluster = self.clusters[h]
            if cluster != None:
                maxlow = cluster.max
            if maxlow != None and l < maxlow:
                offset = cluster.successor(l)
                return self.index(h, offset)
            else:
                succcluster = None
                if self.summary != None:
                    succcluster = self.summary.successor(h)
                if succcluster == None:
                    return None
                else:
                    cluster2 = self.clusters[succcluster]
                    offset = 0
                    if cluster2 != None:
                            offset = cluster2.min
                    return self.index(succcluster, offset)
                
    def predeccessor(self,x):
        if self.u <= 2:
            if x == 1 and self.min == 0:
                return 0
            else:
                return None
        elif self.max != None and x > self.max:
            return self.max
        else:
            h = self.high(x)
            l = self.low(x)
            minlow = None
            cluster = self.clusters[h]
            if cluster != None:
                minlow = cluster.min
            if minlow != None and l > minlow:
                offset = cluster.predecessor(l)
                if offset == None: 
                    offset = 0
                return self.index(h, offset)
            else:
                predcluster = None
                if self.summary != None:
                    predcluster = self.summary.predecessor(h)
                if predcluster == None:
                    if self.min != None and x > self.min:
                            return self.min
                    else:
                            return None
                else:
                    cluster2 = self.clusters[predcluster]
                    offset = 0
                    if cluster2 != None:
                            offset = cluster2.max
                    return self.index(predcluster, offset)

    def emptyInsert(self,x):
        self.max=x
        self.min=x

    def insert(self, x):
        if self.min == None:
            self.emptyInsert(x)
        else:
            if x < self.min:
                temp = self.min
                self.min = x
                x = temp
            if self.u > 2:
                h = self.high(x)
                if self.clusters[h] == None:
                        self.clusters[h] = VEB(self.high(self.u))
                if self.summary == None:
                        self.summary = VEB(self.high(self.u))
                if self.clusters[h].min == None:
                        self.summary.insert(h)
                        self.clusters[h].emptyInsert(self.low(x))
                else:
                        self.clusters[h].insert(self.low(x))
            if x > self.max:
                self.max = x

    def remove(self,x):
        if self.min == self.max:
            self.min = None
            self.max = None
        elif self.u == 2:
            if x == 0:
                self.min = 1
            else:
                self.min = 0

            self.max = self.min
        else:
            if x == self.min:
                first_cluster = self.summary.getMin()
                x = self.index(first_cluster, self.clusters[first_cluster].getMin())
                self.min = x

            self.clusters[self.high(x)].vebTreeDelete(self.low(x))

            if self.clusters[self.high(x)].getMin() is None:
                self.summary.vebTreeDelete(self.high(x))

                if x == self.max:
                    summary_max = self.summary.getMax()
                    if summary_max is None:
                        self.max = self.min
                    else:
                        self.max = self.index(summary_max, self.clusters[summary_max].getMax())
            elif x == self.max:
                self.max = self.index(self.high(x), self.clusters[self.high(x)].getMax())

    def isPresent(self,u):
        if x == self.min or x == self.max:	# found it as the minimum or maximum
            return True
        elif self.u <= 2:					# has not found it in the "leaf"
            return False
        else:
            cluster = self.clusters[self.high(x)]
            if cluster != None:
                return cluster.member(self.low(x))	# looks for it in the clusters inside
            else:
                return False
    
            
        
        

        
        
