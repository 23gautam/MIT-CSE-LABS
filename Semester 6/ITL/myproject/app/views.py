from django.shortcuts import render,get_object_or_404
from .models import Product
# Create your views here.
def home(request):
    return render(request,'home.html')

def add(request):
      return render(request,'add.html')

def fill(request):
        id=int(request.POST['id'])
        name=request.POST['name']
        price=int(request.POST['price'])
        p=Product(id=id,name=name,price=price)
        p.save()
        submitted=True
        return render(request,'add.html',{'submitted':submitted})



def display(request):
      products=Product.objects.all()

      return render(request,'display.html',{'products':products})


def product_detail(request,pk):
      prod=get_object_or_404(Product,pk=pk)
      return render(request,'product_detail.html',{'product':prod})