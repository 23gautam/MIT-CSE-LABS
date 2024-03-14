
from django.http import HttpResponse 
from datetime import datetime 
from django.http import HttpResponseRedirect 


from django.shortcuts import render, redirect
from webapp.models import Category, Page
from webapp.forms import CategoryForm, PageForm

def index(request):
    categories = Category.objects.all()
    return render(request, 'webapp/index.html', {'categories': categories})

def add_category(request):
    if request.method == 'POST':
        form = CategoryForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('index')
    else:
        form = CategoryForm()
    return render(request, 'webapp/add_category.html', {'form': form})

def add_page(request):
    if request.method == 'POST':
        form = PageForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('index')
    else:
        form = PageForm()
    return render(request, 'webapp/add_page.html', {'form': form})
