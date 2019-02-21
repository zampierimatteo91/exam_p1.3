#!/usr/bin/env python3

import datetime

class PostcardList():

    def __init__(self):
        self._file = "default.txt"
        self._postcards = []
        self._date = {}
        self._from = {}
        self._to = {}
        self._counter = 0

    def parsePostcards(self):
        for i in range(len(self._postcards)):
            a = datetime.datetime.strptime(self._postcards[i].split(":")[1].split(";")[0],"%Y-%m-%d")
            b = self._postcards[i].split(";")[1].split(":")[1]
            c = self._postcards[i].split(":")[-1].split(";")[0]

            if a in self._date:
                self._date[a].append(i)
            else:
                self._date[a] = [i]
                
            if b in self._from:
                self._from[b].append(i)
            else:
                self._from[b] = [i]

            if c in self._to:
                self._to[c].append(i)
            else:
                self._to[c] = [i]

    def readFile(self,file):
        self._file = file
        self._postcards = [line.rstrip("\n") for line in open(self._file,"r")]
        self.parsePostcards()

    def updateLists(self,file):
        self._file = file
        tmp= [line.rstrip("\n") for line in open(self._file,"r")]
        self._postcards += tmp
        self.parsePostcards()

    def writeFile(self,file):
        f = open(file,"w")
        self._counter = 0
        for it in self._postcards:
            f.write(it+"\n")
            self._counter += 1
        f.close()

    def updateFile(self,file):
        f = open(file,"a")
        for n in range(self._counter,len(self._postcards)):
            f.write(self._postcards[n]+"\n")
        f.close()

    def getNumberOfPostcards(self):
        return len(self._postcards)

    def getPostcardsBySender(self, sender):
        ret = []
        if sender in self._from:
            for var in self._from[sender]:
                ret.append(self._postcards[var]+"\n")
        return ret

    def getPostcardsByReceiver(self, receiver):
        ret = []
        if receiver in self._to:
            for var in self._to[receiver]:
                ret.append(self._postcards[var]+"\n")
        return ret

    def getPostcardsByDateRange(self, date_range):
        begin = date_range[0]
        end = date_range[1]
        ret = []
        for d in self._date.keys():
            if d>=begin and d<=end:
                for var in self._date[d]:
                    ret.append(self._postcards[var]+"\n")
        return ret
    
p = PostcardList()
print(p._file)
p.readFile("./postcards/exam_postcard_list2.txt")

print(p.getNumberOfPostcards())

p.writeFile("file.txt")
assert p._counter==p.getNumberOfPostcards()

for x in p.getPostcardsByReceiver("Goofy"):
    print(x)
    
date_range=(datetime.datetime.strptime('2000-1-1', "%Y-%m-%d"),datetime.datetime.strptime('2002-12-31', "%Y-%m-%d"))
print(p.getPostcardsByDateRange(date_range))

date_range=(datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))
for x in p.getPostcardsByDateRange(date_range):
    print(x)

p.updateLists("./postcards/exam_postcard_list1.txt")
print(p.getNumberOfPostcards())

p.updateFile("file.txt")

import unittest
class Test(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self._files = ['./postcards/exam_postcard_list{}.txt'.format(i) \
                           for i in range(10)]
        self._PstLst = [PostcardList() for f in self._files]
        [p.readFile(f) for f,p in zip(self._files,self._PstLst)]

    def test_missing_attributes(self): 
        attributes_to_define = ['_file','_postcards','_date','_from','_to',\
                                'writeFile','readFile','parsePostcards',\
                                'updateFile','updateLists',\
                                'getNumberOfPostcards',\
                                'getPostcardsByDateRange',\
                                'getPostcardsBySender',\
                                'getPostcardsByReceiver']
        for attr in attributes_to_define:
            if attr not in dir(self._PstLst[0]): 
                raise Exception(attr+' is missing')

    def test_check_getPostcardByDateRange(self): 
        dr_test = []
        for i in [0,1,4,6]: 
            dr_test.append(\
                self._PstLst[i].getPostcardsByDateRange(date_range=\
                   (datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),\
                    datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))))
        self.assertListEqual(sorted(dr_test[0]),sorted(['date:2010-06-23; from:Sneezy; to:Alice;\n', 'date:2009-12-12; from:Dopey; to:Peter;\n', 'date:2008-03-23; from:Sneezy; to:Pluto;\n', 'date:2008-06-03; from:Goofy; to:Pluto;\n'])) 
        self.assertEqual(len(dr_test[1]),1)
        self.assertListEqual(sorted(dr_test[2]),sorted(['date:2010-03-30; from:Louie; to:Sneezy;\n', 'date:2010-03-05; from:Goofy; to:Dopey;\n', 'date:2009-11-08; from:Daisy; to:Minnie;\n', 'date:2010-07-13; from:Bashful; to:Louie;\n', 'date:2008-06-29; from:Huey; to:Dopey;\n', 'date:2009-01-04; from:Alice; to:Hook;\n', 'date:2009-04-28; from:Bashful; to:Mickey;\n']))
        self.assertEqual(len(dr_test[3]),7)

    def test_check_getPostcardBySender(self): 
        s_test = []
        for i in [2,3,5,7]:
            for sender in ['Daisy','Bashful','Peter']:
                s_test.append(\
                    self._PstLst[i].getPostcardsBySender(sender=sender))
        self.assertIn('date:2011-12-11; from:Daisy; to:Goofy;\n',s_test[0])
        self.assertListEqual(s_test[1],[])
        self.assertEqual(len(s_test[2]),1)
        self.assertEqual(len(s_test[5]),0)
        self.assertGreater(len(s_test[8]),len(s_test[9]))

    def test_check_getPostcardByReceiver(self): 
        r_test = []
        for i in [0,3,8,9]:
            for receiver in ['Peter','Hook','Alice','SnowWhite']:
                r_test.append(\
                  self._PstLst[i].getPostcardsByReceiver(receiver=receiver))
        self.assertIn('date:2009-12-12; from:Dopey; to:Peter;\n',r_test[0])
        self.assertListEqual(r_test[1],['date:2016-10-23; from:Sneezy; to:Hook;\n'])
        self.assertEqual(len(r_test[2]),2)
        self.assertEqual(len(r_test[6]),3)

    def test_check_sent_received_when(self): 
        srw_test = []
        for ii in range(10):
            for jj in ["Mickey","Minnie","Goofy","Pluto","Donald","Daisy","$crooge","Huey","Dewey","Louie","Peter","Hook","Alice","SnowWhite","Doc","Sleepy","Sneezy","Bashful","Dopey","Happy","Grumpy"]:
                try:
                    srw_test.append(self._PstLst[ii]._from[jj])
                    srw_test.append(self._PstLst[ii]._to[jj])
                    srw_test.append(self._PstLst[ii]._date[jj])
                except: pass
        self.assertListEqual(srw_test[0],[1])
        self.assertListEqual(srw_test[130],[14,25])
        self.assertListEqual(srw_test[138],[10])
        self.assertListEqual(srw_test[140],[15])
        self.assertListEqual(srw_test[192],[13,26])
        self.assertListEqual(srw_test[203],[6, 9, 11, 12, 24, 31, 42])

if __name__ == '__main__':

    unittest.main()

