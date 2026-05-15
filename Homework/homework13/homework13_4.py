exit = None
class TaggedList:  #元素带标签的列表
    def __init__(self, elements, labels):
        self.labels = labels
        self.dic = dict(zip(labels, elements))
    def __len__(self):
        return len(self.dic)
    def __contains__(self, item):
        return item in self.dic.values()
    def __str__(self):
        return ''.join([f'{k}:{v},' for k, v in self.dic.items()])
    def __getitem__(self, index):
        if (index in self.labels):
            return self.dic[index]
        return self.dic[self.labels[index]]
    def __setitem__(self, index, val):
        if (index in self.labels):
            self.dic[index] = val
        else:
            self.dic[self.labels[index]] = val
a = TaggedList([70,80,90,100],["语文","数学","英语","物理"])
print(len(a),78 in a, 80 in a) #>>4 False True
print(str(a)) #>>语文:70,数学:80,英语:90,物理:100,
print(a[0],a['数学']) #>>70 80   标签也可以作为下标访问元素
a[1] = a['物理'] = 85
print(a) #>>语文:70,数学:85,英语:90,物理:85,