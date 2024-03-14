from django.urls import re_path
from webapp.views import archive,create_blogpost 

from . import views

urlpatterns = [
    re_path(r'$',archive,name='archive'),
    re_path(r'^create/',create_blogpost,name='create_blogpost'), 
]