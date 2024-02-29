from django.shortcuts import render
from .forms import RegForm 
def home_view(request):
    context = {} 
    form = RegForm(request.POST or None)
    context['form'] = form 
    return render(request, "basic.html", context) 