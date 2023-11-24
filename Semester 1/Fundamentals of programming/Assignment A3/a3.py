import time
import random

def bubble_sort(numbers_list):
    for i in range (len(numbers_list)):
        for j in range (len(numbers_list)-1-i):
            if numbers_list[j]>numbers_list[j+1]:
                aux_tool=numbers_list[j]
                numbers_list[j]=numbers_list[j+1]
                numbers_list[j+1]=aux_tool            


def shell_sort(numbers_list,n):
    gap=n//2
    while gap>0 :
        for i in range(gap,n):
            aux_tool=numbers_list[i]
            j=i
            while j>=gap and numbers_list[j-gap]>aux_tool:
                numbers_list[j]=numbers_list[j-gap]
                j-=gap
            numbers_list[j]=aux_tool
        gap=gap//2    
           
def create_list_for_bubble_sort(n):#for worst case
    numb_list=[]
    for i in range (n,0,-1):
        numb_list.append(i)
    return numb_list 

def create_list_for_shell_sort(n):#for worst case
    numb_list=[]
    for i in range(n):
        if i%2==0:
            numb_list.insert(i,random.randint(7812,12345))
        else:
            numb_list.insert(i,random.randint(0,600))    
    return numb_list                       

def generate_list(n):#average case
    numblist=[]
    for i in range (n):
        numblist.append(random.randint(0,n))
    return numblist    

def gen_for_best_case(n):#best case
    numblist=[]
    for i in range(n):
        numblist.append(i)
    return numblist    

def bubble_sort_best_case(n,numb_list):
    numb_list=gen_for_best_case(n)
    start_time=time.time()
    bubble_sort(numb_list)
    print(numb_list)
    print("The bubble sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the best case")

def bubble_sort_avg_case(n,numb_list):    
    numb_list=generate_list(n)
    start_time=time.time()
    bubble_sort(numb_list)
    print(numb_list)
    print("The bubble sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for average case")

def bubble_sort_worst_case(n,numb_list):
    numb_list=create_list_for_bubble_sort(n)
    start_time=time.time()
    bubble_sort(numb_list)
    print(numb_list)
    print("The bubble sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for worst case")

def shell_sort_best_case(n,num_list):
    num_list=gen_for_best_case(n)
    start_time=time.time()
    shell_sort(num_list,n)
    print(num_list)
    print("The shell sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the best case")

def shell_sort_avg_case(n,num_list):
    num_list=generate_list(n)
    start_time=time.time()
    shell_sort(num_list,n)
    print(num_list)
    print("The shell sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the average case")

def shell_sort_worst_case(n,num_list):
    num_list=create_list_for_shell_sort(n)
    start_time=time.time()
    shell_sort(num_list,n)
    print(num_list)
    print("The shell sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the worst case")   

def main():
    
   key=input("Select which case you'd like to see: best,average or worst\n")
   if key=="best":
      n=500
      while n<=8000:
         num_list=gen_for_best_case(n)
         start_time=time.time()
         bubble_sort(num_list)
         print("The bubble sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the best case")
         n*=2
      print('\n\n')   
      n=500
      while n<=8000:
        num_list=gen_for_best_case(n)
        start_time=time.time()
        shell_sort(num_list,n)
        print("The shell sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the best case")
        n*=2 
   elif key=="average":
        n=500
        while n<=8000:
            num_list=generate_list(n)      
            start_time=time.time()
            bubble_sort(num_list)
            print("The bubble sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the average case")
            n*=2
        print('\n\n')    
        n=500
        while n<=8000:
            num_list=generate_list(n)
            start_time=time.time()
            shell_sort(num_list,n)
            print("The shell sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the average case")
            n*=2 
   elif key=="worst":
        n=500
        while n<=8000:
            num_list=create_list_for_bubble_sort(n)      
            start_time=time.time()
            bubble_sort(num_list)
            print("The bubble sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the worst case")
            n*=2
        print('\n\n')    
        n=500
        while n<=8000:
            num_list=create_list_for_shell_sort(n)
            start_time=time.time()
            shell_sort(num_list,n)
            print("The shell sort method sorts a list of size",n,"in",time.time()-start_time,"seconds for the worst case")
            n*=2           
   else:
    print("Typing error or non implemented sorting algorithm")

#main()

def main_fct():
    n=int(input("Select the size ot the list"))
    key=input("select the sorting method:")
    token=input("select which case to see worst average or best:")
    if key=="bubble" and token=="best":
        numb_list=[]
        bubble_sort_best_case(n,numb_list)
    elif key=="bubble" and token=="average":
        numb_list=[]
        bubble_sort_avg_case(n,numb_list)
    elif key=="bubble" and token=="worst":
        numb_list=[]
        bubble_sort_worst_case(n,numb_list)

    elif key=="shell" and token=="best":
        numb_list=[]
        shell_sort_best_case(n,numb_list)
    elif key=="shell" and token=="average":
        numb_list=[]
        shell_sort_avg_case(n,numb_list)
    elif key=="shell" and token=="worst":
        numb_list=[]
        shell_sort_worst_case(n,numb_list)               

main_fct()

"""
the best case for both shell and bubble sort is that one
where the elements are already sorted in ascending order

for bubble sort : T(n) is included in O(n) because 
if the numbers are already sorted in ascending order, 
the algorithm will determine in the first iteration that no number pairs need to be swapped
and will then terminate immediately.

for shell sort: T(n) is included in O(nlogn) because
the inner while is not executed and the only nested
loops remain the one with the gap which is included in O(logn)
and the for which is included in O(n)
so the time complexity will be include in O(n*logn)


the worst case for shell sort is when between any even positioned elements 
the odd positioned one between them is smaller than both of these elements
because the can be swapped just in the last iteration of the gap loop
T(n) is included in O(n^2)

the worst case for bubble sort is when the list is sorted in a decreasing
order because 
total number of swaps=total number of comparisons=n*(n-1)/2
so the time complexity is include in O(n^2)

average time complexity for shell sort :O(nlogn)
average time complexity for bubble sort : O(n^2)

"""