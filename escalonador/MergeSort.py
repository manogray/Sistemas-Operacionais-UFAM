def merge(llist, rlist):
    final = []
    while llist or rlist:
        if len(llist) and len(rlist):
            if llist[0].prio < rlist[0].prio:
                final.append(llist.pop(0))
            else:
                final.append(rlist.pop(0))

        if not len(llist):
            if len(rlist): final.append(rlist.pop(0))
        if not len(rlist):
            if len(llist): final.append(llist.pop(0))
  
    return final
   
def merge_sort(list):
    if len(list) < 2:
        return list
    mid = int(len(list) / 2)
    return merge(merge_sort(list[:int(mid)]), merge_sort(list[int(mid):]))