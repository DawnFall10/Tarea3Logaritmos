import math
import sys
from time import process_time
# Stores a VEB-tree where the values may be between 0 and x (where x is the lowest power hierarchal squaring starting at 2 less than or equal to u)

class VEBtree:
    def __init__(self, u):
        if u < 0:
            raise Exception("Universe size cannot be less than zero. u = " + str(u))
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

    def getMin(self):
        """
        Returns cached min in the universe in O(1)
        """
        # if self.min is not None:
        #	return int(self.min)
        return self.min

    def getMax(self):
        """
        Returns cached max in the universe in O(1)
        """
        # if self.max is not None:
        #	return int(self.max)
        return self.max

    def high(self, x):
        """
        Returns the cluster number of element x
        """
        return int(math.floor(x / math.sqrt(self.u)))

    def low(self, x):
        """
        Return the position inside cluster of element x
        """
        return int(x % math.ceil(math.sqrt(self.u)))

    def index(self, x, y):
        """
        Returns index from cluster number and position within cluster
        """
        return int(x * math.floor(math.sqrt(self.u)) + y)

    def vEBTreeSearch(self, x):
        """
        Find if x is a member of the tree in O(lg lg u) time
        """
        if self.min == x or self.max == x:
            return True
        elif self.u <= 2:
            return False
        else:
            cluster_of_x = self.clusters[self.high(x)]
            if cluster_of_x is not None:
                return cluster_of_x.isMember(self.low(x))
            else:
                return False


    def emptyVEBTreeInsert(self, x):
        """
        First insert, updates min and max only
        """
        self.min = x
        self.max = x

    def vebTreeInsert(self, x):
        """
        Inserts an element x in the universe of size u
        """
        if self.min is None:
            self.emptyVEBTreeInsert(x)
        else:
            if x < self.min:
                temp = x
                x = self.min
                self.min = temp

            if self.u > 2:
                cluster_id_x = self.high(x)

                if self.clusters[cluster_id_x] is None:
                    # create a new cluster
                    self.clusters[cluster_id_x] = VEBtree(self.high(self.u))
                if self.summary is None:
                    self.summary = VEBtree(self.high(self.u))
                if self.clusters[cluster_id_x].min is None:
                    self.summary.vebTreeInsert(cluster_id_x)
                    self.clusters[cluster_id_x].emptyVEBTreeInsert(self.low(x))
                else:
                    self.clusters[cluster_id_x].vebTreeInsert(self.low(x))
            if x > self.max:
                self.max = x


num = int(sys.argv[1])
fileName = sys.argv[2]

veb = VEBtree(100000)
values = []
f = open(fileName, "r")
for x in f.readlines():
    aux = int(x.replace("\n", ""))
    values.append(aux)

for val in values:
    veb.vebTreeInsert(val)

tic1 = process_time()
result = veb.vEBTreeSearch(num)
tic2 = process_time()

clock = (tic2 - tic1)*1000
clock = '{0:.10f}'.format(clock)
print(result)
print("El tiempo en milisegundos fue de \t", clock)





