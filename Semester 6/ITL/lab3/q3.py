def binarySearch(arr,start,end,key):
    if end>start:
        mid= (start+end)//2

        if arr[mid]==key:
            return mid
        elif key < arr[mid]:
            return binarySearch(arr,start,mid-1,key)
        elif key> arr[mid]:
            return binarySearch(arr,mid+1,end,key)

    else:
        return -1


if __name__=='__main__':
        n = int(input("Enter number of elements : "))

        arr = list(map(int,input("Enter the numbers : ").strip().split()))[:n]
        
        key=int(input("Enter the key to find in the array: "))
        result=binarySearch(arr,0,len(arr)-1,key)

        if result != -1:
             print("Element present at index",result);

        else:
             print("Element not found")
 
