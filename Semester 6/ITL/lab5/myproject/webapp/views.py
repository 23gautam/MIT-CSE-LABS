from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse 
def index(request): 
    return HttpResponse("<H2>HEY! Welcome to Edureka! </H2>")