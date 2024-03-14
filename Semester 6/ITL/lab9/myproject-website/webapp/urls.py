from django.urls import re_path
from webapp.views import index,add_category,add_page

from . import views

urlpatterns = [
    re_path(r'^$', views.index, name='index'),
    re_path(r'^add_category/$', views.add_category, name='add_category'),
    re_path(r'^add_page/$', views.add_page, name='add_page'),
]