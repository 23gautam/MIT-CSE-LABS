from django.urls import re_path
from . import views

urlpatterns = [re_path(r'^$', views.home_view, name='home_view'),] 